#ifndef _GUOSEN_OX_API_STRUCT_H
#define _GUOSEN_OX_API_STRUCT_H

#include "GuosenOXApiType.h"

typedef __int64	int64;

#pragma pack(1)

struct CRspErrorField
{
	int  ErrorId;
	char ErrorInfo[128];
};

struct COXOrderRtnRegisterField
{
	char AccountType;
	char Account[16];          //资金账号
};


struct COXReqTradeAcctField
{
	char Account[16];          //资金账号
};

struct COXReqOrdersField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char Account[16];			//资金账号(必需)
	char ExchangeId;			//交易市场
	char BoardId[4];			//交易板块	
	char Symbol[12];			//代码
	int  OrderNo;				//委托编号
	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
	char QueryFlag[2];			// "1" 可撤单

};

struct COXReqBalanceField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char Account[16];			//资金账号(必需)
};

struct COXReqPositionField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char Account[16];			//资金账号(必需)
	char ExchangeId;			//交易市场
	char BoardId[4];			//交易板块	
	char Symbol[12];			//代码
	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
};

struct COXReqFilledDetailField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char Account[16];			//资金账号(必需)
	
	char BoardId[4];			//交易板块	
	char Symbol[12];			//代码
	int  OrderNo;				//委托编号
	int  OrderBsn;				//委托批号
	char TrdAcct[16];			//证券账户

	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
};


struct COXReqOrderTicketField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
	char CustCode[16];
	char Trdacct[16];
	char ExchangeId;
	char BoardId[4];
	int  StkBiz;
	int  StkBizAction;
	char Symbol[12];
	int  IntOrg;
	char CliOrderNo[32 + 1];
	unsigned OrderQty;
	char OrderPrice[16];
	int  TrdCodeCls;

};

struct COXReqCancelTicketField
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
	char BoradId[4];			//交易板块
	unsigned  OrderDate;		//委托日期
	unsigned  OrderNo;			//委托编号

};


struct COXReqCreditTargetStocks
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
	
	char ExchangeId;            //交易市场
	char BoardId[4];			//交易板块
	char Symbol[12];			//代码
	char CurrEnableFI;			//当日融资
	char CurrEnableSL;			//当日融券

	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
};

struct COXReqCreditCollateralsStocks
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)

	char ExchangeId;            //交易市场
	char BoardId[4];			//交易板块
	char Symbol[12];			//代码
	
	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
};

struct COXReqCreditBalanceDebt  
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
	char Currency;              //货币代码	
};


struct COXReqCreditContracts
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)

	int  BgnDate;               //开始日期
	int  EndDate;               //结束日期
	char OrderId[12];           //合同序号
	char ContractType;          //合约类型
	
	char CustCode[16];          //客户代码
	char ExchangeId;            //交易市场
	char BoardId[4];			//交易板块

	char Trdacct[12];            //交易账户
	char Symbol[12];            //证券代码
	int  IntOrg;                //内部机构
	int  OpOrg;                 //操作机构
	char ContractStatus;        //合约状态
	char RepayFlag;              //平仓状态

	char QueryPos[36];			//定位串
	unsigned QueryNum;			//查询行数 最大1000
};

struct COXReqCreditSecuLendQuota
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
	char CashNo[16];			//头寸编号(必填)
};

struct COXReqCreditReimbursibleBalance
{
	OXAccountType	AcctType;	//账户类型(必需)
	char CuacctCode[16];		//资金账号(必需)
};


struct COXRspTradeAcctField
{
	char CustCode[16];		//客户代码
	char CuacctCode[16];    //资金账号
	char ExchangeId;		//交易市场
	char BoardId[4];		//交易板块
	char TrdAcctStatus;		//账户状态
	char TrdAcct[16];		//证券账户
	char TrdAcctType;		//交易账户类别
};

struct COXRspOrderField
{
	char QryPos[36];
	char CuacctCode[16];
	char CustCode[16];
	char Trdacct[16];
	char ExchangeId;
	char BoardId[4];
	int  StkBiz;
	int  StkBizAction;
	char Symbol[12];
	int  IntOrg;
	unsigned  OrderDate;
	char OrderTime[36];
	unsigned OrderNo;
	char CliOrderNo[32 + 1];
	char CliRemark[32];
	OXOrderExeStatus ExeStatus;
	char ExeInfo[128];
	unsigned OrderQty;
	char OrderPrice[16];
	int  FilledQty;
	int  CanceledQty;
	char FilledAmt[24];
	char UpdateTime[36];

};

