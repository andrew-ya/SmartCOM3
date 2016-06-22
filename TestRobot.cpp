
#include "TestRobot.h"

TestRobot::TestRobot(const char *server, unsigned short port, const char *login, const char *password)
{
	printf("TestRobot::TestRobot()\n");

	symbols["SBER"] = "";
	symbols["VTBR"] = "";
	symbols["GAZP"] = "";
	symbols["ROSN"] = "";

	std::string version = "UNKNOWN";
	ErrorCode ercode = GetClientVersionString(&version);
	printf("TestRobot::GetClientVersionString() %s SmartCOM3 dll version: %s\n",
		GetErrorCodeString(ercode), version.c_str());

	printf("TestRobot::ConfigureClient() %s\n", GetErrorCodeString(
		ConfigureClient(
		"CalcPlannedPos=no;"
		"asyncSocketConnectionMode=yes;"
		"logLevel=4;"
		"logFilePath=C:\\logs;"))); // to store logs in C:\ on Windows you must have administrator permission

	printf("TestRobot::ConfigureServer() %s\n", GetErrorCodeString(
		ConfigureServer(
		"pingTimeout=2;"
		"logLevel=4;"
		"logFilePath=C:\\logs;"))); // to store logs in C:\ on Windows you must have administrator permission

	ercode = Connect(server, port, login, password);
	// for demo server, if bad user name or password, lib calls Disconnected(reason) with zero length of reason string
	// but if real - correctly calls Disconnected(reason) with "Bad user name or password"

	if (ercode == ErrorCode_Success) {
		printf("TestRobot::Connect() Connecting to %s:%d with login %s, please wait...\n", server, port, login);
	} else {
		printf("TestRobot::Connect() Connection error: %s. "
			"Possibly log path (C:\\logs) doesn't exist or "
			"you don't have write permission.\n", GetErrorCodeString(ercode));
		exit(1);
	}

	printf("TestRobot::TestRobot() OK\n\n");
}
TestRobot::~TestRobot()
{
	printf("TestRobot::~TestRobot()\n");

	bool connected;
	IsConnected(&connected);
	if (connected) {
		printf("TestRobot::~TestRobot() Disconnecting...\n");
		Disconnect();
	} else {
		printf("TestRobot::~TestRobot() Not connected\n");
	}

	printf("TestRobot::~TestRobot() OK\n");
}

/* SmartCOM3 events implementation */

