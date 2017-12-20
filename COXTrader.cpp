
#include "COXTrader.h"
#include "COXServer.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#include <windows.h>

using namespace std;

COXTrader::COXTrader(const char *user_id) {
	api_ = NULL;
	snprintf(user_id_, sizeof(user_id_), "%s", user_id);
	logined_ = false;
	request_id_ = 1;
	char log_file_name[64];
	snprintf(log_file_name, sizeof(log_file_name), "%s.log", user_id_);
	log_file_.open(log_file_name, ios::out | ios::app);
}

COXTrader::~COXTrader() {

}

void COXTrader::Init() {
	if (api_ == NULL) {
		api_ = CGuosenOXTraderApi::CreateOXTraderApi();
		api_->RegisterSpi(this);
		string strErr;
		int ret = api_->Init(strErr);
		if (ret) {
			cout << "Failed to initialize trader api: code-" << ret
				<< " message-" << strErr << endl;
			logined_ = false;
			api_ = NULL;
			return;
		}

		cout << "Initialize trader api successfully" << endl;
		logined_ = true;
		OnReqTradeAccountsInit();
		Sleep(2000);
		//api_->OrderRtnRegister(OX_ACCOUNT_STOCK, user_id_);
		api_->OrderRtnRegister(acct_type_, user_id_);
		cout << "Register Order Return" << endl;
	}
}

void COXTrader::Release() {
	if (api_ != NULL) {
		api_->Release();
		//api_->Join();
	}
}

bool COXTrader::Logined() {
	return logined_;
}