struct COXRspBalanceField
{
	char	Currency;			// 货币
	char    AccountWorth[24];	//资产总值
	char	FundValue[24];		//资金资产
	char    MarketValue[24];	//市值

	char    FundPreBalance[24];//资金昨日余额
	char    FundBalance[24];	//资金余额
	char    Avaiable[24];		//资金可用金额
};

struct COXRspPositionField
{
	char  QryPos[36];		    //定位串              
	int   IntOrg;		        //内部机构            
	char  CustCode[16];		    //客户代码            
	char  CuacctCode[16];		//资产账户            
	char  Stkbd[4];		        //交易板块            
	char  Stkpbu[8];		    //交易单元            
	char  Currency;		        //货币代码            
	char  StkCode[12];		    //证券代码            
	char  StkName[16];		    //证券名称            
	char  StkCls[2];		    //证券类别            
	char  StkPrebln[16];		//证券昨日余额        
	int64 StkBln;		        //证券余额            
	int64 StkAvl;		        //证券可用数量        
	int64 StkFrz;		        //证券冻结数量        
	int64 StkUfz;		        //证券解冻数量        
	int64 StkTrdFrz;		    //证券交易冻结数量    
	int64 StkTrdUfz;		    //证券交易解冻数量    
	int64 StkTrdOtd;		    //证券交易在途数量    
	char  StkBcost[24];		    //证券买入成本        
	char  StkBcostRlt[24];	    //证券买入成本（实时）
	char  StkPlamt[24];		    //证券盈亏金额        
	char  StkPlamtRlt[24];		//证券盈亏金额（实时）
	char  MktVal[24];		    //市值                
	char  CostPrice[24];		//成本价格            
	char  ProIncome[24];		 //参考盈亏            
	char  StkCalMktvale[2];		//市值计算标识        
	int64 StkQty[16];		    //当前拥股数          
	char  CurrentPrice[16];		//最新价格            
	char  ProfitPrice[16];		//参考成本价          
	int64 StkDiff;		        //可申赎数量          
	int64 StkTrdUnfrz;		    //已申赎数量          
	char  Trdacct[16];		    //交易账户            
	char  Income[16];		    //盈亏                
	int64 StkRemain;		    //余券可用数量        
	char  AveragePrice[16];		//买入均价            
};

struct COXRspFilledDetailField
{
	char      QryPos[36];         //定位串
	char      CuacctCode[16];	  //资产账户
	char      CustCode[16];       //客户代码
	char      Trdacct[16];        //交易账户
	unsigned  OrderDate;          //委托日期
	unsigned  OrderNo;            //委托号
	char      OrderId[12];        //合同序号
	
	char      ExchangeId;		  //交易所
	char      BoardId[4];         //交易板块
	char      Symbol[12];         //证券代码
	int       StkBiz;             //交易业务
	int       StkBizAction;       //业务活动
	
	char      FilledType;         //成交类型
	char      TradeSn[24];        //成交编号
	int64     FilledQty;          //成交数量
	char      FilledPrice[16];    //成交价格
	unsigned  FilledDate;         //成交日期
	char      FilledTime[12];     //成交时间
	
	int       ErrId;			  //错误ID
	char      ErrMessage[128];	  //错误信息

};

struct COXRspCancelTicketField
{
	char CuacctCode[16];
	char BoardId[4];
	unsigned  OrderDate;
	unsigned  OrderNo;
	char CliOrderNo[32 + 1];
	OXOrderExeStatus ExeStatus;
	char ExeInfo[128];
	unsigned OrderQty;
	int  StkBiz;
	int  StkBizAction;
	char Symbol[12];

};

struct COXRspOrderTicketField
{
	char CuacctCode[16];
	char CliOrderNo[32 + 1];
	int  OrderNo;
	unsigned  OrderBsn;
	unsigned  OrderDate;
	char OrderTime[36];
	
