
#ifndef SMARTCOM3_H_
#define SMARTCOM3_H_

#include <ocidl.h>
#include "SmartCOM3enums.h"
#include <assert.h>
#include <mutex>

namespace SmartCOM3
{
	struct IStServer;
	struct ISmartComVersion;

	/* SmartCOM3 API */
	class IStClient : IDispatch
	{
		/* IUnknown */

		volatile LONG m_cRef;
		STDMETHODIMP_(ULONG) AddRef(void);
		STDMETHODIMP_(ULONG) Release(void);
		STDMETHODIMP QueryInterface(REFIID iid, void **ppv);

		/* IDispatch */

		ITypeInfo *m_ptinfo;
		STDMETHODIMP GetTypeInfoCount(UINT *pctinfo);
		STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
		STDMETHODIMP GetIDsOfNames(
			REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgdispid);
		STDMETHODIMP Invoke(
			DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
			DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr);
		void InvokeDispatch(DISPID dispidMember, DISPPARAMS *pdispparams);

		/* COM HELPERS */

		static std::mutex s_ApartmentsInitializationMutex;
		static bool s_ApartmentsInitializationFlag;

	public:

		static void InitializeApartments();
		static void UninitializeApartments();

	private:

		IStServer *m_IStServer;
		IConnectionPoint *m_pIConnectionPoint;
		DWORD m_dwCookie;
		ISmartComVersion *m_ISmartComVersion;
		HRESULT Advise();
		void UnAdvise();

	public:

		IStClient(bool autoInitializeApartments = true);
		virtual ~IStClient();

	protected:

		/* SmartCOM3 EVENTS */

		virtual void Connected() = 0;
		virtual void Disconnected(
			const char *reason) = 0;
		virtual void UpdateQuote(
			const char *symbol,
			time_t datetime,
			double open,
			double high,
			double low,
			double close,
			double last,
			double volume,
			double size,
			double bid,
			double ask,
			double bidsize,
			double asksize,
			double open_int,
			double go_buy,
			double go_sell,
			double go_base,
			double go_base_backed,
			double high_limit,
			double low_limit,
			long trading_status,
			double volat,
			double theor_price) = 0;
		virtual void UpdateBidAsk(
			const char *symbol,
			long row,
			long nrows,
			double bid,
			double bidsize,
			double ask,
			double asksize) = 0;
		virtual void AddTick(
			const char *symbol,
			time_t datetime,
			double price,
			double volume,
			const char *tradeno,
			OrderAction action) = 0;
		virtual void AddBar(
			long row,
			long nrows,
			const char *symbol,
			BarInterval interval,
			time_t datetime,
			double open,
			double high,
			double low,
			double close,
			double volume,
			double open_int) = 0;
		virtual void SetPortfolio(
			const char *portfolio,
			double cash,
			double leverage,
			double comission,
			double saldo) = 0;
		virtual void AddTrade(
			const char *portfolio,
			const char *symbol,
			const char *orderid,
			double price,
			double amount,
			time_t datetime,
			const char *tradeno) = 0;
		virtual void UpdateOrder(
			const char *portfolio,
			const char *symbol,
			OrderState state,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			double filled,
			time_t datetime,
			const char *orderid,
			const char *orderno,
			long status_mask,
			long cookie) = 0;
		virtual void UpdatePosition(
			const char *portfolio,
			const char *symbol,
			double avprice,
			double amount,
			double planned) = 0;
		virtual void AddTickHistory(
			long row,
			long nrows,
			const char *symbol,
			time_t datetime,
			double price,
			double volume,
			const char *tradeno,
			OrderAction action) = 0;
		virtual void AddSymbol(
			long row,
			long nrows,
			const char *symbol,
			const char *short_name,
			const char *int_name,
			const char *type,
			long decimals,
			long lot_size,
			double punkt,
			double step,
			const char *sec_ext_id,
			const char *sec_exch_name,
			time_t expiry_date,
			double days_before_expiry,
			double strike) = 0;
		virtual void OrderSucceeded(
			long cookie,
			const char *orderid) = 0;
		virtual void OrderFailed(
			long cookie,
			const char *orderid,
			const char *reason) = 0;
		virtual void AddPortfolio(
			long row,
			long nrows,
			const char *portfolioName,
			const char *portfolioExch,
			PortfolioStatus portfolioStatus) = 0;
		virtual void SetSubscribtionCheckResult(
			long result) = 0;
		virtual void SetMyTrade(
			long row,
			long nrows,
			const char *portfolio,
			const char *symbol,
			time_t datetime,
			double price,
			double volume,
			const char *tradeno,
			OrderAction buysell,
			const char *orderno) = 0;
		virtual void SetMyOrder(
			long row,
			long nrows,
			const char *portfolio,
			const char *symbol,
			OrderState state,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			double filled,
			time_t datetime,
			const char *id,
			const char *no,
			long cookie) = 0;
		virtual void SetMyClosePos(
			long row,
			long nrows,
			const char *portfolio,
			const char *symbol,
			double amount,
			double price_buy,
			double price_sell,
			time_t postime,
			const char *order_open,
			const char *order_close) = 0;
		virtual void OrderCancelSucceeded(
			const char *orderid) = 0;
		virtual void OrderCancelFailed(
			const char *orderid) = 0;
		virtual void OrderMoveSucceeded(
			const char *orderid) = 0;
		virtual void OrderMoveFailed(
			const char *orderid) = 0;

