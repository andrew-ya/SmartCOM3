
#ifndef SMARTCOM3ENUMS_H_
#define SMARTCOM3ENUMS_H_

#include <string>
#include <time.h>

namespace SmartCOM3
{
	typedef enum
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
	} OrderState;

	inline const char *GetOrderStateString(OrderState code)
	{
		switch (code)
		{
		case OrderState_ContragentReject: return "ContragentReject";
		case OrderState_Submited: return "Submited";
		case OrderState_Pending: return "Pending";
		case OrderState_Open: return "Open";
		case OrderState_Expired: return "Expired";
		case OrderState_Cancel: return "Cancel";
		case OrderState_Filled: return "Filled";
		case OrderState_Partial: return "Partial";
		case OrderState_ContragentCancel: return "ContragentCancel";
		case OrderState_SystemReject: return "SystemReject";
		case OrderState_SystemCancel: return "SystemCancel";
		}
		return "Unknown OrderState";
	}

	typedef enum
	{
		OrderAction_NoAction = 0,
		OrderAction_Buy = 1,
		OrderAction_Sell = 2,
		OrderAction_Short = 3,
		OrderAction_Cover = 4
	} OrderAction;

	inline const char *GetOrderActionString(OrderAction code)
	{
		switch (code)
		{
		case OrderAction_NoAction: return "NoAction";
		case OrderAction_Buy: return "Buy";
		case OrderAction_Sell: return "Sell";
		case OrderAction_Short: return "Short";
		case OrderAction_Cover: return "Cover";
		}
		return "Unknown OrderAction";
	}

	typedef enum
	{
		OrderType_Market = 1,
		OrderType_Limit = 2,
		OrderType_Stop = 3,
		OrderType_StopLimit = 4
	} OrderType;

	inline const char *GetOrderTypeString(OrderType code)
	{
		switch (code)
		{
		case OrderType_Market: return "Market";
		case OrderType_Limit: return "Limit";
		case OrderType_Stop: return "Stop";
		case OrderType_StopLimit: return "StopLimit";
		}
		return "Unknown OrderType";
	}

	typedef enum
	{
		OrderValidity_Day = 1,
		OrderValidity_Gtc = 2
	} OrderValidity;

	inline const char *GetOrderValidityString(OrderValidity code)
	{
		switch (code)
		{
		case OrderValidity_Day: return "Day";
		case OrderValidity_Gtc: return "Gtc";
		}
		return "Unknown OrderValidity";
	}

	typedef enum
	{
		BarInterval_Tick = 0,
		BarInterval_1Min = 1,
		BarInterval_5Min = 2,
		BarInterval_10Min = 3,
		BarInterval_15Min = 4,
		BarInterval_30Min = 5,
		BarInterval_1Hour = 6,
		BarInterval_2Hour = 7,
		BarInterval_4Hour = 8,
		BarInterval_Day = 9,
		BarInterval_Week = 10,
		BarInterval_Month = 11,
		BarInterval_Quarter = 12,
		BarInterval_Year = 13
	} BarInterval;

	inline const char *GetBarIntervalString(BarInterval code)
	{
		switch (code)
		{
		case BarInterval_Tick:  return " Tick";
		case BarInterval_1Min:  return " 1Min";
		case BarInterval_5Min:  return " 5Min";
		case BarInterval_10Min: return "10Min";
		case BarInterval_15Min: return "15Min";
		case BarInterval_30Min: return "30Min";
		case BarInterval_1Hour: return "1Hour";
		case BarInterval_2Hour: return "2Hour";
		case BarInterval_4Hour: return "4Hour";
		case BarInterval_Day:   return "1Day ";
		case BarInterval_Week:  return "Week ";
		case BarInterval_Month: return "Month";
		case BarInterval_Quarter:return "Quarter";
		case BarInterval_Year:  return "Year ";
		}
		return "Unknown BarInterval";
	}

	typedef enum
	{
		PortfolioStatus_Broker = 0,
		PortfolioStatus_TrustedManagement = 1,
		PortfolioStatus_ReadOnly = 2,
		PortfolioStatus_Blocked = 3,
		PortfolioStatus_Restricted = 4,
		PortfolioStatus_AutoRestricted = 5,
		PortfolioStatus_OrderNotSigned = 6
	} PortfolioStatus;

	inline const char *GetPortfolioStatusString(PortfolioStatus code)
	{
		switch (code)
		{
		case PortfolioStatus_Broker: return "Broker";
		case PortfolioStatus_TrustedManagement: return "TrustedManagement";
		case PortfolioStatus_ReadOnly: return "ReadOnly";
		case PortfolioStatus_Blocked: return "Blocked";
		case PortfolioStatus_Restricted: return "Restricted";
		case PortfolioStatus_AutoRestricted: return "AutoRestricted";
		case PortfolioStatus_OrderNotSigned: return "OrderNotSigned";
		}
		return "Unknown PortfolioStatus";
	}

	typedef enum
	{
		ErrorCode_Success = 0,
		ErrorCode_SecurityNotFound = -1610612735,
		ErrorCode_PortfolioNotFound = -1610612734,
		ErrorCode_NotConnected = -1610612733,
		ErrorCode_BadParameters = -1610612732,
		ErrorCode_InternalError = -1610612731,
		ErrorCode_ExchangeNotAccessible = -1610612730
	} ErrorCode;

	inline const char *GetErrorCodeString(ErrorCode code)
	{
		switch (code)
		{
		case ErrorCode_Success: return "Success";
		case ErrorCode_SecurityNotFound: return "SecurityNotFound";
		case ErrorCode_PortfolioNotFound: return "PortfolioNotFound";
		case ErrorCode_NotConnected: return "NotConnected";
		case ErrorCode_BadParameters: return "BadParameters";
		case ErrorCode_InternalError: return "InternalError";
		case ErrorCode_ExchangeNotAccessible: return "ExchangeNotAccessible";
		}
		return "UnknownErrorCode";
	}

	/* Date & time string */
	inline std::string GetDatetimeString(time_t datetime)
	{
#if defined(WIN32) && !defined(__WINE__)
		struct tm tstruct;
		localtime_s(&tstruct, &datetime);
#else
		struct tm tstruct = *localtime(&datetime);
#endif
	    char buf[20];
	    strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &tstruct);
	    return buf;
	}
}

#endif