	OXOrderExeStatus ExeStatus;
	char ExeInfo[128];
	
	unsigned OrderQty;
	int  StkBiz;
	int  StkBizAction;
	char Symbol[12];
	
};

struct COXOrderFilledField
{
	char  CuacctCode[16];
	char  Symbol[12];
	char  ExchangeId;
	char  BoardId[4];
	int   StkBiz;
	int   StkBizAction;
	char  TradeSn[24];
	unsigned   OrderNo;
	char  OrderId[12];
	char  CliOrderNo[32 + 1];
	char  FilledType;
	int64 FilledQty;
	char  FilledPrice[16];
	unsigned   FilledDate;
	char  FilledTime[12];
	char  RetMessage[128];	

};

struct COXRtnOrderTicket
{
	COXReqOrderTicketField stOrderTicketReq;

	unsigned  OrderDate;
	char OrderTime[36];
	unsigned  OrderNo;
	OXOrderExeStatus ExeStatus;
	char ExeInfo[128];
	int64  FilledQty;
	int64  CanceledQty;
	char FilledAmt[24];
	
};


struct COXRspCreditTargetStocksField
{
	char   QryPos[36];      //定位串        
	char   ExchangeId;      //证券交易所    
	char   BoardId[4];      //交易板块      
	char   Symbol[12];      //证券代码      
	char   StkName[24];     //证券名称      
	double FIMarginRatio;   //融资保证金比例  
    double SLMarginRatio;   //融券保证金比例
	char   CurrEnableFI;    //当日融资标志  
	char   CurrEnableSL;    //当日融券标志  

};

struct COXRspCreditCollatalStocksField
{
	char   QryPos[36];      //定位串        
	char   ExchangeId;      //证券交易所    
	char   BoardId[4];      //交易板块      
	char   Symbol[12];      //证券代码      
	char   StkName[24];     //证券名称      
	double CollatRatio;     //担保品折算率  

};

struct COXRspCreditBalanceDebtField
{
	char   CustCode[16];       //客户代码        
	char   CuacctCode[16];     //资产账户        
	char   Currency;           //货币代码        
	double FIRate;             //融资利率        
	double SLRate;             //融券利率        
	double FreeIntRate;        //罚息利率        
	char   CreditStatus;       //信用状态        
	double MarginRate;         //维持担保比例    
	double RealRate;           //实时担保比例    
	double TotalAssert;        //总资产          
	double TotalDebts;         //总负债          
	double MarginValue;        //保证金可用余额  
	double FundAvl;            //资金可用金额    
	double FundBln;            //资金余额        
	double SlAmt;              //融券卖出所得资金
	double GuaranteOut;        //可转出担保资产  
	double ColMktVal;          //担保证券市值    
	double FiAmt;              //融资本金        
	double TotalFiFee;         //融资息费        
	double FiTotalDebts;       //融资负债合计    
	double SlMktVal;           //应付融券市值    
	double TotalSlFee;         //融券息费        
	double SLTotalDebts;       //融券负债合计    
	double FICredit;           //融资授信额度    
	double FICreditAvl;        //融资可用额度    
	double FICreditFrz;        //融资额度冻结    
	double SLCredit;           //融券授信额度    
	double SLCreditAvl;        //融券可用额度    
	double SLCreditFrz;        //融券额度冻结    
	double Rights;             //红利权益        
	double RightsUncomer;      //红利权益（在途）
	int64  RightsQty;          //红股权益        
	int64  RightsQtyUncomer;   //红股权益（在途）  
	double TotalCredit;        //总额度          
	double TotalCteditAvl;     //总可用额度      

};

