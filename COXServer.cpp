#include "COXServer.h"
#include "TraderManager.h"
#include "utils.h"

#include <wchar.h>
#include <time.h>
#include <string.h>
#include <memory>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



#pragma comment(lib, "ws2_32.lib")

COXClient::COXClient(SOCKET connection, SOCKADDR_IN address) {
	fd_ = connection;
	addr_ = address;
	start_ = false;
	trader_ = NULL;
	log_file_.open("ts.log", std::ios::out | std::ios::app);
}

bool COXClient::start() {
	boost::thread recv_thread(boost::bind(&COXClient::receice_message, this));
	return true;
}

void COXClient::send_msg(const char *buffer, int len, COXTrader *trader) {
	if (start_ && trader == trader_) {
		log_file_ << time_now_ms() << " - Send :" << buffer << endl;
		send(fd_, buffer, len, 0);
	}
}

void COXClient::receice_message() {
	static const int BUF_SIZE = 4096;
	start_ = true;
	char message[BUF_SIZE];
	char *total_msg = NULL;
	int recv_len;
	int sec_cnt = 0;
	int total_len = 0;

	while (true) {
		recv_len = recv(fd_, message, BUF_SIZE, 0);
		if (recv_len <= 0) {
			log_file_ << time_now_ms() << "- Failed to receive data from client socket!" << recv_len << std::endl;
			break;
		}

		sec_cnt++;
		char *tmp_ptr = (char *)malloc((sec_cnt + 1)*BUF_SIZE * sizeof(char));
		if (sec_cnt > 1) {
			memcpy(tmp_ptr, total_msg, total_len);
			free(total_msg);
		}
		memcpy(tmp_ptr + total_len, message, recv_len);
		total_msg = tmp_ptr;
		total_len += recv_len;

		if (total_len > 1 && total_msg[total_len - 1] == '\0')
		{
			log_file_ << time_now_ms() << "- Data total received " << total_len << std::endl;
			char *start = total_msg;
			while (true) {
				char *p = strchr(start, '\0');
				if (p == NULL)
					break;
				if (p - total_msg < total_len - 1) {
					log_file_ << time_now_ms() << "- Multi datagram: " << (long)(p - start)
						<< " : " << start << std::endl;
					// TODO
					char tmp_msg[BUF_SIZE];
					size_t sec_len = (size_t)(p - start);
					strncpy(tmp_msg, start, sec_len);
					tmp_msg[sec_len] = '\0';
					decode(tmp_msg);
					log_file_ << time_now_ms() << "- Decode command : " << tmp_msg << std::endl;
					start = p + 1;
				}
				else {
					log_file_ << time_now_ms() << "- Last datagram: " << (long)(p - start)
						<< " : " << start << std::endl;
					// TODO
					char tmp_msg[BUF_SIZE];
					size_t sec_len = (size_t)(p - start);
					strncpy(tmp_msg, start, sec_len);
					tmp_msg[sec_len] = '\0';
					decode(tmp_msg);
					log_file_ << time_now_ms() << "- Decode command : " << tmp_msg << std::endl;
					break;
				}
			}

			sec_cnt = 0;
			free(total_msg);
			total_msg = NULL;
			total_len = 0;
		}

	}
	log_file_ << "Disconnecting..." << std::endl;
	cout << "Disconnecting..." << std::endl;
	closesocket(fd_);
	start_ = false;
	//trader_->Release();
}

void COXClient::decode(const char *message) {
	vector<string> pairs;
	split(string(message), ";", pairs);
	if (pairs.size() < 1) {
		return;
	}

	map<string, string> properties;
	vector<string> key_val;
	for (size_t i = 0; i < pairs.size(); i++) {
		key_val.clear();
		split(pairs[i], "=", key_val);
		if (key_val.size() != 2) {
			continue;
		}
		properties[key_val[0]] = key_val[1];
	}

	string msg_type = properties["COMMAND"];

	if (msg_type == "LOGIN") {
		ReqUserLogin(properties);
	} 
	else if (msg_type == "SENDORDER") {
		ReqOrderInsert(properties);
	}
	else if (msg_type == "CANCELORDER") {
		ReqOrderAction(properties);
	}
	else if (msg_type == "QUERYPOSITION") {
		ReqQryInvestorPosition(properties);
	}
	else if (msg_type == "QUERYACCOUNT") {
		ReqQryInvestorAccount(properties);
	}
	else if (msg_type == "MARGINSTOCK") {
		ReqQryInvestorMarginStock(properties);
	}
}