	public:

		/* SmartCOM3 METHODS */

		ErrorCode ListenQuotes(
			const char *symbol);
		ErrorCode CancelQuotes(
			const char *symbol);
		ErrorCode ListenBidAsks(
			const char *symbol);
		ErrorCode CancelBidAsks(
			const char *symbol);
		ErrorCode ListenTicks(
			const char *symbol);
		ErrorCode CancelTicks(
			const char *symbol);
		ErrorCode GetBars(
			const char *symbol,
			BarInterval interval,
			time_t since,
			long count);
		ErrorCode ListenPortfolio(
			const char *portfolio);
		ErrorCode CancelPortfolio(
			const char *portfolio);
		ErrorCode PlaceOrder(
			const char *portfolio,
			const char *symbol,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			long cookie);
		ErrorCode CancelOrder(
			const char *portfolio,
			const char *symbol,
			const char *orderid);
		ErrorCode MoveOrder(
			const char *portfolio,
			const char *orderid,
			double targetPrice);
		ErrorCode GetSymbols();
		ErrorCode IsConnected(bool *connected);
		ErrorCode Connect(
			const char *ip,
			unsigned short port,
			const char *login,
			const char *password);
		ErrorCode Disconnect();
		ErrorCode GetPortfolioList();
		ErrorCode GetMyOrders(
			long onlyActive,
			const char *portfolio);
		ErrorCode GetMyTrades(
			const char *portfolio);
		ErrorCode GetMyClosePos(
			const char *portfolio);
		ErrorCode GetTrades(
			const char *symbol,
			time_t from,
			long count);
		ErrorCode ConfigureClient(
			const char *paramsSet);
		ErrorCode ConfigureServer(
			const char *paramsSet);
		ErrorCode GetMoneyAccount(
			const char *portfolioID,
			std::string *portfolioMO);

	public:

		/* SmartCOM3 VERSION METHODS */

		ErrorCode GetServerVersionString(std::string *version);
		ErrorCode GetServerVersion(
			long *major,
			long *minor,
			long *build,
			long *rev);
		ErrorCode GetClientVersionString(std::string *version);
		ErrorCode GetClientVersion(
			long *major,
			long *minor,
			long *build,
			long *rev);
	};

