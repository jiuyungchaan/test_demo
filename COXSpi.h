
#ifndef _COX_SPI_H
#define _COX_SPI_H

#include "GuosenOXAPI.h"

class COXSpi : public CGuosenOXTraderSpi
{
public:
	COXSpi();
	~COXSpi();

	void OnRspTradeAccounts(int nRequest, CRspErrorField *pError, bool bLast, COXRspTradeAcctField *pField);
	void OnRspQueryOrders(int nRequest, CRspErrorField *pError, bool bLast, COXRspOrderField *pField);
	void OnRspQueryBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspBalanceField *pField);
	void OnRspQueryPositions(int nRequest, CRspErrorField *pError, bool bLast, COXRspPositionField *pField);
	void OnRspQueryFilledDetails(int nRequest, CRspErrorField *pError, bool bLast, COXRspFilledDetailField *pField);

	void OnOrderTicketError(int nRequest, CRspErrorField *pError);
	void OnOrderTicketAck(int nRequest, COXRspOrderTicketField *pField);

	void OnRspCancelTicketError(int nRequest, CRspErrorField *pError);

	//委托信息推送
	void OnRtnOrder(COXRtnOrderTicket *pRtnOrderTicket);
	//成交信息推送
	void OnRtnOrderFilled(COXOrderFilledField *pFilledInfo);
	//撤单拒绝推送
	void OnRtnCancelRejected(CRspErrorField *pError, COXRtnOrderTicket *pRtnOrderTicket);
};






#endif