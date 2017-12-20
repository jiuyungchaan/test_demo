#ifndef _GUOSEN_OX_API_TYPE_H
#define _GUOSEN_OX_API_TYPE_H

enum OXAccountType
{
	OX_ACCOUNT_STOCK	= '0',				//现货
	OX_ACCOUNT_OPTION	= '1',				//期权
	OX_ACCOUNT_FUTURE   = '2',				//期货
	OX_ACCOUNT_MARGIN	= '3'				//信用
};


enum OXOrderExeStatus
{
	ORDER_STATE_INACTIVE    		= '0'  ,       // 未报                                                              
	ORDER_STATE_ACTIVE      		= 'A'  ,       // 待报 激活 比如条件还没有满足                                                              
	ORDER_STATE_DOING       		= '1'  ,       // 正报 比如条件已满足，正报还没有收到应答                                                               
	ORDER_STATE_SEND        		= '2'  ,       // 已报                                                                
	ORDER_STATE_CANCELING   		= '3'  ,       // 正撤                                                                                                                          
	ORDER_STATE_PARTIAL_CANCELING	= '4'  ,       // 部成待撤                                                            
	ORDER_STATE_PARTIAL_CANCELED	= '5'  ,       // 部成部撤
	ORDER_STATE_CANCELED      		= '6'  ,       // 已撤                                                                                                                          
	ORDER_STATE_PARTIAL_FILLED		= '7'  ,       // 部分成交                                                            
	ORDER_STATE_FILLED        		= '8'  ,       // 已成交                                                              
	ORDER_STATE_REJECTED			= '9'          // 废单                                                                

};


/************* added by rongcan ************/
/// Exchange
#define OX_EXCHANGE_SZ '0'
#define OX_EXCHANGE_SH '1'

/// Trade Account Type
#define OX_TRDACCTTYPE_PSN_CASH '0'
#define OX_TRDACCTTYPE_AGC_CASH '1'
#define OX_TRDACCTTYPE_PSN_MARGIN '2'
#define OX_TRDACCTTYPE_AGC_MARGIN '3'

/// BoardID 
#define OX_BOARD_SZA "00"
#define OX_BOARD_SZB "01"
#define OX_BOARD_XSB "02"
#define OX_BOARD_SHA "10"
#define OX_BOARD_SHB "11"

/// StkBiz (Direction)
#define OX_BIZ_BUY 100
#define OX_BIZ_SELL 101
#define OX_BIZ_COLLATERALBUY 700
#define OX_BIZ_COLLATERALSELL 701
#define OX_BIZ_BORROWTOBUY 702
#define OX_BIZ_BORROWTOSELL 703
#define OX_BIZ_BUYTOPAY 704
#define OX_BIZ_SELLTOPAY 705
#define OX_BIZ_PAYBYSTOCK 710
#define OX_BIZ_PAYBYCASH 712

/// StkBizAction (Order Type)
#define OX_BUZACTION_LIMIT 100
#define OX_BUZACTION_MARKETLIMIT 120
#define OX_BUZACTION_MARKET 121
#define OX_BUZACTION_FOK 122
#define OX_BUZACTION_FAK 125


#endif