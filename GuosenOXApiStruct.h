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
	char Account[16];          //�ʽ��˺�
};


struct COXReqTradeAcctField
{
	char Account[16];          //�ʽ��˺�
};

struct COXReqOrdersField
{
	OXAccountType	AcctType;	//�˻�����(����)
	char Account[16];			//�ʽ��˺�(����)
	char ExchangeId;			//�����г�
	char BoardId[4];			//���װ��	
	char Symbol[12];			//����
	int  OrderNo;				//ί�б��
	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
	char QueryFlag[2];			// "1" �ɳ���

};

struct COXReqBalanceField
{
	OXAccountType	AcctType;	//�˻�����(����)
	char Account[16];			//�ʽ��˺�(����)
};

struct COXReqPositionField
{
	OXAccountType	AcctType;	//�˻�����(����)
	char Account[16];			//�ʽ��˺�(����)
	char ExchangeId;			//�����г�
	char BoardId[4];			//���װ��	
	char Symbol[12];			//����
	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
};

struct COXReqFilledDetailField
{
	OXAccountType	AcctType;	//�˻�����(����)
	char Account[16];			//�ʽ��˺�(����)
	
	char BoardId[4];			//���װ��	
	char Symbol[12];			//����
	int  OrderNo;				//ί�б��
	int  OrderBsn;				//ί������
	char TrdAcct[16];			//֤ȯ�˻�

	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
};


struct COXReqOrderTicketField
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
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
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
	char BoradId[4];			//���װ��
	unsigned  OrderDate;		//ί������
	unsigned  OrderNo;			//ί�б��

};


struct COXReqCreditTargetStocks
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
	
	char ExchangeId;            //�����г�
	char BoardId[4];			//���װ��
	char Symbol[12];			//����
	char CurrEnableFI;			//��������
	char CurrEnableSL;			//������ȯ

	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
};

struct COXReqCreditCollateralsStocks
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)

	char ExchangeId;            //�����г�
	char BoardId[4];			//���װ��
	char Symbol[12];			//����
	
	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
};

struct COXReqCreditBalanceDebt  
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
	char Currency;              //���Ҵ���	
};


struct COXReqCreditContracts
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)

	int  BgnDate;               //��ʼ����
	int  EndDate;               //��������
	char OrderId[12];           //��ͬ���
	char ContractType;          //��Լ����
	
	char CustCode[16];          //�ͻ�����
	char ExchangeId;            //�����г�
	char BoardId[4];			//���װ��

	char Trdacct[12];            //�����˻�
	char Symbol[12];            //֤ȯ����
	int  IntOrg;                //�ڲ�����
	int  OpOrg;                 //��������
	char ContractStatus;        //��Լ״̬
	char RepayFlag;              //ƽ��״̬

	char QueryPos[36];			//��λ��
	unsigned QueryNum;			//��ѯ���� ���1000
};

struct COXReqCreditSecuLendQuota
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
	char CashNo[16];			//ͷ����(����)
};

struct COXReqCreditReimbursibleBalance
{
	OXAccountType	AcctType;	//�˻�����(����)
	char CuacctCode[16];		//�ʽ��˺�(����)
};


struct COXRspTradeAcctField
{
	char CustCode[16];		//�ͻ�����
	char CuacctCode[16];    //�ʽ��˺�
	char ExchangeId;		//�����г�
	char BoardId[4];		//���װ��
	char TrdAcctStatus;		//�˻�״̬
	char TrdAcct[16];		//֤ȯ�˻�
	char TrdAcctType;		//�����˻����
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
	char	Currency;			// ����
	char    AccountWorth[24];	//�ʲ���ֵ
	char	FundValue[24];		//�ʽ��ʲ�
	char    MarketValue[24];	//��ֵ

	char    FundPreBalance[24];//�ʽ��������
	char    FundBalance[24];	//�ʽ����
	char    Avaiable[24];		//�ʽ���ý��
};

struct COXRspPositionField
{
	char  QryPos[36];		    //��λ��              
	int   IntOrg;		        //�ڲ�����            
	char  CustCode[16];		    //�ͻ�����            
	char  CuacctCode[16];		//�ʲ��˻�            
	char  Stkbd[4];		        //���װ��            
	char  Stkpbu[8];		    //���׵�Ԫ            
	char  Currency;		        //���Ҵ���            
	char  StkCode[12];		    //֤ȯ����            
	char  StkName[16];		    //֤ȯ����            
	char  StkCls[2];		    //֤ȯ���            
	char  StkPrebln[16];		//֤ȯ�������        
	int64 StkBln;		        //֤ȯ���            
	int64 StkAvl;		        //֤ȯ��������        
	int64 StkFrz;		        //֤ȯ��������        
	int64 StkUfz;		        //֤ȯ�ⶳ����        
	int64 StkTrdFrz;		    //֤ȯ���׶�������    
	int64 StkTrdUfz;		    //֤ȯ���׽ⶳ����    
	int64 StkTrdOtd;		    //֤ȯ������;����    
	char  StkBcost[24];		    //֤ȯ����ɱ�        
	char  StkBcostRlt[24];	    //֤ȯ����ɱ���ʵʱ��
	char  StkPlamt[24];		    //֤ȯӯ�����        
	char  StkPlamtRlt[24];		//֤ȯӯ����ʵʱ��
	char  MktVal[24];		    //��ֵ                
	char  CostPrice[24];		//�ɱ��۸�            
	char  ProIncome[24];		 //�ο�ӯ��            
	char  StkCalMktvale[2];		//��ֵ�����ʶ        
	int64 StkQty[16];		    //��ǰӵ����          
	char  CurrentPrice[16];		//���¼۸�            
	char  ProfitPrice[16];		//�ο��ɱ���          
	int64 StkDiff;		        //����������          
	int64 StkTrdUnfrz;		    //����������          
	char  Trdacct[16];		    //�����˻�            
	char  Income[16];		    //ӯ��                
	int64 StkRemain;		    //��ȯ��������        
	char  AveragePrice[16];		//�������            
};

