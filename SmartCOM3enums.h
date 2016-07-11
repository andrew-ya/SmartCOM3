
#ifndef SMARTCOM3_SMARTCOM3ENUMS_H_
#define SMARTCOM3_SMARTCOM3ENUMS_H_

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
		OrderState_SystemCancel = 9,
		OrderState_PlaceDelivered, // extended state: delivered to broker server
		OrderState_PlaceNotDelivered, // extended order state: NOT delivered to broker server
		OrderState_MoveDelivered, // extended state: delivered to broker server
		OrderState_MoveNotDelivered, // extended order state: NOT delivered to broker server
		OrderState_CancelDelivered, // extended state: delivered to broker server
		OrderState_CancelNotDelivered, // extended order state: NOT delivered to broker server
	} OrderState;

	inline const char *GetOrderStateString(OrderState code)
	{
		switch (code)
		{
		case OrderState_ContragentReject: return "ContragentRejected";
		case OrderState_Submited: return "Submited";
		case OrderState_Pending: return "Pending";
		case OrderState_Open: return "Opened";
		case OrderState_Expired: return "Expired";
		case OrderState_Cancel: return "Canceled";
		case OrderState_Filled: return "Filled";
		case OrderState_Partial: return "FilledPartial";
		case OrderState_ContragentCancel: return "ContragentCanceled";
		case OrderState_SystemReject: return "SystemRejected";
		case OrderState_SystemCancel: return "SystemCanceled";
		case OrderState_PlaceDelivered: return "PlaceDelivered";
		case OrderState_PlaceNotDelivered: return "PlaceNotDelivered";
		case OrderState_MoveDelivered: return "MoveDelivered";
		case OrderState_MoveNotDelivered: return "MoveNotDelivered";
		case OrderState_CancelDelivered: return "CancelDelivered";
		case OrderState_CancelNotDelivered: return "CancelNotDelivered";
		default: return "UnknownOrderState";
		}
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
		default: return "UnknownOrderAction";
		}
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
		default: return "UnknownOrderType";
		}
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
		default: return "UnknownOrderValidity";
		}
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
		default: return "UnknownPortfolioStatus";
		}
	}

	typedef enum
	{
		TradingStatus_Tradable = 0,
		TradingStatus_NonTradable = 1
	} TradingStatus;

	inline const char *GetTradingStatusString(TradingStatus code)
	{
		switch (code)
		{
		case TradingStatus_Tradable: return "Tradable";
		case TradingStatus_NonTradable: return "NonTradable";
		default: return "UnknownTradingStatus";
		}
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
		default: return "UnknownErrorCode";
		}
	}

	typedef enum
	{
		BarInterval_NoInterval = -6, // warning: extended time frame, GetBars will fail
		BarInterval_1Sec =  -5, // warning: extended time frame, GetBars will fail
		BarInterval_5Sec =  -4, // warning: extended time frame, GetBars will fail
		BarInterval_10Sec = -3, // warning: extended time frame, GetBars will fail
		BarInterval_15Sec = -2, // warning: extended time frame, GetBars will fail
		BarInterval_30Sec = -1, // warning: extended time frame, GetBars will fail
		BarInterval_Tick = 0, // warning: extended time frame, GetBars will fail
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
		BarInterval_Year = 13,
		BarInterval_Size
	} BarInterval;

	inline const char *GetBarIntervalString(BarInterval code)
	{
		switch (code)
		{
		case BarInterval_NoInterval:  return "NoInterval";
		case BarInterval_Tick:  return "Tick";
		case BarInterval_1Sec:  return "1Sec";
		case BarInterval_5Sec:  return "5Sec";
		case BarInterval_10Sec: return "10Sec";
		case BarInterval_15Sec: return "15Sec";
		case BarInterval_30Sec: return "30Sec";
		case BarInterval_1Min:  return "1Min";
		case BarInterval_5Min:  return "5Min";
		case BarInterval_10Min: return "10Min";
		case BarInterval_15Min: return "15Min";
		case BarInterval_30Min: return "30Min";
		case BarInterval_1Hour: return "1Hour";
		case BarInterval_2Hour: return "2Hour";
		case BarInterval_4Hour: return "4Hour";
		case BarInterval_Day:   return "Day";
		case BarInterval_Week:  return "Week";
		case BarInterval_Month: return "Month";
		case BarInterval_Quarter:return"Quarter";
		case BarInterval_Year:  return "Year";
		default: return "UnknownBarInterval";
		}
	}

	inline size_t GetSecondsCount(BarInterval code)
	{
		switch (code)
		{
		case BarInterval_Tick:  return 1;
		case BarInterval_1Sec:  return 1;
		case BarInterval_5Sec:  return 5;
		case BarInterval_10Sec: return 10;
		case BarInterval_15Sec: return 15;
		case BarInterval_30Sec: return 30;
		case BarInterval_1Min:  return 60;
		case BarInterval_5Min:  return 300;
		case BarInterval_10Min: return 600;
		case BarInterval_15Min: return 900;
		case BarInterval_30Min: return 1800;
		case BarInterval_1Hour: return 3600;
		case BarInterval_2Hour: return 7200;
		case BarInterval_4Hour: return 14400;
		case BarInterval_Day:   return 86400;
		case BarInterval_Week:  return 604800;
		case BarInterval_Month: return 2628000; // rounded: float(365 / 12) * 24 * 60 * 60
		case BarInterval_Quarter:return 7884000; // rounded: float(365 / 4) * 24 * 60 * 60
		case BarInterval_Year:  return 31536000; // rounded: 365 * 24 * 60 * 60
		default: return 0;
		}
	}

	typedef enum
	{
		OPEN_DATE,
		CLOSE_DATE
	} DatetimeType;

	inline const char *GetDatetimeTypeString(DatetimeType type)
	{
		switch (type)
		{
		case OPEN_DATE: return "OPEN";
		case CLOSE_DATE: return "CLOSE";
		default: return "UnknownDatetimeType";
		}
	}

	/* Date & time conversion to string */
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

	/* Rounding date & time */
	inline time_t RoundBarFast(time_t datetime)
	{
		int mod = datetime % 60;
		if (mod) return datetime + (60 - mod);
		return datetime;
	}
	inline time_t RoundBarDatetime(BarInterval barInterval, time_t datetime, DatetimeType type)
	{
		if (barInterval == BarInterval_Tick) return datetime;

		if (barInterval <= BarInterval_1Hour)
		{
			// Rounding to CLOSE
			time_t secondsCount = GetSecondsCount(barInterval);
			double periods = double(datetime) / secondsCount;
			if (periods > size_t(periods)) datetime = secondsCount * size_t(periods + 1);
			else datetime = secondsCount * size_t(periods);

			if (type == CLOSE_DATE) return datetime;
			return datetime - secondsCount;
		}

		// Rounding to 1HOUR CLOSE
		double periods = double(datetime) / 3600;
		if (periods > size_t(periods)) datetime = 3600 * size_t(periods + 1);
		else datetime = 3600 * size_t(periods);

		struct tm localtm = *localtime(&datetime);

		int mod = 0;

		switch (type)
		{
		case OPEN_DATE: {

			switch (barInterval)
			{
				case BarInterval_2Hour: {
					if ((mod = localtm.tm_hour % 2)) localtm.tm_hour -= mod;
					else localtm.tm_hour -= 2;
					break;
				}
				case BarInterval_4Hour: {
					if ((mod = localtm.tm_hour % 4)) localtm.tm_hour -= mod;
					else localtm.tm_hour -= 4;
					break;
				}
				case BarInterval_Day: {
					if ((mod = localtm.tm_hour % 24)) localtm.tm_hour -= mod;
					else localtm.tm_mday--;
					break;
				}
				case BarInterval_Week: {
					if (localtm.tm_hour != 0 || localtm.tm_wday != 1) {
						localtm.tm_hour = 0;
						int day = localtm.tm_wday;
						if (day == 0) day = 7;
						day--;
						localtm.tm_mday -= (day % 7);
					} else localtm.tm_mday -= 7;
					break;
				}
				case BarInterval_Month: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
					} else localtm.tm_mon--;
					break;
				}
				case BarInterval_Quarter: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1 || (mod = localtm.tm_mon % 3) != 0) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
						localtm.tm_mon -= mod;
					} else localtm.tm_mon -= 3;
					break;
				}
				case BarInterval_Year: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1 || localtm.tm_mon != 0) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
						localtm.tm_mon = 0;
					} else localtm.tm_year--;
					break;
				}
				default: return datetime;
			}
			break;
		}
		case CLOSE_DATE: {

			switch (barInterval)
			{
				case BarInterval_2Hour: {
					if ((mod = localtm.tm_hour % 2)) localtm.tm_hour += 2 - mod;
					break;
				}
				case BarInterval_4Hour: {
					if ((mod = localtm.tm_hour % 4)) localtm.tm_hour += 4 - mod;
					break;
				}
				case BarInterval_Day: {
					if (localtm.tm_hour != 0) localtm.tm_hour += 24 - (localtm.tm_hour % 24);
					break;
				}
				case BarInterval_Week: {
					if (localtm.tm_hour != 0 || localtm.tm_wday != 1) {
						localtm.tm_hour = 0;
						int day = localtm.tm_wday;
						if (day == 0) day = 7;
						day--;
						localtm.tm_mday += 7 - (day % 7);
					}
					break;
				}
				case BarInterval_Month: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
						localtm.tm_mon++;
					}
					break;
				}
				case BarInterval_Quarter: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1 || (mod = localtm.tm_mon % 3) != 0) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
						localtm.tm_mon += 3 - mod;
					}
					break;
				}
				case BarInterval_Year: {
					if (localtm.tm_hour != 0 || localtm.tm_mday != 1 || localtm.tm_mon != 0) {
						localtm.tm_hour = 0;
						localtm.tm_mday = 1;
						localtm.tm_mon = 0;
						localtm.tm_year++;
					}
					break;
				}
				default: return datetime;
			}
			break;
		}
		}

		return mktime(&localtm);
	}
	inline void TestRoundBarDatetime(time_t datetime)
	{
		printf("ROUNDING BAR from %s\n", GetDatetimeString(datetime).c_str());

		for (int i = BarInterval_1Sec; i < BarInterval_Size; i++)
		{
			printf("TEST ROUND BAR DATETIME %8s | %s | %s \n", GetBarIntervalString(BarInterval(i)), GetDatetimeString(RoundBarDatetime(BarInterval(i),datetime,OPEN_DATE)).c_str(), GetDatetimeTypeString(OPEN_DATE));
			printf("TEST ROUND BAR DATETIME %8s | %s | %s \n", GetBarIntervalString(BarInterval(i)), GetDatetimeString(RoundBarDatetime(BarInterval(i),datetime,CLOSE_DATE)).c_str(), GetDatetimeTypeString(CLOSE_DATE));
		}
	}
	inline time_t RoundTickDatetime(BarInterval barInterval, time_t datetime, DatetimeType type)
	{
		if (barInterval == BarInterval_Tick) return datetime;

		if (barInterval <= BarInterval_1Hour)
		{
			// Rounding to OPEN
			time_t secondsCount = GetSecondsCount(barInterval);
			datetime = secondsCount * (datetime / secondsCount);

			if (type == OPEN_DATE) return datetime;
			return datetime + secondsCount;
		}

		struct tm localtm = *localtime(&datetime);
		localtm.tm_min = 0;
		localtm.tm_sec = 0;

		switch (type)
		{
		case OPEN_DATE: {

			switch (barInterval)
			{
				case BarInterval_2Hour: {
					localtm.tm_hour -= localtm.tm_hour % 2;
					break;
				}
				case BarInterval_4Hour: {
					localtm.tm_hour -= localtm.tm_hour % 4;
					break;
				}
				case BarInterval_Day: {
					localtm.tm_hour = 0;
					break;
				}
				case BarInterval_Week: {
					localtm.tm_hour = 0;
					int day = localtm.tm_wday;
					if (day == 0) day = 7;
					day--;
					localtm.tm_mday -= day % 7;
					break;
				}
				case BarInterval_Month: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					break;
				}
				case BarInterval_Quarter: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					localtm.tm_mon -= localtm.tm_mon % 3;
					break;
				}
				case BarInterval_Year: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					localtm.tm_mon = 0;
					break;
				}
				default: return datetime;
			}
			break;
		}
		case CLOSE_DATE: {

			switch (barInterval)
			{
				case BarInterval_2Hour: {
					localtm.tm_hour += 2 - (localtm.tm_hour % 2);
					break;
				}
				case BarInterval_4Hour: {
					localtm.tm_hour += 4 - (localtm.tm_hour % 4);
					break;
				}
				case BarInterval_Day: {
					localtm.tm_hour = 0;
					localtm.tm_mday++;
					break;
				}
				case BarInterval_Week: {
					localtm.tm_hour = 0;
					int day = localtm.tm_wday;
					if (day == 0) day = 7;
					day--;
					localtm.tm_mday -= day % 7;
					localtm.tm_mday += 7;
					break;
				}
				case BarInterval_Month: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					localtm.tm_mon++;
					break;
				}
				case BarInterval_Quarter: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					localtm.tm_mon += 3 - localtm.tm_mon % 3;
					break;
				}
				case BarInterval_Year: {
					localtm.tm_hour = 0;
					localtm.tm_mday = 1;
					localtm.tm_mon = 0;
					localtm.tm_year++;
					break;
				}
				default: return datetime;
			}
			break;
		}
		}

		return mktime(&localtm);
	}
	inline void TestRoundTickDatetime(time_t datetime)
	{
		printf("ROUNDING TICK from %s\n", GetDatetimeString(datetime).c_str());

		for (int i = BarInterval_1Sec; i < BarInterval_Size; i++)
		{
			printf("TEST ROUND TICK DATETIME %8s | %s | %s \n", GetBarIntervalString(BarInterval(i)), GetDatetimeString(RoundTickDatetime(BarInterval(i),datetime,OPEN_DATE)).c_str(), GetDatetimeTypeString(OPEN_DATE));
			printf("TEST ROUND TICK DATETIME %8s | %s | %s \n", GetBarIntervalString(BarInterval(i)), GetDatetimeString(RoundTickDatetime(BarInterval(i),datetime,CLOSE_DATE)).c_str(), GetDatetimeTypeString(CLOSE_DATE));
		}
	}
}

#endif /* SMARTCOM3_SMARTCOM3ENUMS_H_ */
