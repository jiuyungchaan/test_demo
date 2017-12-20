#ifndef _COX_TRADER_H
#define _COX_TRADER_H


#include "GuosenOXAPI.h"

#include <map>
#include <string>
#include <fstream>

class COXTrader : public CGuosenOXTraderSpi
{
public:
	COXTrader(const char *user_id);
	virtual ~COXTrader();

	void Init();
	void Release();
	bool Logined();

	/// api interfaces
	int OnReqOrderTicket(std::map<std::string, std::string>& properties);
	int OnReqCancelTicket(std::map<std::string, std::string>& properties);
	int OnReqTradeAccounts(std::map<std::string, std::string>& properties);
	int OnReqQueryBalance(std::map<std::string, std::string>& properties);
	int OnReqQueryPositions(std::map<std::string, std::string>& properties);
	int OnReqCreditSecuLendQuota(std::map<std::string, std::string>& properties);
	int OnReqTradeAccountsInit();

private:
	struct request_ptr {
	public:
		static const int TYPE_INVALID = 0;
		static const int TYPE_ORDER_TICKET = 1;
		static const int TYPE_CANCEL_TICKET = 2;
		static const int TYPE_TRADE_ACCOUNT = 3;
		static const int TYPE_QUERY_BALANCE = 4;
		static const int TYPE_QUERY_POSITION = 5;
		static const int TYPE_QUERY_MARGINSTOCK = 6;

		int request_type;
		void *ptr;

		request_ptr() : request_type(TYPE_INVALID), ptr(NULL) {}
		request_ptr(int type, void *p) : request_type(type), ptr(p) {}
	};
	/// spi interfaces
	void OnRspTradeAccounts(int nRequest, CRspErrorField *pError, bool bLast, COXRspTradeAcctField *pField);
	void OnRspQueryOrders(int nRequest, CRspErrorField *pError, bool bLast, COXRspOrderField *pField);
	void OnRspQueryBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspBalanceField *pField);
	void OnRspQueryPositions(int nRequest, CRspErrorField *pError, bool bLast, COXRspPositionField *pField);
	void OnRspQueryFilledDetails(int nRequest, CRspErrorField *pError, bool bLast, COXRspFilledDetailField *pField);
	void OnRspQueryCreditSecuLendQuota(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditSecuLendQuotaField *pField);

	void OnOrderTicketError(int nRequest, CRspErrorField *pError);
	void OnOrderTicketAck(int nRequest, COXRspOrderTicketField *pField);

	void OnRspCancelTicketError(int nRequest, CRspErrorField *pError);

	void OnRtnOrder(COXRtnOrderTicket *pRtnOrderTicket);
	void OnRtnOrderFilled(COXOrderFilledField *pFilledInfo);
	void OnRtnCancelRejected(CRspErrorField *pError, COXRtnOrderTicket *pRtnOrderTicket);

	/// members
	CGuosenOXTraderApi *api_;
	char user_id_[32];
	bool logined_;
	OXAccountType acct_type_;
	char gdh_sh_[64];  // Gu Dong Hao
	char gdh_sz_[64];
	int request_id_;
	request_ptr* requests_[50000];
	std::map<std::string, unsigned> client_sys_map_;
	std::fstream log_file_;
};

#endif
