
#include "COXSpi.h"
#include <iostream>

using std::cout;
using std::endl;

#pragma comment(lib, "../lib/GuosenOXAPI.lib")

COXSpi::COXSpi()
{

}

COXSpi::~COXSpi()
{

}

void COXSpi::OnRspTradeAccounts(int nRequest, CRspErrorField *pError, bool bLast, COXRspTradeAcctField *pField)
{
	cout << "COXSPI-OnRspTradeAccounts::"
		<< " Request id: " << nRequest
		<< " Last is  " << bLast
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;

	if (!pError->ErrorId)
	{
		cout << "资金账号: " << pField->CuacctCode
			<< " 客户代码:" << pField->CustCode
			<< " 交易板块:" << pField->BoardId
			<< " 交易市场:" << pField->ExchangeId
			<< " 股东账户:" << pField->TrdAcct
			<< " 账户状态:" << pField->TrdAcctStatus
			<< " 账户类别:" << pField->TrdAcctType
			<< endl;
	}

}

void COXSpi::OnRspQueryOrders(int nRequest, CRspErrorField *pError, bool bLast, COXRspOrderField *pField)
{
	cout << "OnRspQueryOrders::"
		<< " Request id: " << nRequest
		<< " Last is  " << bLast
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;

	if (!pError->ErrorId)
	{
		cout << " QryPos			" << pField->QryPos << endl
			<< " CuacctCode		" << pField->CuacctCode << endl
			<< " CustCode		" << pField->CustCode << endl
			<< " Trdacct			" << pField->Trdacct << endl
			<< " ExchangeId		" << pField->ExchangeId << endl
			<< " BoardId			" << pField->BoardId << endl
			<< " StkBiz			" << pField->StkBiz << endl
			<< " StkBizActiion	" << pField->StkBizAction << endl
			<< " Symbol			" << pField->Symbol << endl
			<< " IntOrg			" << pField->IntOrg << endl
			<< " OrderDate		" << pField->OrderDate << endl
			<< " OrderTime		" << pField->OrderTime << endl
			<< " OrderNo			" << pField->OrderNo << endl
			<< " CliOrderNo		" << pField->CliOrderNo << endl
			<< " CliRemark		" << pField->CliRemark << endl
			<< " ExeStatus		" << pField->ExeStatus << endl
			<< " ExeInfo			" << pField->ExeInfo << endl
			<< " OrderQty		" << pField->OrderQty << endl
			<< " OrderPrice		" << pField->OrderPrice << endl
			<< " FilledQty		" << pField->FilledQty << endl
			<< " CanceledQty		" << pField->CanceledQty << endl
			<< " FilledAmt		" << pField->FilledAmt << endl
			<< " UpdateTime		" << pField->UpdateTime << endl
			<< endl;
	}

}

void COXSpi::OnRspQueryBalance(int nRequest, CRspErrorField *pError, bool bLast, COXRspBalanceField *pField)
{
	cout << "OnRspQueryBalance::"
		<< " Request id: " << nRequest
		<< " Last is  " << bLast
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;

	if (!pError->ErrorId)
	{
		cout << " AccountWorth:	" << pField->AccountWorth << endl
			<< " Avaiable:		" << pField->Avaiable << endl
			<< " Currency:		" << pField->Currency << endl
			<< " FundBalance:	" << pField->FundBalance << endl
			<< " FundPreBalance:	" << pField->FundPreBalance << endl
			<< " FundValue:		" << pField->FundValue << endl
			<< " MarketValue:	" << pField->MarketValue << endl
			<< endl;
	}
}

void COXSpi::OnRspQueryPositions(int nRequest, CRspErrorField *pError, bool bLast, COXRspPositionField *pField)
{
	cout << "OnRspQueryPositions::"
		<< " Request id: " << nRequest
		<< " Last is  " << bLast
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;

	if (!pError->ErrorId)
	{
		cout << " AveragePrice	" << pField->AveragePrice << endl
			<< " CostPrice		" << pField->CostPrice << endl
			<< " CuacctCode		" << pField->CuacctCode << endl
			<< " Currency		" << pField->Currency << endl
			<< " CurrentPrice	" << pField->CurrentPrice << endl
			<< " CustCode		" << pField->CustCode << endl
			<< " Income			" << pField->Income << endl
			<< " IntOrg			" << pField->IntOrg << endl
			<< " MktVal			" << pField->MktVal << endl
			<< " ProfitPrice		" << pField->ProfitPrice << endl
			<< " ProIncome		" << pField->ProIncome << endl
			<< " QryPos			" << pField->QryPos << endl
			<< " StkAvl			" << pField->StkAvl << endl
			<< " StkBcost		" << pField->StkBcost << endl
			<< " StkBcostRlt		" << pField->StkBcostRlt << endl
			<< " Stkbd			" << pField->Stkbd << endl
			<< " StkCalMktvale	" << pField->StkCalMktvale << endl
			<< " StkCls			" << pField->StkCls << endl
			<< " StkCode			" << pField->StkCode << endl
			<< " StkName			" << pField->StkName << endl;

	}

}