int COXTrader::OnReqOrderTicket(map<string, string>& properties) {
	if (api_ != NULL) {
		//log_file_ << time_now_ms() << " - OnReqOrderTicket" << endl;
		COXReqOrderTicketField *req = new COXReqOrderTicketField;
		memset(req, 0, sizeof(*req));

		string account = properties["ACCOUNT"];
		if (strcmp(account.c_str(), user_id_) != 0)
			return 2001;

		string action = properties["ACTION"];
		string symbol = properties["SYMBOL"];
		string quantity = properties["QUANTITY"];
		string type = properties["TYPE"];
		string limit_price = properties["LIMITPRICE"];
		string duration = properties["DURATION"];
		string client_id = properties["CLIENTID"];
		vector<string> ins_exch;
		string readable_symbol = symbol;
		string exchange;
		split(symbol, ".", ins_exch);
		if (ins_exch.size() == 2) {
			readable_symbol = ins_exch[0];
			exchange = ins_exch[1];
		}

		//req->AcctType = OX_ACCOUNT_STOCK;
		req->AcctType = acct_type_;
		//req->AcctType = OX_ACCOUNT_MARGIN;
		snprintf(req->CuacctCode, sizeof(req->CuacctCode), "%s", account.c_str());
		snprintf(req->CustCode, sizeof(req->CustCode), "%s", account.c_str());

		if (exchange == "SH") {
			snprintf(req->Trdacct, sizeof(req->Trdacct), "%s", gdh_sh_);
			snprintf(req->BoardId, sizeof(req->BoardId), "%s", OX_BOARD_SHA);
			req->ExchangeId = OX_EXCHANGE_SH;
		}
		else if (exchange == "SZ") {
			snprintf(req->Trdacct, sizeof(req->Trdacct), "%s", gdh_sz_);
			snprintf(req->BoardId, sizeof(req->BoardId), "%s", OX_BOARD_SZA);
			req->ExchangeId = OX_EXCHANGE_SZ;
		}

		snprintf(req->Symbol, sizeof(req->Symbol), "%s", readable_symbol.c_str());

		if (action == "BUY") {
			req->StkBiz = OX_BIZ_BUY;
		}
		else if (action == "SELL") {
			req->StkBiz = OX_BIZ_SELL;
		}
		else if (action == "COLLATERALBUY") {
			req->StkBiz = OX_BIZ_COLLATERALBUY;
		}
		else if (action == "COLLATERALSELL") {
			req->StkBiz = OX_BIZ_COLLATERALSELL;
		}
		else if (action == "BORROWTOBUY") {
			req->StkBiz = OX_BIZ_BORROWTOBUY;
		}
		else if (action == "BORROWTOSELL") {
			req->StkBiz = OX_BIZ_BORROWTOSELL;
		}
		else if (action == "BUYTOPAY") {
			req->StkBiz = OX_BIZ_BUYTOPAY;
		}
		else if (action == "SELLTOPAY") {
			req->StkBiz = OX_BIZ_SELLTOPAY;
		}
		else if (action == "PAYBYCASH") {
			req->StkBiz = OX_BIZ_PAYBYCASH;
		}
		else if (action == "PAYBYSTOCK") {
			req->StkBiz = OX_BIZ_PAYBYSTOCK;
		}
		req->StkBizAction = OX_BUZACTION_LIMIT;

		req->IntOrg = 100;

		snprintf(req->CliOrderNo, sizeof(req->CliOrderNo), "%s", client_id.c_str());

		snprintf(req->OrderPrice, sizeof(req->OrderPrice), "%s", limit_price.c_str());
		req->OrderQty = atoi(quantity.c_str());

		//log_file_ << time_now_ms() << " - Filling fields of OrderTicket" << endl;
		/*
		cout << "ReqOrderTicket: AcctType:" << req->AcctType
			<< " CuacctCode:" << req->CuacctCode
			<< " CustCode:" << req->CustCode
			<< " Trdacct:" << req->Trdacct
			<< " Symbol:" << req->Symbol
			<< " Board:" << req->BoardId
			<< " Exchange:" << req->ExchangeId
			<< " StkBiz:" << req->StkBiz
			<< " StkBizAction:" << req->StkBizAction
			<< " IntOrg:" << req->IntOrg
			<< " CliOrderNo:" << req->CliOrderNo
			<< " OrderPrice:" << req->OrderPrice
			<< " OrderQty:" << req->OrderQty << endl;

		cout << "ReqOrderInsert:" << time_now_ms() << " - " << req->CliOrderNo << endl;
		*/
		log_file_ << "ReqOrderInsert:" << time_now_ms() << " - " << req->CliOrderNo << endl;
		int iRet = api_->OnReqOrderTicket(request_id_++, req);
		//cout << "After ReqOrderInsert:" << time_now_ms() << " - " << req->CliOrderNo << endl;
		log_file_ << "After ReqOrderInsert:" << time_now_ms() << " - " << req->CliOrderNo << endl;
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_ORDER_TICKET, (void*)req);
		if (iRet)
		{
			cout << " OnReqOrderTicket Error: iRet = " << iRet << endl;
		}
		else {
			cout << "OnReqOrderTicket Successfully" << endl;
		}
		return iRet;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqCancelTicket(map<string, string>& properties) {
	if (api_ != NULL) {
		COXReqCancelTicketField *req = new COXReqCancelTicketField;
		memset(req, 0, sizeof(*req));

		string client_id = properties["CLIENTID"];
		string exchange = properties["EXCHANGE"];

		map<string, unsigned>::iterator it = client_sys_map_.find(client_id);
		if (it == client_sys_map_.end()) {
			cout << "Client ID-" << client_id << " not exist" << endl;
			return 2001;
		}

		unsigned sys_id = it->second;
		req->OrderNo = sys_id;
		//req->AcctType = OX_ACCOUNT_STOCK;
		req->AcctType = acct_type_;
		snprintf(req->CuacctCode, sizeof(req->CuacctCode), "%s", user_id_);
		if (exchange == "SH" || exchange == "SSE") {
			snprintf(req->BoradId, sizeof(req->BoradId), "%s", OX_BOARD_SHA);
		}
		else if (exchange == "SZ" || exchange == "SZE") {
			snprintf(req->BoradId, sizeof(req->BoradId), "%s", OX_BOARD_SZA);
		}
		req->OrderDate = date_now();

		int iRet = api_->OnReqCancelTicket(request_id_++, req);
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_CANCEL_TICKET, (void*)req);
		if (iRet)
		{
			cout << " OnReqCancelTicket Error: iRet = " << iRet << endl;
		}
		else {
			cout << "OnReqCancelTicket Successfully" << endl;
		}
		return iRet;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqTradeAccounts(map<string, string>& properties) {
	if (api_ != NULL) {
		return 0;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqTradeAccountsInit() {
	if (api_ != NULL) {
		COXReqTradeAcctField *req = new COXReqTradeAcctField;
		memset(req, 0, sizeof(*req));
		snprintf(req->Account, sizeof(req->Account), "%s", user_id_);
		int ret = api_->OnReqTradeAccounts(request_id_++, req);
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_TRADE_ACCOUNT, (void*)req);
		cout << "OnReqTradeAccountsInit:" << ret << endl;
		return ret;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqQueryBalance(map<string, string>& properties) {
	if (api_ != NULL) {
		COXReqBalanceField *req = new COXReqBalanceField;
		memset(req, 0, sizeof(*req));

		//q.AcctType = OX_ACCOUNT_STOCK;
		req->AcctType = acct_type_;
		snprintf(req->Account, sizeof(req->Account), "%s", user_id_);
		int ret = api_->OnReqQueryBalance(request_id_++, req);
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_QUERY_BALANCE, (void*)req);
		cout << "OnReqQueryBalance:" << ret << endl;
		return ret;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqQueryPositions(map<string, string>& properties) {
	if (api_ != NULL) {
		COXReqPositionField *req = new COXReqPositionField;
		memset(req, 0, sizeof(*req));
		string account = properties["ACCOUNT"];
		if (strcmp(account.c_str(), user_id_) != 0) {
			return -1;
		}
		//req->AcctType = OX_ACCOUNT_STOCK;
		req->AcctType = acct_type_;;
		snprintf(req->Account, sizeof(req->Account), "%s", user_id_);
		req->QueryNum = 200;
		int ret = api_->OnReqQueryPositions(request_id_++, req);
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_QUERY_POSITION, (void*)req);
		if (ret) {
			cout << "OnReqQueryPosition Error:" << ret << endl;
		}
		else {
			cout << "OnReqQueryPositions successfully" << endl;
		}
		//return api_->OnReqQueryPositions(nRequest, pField);
		return ret;
	}
	else {
		return -1;
	}
}

int COXTrader::OnReqCreditSecuLendQuota(map<string, string>& properties) {
	if (api_ != NULL) {
		COXReqCreditSecuLendQuota *req = new COXReqCreditSecuLendQuota;
		memset(req, 0, sizeof(*req));
		string account = properties["ACCOUNT"];
		if (strcmp(account.c_str(), user_id_) != 0) {
			return -1;
		}
		//req->AcctType = OX_ACCOUNT_STOCK;
		req->AcctType = acct_type_;;
		snprintf(req->CuacctCode, sizeof(req->CuacctCode), "%s", user_id_);
		snprintf(req->CashNo, sizeof(req->CashNo), "%s", user_id_);
		//req->QueryNum = 200;
		int ret = api_->OnReqCreditSecuLendQuota(request_id_++, req);
		requests_[request_id_ - 1] = new request_ptr(request_ptr::TYPE_QUERY_MARGINSTOCK, (void*)req);
		if (ret) {
			cout << "OnReqQueryMarginStock Error:" << ret << endl;
		}
		else {
			cout << "OnReqQueryMarginStock successfully" << endl;
		}
		//return api_->OnReqQueryPositions(nRequest, pField);
		return ret;
	}
	else {
		return -1;
	}
}

void COXTrader::OnRspTradeAccounts(int nRequest, CRspErrorField *pError, bool bLast, COXRspTradeAcctField *pField) {
	if (!pError->ErrorId) {
		cout << "OnRspTradeAccounts:" << pField->CuacctCode
			<< " Board:" << pField->BoardId
			<< " AcctType:" << pField->TrdAcctType
			<< " GDH:" << pField->TrdAcct << endl;
		if (strcmp(pField->CuacctCode, user_id_) == 0) {
			if (pField->TrdAcctType == OX_TRDACCTTYPE_AGC_CASH ||
				pField->TrdAcctType == OX_TRDACCTTYPE_PSN_CASH) {
				acct_type_ = OX_ACCOUNT_STOCK;
			}
			else if (pField->TrdAcctType == OX_TRDACCTTYPE_AGC_MARGIN ||
				pField->TrdAcctType == OX_TRDACCTTYPE_PSN_MARGIN) {
				acct_type_ = OX_ACCOUNT_MARGIN;
			}
			if (strcmp(pField->BoardId, OX_BOARD_SHA) == 0) {
				snprintf(gdh_sh_, sizeof(gdh_sh_), "%s", pField->TrdAcct);
			}
			else if (strcmp(pField->BoardId, OX_BOARD_SZA) == 0) {
				snprintf(gdh_sz_, sizeof(gdh_sz_), "%s", pField->TrdAcct);
			}
		}
	}
	else {
		cout << "OnRspTradeAccounts-Error:" << pError->ErrorId << " " << pError->ErrorId << endl;
	}
}

void COXTrader::OnRspQueryOrders(int nRequest, CRspErrorField *pError, bool bLast, COXRspOrderField *pField) {

}

void COXTrader::OnRspQueryBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspBalanceField *pField) {
	if (!pError->ErrorId) {
		cout << "OnRspQueryBalance:" << user_id_
			<< " Currency:" << pField->Currency
			<< " AccountWorth:" << pField->AccountWorth
			<< " FundValue:" << pField->FundValue
			<< " MarketValue:" << pField->MarketValue
			<< " FundPreBalance:" << pField->FundPreBalance
			<< " FundBalance:" << pField->FundBalance
			<< " Available:" << pField->Avaiable
			<< endl;

		char message[2048];
		int is_last = (bLast) ? 1 : 0;
		snprintf(message, sizeof(message), "TYPE=ACCOUNT;ACCOUNT_ID=%s;IS_LAST=%d;"
			"RT_ACCOUNT_NET_WORTH=%s;RT_CASH_BALANCE=%s;RT_MARKET_VALUE=%s;"
			"RT_TRADING_POWER=%s",
			user_id_, is_last, pField->AccountWorth, pField->FundBalance, pField->MarketValue,
			pField->Avaiable);

		cout << "OnRspQueryBalance:" << message << endl;
		COXServer::Instance().Callback(message, this);

	}
	else {
		cout << "OnRspQueryBalance-Error:" << pError->ErrorId << " " << pError->ErrorId << endl;
	}
}

void COXTrader::OnRspQueryPositions(int nRequest, CRspErrorField *pError, bool bLast, COXRspPositionField *pField) {
	if (!pError->ErrorId) {
		cout << "OnRspQueryPositions:" << pField->StkCode
			<< " StkName:" << pField->StkName
			<< " StkCls:" << pField->StkCls
			<< " AveragePrice:" << pField->AveragePrice
			<< " CostPrice:" << pField->CostPrice
			<< " CurrentPrice:" << pField->CurrentPrice
			<< " MktVal:" << pField->MktVal
			<< " StkAvl:" << pField->StkAvl
			<< " StkBcost:" << pField->StkBcost
			<< " StkPrebln:" << pField->StkPrebln
			<< " StkBln:" << pField->StkBln
			<< " StkQty:" << pField->StkQty[0]
			<< " StkRemain:" << pField->StkRemain
			<< endl;

		char message[2048];
		// available = StkAvl,  yesterday position = StkBln = StkPrebln, current position = StkQty[0]
		int available = (int)pField->StkAvl;
		int ydpos = (int)pField->StkBln;
		int curpos = (int)pField->StkQty[0];
		int long_qty = ydpos - available;
		int short_qty = curpos - available;
		double total_cost = atof(pField->CostPrice) * (double)curpos;
		int is_last = (bLast) ? 1 : 0;

		snprintf(message, sizeof(message), "TYPE=POSITION;ACCOUNT_ID=%s;IS_LAST=%d;POSITION_TYPE=%s;"
			"SYMBOL=%s;QUANTITY=%d;AVAILABLE_QTY=%d;LONG_QTY=%d;SHORT_QTY=%d;AVERAGE_PRICE=%s;"
			"TOTAL_COST=%lf;MARKET_VALUE=%s", pField->CuacctCode, is_last, "LONG_POSITION", pField->StkCode,
			curpos, available, long_qty, short_qty, pField->AveragePrice, total_cost, pField->MktVal);

		cout << "OnRspQueryPositions:" << message << endl;
		COXServer::Instance().Callback(message, this);
	}
	else {
		cout << "OnRspQueryPositions-Error:" << pError->ErrorId << " " << pError->ErrorId << endl;
	}
}

void COXTrader::OnRspQueryCreditSecuLendQuota(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditSecuLendQuotaField *pField) {
	if (!pError->ErrorId) {
		cout << "OnRspQueryCreditSecuLendQuota:" << pField->Symbol
			<< " CashNo:" << pField->CashNo
			<< " BoardId:" << pField->BoardId
			<< " AssetBln:" << pField->AssetBln
			<< " AssetAvl:" << pField->AssetAvl
			<< endl;

		char message[2048];
		// available = StkAvl,  yesterday position = StkBln = StkPrebln, current position = StkQty[0]
		int available = (int)pField->AssetAvl;
		int balance = (int)pField->AssetBln;
		int is_last = (bLast) ? 1 : 0;

		snprintf(message, sizeof(message), "TYPE=MARGINSTOCK;ACCOUNT_ID=%s;IS_LAST=%d;"
			"SYMBOL=%s;TOTAL_MARGIN_QUOTA=%d;AVAILABLE_MARGIN_QUOTA=%d", 
			pField->CashNo, is_last, pField->Symbol, available, balance);

		cout << "OnRspQueryMarginStock:" << message << endl;
		COXServer::Instance().Callback(message, this);
	}
	else {
		cout << "OnRspQueryMarginStock-Error:" << pError->ErrorId << " " << pError->ErrorId << endl;
	}
}

void COXTrader::OnRspQueryFilledDetails(int nRequest, CRspErrorField *pError, bool bLast, COXRspFilledDetailField *pField) {

}

void COXTrader::OnOrderTicketError(int nRequest, CRspErrorField *pError) {
	cout << "OnOrderTicketError: Code-" << pError->ErrorId << " Message-" << pError->ErrorInfo << endl;
	int request_type = requests_[nRequest]->request_type;
	if (request_type != request_ptr::TYPE_ORDER_TICKET) {
		cout << "Wrong request type!" << endl;
	}
	else {
		COXReqOrderTicketField* req = (COXReqOrderTicketField*)requests_[nRequest]->ptr;
		char message[2048];
		//cout << "OnRtnOrder:" << time_now_ms() << " -  " << req->CliOrderNo << endl;

		string status = "REJECTED";

		string direction;
		switch (req->StkBiz) {
		case OX_BIZ_BUY:
			direction = "BUY";
			break;
		case OX_BIZ_SELL:
			direction = "SELL";
			break;
		case OX_BIZ_COLLATERALBUY:
			direction = "COLLATERALBUY";
			break;
		case OX_BIZ_COLLATERALSELL:
			direction = "COLLATERALSELL";
			break;
		case OX_BIZ_BORROWTOBUY:
			direction = "BORROWTOBUY";
			break;
		case OX_BIZ_BORROWTOSELL:
			direction = "BORROWTOSELL";
			break;
		case OX_BIZ_BUYTOPAY:
			direction = "BUYTOPAY";
			break;
		case OX_BIZ_SELLTOPAY:
			direction = "SELLTOPAY";
			break;
		case OX_BIZ_PAYBYCASH:
			direction = "PAYBYCASH";
			break;
		case OX_BIZ_PAYBYSTOCK:
			direction = "PAYBYSTOCK";
			break;
		}

		string client_no(req->CliOrderNo);

		snprintf(message, sizeof(message), "TYPE=UPDATE;STATUS=%s;SYS_ORDER_ID=%d;"
			"LOCAL_ORDER_ID=%s;SYMBOL=%s;ACCOUNT=%s;QUANTITY=%d;LIMIT_PRICE=%lf;"
			"DIRECTION=%s;FILLED_QUANTITY=%d;AVG_FILLED_PRICE=%lf;LEFT_QUANTITY=%du",
			status.c_str(), 0, req->CliOrderNo, req->Symbol, req->CuacctCode,
			req->OrderQty, atof(req->OrderPrice), direction.c_str(), 0, 0.0, req->OrderQty);

		//cout << "OnRspOrderInsert:" << message << endl;
		log_file_ << time_now_ms() << " - OnRspOrderInsert:" << message << endl;
		COXServer::Instance().Callback(message, this);
	}
}

void COXTrader::OnOrderTicketAck(int nRequest, COXRspOrderTicketField *pField) {
	cout << "OnOrderTicketAck: " << endl;
}

void COXTrader::OnRspCancelTicketError(int nRequest, CRspErrorField *pError) {
	cout << "OnRspCancelTicketError: Code-" << pError->ErrorId << " Message-" << pError->ErrorInfo << endl;
}

void COXTrader::OnRtnOrder(COXRtnOrderTicket *pRtnOrderTicket) {
	char message[2048];

	string status;
	//cout << "OnRtnOrder:" << time_now_ms() << " -  " << pRtnOrderTicket->stOrderTicketReq.CliOrderNo << " status:" << pRtnOrderTicket->ExeStatus << endl;
	log_file_ << "OnRtnOrder:" << time_now_ms() << " -  " << pRtnOrderTicket->stOrderTicketReq.CliOrderNo << " status:" << pRtnOrderTicket->ExeStatus << endl;
	switch (pRtnOrderTicket->ExeStatus) {
	case ORDER_STATE_SEND:
		status = "RECEIVED";
		break;
	case ORDER_STATE_PARTIAL_FILLED:
		status = "PARTIALLYFILLED";
		break;
	case ORDER_STATE_FILLED:
		status = "FILLED";
		break;
	case ORDER_STATE_CANCELED:
		status = "CANCELED";
		break;
	case ORDER_STATE_PARTIAL_CANCELED:
		status = "PARTIALLYFILLEDUROUT";
		break;
	case ORDER_STATE_REJECTED:
		status = "REJECTED";
		//status = "CANCELED";
		break;
	default:
		//return;
		break;
	} // switch

	string direction;
	switch (pRtnOrderTicket->stOrderTicketReq.StkBiz) {
	case OX_BIZ_BUY:
		direction = "BUY";
		break;
	case OX_BIZ_SELL:
		direction = "SELL";
		break;
	case OX_BIZ_COLLATERALBUY:
		direction = "COLLATERALBUY";
		break;
	case OX_BIZ_COLLATERALSELL:
		direction = "COLLATERALSELL";
		break;
	case OX_BIZ_BORROWTOBUY:
		direction = "BORROWTOBUY";
		break;
	case OX_BIZ_BORROWTOSELL:
		direction = "BORROWTOSELL";
		break;
	case OX_BIZ_BUYTOPAY:
		direction = "BUYTOPAY";
		break;
	case OX_BIZ_SELLTOPAY:
		direction = "SELLTOPAY";
		break;
	case OX_BIZ_PAYBYCASH:
		direction = "PAYBYCASH";
		break;
	case OX_BIZ_PAYBYSTOCK:
		direction = "PAYBYSTOCK";
		break;
	}

	string client_no(pRtnOrderTicket->stOrderTicketReq.CliOrderNo);
	map<string, unsigned>::iterator it = client_sys_map_.find(client_no);
	
	if (it == client_sys_map_.end()) {
		client_sys_map_.insert(pair<string, unsigned>(client_no, pRtnOrderTicket->OrderNo));
		//return; // do not send feedback message whose client ID cannot be found in local 
	} 

	
	int filled_qty = pRtnOrderTicket->FilledQty;
	if (pRtnOrderTicket->ExeStatus == ORDER_STATE_PARTIAL_CANCELED) {
		filled_qty = pRtnOrderTicket->stOrderTicketReq.OrderQty - abs(pRtnOrderTicket->CanceledQty);
	}
	/*
	snprintf(message, sizeof(message), "TYPE=UPDATE;STATUS=%s;SYS_ORDER_ID=%du;"
		"LOCAL_ORDER_ID=%s;SYMBOL=%s;ACCOUNT=%s;QUANTITY=%d;LIMIT_PRICE=%lf;"
		"DIRECTION=%s;FILLED_QUANTITY=%lld;AVG_FILLED_PRICE=%lf;LEFT_QUANTITY=%lld;"
		"FILLED_AMT=%s;WITHDRAW_QUANTITY=%lld;FILLED_QTY=%d",
		status.c_str(), pRtnOrderTicket->OrderNo, pRtnOrderTicket->stOrderTicketReq.CliOrderNo,
		pRtnOrderTicket->stOrderTicketReq.Symbol, pRtnOrderTicket->stOrderTicketReq.CuacctCode,
		pRtnOrderTicket->stOrderTicketReq.OrderQty, atof(pRtnOrderTicket->stOrderTicketReq.OrderPrice),
		direction.c_str(), pRtnOrderTicket->FilledQty, atof(pRtnOrderTicket->FilledAmt) / (double)pRtnOrderTicket->FilledQty,
		pRtnOrderTicket->stOrderTicketReq.OrderQty - pRtnOrderTicket->FilledQty, pRtnOrderTicket->FilledAmt,
		pRtnOrderTicket->CanceledQty, filled_qty); */
	
	snprintf(message, sizeof(message), "TYPE=UPDATE;STATUS=%s;SYS_ORDER_ID=%du;"
		"LOCAL_ORDER_ID=%s;SYMBOL=%s;ACCOUNT=%s;QUANTITY=%d;LIMIT_PRICE=%lf;"
		"DIRECTION=%s;FILLED_QUANTITY=%d;AVG_FILLED_PRICE=%lf;LEFT_QUANTITY=%du;"
		"FILLED_AMT=%s",
		status.c_str(), pRtnOrderTicket->OrderNo, pRtnOrderTicket->stOrderTicketReq.CliOrderNo,
		pRtnOrderTicket->stOrderTicketReq.Symbol, pRtnOrderTicket->stOrderTicketReq.CuacctCode,
		pRtnOrderTicket->stOrderTicketReq.OrderQty, atof(pRtnOrderTicket->stOrderTicketReq.OrderPrice),
		direction.c_str(), filled_qty, atof(pRtnOrderTicket->FilledAmt) / (double)filled_qty,
		pRtnOrderTicket->stOrderTicketReq.OrderQty - filled_qty, pRtnOrderTicket->FilledAmt); 
	//log_file_ << time_now_ms() << " -  OnRtnOrder Filling Fields:" << message << endl;
	//cout << "OnRtnOrder:" << message << endl;
	COXServer::Instance().Callback(message, this);
}

void COXTrader::OnRtnOrderFilled(COXOrderFilledField *pFilledInfo) {
	cout << "OnRtnOrderFilled" << endl;
}

void COXTrader::OnRtnCancelRejected(CRspErrorField *pError, COXRtnOrderTicket *pRtnOrderTicket) {
	cout << "OnRtnCancelRejected: Code-" << pError->ErrorId << " Message-" << pError->ErrorInfo << endl;
}