void COXClient::ReqUserLogin(map<string, string>& properties) {
	string account = properties["ACCOUNT"];

	char message[1024];
	trader_ = TraderManager::GetInstance()->GetTrader(account);
	snprintf(user_id_, sizeof(user_id_), "%s", account.c_str());
	if (trader_->Logined()) {
		snprintf(message, sizeof(message), "TYPE=LOGIN;ERROR=0;MESSAGE=");
		//cout << "Login success" << endl;
	}
	else {
		snprintf(message, sizeof(message), "TYPE=LOGIN;ERROR=2201;MESSAGE=Account[%s] not exist", account.c_str());
	}
	send_msg(message, strlen(message) + 1, trader_);
}

void COXClient::ReqOrderInsert(map<string, string>& properties) {
	trader_->OnReqOrderTicket(properties);

	return;
}

void COXClient::ReqOrderAction(map<string, string>& properties) {
	trader_->OnReqCancelTicket(properties);

	return;
}

void COXClient::ReqQryInvestorAccount(map<string, string>& properties) {
	trader_->OnReqQueryBalance(properties);
	return;
}

void COXClient::ReqQryInvestorPosition(map<string, string>& properties) {
	trader_->OnReqQueryPositions(properties);
	return;
}

void COXClient::ReqQryInvestorMarginStock(map<string, string>& properties) {
	trader_->OnReqCreditSecuLendQuota(properties);
	return;
}





COXServer::~COXServer() {};

COXServer& COXServer::Instance() {
	static COXServer server;
	return server;
}

// Easy Language Inter interfaces
bool COXServer::RegisterServer(int port) {
	socket_port_ = port;
	clients_ = new COXClient*[1000];
	memset(clients_, 0, sizeof(COXClient*) * 1000);
	client_size_ = 0;
	boost::thread server_thread(boost::bind(&COXServer::listen_thread, this));
	// server_thread.join();
	return true;
}


bool COXServer::Callback(const char* message, COXTrader *trader) {
	int con_size = client_size_;
	for (int i = 0; i < con_size; i++) {
		clients_[i]->send_msg(message, strlen(message) + 1, trader);
	}
	// int ret = send(client_con_, buffer, strlen(buffer) + 1, 0);
	return true;
}

COXServer::COXServer() {
	socket_port_ = 0;
}

void COXServer::listen_thread() {
	WORD version_request;
	WSADATA wsa_data;
	version_request = MAKEWORD(2, 2);
	int err = WSAStartup(version_request, &wsa_data);
	if (!err) {
		// log_file_ << "Open winsock successfully!" << std::endl;
		cout << "Open winsock successfully!" << endl;
	}
	else {
		// log_file_ << "Failed to open winsock lib!" << std::endl;
		cout << "Failed to open winsock lib!" << endl;
		return;
	}

	server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	address_.sin_family = AF_INET;
	address_.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	address_.sin_port = htons(socket_port_);
	int ret = ::bind(server_socket_, (SOCKADDR*)&address_, sizeof(SOCKADDR));
	if (ret == SOCKET_ERROR) {
		// log_file_ << "Bind error!" << std::endl;
		cout << "Bind error!" << endl;
		return;
	}
	// listen(server_socket, 5);
	if (listen(server_socket_, 5) == SOCKET_ERROR) {
		// log_file_ << "Listen error!" << std::endl;
		cout << "Listen error!" << endl;
		return;
	}
	cout << "Bind and listen..." << endl;

	while (true) {
		SOCKADDR_IN client_addr;
		int len = sizeof(SOCKADDR);
		SOCKET client_con = accept(server_socket_, (SOCKADDR*)&client_addr, &len);
		// log_file_ << "Accept socket..." << std::endl;
		cout << "Accept socket..." << endl;
		// multi-client connection
		COXClient *client = new COXClient(client_con, client_addr);
		clients_[client_size_++] = client;
		client->start();
	}

	WSACleanup();
}