struct COXRspCreditContractField
{
	char    QryPos[36]         ;     //定位串              
	char    CashNo[16]         ;     //头寸编号            
	int     TrdDate            ;     //交易日期            
	char    ContractType       ;     //合约类型            
	char    Trdacct[12]        ;     //交易账户            
	char    ExchangeId         ;     //交易市场            
	char    BoardId[4]         ;     //交易板块            
	int     OpeningDate        ;     //开仓日期            
	char    Symbol[12]         ;     //证券代码            
	char    OrderId[12]        ;     //合同序号            
	double  FIDebtsAmt         ;     //融资负债金额        
	int64   SLDebtsQty         ;     //融券负债数量        
	int64   RepaidQty          ;     //融券已还数量        
	double  RepaidAmt          ;     //融资已还金额        
	char    ContractStatus     ;     //合约状态            
	int     ContractExpireDate ;     //合约到期日          
	double  MarginRatio        ;     //保证金比例          
	double  MarginAmt          ;     //占用保证金          
	double  Rights             ;     //未偿还权益金额      
	int64   RightsQty          ;     //未偿还权益数量      
	double  OverdueFee         ;     //逾期未偿还息费      
	int     LastRepayDate      ;     //最后偿还日期        
	char    CustCode[16]       ;     //客户代码            
	char    CuacctCode[16]     ;     //资产账户            
	char    Currency           ;     //货币代码            
	int     IntOrg             ;     //内部机构            
	double  OrderPrice         ;     //委托价格            
	int64   OrderQty           ;     //委托数量            
	double  OrderAmt           ;     //委托金额            
	double  OrderFrzAmt        ;     //委托冻结金额        
	int64   WithdrawnQty       ;     //已撤单数量          
	int64   MatchedQty         ;     //成交数量            
	double  MatchedAmt         ;     //成交金额            
	double  RltSettAmt         ;     //实时清算金额        
	double  SLDebtsMktvalue    ;     //融券负债市值        
	int64   RltRepaidQty       ;     //融券实时归还数量    
	double  RltRepaidAmt       ;     //融资实时归还金额    
	double  MatchedAmtRepay    ;     //还成交金额          
	int     CalIntDate         ;     //开始计息日期        
	double  ContractInt        ;     //合约利息            
	double  ContractIntAccrual ;     //利息积数            
	double  OverRights         ;     //逾期未偿还权益      
	double  RightsRepay        ;     //己偿还权益          
	double  RightsRlt          ;     //实时偿还权益        
	double  OverRightsRlt      ;     //实时偿还预期权益    
	int64   OverRightsQty      ;     //逾期未偿还权益数量  
	int64   RightsQtyRepay     ;     //已偿还权益数量      
	int64   RightsQtyRlt       ;     //实时偿还权益数量    
	int64   OverRightsQtyRlt   ;     //实时偿还逾期权益数量
	double  ContractFee        ;     //融资融券息费        
	double  FeeRepay           ;     //己偿还息费          
	double  FeeRlt             ;     //实时偿还息费        
	double  OverDuefeeRlt      ;     //实时偿还逾期息费    
	double  PuniDebts          ;     //逾期本金罚息        
	double  PuniDebtsRepay     ;     //本金罚息偿还        
	double  PuniDebtsRlt       ;     //实时逾期本金罚息    
	double  PuniFee            ;     //利息产生的罚息      
	double  PuniFeeRepay       ;     //己偿还罚息          
	double  PuniFeeRlt         ;     //实时逾期息费罚息    
	double  PuniRights         ;     //逾期权益罚息        
	double  PuniRightsRepay    ;     //权益罚息偿还        
	double  PuniRightsRlt      ;     //实时逾期权益罚息    
	int     ClosingDate        ;     //合约了结日期        
	double  ClosingPrice       ;     //合约了结价格        
	int     OpOrg              ;     //操作机构            
	char    ContractCls        ;     //合约类别  
	double  ProIncome          ;     //参考盈亏  
	double  PledgeCuacct       ;     //抵押资产  
	double  FIRepayAmt         ;     //融资偿还  
	int64   SLRepayQty         ;     //融券偿还  
          
};


struct COXRspCreditSecuLendQuotaField
{
	char   CashNo[16];      //头寸编号
	char   BoardId[4];      //交易板块      
	char   Symbol[12];      //证券代码         
	int64  AssetBln;        //头寸总额度  
	int64  AssetAvl;        //头寸可用额度  

};

struct COXRspCreditReimbursibleBalField
{
	char   CuacctCode[16];   //资产账户
	
	double FITotalDebts;     //融资负债合计
	double TotalSLFee;       //融券息费
	
    double CanRepayAmt;      //可偿还金额
	double Mayrepay;         //偿还可用金额
};

#pragma pack()
#endif