	/* SmartCOM3 RAW METHODS */
	struct IStServer : IDispatch
	{
		virtual HRESULT __stdcall raw_ListenQuotes(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_CancelQuotes(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_ListenBidAsks(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_CancelBidAsks(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_ListenTicks(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_CancelTicks(
			const wchar_t *symbol) = 0;
		virtual HRESULT __stdcall raw_GetBars(
			const wchar_t *symbol,
			BarInterval interval,
			DATE since,
			long count) = 0;
		virtual HRESULT __stdcall raw_ListenPortfolio(
			const wchar_t *portfolio) = 0;
		virtual HRESULT __stdcall raw_CancelPortfolio(
			const wchar_t *portfolio) = 0;
		virtual HRESULT __stdcall raw_PlaceOrder(
			const wchar_t *portfolio,
			const wchar_t *symbol,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			long cookie) = 0;
		virtual HRESULT __stdcall raw_CancelOrder(
			const wchar_t *portfolio,
			const wchar_t *symbol,
			const wchar_t *orderid) = 0;
		virtual HRESULT __stdcall raw_MoveOrder(
			const wchar_t *portfolio,
			const wchar_t *orderid,
			double targetPrice) = 0;
		virtual HRESULT __stdcall raw_GetSymbols() = 0;
		virtual HRESULT __stdcall raw_IsConnected(
			short *result) = 0;
		virtual HRESULT __stdcall raw_connect(
			const wchar_t *ip,
			unsigned short port,
			const wchar_t *login,
			const wchar_t *password) = 0;
		virtual HRESULT __stdcall raw_disconnect() = 0;
		virtual HRESULT __stdcall raw_GetPortfolioList() = 0;
		virtual HRESULT __stdcall raw_GetMyOrders(
			long onlyActive,
			const wchar_t *portfolio) = 0;
		virtual HRESULT __stdcall raw_GetMyTrades(
			const wchar_t *portfolio) = 0;
		virtual HRESULT __stdcall raw_GetMyClosePos(
			const wchar_t *portfolio) = 0;
		virtual HRESULT __stdcall raw_GetTrades(
			const wchar_t *symbol,
			DATE from,
			long count) = 0;
		virtual HRESULT __stdcall raw_ConfigureClient(
			const wchar_t *paramsSet) = 0;
		virtual HRESULT __stdcall raw_ConfigureServer(
			const wchar_t *paramsSet) = 0;
		virtual HRESULT __stdcall raw_GetMoneyAccount(
			const wchar_t *portfolioID,
			wchar_t **moneyAccount) = 0;
	};

	/* SmartCOM3 VERSION RAW METHODS */
	struct ISmartComVersion : IDispatch
	{
		virtual HRESULT __stdcall raw_GetServerVersionString(
			wchar_t **stversion) = 0;
		virtual HRESULT __stdcall raw_GetServerVersion(
			long *major,
			long *minor,
			long *build,
			long *rev) = 0;
		virtual HRESULT __stdcall raw_GetStClientVersionString(
			wchar_t **stversion) = 0;
		virtual HRESULT __stdcall raw_GetStClientVersion(
			long *major,
			long *minor,
			long *build,
			long *rev) = 0;
	};

	/* SmartCOM3 GUIDs */
	const GUID LIBID_SmartCOM3Lib = {0x8252879c,0x6e32,0x4322,{0xa3,0x8d,0x8e,0xba,0x54,0xe5,0x25,0x95}};
	const GUID DIID_IStClient = {0x213e62b6,0xa2d7,0x4f14,{0x92,0xe0,0x10,0x5f,0xa0,0x33,0xe0,0x48}};
	const GUID IID_IStServer = {0x2c00fda6,0x45fd,0x4102,{0x90,0x9c,0x46,0xe2,0xb7,0xe2,0x55,0xdc}};
	const GUID IID_ISmartComVersion = {0x53722a24,0xf75c,0x44c7,{0x86,0xcf,0x92,0x32,0x65,0x45,0x66,0xad}};
	const GUID CLSID_StServer = {0x99f5ea2e,0x0636,0x49be,{0x81,0x00,0x8a,0xe3,0x09,0xb0,0x33,0x31}};

	/* WIDECHAR <-> UNICODE */
	inline std::string ws2s(const wchar_t *wstr)
	{
		if (wstr == NULL) return "NULL_POINTER";
		size_t wsize = 0; // wcslen(wstr); // wrong size
		while (wstr[wsize++] != '\0'); wsize--; // temp fix
		if (wsize < 1) return "ZERO_LENGTH";

		size_t size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, wsize, NULL, 0, NULL, NULL);

		std::string strTo(size_needed, 0);
		int result = WideCharToMultiByte(CP_UTF8, 0, wstr, wsize, &strTo[0], size_needed, NULL, NULL);
		assert(result != 0);

		return strTo;
	}
	inline std::wstring s2ws(const char *str)
	{
		if (str == NULL) return L"NULL_POINTER";
		size_t size = strlen(str);
		if (size < 1) return L"ZERO_LENGTH";

		size_t size_needed = MultiByteToWideChar(CP_UTF8, 0, str, size, NULL, 0);

		std::wstring wstrTo(size_needed, 0);
		int result = MultiByteToWideChar(CP_UTF8, 0, str, size, &wstrTo[0], size_needed);
		assert(result != 0);

		return wstrTo;
	}

	/* MS OLE DATE <-> POSIX time_t */
	inline time_t d2t(DATE vt_date)
	{
	    SYSTEMTIME sysTime;
	    int result = VariantTimeToSystemTime(vt_date, &sysTime);
	    assert(result != 0);

	    struct tm localtm;
	    localtm.tm_sec = sysTime.wSecond;
	    localtm.tm_min = sysTime.wMinute;
	    localtm.tm_hour = sysTime.wHour;
	    localtm.tm_mday = sysTime.wDay;
	    localtm.tm_mon = sysTime.wMonth - 1;        // tm_mon is 0 based
	    localtm.tm_year = sysTime.wYear - 1900;     // tm_year is 1900 based
	    localtm.tm_isdst = -1;

	    return mktime(&localtm);
	}
	inline DATE t2d(time_t timet)
	{
#if defined(WIN32) && !defined(__WINE__)
		struct tm localtm;
		localtime_s(&localtm, &timet);
#else
		struct tm localtm = *localtime(&timet);
#endif
	    SYSTEMTIME sysTime;
	    sysTime.wYear = static_cast<WORD>(1900 + localtm.tm_year);
	    sysTime.wMonth = static_cast<WORD>(localtm.tm_mon + 1);
	    sysTime.wDayOfWeek = 0;
	    sysTime.wDay = static_cast<WORD>(localtm.tm_mday);
	    sysTime.wHour = static_cast<WORD>(localtm.tm_hour);
	    sysTime.wMinute = static_cast<WORD>(localtm.tm_min);
	    sysTime.wSecond = static_cast<WORD>(localtm.tm_sec);
	    sysTime.wMilliseconds = 0;

	    DATE vt_date;
	    int result = SystemTimeToVariantTime(&sysTime, &vt_date);
	    assert(result != 0);

	    return vt_date;
	}
}

#endif