struct COXRspFilledDetailField
{
	char      QryPos[36];         //��λ��
	char      CuacctCode[16];	  //�ʲ��˻�
	char      CustCode[16];       //�ͻ�����
	char      Trdacct[16];        //�����˻�
	unsigned  OrderDate;          //ί������
	unsigned  OrderNo;            //ί�к�
	char      OrderId[12];        //��ͬ���
	
	char      ExchangeId;		  //������
	char      BoardId[4];         //���װ��
	char      Symbol[12];         //֤ȯ����
	int       StkBiz;             //����ҵ��
	int       StkBizAction;       //ҵ��
	
	char      FilledType;         //�ɽ�����
	char      TradeSn[24];        //�ɽ����
	int64     FilledQty;          //�ɽ�����
	char      FilledPrice[16];    //�ɽ��۸�
	unsigned  FilledDate;         //�ɽ�����
	char      FilledTime[12];     //�ɽ�ʱ��
	
	int       ErrId;			  //����ID
	char      ErrMessage[128];	  //������Ϣ

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
	char   QryPos[36];      //��λ��        
	char   ExchangeId;      //֤ȯ������    
	char   BoardId[4];      //���װ��      
	char   Symbol[12];      //֤ȯ����      
	char   StkName[24];     //֤ȯ����      
	double FIMarginRatio;   //���ʱ�֤�����  
    double SLMarginRatio;   //��ȯ��֤�����
	char   CurrEnableFI;    //�������ʱ�־  
	char   CurrEnableSL;    //������ȯ��־  

};

struct COXRspCreditCollatalStocksField
{
	char   QryPos[36];      //��λ��        
	char   ExchangeId;      //֤ȯ������    
	char   BoardId[4];      //���װ��      
	char   Symbol[12];      //֤ȯ����      
	char   StkName[24];     //֤ȯ����      
	double CollatRatio;     //����Ʒ������  

};

struct COXRspCreditBalanceDebtField
{
	char   CustCode[16];       //�ͻ�����        
	char   CuacctCode[16];     //�ʲ��˻�        
	char   Currency;           //���Ҵ���        
	double FIRate;             //��������        
	double SLRate;             //��ȯ����        
	double FreeIntRate;        //��Ϣ����        
	char   CreditStatus;       //����״̬        
	double MarginRate;         //ά�ֵ�������    
	double RealRate;           //ʵʱ��������    
	double TotalAssert;        //���ʲ�          
	double TotalDebts;         //�ܸ�ծ          
	double MarginValue;        //��֤��������  
	double FundAvl;            //�ʽ���ý��    
	double FundBln;            //�ʽ����        
	double SlAmt;              //��ȯ���������ʽ�
	double GuaranteOut;        //��ת�������ʲ�  
	double ColMktVal;          //����֤ȯ��ֵ    
	double FiAmt;              //���ʱ���        
	double TotalFiFee;         //����Ϣ��        
	double FiTotalDebts;       //���ʸ�ծ�ϼ�    
	double SlMktVal;           //Ӧ����ȯ��ֵ    
	double TotalSlFee;         //��ȯϢ��        
	double SLTotalDebts;       //��ȯ��ծ�ϼ�    
	double FICredit;           //�������Ŷ��    
	double FICreditAvl;        //���ʿ��ö��    
	double FICreditFrz;        //���ʶ�ȶ���    
	double SLCredit;           //��ȯ���Ŷ��    
	double SLCreditAvl;        //��ȯ���ö��    
	double SLCreditFrz;        //��ȯ��ȶ���    
	double Rights;             //����Ȩ��        
	double RightsUncomer;      //����Ȩ�棨��;��
	int64  RightsQty;          //���Ȩ��        
	int64  RightsQtyUncomer;   //���Ȩ�棨��;��  
	double TotalCredit;        //�ܶ��          
	double TotalCteditAvl;     //�ܿ��ö��      

};

