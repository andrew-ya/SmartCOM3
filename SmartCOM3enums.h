
#ifndef SMARTCOM3ENUMS_H_
#define SMARTCOM3ENUMS_H_

namespace SmartCOM3
{
	enum OrderState
	{
		OrderState_ContragentReject = -1,
		OrderState_Submited = 0,
		OrderState_Pending = 1,
		OrderState_Open = 2,
		OrderState_Expired = 3,
		OrderState_Cancel = 4,
		OrderState_Filled = 5,
		OrderState_Partial = 6,
		OrderState_ContragentCancel = 7,
		OrderState_SystemReject = 8,
		OrderState_SystemCancel = 9
	};
	const char *GetOrderStateString(OrderState code);
	enum OrderAction
	{
		OrderAction_Buy = 1,
		OrderAction_Sell = 2,
		OrderAction_Short = 3,
		OrderAction_Cover = 4
	};
	const char *GetOrderActionString(OrderAction code);
	enum OrderType
	{
		OrderType_Market = 1,
		OrderType_Limit = 2,
		OrderType_Stop = 3,
		OrderType_StopLimit = 4
	};
	const char *GetOrderTypeString(OrderType code);
	enum OrderValidity
	{
		OrderValidity_Day = 1,
		OrderValidity_Gtc = 2
	};
	const char *GetOrderValidityString(OrderValidity code);
	enum BarInterval
	{
		BarInterval_Tick = 0,
		BarInterval_1Min = 1,
		BarInterval_5Min = 2,
		BarInterval_10Min = 3,
		BarInterval_15Min = 4,
		BarInterval_30Min = 5,
		BarInterval_60Min = 6,
		BarInterval_2Hour = 7,
		BarInterval_4Hour = 8,
		BarInterval_Day = 9,
		BarInterval_Week = 10,
		BarInterval_Month = 11,
		BarInterval_Quarter = 12,
		BarInterval_Year = 13
	};
	const char *GetBarIntervalString(BarInterval code);
	enum PortfolioStatus
	{
		PortfolioStatus_Broker = 0,
		PortfolioStatus_TrustedManagement = 1,
		PortfolioStatus_ReadOnly = 2,
		PortfolioStatus_Blocked = 3,
		PortfolioStatus_Restricted = 4,
		PortfolioStatus_AutoRestricted = 5,
		PortfolioStatus_OrderNotSigned = 6
	};
	const char *GetPortfolioStatusString(PortfolioStatus code);
	enum ErrorCode
	{
		ErrorCode_SecurityNotFound = -1610612735,
		ErrorCode_PortfolioNotFound = -1610612734,
		ErrorCode_NotConnected = -1610612733,
		ErrorCode_BadParameters = -1610612732,
		ErrorCode_InternalError = -1610612731,
		ErrorCode_ExchangeNotAccessible = -1610612730
	};
	const char *GetErrorCodeString(ErrorCode code);
}

#endif