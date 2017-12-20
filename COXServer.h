#ifndef _COX_SERVER_H
#define _COX_SERVER_H

#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <boost/thread/thread.hpp>
#include <wchar.h>
#include <time.h>
#include <string.h>
#include <memory>
#include <fstream>
#include <string>
#include <map>
#include <WINSOCK2.h>

#include "COXTrader.h"

class COXClient {
public:
	COXClient(SOCKET connection, SOCKADDR_IN address);

	bool start();

	void send_msg(const char *buffer, int len, COXTrader *trader);

	void receice_message();

	void decode(const char *message);

private:
	void ReqUserLogin(std::map<std::string, std::string>& properties);
	void ReqOrderInsert(std::map<std::string, std::string>& properties);
	void ReqOrderAction(std::map<std::string, std::string>& properties);
	void ReqQryInvestorPosition(std::map<std::string, std::string>& properties);
	void ReqQryInvestorAccount(std::map<std::string, std::string>& properties);
	void ReqQryInvestorMarginStock(std::map<std::string, std::string>& properties);

	// COX Trader members
	COXTrader *trader_;
	char user_id_[32];
	char password_[64];

	// socket functionality members
	SOCKET fd_;
	SOCKADDR_IN addr_;
	bool start_;
	std::fstream log_file_;
};


class COXServer {
public:
	virtual ~COXServer();
	static COXServer& Instance();

	bool RegisterServer(int port);

	bool Callback(const char* message, COXTrader *trader);

private:
	COXServer();

	void listen_thread();

	// members
	int                 socket_port_;
	// boost::thread_group client_threads_;
	// boost::thread       server_thread_;

	// std::fstream log_file_;
	SOCKET server_socket_;
	SOCKADDR_IN address_;

	COXClient **clients_;
	int             client_size_;
};

#endif