struct COXRspCreditContractField
{
	char    QryPos[36]         ;     //��λ��              
	char    CashNo[16]         ;     //ͷ����            
	int     TrdDate            ;     //��������            
	char    ContractType       ;     //��Լ����            
	char    Trdacct[12]        ;     //�����˻�            
	char    ExchangeId         ;     //�����г�            
	char    BoardId[4]         ;     //���װ��            
	int     OpeningDate        ;     //��������            
	char    Symbol[12]         ;     //֤ȯ����            
	char    OrderId[12]        ;     //��ͬ���            
	double  FIDebtsAmt         ;     //���ʸ�ծ���        
	int64   SLDebtsQty         ;     //��ȯ��ծ����        
	int64   RepaidQty          ;     //��ȯ�ѻ�����        
	double  RepaidAmt          ;     //�����ѻ����        
	char    ContractStatus     ;     //��Լ״̬            
	int     ContractExpireDate ;     //��Լ������          
	double  MarginRatio        ;     //��֤�����          
	double  MarginAmt          ;     //ռ�ñ�֤��          
	double  Rights             ;     //δ����Ȩ����      
	int64   RightsQty          ;     //δ����Ȩ������      
	double  OverdueFee         ;     //����δ����Ϣ��      
	int     LastRepayDate      ;     //��󳥻�����        
	char    CustCode[16]       ;     //�ͻ�����            
	char    CuacctCode[16]     ;     //�ʲ��˻�            
	char    Currency           ;     //���Ҵ���            
	int     IntOrg             ;     //�ڲ�����            
	double  OrderPrice         ;     //ί�м۸�            
	int64   OrderQty           ;     //ί������            
	double  OrderAmt           ;     //ί�н��            
	double  OrderFrzAmt        ;     //ί�ж�����        
	int64   WithdrawnQty       ;     //�ѳ�������          
	int64   MatchedQty         ;     //�ɽ�����            
	double  MatchedAmt         ;     //�ɽ����            
	double  RltSettAmt         ;     //ʵʱ������        
	double  SLDebtsMktvalue    ;     //��ȯ��ծ��ֵ        
	int64   RltRepaidQty       ;     //��ȯʵʱ�黹����    
	double  RltRepaidAmt       ;     //����ʵʱ�黹���    
	double  MatchedAmtRepay    ;     //���ɽ����          
	int     CalIntDate         ;     //��ʼ��Ϣ����        
	double  ContractInt        ;     //��Լ��Ϣ            
	double  ContractIntAccrual ;     //��Ϣ����            
	double  OverRights         ;     //����δ����Ȩ��      
	double  RightsRepay        ;     //������Ȩ��          
	double  RightsRlt          ;     //ʵʱ����Ȩ��        
	double  OverRightsRlt      ;     //ʵʱ����Ԥ��Ȩ��    
	int64   OverRightsQty      ;     //����δ����Ȩ������  
	int64   RightsQtyRepay     ;     //�ѳ���Ȩ������      
	int64   RightsQtyRlt       ;     //ʵʱ����Ȩ������    
	int64   OverRightsQtyRlt   ;     //ʵʱ��������Ȩ������
	double  ContractFee        ;     //������ȯϢ��        
	double  FeeRepay           ;     //������Ϣ��          
	double  FeeRlt             ;     //ʵʱ����Ϣ��        
	double  OverDuefeeRlt      ;     //ʵʱ��������Ϣ��    
	double  PuniDebts          ;     //���ڱ���Ϣ        
	double  PuniDebtsRepay     ;     //����Ϣ����        
	double  PuniDebtsRlt       ;     //ʵʱ���ڱ���Ϣ    
	double  PuniFee            ;     //��Ϣ�����ķ�Ϣ      
	double  PuniFeeRepay       ;     //��������Ϣ          
	double  PuniFeeRlt         ;     //ʵʱ����Ϣ�ѷ�Ϣ    
	double  PuniRights         ;     //����Ȩ�淣Ϣ        
	double  PuniRightsRepay    ;     //Ȩ�淣Ϣ����        
	double  PuniRightsRlt      ;     //ʵʱ����Ȩ�淣Ϣ    
	int     ClosingDate        ;     //��Լ�˽�����        
	double  ClosingPrice       ;     //��Լ�˽�۸�        
	int     OpOrg              ;     //��������            
	char    ContractCls        ;     //��Լ���  
	double  ProIncome          ;     //�ο�ӯ��  
	double  PledgeCuacct       ;     //��Ѻ�ʲ�  
	double  FIRepayAmt         ;     //���ʳ���  
	int64   SLRepayQty         ;     //��ȯ����  
          
};


struct COXRspCreditSecuLendQuotaField
{
	char   CashNo[16];      //ͷ����
	char   BoardId[4];      //���װ��      
	char   Symbol[12];      //֤ȯ����         
	int64  AssetBln;        //ͷ���ܶ��  
	int64  AssetAvl;        //ͷ����ö��  

};

struct COXRspCreditReimbursibleBalField
{
	char   CuacctCode[16];   //�ʲ��˻�
	
	double FITotalDebts;     //���ʸ�ծ�ϼ�
	double TotalSLFee;       //��ȯϢ��
	
    double CanRepayAmt;      //�ɳ������
	double Mayrepay;         //�������ý��
};

#pragma pack()
#endif