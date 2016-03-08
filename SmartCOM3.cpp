
#include "SmartCOM3.h"
#include <assert.h>
#include <iomanip>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

namespace SmartCOM3
{
	/* IUnknown */

	STDMETHODIMP_(ULONG) IStClient::AddRef(void)
	{
		return InterlockedIncrement(&m_cRef);
	}
	STDMETHODIMP_(ULONG) IStClient::Release(void)
	{
		LONG cRef = InterlockedDecrement(&m_cRef);
		if (cRef == 0) delete this;
		return cRef;
	}
	STDMETHODIMP IStClient::QueryInterface(REFIID iid, void ** ppv)
	{
		*ppv = nullptr;
		HRESULT hr = E_NOINTERFACE;

		if (iid == IID_IUnknown || iid == IID_IDispatch || iid == DIID_IStClient)
		{
			*ppv = static_cast<IStClient*>(static_cast<IDispatch*>(this));
			AddRef();
			hr = S_OK;
		}

		return hr;
	}

	/* IDispatch */

	STDMETHODIMP IStClient::GetTypeInfoCount(UINT *pctinfo)
	{
		if (pctinfo == NULL) return E_NOTIMPL;
		*pctinfo = 1;
		return NOERROR;
	}
	STDMETHODIMP IStClient::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo ** pptinfo)
	{
		if (pptinfo == NULL) return E_INVALIDARG;
		if (itinfo != 0) return DISP_E_BADINDEX;
		*pptinfo = NULL;
		m_ptinfo->AddRef();
		*pptinfo = m_ptinfo;
		return NOERROR;
	}
	STDMETHODIMP IStClient::GetIDsOfNames(REFIID riid, OLECHAR ** rgszNames, UINT cNames, LCID lcid, DISPID * rgdispid)
	{
		return m_ptinfo->GetIDsOfNames(rgszNames, cNames, rgdispid);
	}
	STDMETHODIMP IStClient::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS * pdispparams, VARIANT * pvarResult, EXCEPINFO * pexcepinfo, UINT * puArgErr)
	{
		if (pvarResult) VariantInit(pvarResult);

		InvokeDispatch(dispidMember, pdispparams);

		return S_OK;
	}
	void IStClient::InvokeDispatch(DISPID dispidMember, DISPPARAMS *pdispparams)
	{
		switch (dispidMember)
		{
		case 0x01: {
		   Connected();
		   break;
		}
		case 0x02: {
		   Disconnected(
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string reason
		   );
		   break;
		}
		case 0x03: {
		   UpdateQuote(
			   ws2s(pdispparams->rgvarg[22].bstrVal), // std::string symbol
			   double2time(pdispparams->rgvarg[21].dblVal), // time_t datetime
			   (double)pdispparams->rgvarg[20].dblVal, // double open
			   (double)pdispparams->rgvarg[19].dblVal, // double high
			   (double)pdispparams->rgvarg[18].dblVal, // double low
			   (double)pdispparams->rgvarg[17].dblVal, // double close
			   (double)pdispparams->rgvarg[16].dblVal, // double last
			   (double)pdispparams->rgvarg[15].dblVal, // double volume
			   (double)pdispparams->rgvarg[14].dblVal, // double size
			   (double)pdispparams->rgvarg[13].dblVal, // double bid
			   (double)pdispparams->rgvarg[12].dblVal, // double ask
			   (double)pdispparams->rgvarg[11].dblVal, // double bidsize
			   (double)pdispparams->rgvarg[10].dblVal, // double asksize
			   (double)pdispparams->rgvarg[9].dblVal, // double open_int
			   (double)pdispparams->rgvarg[8].dblVal, // double go_buy
			   (double)pdispparams->rgvarg[7].dblVal, // double go_sell
			   (double)pdispparams->rgvarg[6].dblVal, // double go_base
			   (double)pdispparams->rgvarg[5].dblVal, // double go_base_backed
			   (double)pdispparams->rgvarg[4].dblVal, // double high_limit
			   (double)pdispparams->rgvarg[3].dblVal, // double low_limit
			   (long)pdispparams->rgvarg[2].lVal, // long trading_status
			   (double)pdispparams->rgvarg[1].dblVal, // double volat
			   (double)pdispparams->rgvarg[0].dblVal // double theor_price
		   );
		   break;
		}
		case 0x04: {
		   UpdateBidAsk(
			   ws2s(pdispparams->rgvarg[6].bstrVal), // std::string symbol
			   (long)pdispparams->rgvarg[5].lVal, // long row
			   (long)pdispparams->rgvarg[4].lVal, // long nrows
			   (double)pdispparams->rgvarg[3].dblVal, // double bid
			   (double)pdispparams->rgvarg[2].dblVal, // double bidsize
			   (double)pdispparams->rgvarg[1].dblVal, // double ask
			   (double)pdispparams->rgvarg[0].dblVal // double asksize
		   );
		   break;
		}
		case 0x05: {
		   AddTick(
			   ws2s(pdispparams->rgvarg[5].bstrVal), // std::string symbol
			   double2time(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   (double)pdispparams->rgvarg[3].dblVal, // double price
			   (double)pdispparams->rgvarg[2].dblVal, // double volume
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string tradeno
			   (OrderAction)
			   pdispparams->rgvarg[0].bVal // OrderAction action
		   );
		   break;
		}
		case 0x06: {
		   AddBar(
			   (long)pdispparams->rgvarg[10].lVal, // long row
			   (long)pdispparams->rgvarg[9].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[8].bstrVal), // std::string symbol
			   (BarInterval)
			   pdispparams->rgvarg[7].bVal, // BarInterval interval
			   double2time(pdispparams->rgvarg[6].dblVal), // time_t datetime
			   (double)pdispparams->rgvarg[5].dblVal, // double open
			   (double)pdispparams->rgvarg[4].dblVal, // double high
			   (double)pdispparams->rgvarg[3].dblVal, // double low
			   (double)pdispparams->rgvarg[2].dblVal, // double close
			   (double)pdispparams->rgvarg[1].dblVal, // double volume
			   (double)pdispparams->rgvarg[0].dblVal // double open_int
		   );
		   break;
		}
		case 0x07: {
		   SetPortfolio(
			   ws2s(pdispparams->rgvarg[4].bstrVal), // std::string portfolio
			   (double)pdispparams->rgvarg[3].dblVal, // double cash
			   (double)pdispparams->rgvarg[2].dblVal, // double leverage
			   (double)pdispparams->rgvarg[1].dblVal, // double comission
			   (double)pdispparams->rgvarg[0].dblVal // double saldo
		   );
		   break;
		}
		case 0x08: {
		   AddTrade(
			   ws2s(pdispparams->rgvarg[6].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[5].bstrVal), // std::string symbol
			   ws2s(pdispparams->rgvarg[4].bstrVal), // std::string orderid
			   (double)pdispparams->rgvarg[3].dblVal, // double price
			   (double)pdispparams->rgvarg[2].dblVal, // double amount
			   double2time(pdispparams->rgvarg[1].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string tradeno
		   );
		   break;
		}
		case 0x09: {
		   UpdateOrder(
			   ws2s(pdispparams->rgvarg[14].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[13].bstrVal), // std::string symbol
			   (OrderState)
			   pdispparams->rgvarg[12].bVal, // OrderState state
			   (OrderAction)
			   pdispparams->rgvarg[11].bVal, // OrderAction action
			   (OrderType)
			   pdispparams->rgvarg[10].bVal, // OrderType type
			   (OrderValidity)
			   pdispparams->rgvarg[9].bVal, // OrderValidity validity
			   (double)pdispparams->rgvarg[8].dblVal, // double price
			   (double)pdispparams->rgvarg[7].dblVal, // double amount
			   (double)pdispparams->rgvarg[6].dblVal, // double stop
			   (double)pdispparams->rgvarg[5].dblVal, // double filled
			   double2time(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[3].bstrVal), // std::string orderid
			   ws2s(pdispparams->rgvarg[2].bstrVal), // std::string orderno
			   (long)pdispparams->rgvarg[1].lVal, // long status_mask
			   (long)pdispparams->rgvarg[0].lVal // long cookie
		   );
		   break;
		}
		case 0x0a: {
		   UpdatePosition(
			   ws2s(pdispparams->rgvarg[4].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[3].bstrVal), // std::string symbol
			   (double)pdispparams->rgvarg[2].dblVal, // double avprice
			   (double)pdispparams->rgvarg[1].dblVal, // double amount
			   (double)pdispparams->rgvarg[0].dblVal // double planned
		   );
		   break;
		}
		case 0x0f: {
		   AddTickHistory(
			   (long)pdispparams->rgvarg[7].lVal, // long row
			   (long)pdispparams->rgvarg[6].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[5].bstrVal), // std::string symbol
			   double2time(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   (double)pdispparams->rgvarg[3].dblVal, // double price
			   (double)pdispparams->rgvarg[2].dblVal, // double volume
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string tradeno
			   (OrderAction)
			   pdispparams->rgvarg[0].bVal // OrderAction action
		   );
		   break;
		}
		case 0x14: {
		   AddSymbol(
			   (long)pdispparams->rgvarg[14].lVal, // long row
			   (long)pdispparams->rgvarg[13].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[12].bstrVal), // std::string symbol
			   ws2s(pdispparams->rgvarg[11].bstrVal), // std::string short_name
			   ws2s(pdispparams->rgvarg[10].bstrVal), // std::string int_name
			   ws2s(pdispparams->rgvarg[9].bstrVal), // std::string type
			   (long)pdispparams->rgvarg[8].lVal, // long decimals
			   (long)pdispparams->rgvarg[7].lVal, // long lot_size
			   (double)pdispparams->rgvarg[6].dblVal, // double punkt
			   (double)pdispparams->rgvarg[5].dblVal, // double step
			   ws2s(pdispparams->rgvarg[4].bstrVal), // std::string sec_ext_id
			   ws2s(pdispparams->rgvarg[3].bstrVal), // std::string sec_exch_name
			   double2time(pdispparams->rgvarg[2].dblVal), // time_t expiry_date
			   (double)pdispparams->rgvarg[1].dblVal, // double days_before_expiry
			   (double)pdispparams->rgvarg[0].dblVal // double strike
		   );
		   break;
		}
		case 0x1e: {
		   OrderSucceeded(
			   (long)pdispparams->rgvarg[1].lVal, // long cookie
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderid
		   );
		   break;
		}
		case 0x1f: {
		   OrderFailed(
			   (long)pdispparams->rgvarg[2].lVal, // long cookie
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string orderid
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string reason
		   );
		   break;
		}
		case 0x20: {
		   AddPortfolio(
			   (long)pdispparams->rgvarg[4].lVal, // long row
			   (long)pdispparams->rgvarg[3].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[2].bstrVal), // std::string portfolioName
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string portfolioExch
			   (PortfolioStatus)
			   pdispparams->rgvarg[0].bVal // PortfolioStatus portfolioStatus
		   );
		   break;
		}
		case 0x21: {
		   SetSubscribtionCheckReult(
			   (long)pdispparams->rgvarg[0].lVal // long result
		   );
		   break;
		}
		case 0x22: {
		   SetMyTrade(
			   (long)pdispparams->rgvarg[9].lVal, // long row
			   (long)pdispparams->rgvarg[8].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[7].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[6].bstrVal), // std::string symbol
			   double2time(pdispparams->rgvarg[5].dblVal), // time_t datetime
			   (double)pdispparams->rgvarg[4].dblVal, // double price
			   (double)pdispparams->rgvarg[3].dblVal, // double volume
			   ws2s(pdispparams->rgvarg[2].bstrVal), // std::string tradeno
			   (OrderAction)
			   pdispparams->rgvarg[1].bVal, // OrderAction buysell
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderno
		   );
		   break;
		}
		case 0x23: {
		   SetMyOrder(
			   (long)pdispparams->rgvarg[15].lVal, // long row
			   (long)pdispparams->rgvarg[14].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[13].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[12].bstrVal), // std::string symbol
			   (OrderState)
			   pdispparams->rgvarg[11].bVal, // OrderState state
			   (OrderAction)
			   pdispparams->rgvarg[10].bVal, // OrderAction action
			   (OrderType)
			   pdispparams->rgvarg[9].bVal, // OrderType type
			   (OrderValidity)
			   pdispparams->rgvarg[8].bVal, // OrderValidity validity
			   (double)pdispparams->rgvarg[7].dblVal, // double price
			   (double)pdispparams->rgvarg[6].dblVal, // double amount
			   (double)pdispparams->rgvarg[5].dblVal, // double stop
			   (double)pdispparams->rgvarg[4].dblVal, // double filled
			   double2time(pdispparams->rgvarg[3].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[2].bstrVal), // std::string id
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string no
			   (long)pdispparams->rgvarg[0].lVal // long cookie
		   );
		   break;
		}
		case 0x25: {
		   SetMyClosePos(
			   (long)pdispparams->rgvarg[9].lVal, // long row
			   (long)pdispparams->rgvarg[8].lVal, // long nrows
			   ws2s(pdispparams->rgvarg[7].bstrVal), // std::string portfolio
			   ws2s(pdispparams->rgvarg[6].bstrVal), // std::string symbol
			   (double)pdispparams->rgvarg[5].dblVal, // double amount
			   (double)pdispparams->rgvarg[4].dblVal, // double price_buy
			   (double)pdispparams->rgvarg[3].dblVal, // double price_sell
			   double2time(pdispparams->rgvarg[2].dblVal), // time_t postime
			   ws2s(pdispparams->rgvarg[1].bstrVal), // std::string order_open
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string order_close
		   );
		   break;
		}
		case 0x26: {
		   OrderCancelSucceeded(
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderid
		   );
		   break;
		}
		case 0x27: {
		   OrderCancelFailed(
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderid
		   );
		   break;
		}
		case 0x28: {
		   OrderMoveSucceeded(
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderid
		   );
		   break;
		}
		case 0x29: {
		   OrderMoveFailed(
			   ws2s(pdispparams->rgvarg[0].bstrVal) // std::string orderid
		   );
		   break;
		}
		default: {
			 printf("IStClient::InvokeDispatch(%d) unknown code\n", dispidMember);
			 break;
		}
		}
	}

	/* COM HELPERS */

	std::mutex apartmentsInitializationMutex;
	bool apartmentsInitializationFlag = false;
	void IStClient::InitializeApartments()
	{
		printf("IStClient::InitializeApartments()\n");
		apartmentsInitializationMutex.lock();
		if (apartmentsInitializationFlag == false) {
			if (S_OK != CoInitializeEx(NULL, COINIT_MULTITHREADED)) { printf("IStClient::InitializeApartments() CoInitializeEx(NULL, COINIT_MULTITHREADED) FAIL\n"); exit(1); }
			apartmentsInitializationFlag = true;
			printf("IStClient::InitializeApartments() OK\n");
		} else {
			printf("IStClient::InitializeApartments() already initialized\n");
		}
		apartmentsInitializationMutex.unlock();
	}
	void IStClient::UninitializeApartments()
	{
		printf("IStClient::UninitializeApartments()\n");
		apartmentsInitializationMutex.lock();
		if (apartmentsInitializationFlag == true) {
			CoUninitialize();
			apartmentsInitializationFlag = false;
			printf("IStClient::UninitializeApartments() OK\n");
		} else {
			printf("IStClient::UninitializeApartments() not initialized\n");
		}
		apartmentsInitializationMutex.unlock();
	}
	HRESULT IStClient::Advise()
	{
		HRESULT hr = S_FALSE;
		IConnectionPointContainer* cpc;
		if (S_OK == m_IStServer->QueryInterface(IID_IConnectionPointContainer, (void **)&cpc))
		{
			if (S_OK == cpc->FindConnectionPoint(DIID_IStClient, &m_pIConnectionPoint))
			{
				hr = m_pIConnectionPoint->Advise(this, &m_dwCookie);
			}
			cpc->Release();
		}
		return hr;
	}
	void IStClient::UnAdvise()
	{
		if (m_dwCookie) {
			m_pIConnectionPoint->Unadvise(m_dwCookie);
			m_pIConnectionPoint->Release();
			m_dwCookie = 0;
		}
	}
	
	IStClient::IStClient()
		: m_cRef(1), m_dwCookie(0)
	{
		printf("IStClient::IStClient()\n");

		LPTYPELIB pTypeLib;
		if (S_OK != LoadRegTypeLib(LIBID_SmartCOM3Lib, 1, 0, LOCALE_SYSTEM_DEFAULT, &pTypeLib)) { printf("IStClient::IStClient() LoadRegTypeLib FAIL\n"); exit(1); }
		if (S_OK != pTypeLib->GetTypeInfoOfGuid(DIID_IStClient, &m_ptinfo)) { printf("IStClient::IStClient() GetTypeInfoOfGuid FAIL\n"); exit(1); }
		pTypeLib->Release();

		if (S_OK != CoCreateInstance(CLSID_StServer, NULL, CLSCTX_INPROC_SERVER, IID_IStServer, reinterpret_cast<void**>(&m_IStServer)))  { printf("IStClient::IStClient() CoCreateInstance(Server) FAIL\n"); exit(1); }
		if (S_OK != Advise()) { printf("IStClient::IStClient() COM Advise FAIL\n"); exit(1); }
		if (S_OK != CoCreateInstance(CLSID_StServer, NULL, CLSCTX_INPROC_SERVER, IID_ISmartComVersion, reinterpret_cast<void**>(&m_ISmartComVersion)))  { printf("IStClient::IStClient() CoCreateInstance(Version) FAIL\n"); exit(1); }
		
		printf("IStClient::IStClient() OK\n");
	}
	IStClient::~IStClient()
	{
		printf("IStClient::~IStClient()\n");
		if (IsConnected()) {
			Disconnect();
			int timeout = 100;
			while (timeout-- && IsConnected()) std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		UnAdvise();
		m_IStServer->Release();
		m_ISmartComVersion->Release();
		m_ptinfo->Release();
		printf("IStClient::~IStClient() OK\n");
	}

	/* SmartCOM3 METHODS */

	void IStClient::ListenQuotes(std::string symbol) {
		HRESULT hr = m_IStServer->raw_ListenQuotes(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ListenQuotes(): COM error!");
	}
	void IStClient::CancelQuotes(std::string symbol) {
		HRESULT hr = m_IStServer->raw_CancelQuotes(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("CancelQuotes(): COM error!");
	}
	void IStClient::ListenBidAsks(std::string symbol) {
		HRESULT hr = m_IStServer->raw_ListenBidAsks(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ListenBidAsks(): COM error!");
	}
	void IStClient::CancelBidAsks(std::string symbol) {
		HRESULT hr = m_IStServer->raw_CancelBidAsks(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("CancelBidAsks(): COM error!");
	}
	void IStClient::ListenTicks(std::string symbol) {
		HRESULT hr = m_IStServer->raw_ListenTicks(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ListenTicks(): COM error!");
	}
	void IStClient::CancelTicks(std::string symbol) {
		HRESULT hr = m_IStServer->raw_CancelTicks(s2ws(symbol.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("CancelTicks(): COM error!");
	}
	void IStClient::GetBars(std::string symbol, BarInterval interval, time_t since, long count) {
		HRESULT hr = m_IStServer->raw_GetBars(s2ws(symbol.c_str()).c_str(), interval, time2double(since), count);
		if (FAILED(hr)) throw std::runtime_error("GetBars(): COM error!");
	}
	void IStClient::ListenPortfolio(std::string portfolio) {
		HRESULT hr = m_IStServer->raw_ListenPortfolio(s2ws(portfolio.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ListenPortfolio(): COM error!");
	}
	void IStClient::CancelPortfolio(std::string portfolio) {
		HRESULT hr = m_IStServer->raw_CancelPortfolio(s2ws(portfolio.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("CancelPortfolio(): COM error!");
	}
	void IStClient::PlaceOrder(std::string portfolio, std::string symbol, OrderAction action, OrderType type, OrderValidity validity, double price, double amount, double stop, long cookie) {
		HRESULT hr = m_IStServer->raw_PlaceOrder(s2ws(portfolio.c_str()).c_str(), s2ws(symbol.c_str()).c_str(), action, type, validity, price, amount, stop, cookie);
		if (FAILED(hr)) throw std::runtime_error("PlaceOrder(): COM error!");
	}
	void IStClient::CancelOrder(std::string portfolio, std::string symbol, std::string orderid) {
		HRESULT hr = m_IStServer->raw_CancelOrder(s2ws(portfolio.c_str()).c_str(), s2ws(symbol.c_str()).c_str(), s2ws(orderid.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("CancelOrder(): COM error!");
	}
	void IStClient::MoveOrder(std::string portfolio, std::string orderid, double targetPrice) {
		HRESULT hr = m_IStServer->raw_MoveOrder(s2ws(portfolio.c_str()).c_str(), s2ws(orderid.c_str()).c_str(), targetPrice);
		if (FAILED(hr)) throw std::runtime_error("MoveOrder(): COM error!");
	}
	void IStClient::GetSymbols() {
		HRESULT hr = m_IStServer->raw_GetSymbols();
		if (FAILED(hr)) throw std::runtime_error("GetSymbols(): COM error!");
	}
	bool IStClient::IsConnected() {
		VARIANT_BOOL result = 0;
		HRESULT hr = m_IStServer->raw_IsConnected(&result);
		if (FAILED(hr)) throw std::runtime_error("IsConnected(): COM error!");
		if (result == 0) return false;
		else return true;
	}
	void IStClient::Connect(std::string ip, unsigned short port, std::string login, std::string password) {
		HRESULT hr = m_IStServer->raw_connect(s2ws(ip.c_str()).c_str(), port, s2ws(login.c_str()).c_str(), s2ws(password.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("Connect(): COM error!");
	}
	void IStClient::Disconnect() {
		HRESULT hr = m_IStServer->raw_disconnect();
		if (FAILED(hr)) throw std::runtime_error("Disconnect(): COM error!");
	}
	void IStClient::GetPrortfolioList() {
		HRESULT hr = m_IStServer->raw_GetPrortfolioList();
		if (FAILED(hr)) throw std::runtime_error("GetPrortfolioList(): COM error!");
	}
	void IStClient::GetMyOrders(long onlyActive, std::string portfolio) {
		HRESULT hr = m_IStServer->raw_GetMyOrders(onlyActive, s2ws(portfolio.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("GetMyOrders(): COM error!");
	}
	void IStClient::GetMyTrades(std::string portfolio) {
		HRESULT hr = m_IStServer->raw_GetMyTrades(s2ws(portfolio.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("GetMyTrades(): COM error!");
	}
	void IStClient::GetMyClosePos(std::string portfolio) {
		HRESULT hr = m_IStServer->raw_GetMyClosePos(s2ws(portfolio.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("GetMyClosePos(): COM error!");
	}
	void IStClient::GetTrades(std::string symbol, time_t from, long count) {
		HRESULT hr = m_IStServer->raw_GetTrades(s2ws(symbol.c_str()).c_str(), time2double(from), count);
		if (FAILED(hr)) throw std::runtime_error("GetTrades(): COM error!");
	}
	void IStClient::ConfigureClient(std::string paramsSet) {
		HRESULT hr = m_IStServer->raw_ConfigureClient(s2ws(paramsSet.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ConfigureClient(): COM error!");
	}
	void IStClient::ConfigureServer(std::string paramsSet) {
		HRESULT hr = m_IStServer->raw_ConfigureServer(s2ws(paramsSet.c_str()).c_str());
		if (FAILED(hr)) throw std::runtime_error("ConfigureServer(): COM error!");
	}
	std::string IStClient::GetMoneyAccount(std::string portfolioID) {
		const wchar_t *result = 0;
		HRESULT hr = m_IStServer->raw_GetMoneyAccount(s2ws(portfolioID.c_str()).c_str(), &result);
		if (FAILED(hr)) throw std::runtime_error("GetMoneyAccount(): COM error!");
		return ws2s(result);
	}

	/* SmartCOM3 VERSION METHODS */

	std::string IStClient::GetServerVersionString() {
		BSTR result = 0;
		HRESULT hr = m_ISmartComVersion->raw_GetServerVersionString(&result);
		if (FAILED(hr)) throw std::runtime_error("GetServerVersionString(): COM error!");
		return ws2s(result);
	}
	void IStClient::GetServerVersion(long *major, long *minor, long *build, long *rev) {
		HRESULT hr = m_ISmartComVersion->raw_GetServerVersion(major, minor, build, rev);
		if (FAILED(hr)) throw std::runtime_error("GetServerVersion(): COM error!");
	}
	std::string IStClient::GetClientVersionString() {
		BSTR result = 0;
		HRESULT hr = m_ISmartComVersion->raw_GetStClientVersionString(&result);
		if (FAILED(hr)) throw std::runtime_error("GetClientVersionString(): COM error!");
		return ws2s(result);
	}
	void IStClient::GetClientVersion(long *major, long *minor, long *build, long *rev) {
		HRESULT hr = m_ISmartComVersion->raw_GetStClientVersion(major, minor, build, rev);
		if (FAILED(hr)) throw std::runtime_error("GetClientVersion(): COM error!");
	}
}

namespace SmartCOM3
{
	/* WIDECHAR <-> UNICODE */

	inline std::string ws2s(const wchar_t *wstr)
	{
		if (wstr == NULL) return std::string("NULL_POINTER");
		int wsize = 0;
		while (wstr[wsize++] != L'\0');
		if (wsize == 0) return std::string("ZERO_LENGTH");

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, wsize, NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr, wsize, &strTo[0], size_needed, NULL, NULL);
		return strTo;
	}
	inline std::wstring s2ws(const char *str)
	{
		if (str == NULL) return std::wstring(L"NULL_POINTER");
		int size = 0;
		while (str[size++] != '\0');
		if (size == 0) return std::wstring(L"ZERO_LENGTH");

		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str, size, NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, str, size, &wstrTo[0], size_needed);
		return wstrTo;
	}

	/* OLE DATE <-> POSIX */

	const DATE VARIANT_TIMET_DAY0 = 25569;
	const LONG TIMET_ONE_DAY = 86400;
	static const time_t TIMET_VARIANT_OVERFLOW = 253402300800;
	inline time_t double2time(double date)
	{
		time_t pTimeT;

		if (date < VARIANT_TIMET_DAY0) date = VARIANT_TIMET_DAY0;
		pTimeT = time_t(((date - VARIANT_TIMET_DAY0) * TIMET_ONE_DAY) + 0.5);

		return pTimeT;
	}
	inline double time2double(time_t timeT)
	{
		double pDate;
		struct tm localtm, utctm, *ptm = NULL;
		time_t timeTLocal, timeTUtc;

		#if defined (__WINE__)
		ptm = localtime(&timeT);
		#else
		localtime_s(ptm, &timeT);
		#endif

		if (ptm == NULL) return VARIANT_TIMET_DAY0;
		localtm = *ptm;

		#if defined (__WINE__)
		ptm = gmtime(&timeT);
		#else
		gmtime_s(ptm, &timeT);
		#endif

		if (ptm == NULL) return VARIANT_TIMET_DAY0;
		utctm = *ptm;

		localtm.tm_isdst = 0;
		utctm.tm_isdst = 0;

		if ((timeTLocal = mktime(&localtm)) == (time_t)-1 || (timeTUtc = mktime(&utctm)) == (time_t)-1)
			return VARIANT_TIMET_DAY0;

		timeT += timeTLocal - timeTUtc;

		if (timeT >= TIMET_VARIANT_OVERFLOW) return VARIANT_TIMET_DAY0;

		pDate = (DATE)(timeT / (double)TIMET_ONE_DAY) + VARIANT_TIMET_DAY0;

		return pDate;
	}
}
