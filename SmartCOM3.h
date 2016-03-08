
#ifndef SMARTCOM3_H_
#define SMARTCOM3_H_

#include "SmartCOM3enums.h"
#include <ocidl.h>
#include <string>
#include <time.h>

namespace SmartCOM3
{
	struct IStServer;
	struct ISmartComVersion;

	/* SmartCOM3 API */
	struct IStClient : IDispatch
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

		IStServer *m_IStServer;
		IConnectionPoint *m_pIConnectionPoint;
		DWORD m_dwCookie;
		ISmartComVersion *m_ISmartComVersion;
		static void InitializeApartments();
		static void UninitializeApartments();
		HRESULT Advise();
		void UnAdvise();

		IStClient();
		virtual ~IStClient();

		/* SmartCOM3 EVENTS */

		virtual void Connected() = 0;
		virtual void Disconnected(
			std::string reason) = 0;
		virtual void UpdateQuote(
			std::string symbol,
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
			std::string symbol,
			long row,
			long nrows,
			double bid,
			double bidsize,
			double ask,
			double asksize) = 0;
		virtual void AddTick(
			std::string symbol,
			time_t datetime,
			double price,
			double volume,
			std::string tradeno,
			OrderAction action) = 0;
		virtual void AddBar(
			long row,
			long nrows,
			std::string symbol,
			BarInterval interval,
			time_t datetime,
			double open,
			double high,
			double low,
			double close,
			double volume,
			double open_int) = 0;
		virtual void SetPortfolio(
			std::string portfolio,
			double cash,
			double leverage,
			double comission,
			double saldo) = 0;
		virtual void AddTrade(
			std::string portfolio,
			std::string symbol,
			std::string orderid,
			double price,
			double amount,
			time_t datetime,
			std::string tradeno) = 0;
		virtual void UpdateOrder(
			std::string portfolio,
			std::string symbol,
			OrderState state,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			double filled,
			time_t datetime,
			std::string orderid,
			std::string orderno,
			long status_mask,
			long cookie) = 0;
		virtual void UpdatePosition(
			std::string portfolio,
			std::string symbol,
			double avprice,
			double amount,
			double planned) = 0;
		virtual void AddTickHistory(
			long row,
			long nrows,
			std::string symbol,
			time_t datetime,
			double price,
			double volume,
			std::string tradeno,
			OrderAction action) = 0;
		virtual void AddSymbol(
			long row,
			long nrows,
			std::string symbol,
			std::string short_name,
			std::string int_name,
			std::string type,
			long decimals,
			long lot_size,
			double punkt,
			double step,
			std::string sec_ext_id,
			std::string sec_exch_name,
			time_t expiry_date,
			double days_before_expiry,
			double strike) = 0;
		virtual void OrderSucceeded(
			long cookie,
			std::string orderid) = 0;
		virtual void OrderFailed(
			long cookie,
			std::string orderid,
			std::string reason) = 0;
		virtual void AddPortfolio(
			long row,
			long nrows,
			std::string portfolioName,
			std::string portfolioExch,
			PortfolioStatus portfolioStatus) = 0;
		virtual void SetSubscribtionCheckReult(
			long result) = 0;
		virtual void SetMyTrade(
			long row,
			long nrows,
			std::string portfolio,
			std::string symbol,
			time_t datetime,
			double price,
			double volume,
			std::string tradeno,
			OrderAction buysell,
			std::string orderno) = 0;
		virtual void SetMyOrder(
			long row,
			long nrows,
			std::string portfolio,
			std::string symbol,
			OrderState state,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			double filled,
			time_t datetime,
			std::string id,
			std::string no,
			long cookie) = 0;
		virtual void SetMyClosePos(
			long row,
			long nrows,
			std::string portfolio,
			std::string symbol,
			double amount,
			double price_buy,
			double price_sell,
			time_t postime,
			std::string order_open,
			std::string order_close) = 0;
		virtual void OrderCancelSucceeded(
			std::string orderid) = 0;
		virtual void OrderCancelFailed(
			std::string orderid) = 0;
		virtual void OrderMoveSucceeded(
			std::string orderid) = 0;
		virtual void OrderMoveFailed(
			std::string orderid) = 0;

		/* SmartCOM3 METHODS */

		void ListenQuotes(
			std::string symbol);
		void CancelQuotes(
			std::string symbol);
		void ListenBidAsks(
			std::string symbol);
		void CancelBidAsks(
			std::string symbol);
		void ListenTicks(
			std::string symbol);
		void CancelTicks(
			std::string symbol);
		void GetBars(
			std::string symbol,
			BarInterval interval,
			time_t since,
			long count);
		void ListenPortfolio(
			std::string portfolio);
		void CancelPortfolio(
			std::string portfolio);
		void PlaceOrder(
			std::string portfolio,
			std::string symbol,
			OrderAction action,
			OrderType type,
			OrderValidity validity,
			double price,
			double amount,
			double stop,
			long cookie);
		void CancelOrder(
			std::string portfolio,
			std::string symbol,
			std::string orderid);
		void MoveOrder(
			std::string portfolio,
			std::string orderid,
			double targetPrice);
		void GetSymbols();
		bool IsConnected();
		void Connect(
			std::string ip,
			unsigned short port,
			std::string login,
			std::string password);
		void Disconnect();
		void GetPrortfolioList();
		void GetMyOrders(
			long onlyActive,
			std::string portfolio);
		void GetMyTrades(
			std::string portfolio);
		void GetMyClosePos(
			std::string portfolio);
		void GetTrades(
			std::string symbol,
			time_t from,
			long count);
		void ConfigureClient(
			std::string paramsSet);
		void ConfigureServer(
			std::string paramsSet);
		std::string GetMoneyAccount(
			std::string portfolioID);

		/* SmartCOM3 VERSION METHODS */

		std::string GetServerVersionString();
		void GetServerVersion(
			long *major,
			long *minor,
			long *build,
			long *rev);
		std::string GetClientVersionString();
		void GetClientVersion(
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
			VARIANT_BOOL *result) = 0;
		virtual HRESULT __stdcall raw_connect(
			const wchar_t *ip,
			unsigned short port,
			const wchar_t *login,
			const wchar_t *password) = 0;
		virtual HRESULT __stdcall raw_disconnect() = 0;
		virtual HRESULT __stdcall raw_GetPrortfolioList() = 0;
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
			const wchar_t **moneyAccount) = 0;
	};

	/* SmartCOM3 VERSION RAW METHODS */
	struct ISmartComVersion : IDispatch
	{
		virtual HRESULT __stdcall raw_GetServerVersionString(
			BSTR *stversion) = 0;
		virtual HRESULT __stdcall raw_GetServerVersion(
			long *major,
			long *minor,
			long *build,
			long *rev) = 0;
		virtual HRESULT __stdcall raw_GetStClientVersionString(
			BSTR *stversion) = 0;
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
}

namespace SmartCOM3
{
	/* WIDECHAR <-> UNICODE */
	inline std::string ws2s(const wchar_t *wstr);
	inline std::wstring s2ws(const char *str);

	/* OLE DATE <-> POSIX */
	inline time_t double2time(double date);
	inline double time2double(time_t timeT);
}

#endif