void TestRobot::Connected()
{
	printf("\nTestRobot::Connected()\n");
	printf("TestRobot::GetSymbols() %s\n", GetErrorCodeString(GetSymbols()));
	printf("TestRobot::GetPortfolioList() %s\n", GetErrorCodeString(GetPortfolioList()));
}
void TestRobot::Disconnected(const char *reason)
{
	printf("TestRobot::Disconnected(%s)\n", reason);
}
void TestRobot::UpdateQuote(
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
	TradingStatus trading_status,
	double volat,
	double theor_price)
{
	printf("TestRobot::UpdateQuote(%s) %s ask %.5f bid %.5f status %d - %s\n",
		symbol, GetDatetimeString(datetime).c_str(), ask, bid, trading_status, GetTradingStatusString(trading_status));
}
void TestRobot::UpdateBidAsk(
	const char *symbol,
	long row,
	long nrows,
	double bid,
	double bidsize,
	double ask,
	double asksize)
{
	if (row == 0) printf("TestRobot::UpdateBidAsk() %s %ld:%ld %.5f %.f %.5f %.f\n",
		symbol, row, nrows, bid, bidsize, ask, asksize);
}
void TestRobot::AddTick(
	const char *symbol,
	time_t datetime,
	double price,
	double volume,
	const char *tradeno,
	OrderAction action)
{
	printf("TestRobot::AddTick(%s) %s %.5f %.f %s %s\n",
		symbol, GetDatetimeString(datetime).c_str(), price, volume, tradeno, GetOrderActionString(action));
}
void TestRobot::AddBar(
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
	double open_int)
{
	if (row == 0 || row == nrows - 1)
		printf("TestRobot::AddBar() %ld:%ld %s %s %s %.5f %.5f %.5f %.5f %.f %.f\n",
			row, nrows, symbol,
			GetBarIntervalString(interval),
			GetDatetimeString(datetime).c_str(),
			open, high, low, close, volume, open_int);
}
void TestRobot::SetPortfolio(
	const char *portfolio,
	double cash,
	double leverage,
	double comission,
	double saldo)
{
	printf("TestRobot::SetPortfolio() %s %.2f %.f %.2f %.2f\n",
		portfolio, cash, leverage, comission, saldo);
}
void TestRobot::AddTrade(
	const char *portfolio,
	const char *symbol,
	const char *orderid,
	double price,
	double amount,
	time_t datetime,
	const char *tradeno)
{
	printf("TestRobot::AddTrade() %s %s %s %.5f %.f %s %sf\n",
		portfolio, symbol, orderid, price, amount,
		GetDatetimeString(datetime).c_str(),
		tradeno);
}
void TestRobot::UpdateOrder(
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
	long cookie)
{
	printf("TestRobot::UpdateOrder() %s %s %s %s %s %s %.5f %.f %.5f %.f %s %s %s %ld %ld\n",
		portfolio, symbol,
		GetOrderStateString(state),
		GetOrderActionString(action),
		GetOrderTypeString(type),
		GetOrderValidityString(validity),
		price, amount, stop, filled,
		GetDatetimeString(datetime).c_str(),
		orderid, orderno, status_mask, cookie);
}
void TestRobot::UpdatePosition(
	const char *portfolio,
	const char *symbol,
	double avprice,
	double amount,
	double planned)
{
	printf("TestRobot::UpdatePosition() %s %s %.f %.f %.f\n",
		portfolio, symbol, avprice, amount, planned);
}
void TestRobot::AddTickHistory(
	long row,
	long nrows,
	const char *symbol,
	time_t datetime,
	double price,
	double volume,
	const char *tradeno,
	OrderAction action)
{
	printf("TestRobot::AddTickHistory() %ld:%ld %s %s %.5f %.f %s %s\n",
		row, nrows, symbol,
		GetDatetimeString(datetime).c_str(),
		price, volume, tradeno,
		GetOrderActionString(action));
}
void TestRobot::AddSymbol(
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
	double strike)
{
	auto it = symbols.find(symbol);
	if (it != symbols.end()) it->second = short_name;
	if (row == nrows - 1) {
		printf("TestRobot::AddSymbol() received all of %ld symbols\n", nrows);
		for (auto &pair : symbols) {
			printf("TestRobot::AddSymbol() added symbol '%s' with short_name '%s'\n",
				pair.first.c_str(), pair.second.c_str());
		}
		//printf("TestRobot::ListenQuotes(%s) %s\n", symbols.begin()->first.c_str(), GetErrorCodeString(ListenQuotes(symbols.begin()->first.c_str())));
		//printf("TestRobot::ListenBidAsks(%s) %s\n", symbols.begin()->first.c_str(), GetErrorCodeString(ListenBidAsks(symbols.begin()->first.c_str())));
		printf("TestRobot::ListenTicks(%s) %s\n", symbols.begin()->first.c_str(), GetErrorCodeString(ListenTicks(symbols.begin()->first.c_str())));
	}
}
void TestRobot::OrderSucceeded(
	long cookie,
	const char *orderid)
{
	printf("TestRobot::OrderSucceeded() %ld %s\n", cookie, orderid);
}
void TestRobot::OrderFailed(
	long cookie,
	const char *orderid,
	const char *reason)
{
	printf("TestRobot::OrderFailed() %ld %s %s\n", cookie, orderid, reason);
}
void TestRobot::AddPortfolio(
	long row,
	long nrows,
	const char *portfolioName,
	const char *portfolioExch,
	PortfolioStatus portfolioStatus)
{
	printf("TestRobot::AddPortfolio(%ld/%ld) name %s exchage %s status %s\n",
		row, nrows, portfolioName, portfolioExch, GetPortfolioStatusString(portfolioStatus));
}
void TestRobot::SetSubscribtionCheckResult(long result)
{
	printf("TestRobot::SetSubscribtionCheckResult() %ld\n", result);
}
void TestRobot::SetMyTrade(
	long row,
	long nrows,
	const char *portfolio,
	const char *symbol,
	time_t datetime,
	double price,
	double volume,
	const char *tradeno,
	OrderAction buysell,
	const char *orderno)
{
	printf("TestRobot::SetMyTrade() %ld:%ld %s %s %s %.5f %.f %s %s %s\n",
		row, nrows, portfolio, symbol,
		GetDatetimeString(datetime).c_str(),
		price, volume, tradeno,
		GetOrderActionString(buysell),
		orderno);
}
void TestRobot::SetMyOrder(
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
	long cookie)
{
	printf("TestRobot::SetMyOrder() %ld:%ld %s %s %s %s %s %s %.5f %.f %.5f %.f %s %s %s %ld\n",
		row, nrows, portfolio, symbol,
		GetOrderStateString(state),
		GetOrderActionString(action),
		GetOrderTypeString(type),
		GetOrderValidityString(validity),
		price, amount, stop, filled,
		GetDatetimeString(datetime).c_str(),
		id, no, cookie);
}
void TestRobot::SetMyClosePos(
	long row,
	long nrows,
	const char *portfolio,
	const char *symbol,
	double amount,
	double price_buy,
	double price_sell,
	time_t postime,
	const char *order_open,
	const char *order_close)
{
	printf("TestRobot::SetMyClosePos() %ld:%ld %s %s %.f %.5f %.5f %s %s %s\n",
		row, nrows - 1, portfolio, symbol, amount, price_buy, price_sell,
		GetDatetimeString(postime).c_str(), order_open, order_close);
}
void TestRobot::OrderCancelSucceeded(const char *orderid)
{
	printf("TestRobot::OrderCancelSucceeded(%s)\n", orderid);
}
void TestRobot::OrderCancelFailed(const char *orderid)
{
	printf("TestRobot::OrderCancelFailed(%s)\n", orderid);
}
void TestRobot::OrderMoveSucceeded(const char *orderid)
{
	printf("TestRobot::OrderMoveSucceeded(%s)\n", orderid);
}
void TestRobot::OrderMoveFailed(const char *orderid)
{
	printf("TestRobot::OrderMoveFailed(%s)\n", orderid);
}


int main(int argc, char **argv)
{
	SetConsoleOutputCP(CP_UTF8);

	if (argc != 5) {
		printf("Usage: SmartCOM3.exe <server> <port> <login> <password>\n");
		printf("E.g.: SmartCOM3.exe mxdemo.ittrade.ru 8443 LOGIN PASSWORD\n");
		return 0;
	}

	const char *server = argv[1];
	unsigned int port = atoi(argv[2]);
	assert(port > 0 && port <= 65535);
	const char *login = argv[3];
	const char *password = argv[4];

	TestRobot *robot = nullptr;

	try {
		robot = new TestRobot(server,port,login,password);
	} catch (std::runtime_error &er) {
		printf("Robot error: %s\n", er.what());
		return 0;
	}

	printf("Press ENTER to exit\n");
	getchar();

	delete robot;

	TestRobot::UninitializeApartments();

	return 0;
}
