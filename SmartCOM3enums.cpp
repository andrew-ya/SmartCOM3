
#include "SmartCOM3enums.h"

namespace SmartCOM3
{
	const char *GetOrderStateString(OrderState code)
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
	const char *GetOrderActionString(OrderAction code)
	{
		switch (code)
		{
		case OrderAction_Buy: return "Buy";
		case OrderAction_Sell: return "Sell";
		case OrderAction_Short: return "Short";
		case OrderAction_Cover: return "Cover";
		}
		return "Unknown OrderAction";
	}
	const char *GetOrderTypeString(OrderType code)
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
	const char *GetOrderValidityString(OrderValidity code)
	{
		switch (code)
		{
		case OrderValidity_Day: return "Day";
		case OrderValidity_Gtc: return "Gtc";
		}
		return "Unknown OrderValidity";
	}
	const char *GetBarIntervalString(BarInterval code)
	{
		switch (code)
		{
		case BarInterval_Tick: return "Tick";
		case BarInterval_1Min: return "1Min";
		case BarInterval_5Min: return "5Min";
		case BarInterval_10Min: return "10Min";
		case BarInterval_15Min: return "15Min";
		case BarInterval_30Min: return "30Min";
		case BarInterval_60Min: return "60Min";
		case BarInterval_2Hour: return "2Hour";
		case BarInterval_4Hour: return "4Hour";
		case BarInterval_Day: return "Day";
		case BarInterval_Week: return "Week";
		case BarInterval_Month: return "Month";
		case BarInterval_Quarter: return "Quarter";
		case BarInterval_Year: return "Year";
		}
		return "Unknown BarInterval";
	}
	const char *GetPortfolioStatusString(PortfolioStatus code)
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
	const char *GetErrorCodeString(ErrorCode code)
	{
		switch (code)
		{
		case ErrorCode_SecurityNotFound: return "SecurityNotFound";
		case ErrorCode_PortfolioNotFound: return "PortfolioNotFound";
		case ErrorCode_NotConnected: return "NotConnected";
		case ErrorCode_BadParameters: return "BadParameters";
		case ErrorCode_InternalError: return "InternalError";
		case ErrorCode_ExchangeNotAccessible: return "ExchangeNotAccessible";
		}
		return "Unknown ErrorCode";
	}
}