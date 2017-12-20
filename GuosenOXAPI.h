#ifndef  _GUOSEN_OX_API_H
#define  _GUOSEN_OX_API_H


#ifdef LIB_GUOSEN_OX_API_EXPORT
#define GUOSEN_OX_API_EXPORT __declspec(dllexport)
#else 
#define GUOSEN_OX_API_EXPORT __declspec(dllimport)
#endif 

#include "GuosenOXApiStruct.h"
#include <string>


class CGuosenOXTraderSpi
{
public:
	virtual void OnRspTradeAccounts(int nRequest, CRspErrorField *pError, bool bLast, COXRspTradeAcctField *pField) {};
	virtual void OnRspQueryOrders(int nRequest, CRspErrorField *pError, bool bLast, COXRspOrderField *pField) {};
	virtual void OnRspQueryBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspBalanceField *pField) {};
	virtual void OnRspQueryPositions(int nRequest, CRspErrorField *pError, bool bLast, COXRspPositionField *pField) {};
	virtual void OnRspQueryFilledDetails(int nRequest, CRspErrorField *pError, bool bLast, COXRspFilledDetailField *pField) {};

	virtual void OnOrderTicketError(int nRequest, CRspErrorField *pError) {};
	//virtual void OnOrderTicketAck(int nRequest, COXRspOrderTicketField *pField) {};

	virtual void OnRspCancelTicketError(int nRequest, CRspErrorField *pError) {};

	//委托信息推送
	virtual void OnRtnOrder(COXRtnOrderTicket *pRtnOrderTicket) {};
	//成交信息推送
	virtual void OnRtnOrderFilled(COXOrderFilledField *pFilledInfo) {};
	//撤单拒绝推送
	virtual void OnRtnCancelRejected(CRspErrorField *pError, COXRtnOrderTicket *pRtnOrderTicket){};

	//信用查询相关应答
	virtual void OnRspQueryCreditTargetStocks(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditTargetStocksField *pField) {};
	virtual void OnRspQueryCreditCollateralsStocks(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditCollatalStocksField *pField) {};
	virtual void OnRspQueryCreditBalanceDebt(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditBalanceDebtField *pField) {};
	virtual void OnRspQueryCreditContracts(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditContractField *pField) {};
	virtual void OnRspQueryCreditSecuLendQuota(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditSecuLendQuotaField *pField) {};
	virtual void OnRspQueryCreditReimbursibleBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspCreditReimbursibleBalField *pField) {};

};


class GUOSEN_OX_API_EXPORT CGuosenOXTraderApi
{
public:

	static CGuosenOXTraderApi *CreateOXTraderApi( );
	virtual void RegisterSpi(CGuosenOXTraderSpi *pSpi) =0;

	virtual void Release() = 0;
	
	virtual int  Init(std::string &strErr) = 0;
	//virtual int  OrderRtnRegister(char accountType, const std::string & strAcctId) = 0;
	virtual int  OrderRtnRegister(char accountType, const char * pcstrAcctId) = 0;
	virtual void Join() = 0;

	virtual int OnReqTradeAccounts(int nRequest, const COXReqTradeAcctField * pField) = 0;
	virtual int OnReqQueryOrders(int nRequest, const COXReqOrdersField *pField) = 0;
	virtual int OnReqQueryBalance(int nRequest, const COXReqBalanceField *pField) = 0;
	virtual int OnReqQueryPositions(int nRequest, const COXReqPositionField *pField)  = 0;
	virtual int OnReqQueryFilledDetails(int nRequest, const COXReqFilledDetailField *pField)  = 0;

	virtual int OnReqOrderTicket(int nRequest, const COXReqOrderTicketField *pField) = 0;
	virtual int OnReqCancelTicket(int nRequest, const COXReqCancelTicketField *pField) = 0;

	//信用交易相关查询接口  	
	virtual int OnReqCreditTargetStocks(int nRequest, const COXReqCreditTargetStocks *pField) = 0;               //标的券查询
	virtual int OnReqCreditCollateralsStocks(int nRequest, const COXReqCreditCollateralsStocks *pField) = 0;     //担保券查询

	virtual int OnReqCreditBalanceDebt(int nRequest, const COXReqCreditBalanceDebt *pField) = 0;                 //资产负债查询 
	virtual int OnReqCreditContracts(int nRequest, const COXReqCreditContracts *pField) = 0;                     //融资融券合约查询
	virtual int OnReqCreditSecuLendQuota(int nRequest, const COXReqCreditSecuLendQuota *pField) = 0;             //融券头寸查询

	virtual int OnReqCreditReimbursibleBalance(int nRequest, const COXReqCreditReimbursibleBalance *pField) = 0;//可偿还金额查询


};

#endif