void COXSpi::OnRspQueryFilledDetails(int nRequest, CRspErrorField *pError, bool bLast, COXRspFilledDetailField *pField)
{
	cout << "OnRspQueryFilledDetails::"
		<< " Request id: " << nRequest
		<< " Last is  " << bLast
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;

	if (!pError->ErrorId)
	{
		cout << " QryPos	        " << pField->QryPos << endl
			<< " CuacctCode		" << pField->CuacctCode << endl
			<< " CustCode		" << pField->CustCode << endl
			<< " Trdacct		    " << pField->Trdacct << endl

			<< " OrderDate	    " << pField->OrderDate << endl
			<< " OrderNo		    " << pField->OrderNo << endl
			<< " OrderId			" << pField->OrderId << endl

			<< " ExchangeId		" << pField->ExchangeId << endl
			<< " BoardId		    " << pField->BoardId << endl
			<< " Symbol		    " << pField->Symbol << endl
			<< " StkBiz			" << pField->StkBiz << endl
			<< " StkBizAction	" << pField->StkBizAction << endl

			<< " FilledType		" << pField->FilledType << endl
			<< " TradeSn		    " << pField->TradeSn << endl
			<< " FilledQty		" << pField->FilledQty << endl
			<< " FilledPrice	    " << pField->FilledPrice << endl
			<< " FilledDate		" << pField->FilledDate << endl
			<< " FilledTime		" << pField->FilledTime << endl
			<< " ErrId			" << pField->ErrId << endl
			<< " ErrMessage		" << pField->ErrMessage << endl;

	}
}

void COXSpi::OnOrderTicketError(int nRequest, CRspErrorField *pError)
{
	cout << "OnOrderTicketError::"
		<< " Request id: " << nRequest
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;
}

void COXSpi::OnOrderTicketAck(int nRequest, COXRspOrderTicketField *pField)
{
	cout << "OnOrderTicketAck::"
		<< " Request id: " << nRequest
		<< endl;

	cout << " OrderNo: " << pField->OrderNo
		<< "CliOrderNo : " << pField->CliOrderNo
		<< endl;

}

void COXSpi::OnRspCancelTicketError(int nRequest, CRspErrorField *pError)
{
	cout << "OnRspCancelTicketError::"
		<< " Request id: " << nRequest
		<< endl;

	cout << " ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;
}

void COXSpi::OnRtnOrder(COXRtnOrderTicket *pOrderTicket)
{
	cout << "****** OnRtnOrder ******" << endl;
	cout << "BoardId: " << pOrderTicket->stOrderTicketReq.BoardId << endl
		<< "CanceledQty:" << pOrderTicket->CanceledQty << endl
		<< "CliOrderNo:" << pOrderTicket->stOrderTicketReq.CliOrderNo << endl
		<< "CuacctCode:" << pOrderTicket->stOrderTicketReq.CuacctCode << endl
		<< "CustCode:" << pOrderTicket->stOrderTicketReq.CustCode << endl
		<< "ExchangeId:" << pOrderTicket->stOrderTicketReq.ExchangeId << endl
		<< "ExeInfo:" << pOrderTicket->ExeInfo << endl
		<< "ExeStatus:" << pOrderTicket->ExeStatus << endl
		<< "FilledAmt: " << pOrderTicket->FilledAmt << endl
		<< "FilledQty: " << pOrderTicket->FilledQty << endl
		<< "IntOrg: " << pOrderTicket->stOrderTicketReq.IntOrg << endl
		<< "OrderDate: " << pOrderTicket->OrderDate << endl
		<< "OrderNo: " << pOrderTicket->OrderNo << endl
		<< "OrderQty: " << pOrderTicket->stOrderTicketReq.OrderQty << endl
		<< "OrderPrice: " << pOrderTicket->stOrderTicketReq.OrderPrice << endl
		<< "OrderTime: " << pOrderTicket->OrderTime << endl
		<< endl;
}

void COXSpi::OnRtnOrderFilled(COXOrderFilledField *pFilledInfo)
{
	cout << "****** OnRtnOrderFilled ******" << endl;
	cout << "Symbol: " << pFilledInfo->Symbol << endl
		<< "CliOrderNo: " << pFilledInfo->CliOrderNo << endl
		<< "OrderNo: " << pFilledInfo->OrderNo << endl
		<< "FilledQty: " << pFilledInfo->FilledQty << endl
		<< "FilledPrice: " << pFilledInfo->FilledPrice << endl
		<< "TradeSn: " << pFilledInfo->TradeSn << endl
		<< endl;
}

void COXSpi::OnRtnCancelRejected(CRspErrorField *pError, COXRtnOrderTicket *pRtnOrderTicket)
{

	cout << "OnRtnCancelRejected ErrorId: " << pError->ErrorId
		<< " ErrorInfo: " << pError->ErrorInfo
		<< endl;
}
