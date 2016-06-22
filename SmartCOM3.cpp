
#include "SmartCOM3.h"

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
	STDMETHODIMP IStClient::QueryInterface(REFIID iid, void **ppv)
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
		if (pctinfo == nullptr) return E_NOTIMPL;
		*pctinfo = 1;
		return NOERROR;
	}
	STDMETHODIMP IStClient::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo **pptinfo)
	{
		if (pptinfo == nullptr) return E_INVALIDARG;
		if (itinfo != 0) return DISP_E_BADINDEX;
		*pptinfo = nullptr;
		m_ptinfo->AddRef();
		*pptinfo = m_ptinfo;
		return NOERROR;
	}
	STDMETHODIMP IStClient::GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames,
		LCID lcid, DISPID *rgdispid)
	{
		return m_ptinfo->GetIDsOfNames(rgszNames, cNames, rgdispid);
	}
	STDMETHODIMP IStClient::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
		DISPPARAMS *pdispparams, VARIANT *pvarResult, EXCEPINFO *pexcepinfo, UINT *puArgErr)
	{
		if (pvarResult) VariantInit(pvarResult);

		InvokeDispatch(dispidMember, pdispparams);

		return S_OK;
	}
	const char *GetTypeString(VARTYPE vt)
	{
		switch (vt)
		{
	    case VT_EMPTY: return "VT_EMPTY"; //0,
	    case VT_NULL: return "VT_NULL"; //1,
	    case VT_I2: return "VT_I2"; //2,
	    case VT_I4: return "VT_I4"; //3,
	    case VT_R4: return "VT_R4"; //4,
	    case VT_R8: return "VT_R8"; //5,
	    case VT_CY: return "VT_CY"; //6,
	    case VT_DATE: return "VT_DATE"; //7,
	    case VT_BSTR: return "VT_BSTR"; //8,
	    case VT_DISPATCH: return "VT_DISPATCH"; //9,
	    case VT_ERROR: return "VT_ERROR"; //10,
	    case VT_BOOL: return "VT_BOOL"; //11,
	    case VT_VARIANT: return "VT_VARIANT"; //12,
	    case VT_UNKNOWN: return "VT_UNKNOWN"; //13,
	    case VT_DECIMAL: return "VT_DECIMAL"; //14,
	    case VT_I1: return "VT_I1"; //16,
	    case VT_UI1: return "VT_UI1"; //17,
	    case VT_UI2: return "VT_UI2"; //18,
	    case VT_UI4: return "VT_UI4"; //19,
	    case VT_I8: return "VT_I8"; //20,
	    case VT_UI8: return "VT_UI8"; //21,
	    case VT_INT: return "VT_INT"; //22,
	    case VT_UINT: return "VT_UINT"; //23,
	    case VT_VOID: return "VT_VOID"; //24,
	    case VT_HRESULT: return "VT_HRESULT"; //25,
	    case VT_PTR: return "VT_PTR"; //26,
	    case VT_SAFEARRAY: return "VT_SAFEARRAY"; //27,
	    case VT_CARRAY: return "VT_CARRAY"; //28,
	    case VT_USERDEFINED: return "VT_USERDEFINED"; //29,
	    case VT_LPSTR: return "VT_LPSTR"; //30,
	    case VT_LPWSTR: return "VT_LPWSTR"; //31,
	    case VT_RECORD: return "VT_RECORD"; //36,
	    case VT_INT_PTR: return "VT_INT_PTR"; //37,
	    case VT_UINT_PTR: return "VT_UINT_PTR"; //38,
	    case VT_FILETIME: return "VT_FILETIME"; //64,
	    case VT_BLOB: return "VT_BLOB"; //65,
	    case VT_STREAM: return "VT_STREAM"; //66,
	    case VT_STORAGE: return "VT_STORAGE"; //67,
	    case VT_STREAMED_OBJECT: return "VT_STREAMED_OBJECT"; //68,
	    case VT_STORED_OBJECT: return "VT_STORED_OBJECT"; //69,
	    case VT_BLOB_OBJECT: return "VT_BLOB_OBJECT"; //70,
	    case VT_CF: return "VT_CF"; //71,
	    case VT_CLSID: return "VT_CLSID"; //72,
	    case VT_VERSIONED_STREAM: return "VT_VERSIONED_STREAM"; //73,
	    case VT_BSTR_BLOB: return "VT_BSTR_BLOB"; //0xfff,
	    case VT_VECTOR: return "VT_VECTOR"; //0x1000,
	    case VT_ARRAY: return "VT_ARRAY"; //0x2000,
	    case VT_BYREF: return "VT_BYREF"; //0x4000,
	    case VT_RESERVED: return "VT_RESERVED"; //0x8000,
	    case VT_ILLEGAL: return "VT_ILLEGAL"; //0xffff,
	    default: return "UNKNOWN_VARTYPE";
		}
	}
	void IStClient::InvokeDispatch(DISPID dispidMember, DISPPARAMS *pdispparams)
	{
#if 0 // DEBUG INVOKE PARAMS
{
	wchar_t *names[1];
	uint32_t count = 0;
	m_ptinfo->GetNames(dispidMember,names,1,&count);
	if (count > 0) printf("%s (", ws2s(names[0]).c_str());
	for (int i = pdispparams->cArgs - 1; i >= 0; i--)
	{
		printf("%s", GetTypeString(pdispparams->rgvarg[i].vt));
		if (i > 0) printf(" ");
		else printf(")\n");
	}
}
#endif
		switch (dispidMember)
		{
		case 0x01: {
		   Connected();
		   break;
		}
		case 0x02: {
		   Disconnected(
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string reason
		   );
		   break;
		}
		case 0x03: {
		   UpdateQuote(
			   ws2s(pdispparams->rgvarg[22].bstrVal).c_str(), // std::string symbol
			   d2t(pdispparams->rgvarg[21].dblVal), // time_t datetime
			   static_cast<double>(pdispparams->rgvarg[20].dblVal), // double open
			   static_cast<double>(pdispparams->rgvarg[19].dblVal), // double high
			   static_cast<double>(pdispparams->rgvarg[18].dblVal), // double low
			   static_cast<double>(pdispparams->rgvarg[17].dblVal), // double close
			   static_cast<double>(pdispparams->rgvarg[16].dblVal), // double last
			   static_cast<double>(pdispparams->rgvarg[15].dblVal), // double volume
			   static_cast<double>(pdispparams->rgvarg[14].dblVal), // double size
			   static_cast<double>(pdispparams->rgvarg[13].dblVal), // double bid
			   static_cast<double>(pdispparams->rgvarg[12].dblVal), // double ask
			   static_cast<double>(pdispparams->rgvarg[11].dblVal), // double bidsize
			   static_cast<double>(pdispparams->rgvarg[10].dblVal), // double asksize
			   static_cast<double>(pdispparams->rgvarg[9].dblVal), // double open_int
			   static_cast<double>(pdispparams->rgvarg[8].dblVal), // double go_buy
			   static_cast<double>(pdispparams->rgvarg[7].dblVal), // double go_sell
			   static_cast<double>(pdispparams->rgvarg[6].dblVal), // double go_base
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double go_base_backed
			   static_cast<double>(pdispparams->rgvarg[4].dblVal), // double high_limit
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double low_limit
			   static_cast<TradingStatus>(pdispparams->rgvarg[2].lVal), // long trading_status
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double volat
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double theor_price
		   );
		   break;
		}
		case 0x04: {
		   UpdateBidAsk(
			   ws2s(pdispparams->rgvarg[6].bstrVal).c_str(), // std::string symbol
			   static_cast<long>(pdispparams->rgvarg[5].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[4].lVal), // long nrows
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double bid
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double bidsize
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double ask
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double asksize
		   );
		   break;
		}
		case 0x05: {
		   AddTick(
			   ws2s(pdispparams->rgvarg[5].bstrVal).c_str(), // std::string symbol
			   d2t(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double volume
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string tradeno
			   static_cast<OrderAction>(pdispparams->rgvarg[0].bVal) // OrderAction action
		   );
		   break;
		}
		case 0x06: {
		   AddBar(
			   static_cast<long>(pdispparams->rgvarg[10].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[9].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[8].bstrVal).c_str(), // std::string symbol
			   static_cast<BarInterval>(pdispparams->rgvarg[7].bVal), // BarInterval interval
			   d2t(pdispparams->rgvarg[6].dblVal), // time_t datetime
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double open
			   static_cast<double>(pdispparams->rgvarg[4].dblVal), // double high
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double low
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double close
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double volume
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double open_int
		   );
		   break;
		}
		case 0x07: {
		   SetPortfolio(
			   ws2s(pdispparams->rgvarg[4].bstrVal).c_str(), // std::string portfolio
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double cash
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double leverage
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double comission
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double saldo
		   );
		   break;
		}
		case 0x08: {
		   AddTrade(
			   ws2s(pdispparams->rgvarg[6].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[5].bstrVal).c_str(), // std::string symbol
			   ws2s(pdispparams->rgvarg[4].bstrVal).c_str(), // std::string orderid
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double amount
			   d2t(pdispparams->rgvarg[1].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string tradeno
		   );
		   break;
		}
		case 0x09: {
		   UpdateOrder(
			   ws2s(pdispparams->rgvarg[14].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[13].bstrVal).c_str(), // std::string symbol
			   static_cast<OrderState>(pdispparams->rgvarg[12].bVal), // OrderState state
			   static_cast<OrderAction>(pdispparams->rgvarg[11].bVal), // OrderAction action
			   static_cast<OrderType>(pdispparams->rgvarg[10].bVal), // OrderType type
			   static_cast<OrderValidity>(pdispparams->rgvarg[9].bVal), // OrderValidity validity
			   static_cast<double>(pdispparams->rgvarg[8].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[7].dblVal), // double amount
			   static_cast<double>(pdispparams->rgvarg[6].dblVal), // double stop
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double filled
			   d2t(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[3].bstrVal).c_str(), // std::string orderid
			   ws2s(pdispparams->rgvarg[2].bstrVal).c_str(), // std::string orderno
			   static_cast<long>(pdispparams->rgvarg[1].lVal), // long status_mask
			   static_cast<long>(pdispparams->rgvarg[0].lVal) // long cookie
		   );
		   break;
		}
		case 0x0a: {
		   UpdatePosition(
			   ws2s(pdispparams->rgvarg[4].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[3].bstrVal).c_str(), // std::string symbol
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double avprice
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double amount
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double planned
		   );
		   break;
		}
		case 0x0f: {
		   AddTickHistory(
			   static_cast<long>(pdispparams->rgvarg[7].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[6].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[5].bstrVal).c_str(), // std::string symbol
			   d2t(pdispparams->rgvarg[4].dblVal), // time_t datetime
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[2].dblVal), // double volume
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string tradeno
			   static_cast<OrderAction>(pdispparams->rgvarg[0].bVal) // OrderAction action
		   );
		   break;
		}
		case 0x14: {
		   AddSymbol(
			   static_cast<long>(pdispparams->rgvarg[14].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[13].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[12].bstrVal).c_str(), // std::string symbol
			   ws2s(pdispparams->rgvarg[11].bstrVal).c_str(), // std::string short_name
			   ws2s(pdispparams->rgvarg[10].bstrVal).c_str(), // std::string int_name
			   ws2s(pdispparams->rgvarg[9].bstrVal).c_str(), // std::string type
			   static_cast<long>(pdispparams->rgvarg[8].lVal), // long decimals
			   static_cast<long>(pdispparams->rgvarg[7].lVal), // long lot_size
			   static_cast<double>(pdispparams->rgvarg[6].dblVal), // double punkt
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double step
			   ws2s(pdispparams->rgvarg[4].bstrVal).c_str(), // std::string sec_ext_id
			   ws2s(pdispparams->rgvarg[3].bstrVal).c_str(), // std::string sec_exch_name
			   d2t(pdispparams->rgvarg[2].dblVal), // time_t expiry_date
			   static_cast<double>(pdispparams->rgvarg[1].dblVal), // double days_before_expiry
			   static_cast<double>(pdispparams->rgvarg[0].dblVal) // double strike
		   );
		   break;
		}
		case 0x1e: {
		   OrderSucceeded(
			   static_cast<long>(pdispparams->rgvarg[1].lVal), // long cookie
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderid
		   );
		   break;
		}
		case 0x1f: {
		   OrderFailed(
			   static_cast<long>(pdispparams->rgvarg[2].lVal), // long cookie
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string orderid
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string reason
		   );
		   break;
		}
		case 0x20: {
		   AddPortfolio(
			   static_cast<long>(pdispparams->rgvarg[4].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[3].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[2].bstrVal).c_str(), // std::string portfolioName
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string portfolioExch
			   static_cast<PortfolioStatus>(pdispparams->rgvarg[0].bVal) // PortfolioStatus portfolioStatus
		   );
		   break;
		}
		case 0x21: {
		   SetSubscribtionCheckResult(
			   static_cast<long>(pdispparams->rgvarg[0].lVal) // long result
		   );
		   break;
		}
		case 0x22: {
		   SetMyTrade(
			   static_cast<long>(pdispparams->rgvarg[9].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[8].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[7].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[6].bstrVal).c_str(), // std::string symbol
			   d2t(pdispparams->rgvarg[5].dblVal), // time_t datetime
			   static_cast<double>(pdispparams->rgvarg[4].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double volume
			   ws2s(pdispparams->rgvarg[2].bstrVal).c_str(), // std::string tradeno
			   static_cast<OrderAction>(pdispparams->rgvarg[1].bVal), // OrderAction buysell
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderno
		   );
		   break;
		}
		case 0x23: {
		   SetMyOrder(
			   static_cast<long>(pdispparams->rgvarg[15].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[14].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[13].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[12].bstrVal).c_str(), // std::string symbol
			   static_cast<OrderState>(pdispparams->rgvarg[11].bVal), // OrderState state
			   static_cast<OrderAction>(pdispparams->rgvarg[10].bVal), // OrderAction action
			   static_cast<OrderType>(pdispparams->rgvarg[9].bVal), // OrderType type
			   static_cast<OrderValidity>(pdispparams->rgvarg[8].bVal), // OrderValidity validity
			   static_cast<double>(pdispparams->rgvarg[7].dblVal), // double price
			   static_cast<double>(pdispparams->rgvarg[6].dblVal), // double amount
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double stop
			   static_cast<double>(pdispparams->rgvarg[4].dblVal), // double filled
			   d2t(pdispparams->rgvarg[3].dblVal), // time_t datetime
			   ws2s(pdispparams->rgvarg[2].bstrVal).c_str(), // std::string id
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string no
			   static_cast<long>(pdispparams->rgvarg[0].lVal) // long cookie
		   );
		   break;
		}
		case 0x25: {
		   SetMyClosePos(
			   static_cast<long>(pdispparams->rgvarg[9].lVal), // long row
			   static_cast<long>(pdispparams->rgvarg[8].lVal), // long nrows
			   ws2s(pdispparams->rgvarg[7].bstrVal).c_str(), // std::string portfolio
			   ws2s(pdispparams->rgvarg[6].bstrVal).c_str(), // std::string symbol
			   static_cast<double>(pdispparams->rgvarg[5].dblVal), // double amount
			   static_cast<double>(pdispparams->rgvarg[4].dblVal), // double price_buy
			   static_cast<double>(pdispparams->rgvarg[3].dblVal), // double price_sell
			   d2t(pdispparams->rgvarg[2].dblVal), // time_t postime
			   ws2s(pdispparams->rgvarg[1].bstrVal).c_str(), // std::string order_open
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string order_close
		   );
		   break;
		}
		case 0x26: {
		   OrderCancelSucceeded(
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderid
		   );
		   break;
		}
		case 0x27: {
		   OrderCancelFailed(
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderid
		   );
		   break;
		}
		case 0x28: {
		   OrderMoveSucceeded(
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderid
		   );
		   break;
		}
		case 0x29: {
		   OrderMoveFailed(
			   ws2s(pdispparams->rgvarg[0].bstrVal).c_str() // std::string orderid
		   );
		   break;
		}
		default: {
			throw std::runtime_error(
				("IStClient::InvokeDispatch(" + std::to_string(dispidMember) + ") unknown code").c_str());
		}
		}
	}

	/* COM HELPERS */

	std::mutex IStClient::s_ApartmentsInitializationMutex;
	bool IStClient::s_ApartmentsInitializationFlag = false;
	void IStClient::InitializeApartments()
	{
		s_ApartmentsInitializationMutex.lock();

		if (s_ApartmentsInitializationFlag == false)
		{
			if (S_OK != CoInitializeEx(nullptr, COINIT_MULTITHREADED))
			{
				throw std::runtime_error("IStClient::InitializeApartments() "
					"CoInitializeEx(nullptr,COINIT_MULTITHREADED)");
			}
			s_ApartmentsInitializationFlag = true;
		}
		s_ApartmentsInitializationMutex.unlock();
	}
	void IStClient::UninitializeApartments()
	{
		s_ApartmentsInitializationMutex.lock();

		if (s_ApartmentsInitializationFlag == true)
		{
			CoUninitialize();
			s_ApartmentsInitializationFlag = false;
		}
		s_ApartmentsInitializationMutex.unlock();
	}
	HRESULT IStClient::Advise()
	{
		HRESULT hr = S_FALSE;
		IConnectionPointContainer* cpc;

		if (S_OK == m_IStServer->QueryInterface(IID_IConnectionPointContainer, (void**)&cpc))
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
		if (m_dwCookie)
		{
			m_pIConnectionPoint->Unadvise(m_dwCookie);
			m_pIConnectionPoint->Release();
			m_dwCookie = 0;
		}
	}
	
	/* Constructor / destructor */

	IStClient::IStClient(bool autoInitializeApartments)
		: m_cRef(1), m_dwCookie(0)
	{
		if (autoInitializeApartments) InitializeApartments();

		LPTYPELIB pTypeLib;
		if (S_OK != LoadRegTypeLib(LIBID_SmartCOM3Lib, 1, 0, LOCALE_SYSTEM_DEFAULT, &pTypeLib))
		{
			throw std::runtime_error("IStClient::IStClient() LoadRegTypeLib. SmartCOM3.dll not installed?");
		}
		if (S_OK != pTypeLib->GetTypeInfoOfGuid(DIID_IStClient, &m_ptinfo))
		{
			throw std::runtime_error("IStClient::IStClient() GetTypeInfoOfGuid");
		}
		pTypeLib->Release();

		if (S_OK != CoCreateInstance(CLSID_StServer, nullptr, CLSCTX_INPROC_SERVER, IID_IStServer,
				reinterpret_cast<void**>(&m_IStServer)))
		{
			throw std::runtime_error("IStClient::IStClient() CoCreateInstance(Server)");
		}
		if (S_OK != Advise())
		{
			throw std::runtime_error("IStClient::IStClient() COM Advise");
		}
		if (S_OK != CoCreateInstance(CLSID_StServer, nullptr, CLSCTX_INPROC_SERVER,
				IID_ISmartComVersion, reinterpret_cast<void**>(&m_ISmartComVersion)))
		{
			throw std::runtime_error("IStClient::IStClient() CoCreateInstance(Version)");
		}
	}
	IStClient::~IStClient()
	{
		UnAdvise();
		m_IStServer->Release();
		m_ISmartComVersion->Release();
		m_ptinfo->Release();
	}

	/* SmartCOM3 METHODS */

	ErrorCode IStClient::ListenQuotes(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ListenQuotes(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::CancelQuotes(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_CancelQuotes(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::ListenBidAsks(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ListenBidAsks(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::CancelBidAsks(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_CancelBidAsks(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::ListenTicks(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ListenTicks(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::CancelTicks(const char *symbol)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_CancelTicks(s2ws(symbol).c_str()));
	}
	ErrorCode IStClient::GetBars(const char *symbol, BarInterval interval, time_t since, long count)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetBars(s2ws(symbol).c_str(), interval, t2d(since), count));
	}
	ErrorCode IStClient::ListenPortfolio(const char *portfolio)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ListenPortfolio(s2ws(portfolio).c_str()));
	}
	ErrorCode IStClient::CancelPortfolio(const char *portfolio)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_CancelPortfolio(s2ws(portfolio).c_str()));
	}
	ErrorCode IStClient::PlaceOrder(const char *portfolio, const char *symbol,
		OrderAction action, OrderType type, OrderValidity validity,
		double price, double amount, double stop, long cookie)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_PlaceOrder(s2ws(portfolio).c_str(),
			s2ws(symbol).c_str(), action, type, validity, price, amount, stop, cookie));
	}
	ErrorCode IStClient::CancelOrder(const char *portfolio, const char *symbol, const char *orderid)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_CancelOrder(s2ws(portfolio).c_str(),
			s2ws(symbol).c_str(), s2ws(orderid).c_str()));
	}
	ErrorCode IStClient::MoveOrder(const char *portfolio, const char *orderid, double targetPrice)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_MoveOrder(s2ws(portfolio).c_str(),
			s2ws(orderid).c_str(), targetPrice));
	}
	ErrorCode IStClient::GetSymbols()
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetSymbols());
	}
	ErrorCode IStClient::IsConnected(bool *connected)
	{
		short raw_connected;
		ErrorCode ercode = static_cast<ErrorCode>(m_IStServer->raw_IsConnected(&raw_connected));
		if (ercode == ErrorCode_Success) {
			if (raw_connected == 0) *connected = false; // *connected = bool(result); // slow performance warning
			else *connected = true;
		}
		return ercode;
	}
	ErrorCode IStClient::Connect(const char *ip, unsigned short port, const char *login, const char *password)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_connect(s2ws(ip).c_str(), port,
			s2ws(login).c_str(), s2ws(password).c_str()));
	}
	ErrorCode IStClient::Disconnect()
	{
		return static_cast<ErrorCode>(m_IStServer->raw_disconnect());
	}
	ErrorCode IStClient::GetPortfolioList()
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetPortfolioList());
	}
	ErrorCode IStClient::GetMyOrders(long onlyActive, const char *portfolio)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetMyOrders(onlyActive, s2ws(portfolio).c_str()));
	}
	ErrorCode IStClient::GetMyTrades(const char *portfolio)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetMyTrades(s2ws(portfolio).c_str()));
	}
	ErrorCode IStClient::GetMyClosePos(const char *portfolio)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetMyClosePos(s2ws(portfolio).c_str()));
	}
	ErrorCode IStClient::GetTrades(const char *symbol, time_t from, long count)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_GetTrades(s2ws(symbol).c_str(), t2d(from), count));
	}
	ErrorCode IStClient::ConfigureClient(const char *paramsSet)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ConfigureClient(s2ws(paramsSet).c_str()));
	}
	ErrorCode IStClient::ConfigureServer(const char *paramsSet)
	{
		return static_cast<ErrorCode>(m_IStServer->raw_ConfigureServer(s2ws(paramsSet).c_str()));
	}
	ErrorCode IStClient::GetMoneyAccount(const char *portfolioID, std::string *portfolioMO)
	{
		wchar_t *raw_portfoliomo;
		ErrorCode ercode = static_cast<ErrorCode>(
			m_IStServer->raw_GetMoneyAccount(s2ws(portfolioID).c_str(), &raw_portfoliomo));
		if (ercode == ErrorCode_Success) *portfolioMO = ws2s(raw_portfoliomo);
		return ercode;
	}

	/* SmartCOM3 VERSION METHODS */

	ErrorCode IStClient::GetServerVersionString(std::string *version)
	{
		wchar_t *raw_version;
		ErrorCode ercode = static_cast<ErrorCode>(m_ISmartComVersion->raw_GetServerVersionString(&raw_version));
		if (ercode == ErrorCode_Success) *version = ws2s(raw_version);
		return ercode;
	}
	ErrorCode IStClient::GetServerVersion(long *major, long *minor, long *build, long *rev)
	{
		return static_cast<ErrorCode>(m_ISmartComVersion->raw_GetServerVersion(major, minor, build, rev));
	}
	ErrorCode IStClient::GetClientVersionString(std::string *version)
	{
		wchar_t *raw_version;
		ErrorCode ercode = static_cast<ErrorCode>(m_ISmartComVersion->raw_GetStClientVersionString(&raw_version));
		if (ercode == ErrorCode_Success) *version = ws2s(raw_version);
		return ercode;
	}
	ErrorCode IStClient::GetClientVersion(long *major, long *minor, long *build, long *rev)
	{
		return static_cast<ErrorCode>(m_ISmartComVersion->raw_GetStClientVersion(major, minor, build, rev));
	}
}
