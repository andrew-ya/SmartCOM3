
#include "Test.h"

void TestRobot::Connected()
{
	printf("TestRobot::Connected()\n");
	this->GetSymbols();
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
	long trading_status,
	double volat,
	double theor_price){}
void TestRobot::UpdateBidAsk(
	const char *symbol,
	long row,
	long nrows,
	double bid,
	double bidsize,
	double ask,
	double asksize){}
void TestRobot::AddTick(
	const char *symbol,
	time_t datetime,
	double price,
	double volume,
	const char *tradeno,
	OrderAction action){}
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
	double open_int){}
void TestRobot::SetPortfolio(
	const char *portfolio,
	double cash,
	double leverage,
	double comission,
	double saldo){}
void TestRobot::AddTrade(
	const char *portfolio,
	const char *symbol,
	const char *orderid,
	double price,
	double amount,
	time_t datetime,
	const char *tradeno){}
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
	long cookie){}
void TestRobot::UpdatePosition(
	const char *portfolio,
	const char *symbol,
	double avprice,
	double amount,
	double planned){}
void TestRobot::AddTickHistory(
	long row,
	long nrows,
	const char *symbol,
	time_t datetime,
	double price,
	double volume,
	const char *tradeno,
	OrderAction action){}
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
	if (row < 10) printf("TestRobot::AddSymbol(%s) %ld of %ld\n", symbol, row + 1, nrows);
	else if (row == 10) printf(".....\n");
	else if (row == nrows - 1) printf("TestRobot::AddSymbol() added %ld of %ld\n", row + 1, nrows);
}
void TestRobot::OrderSucceeded(long cookie, const char *orderid){}
void TestRobot::OrderFailed(long cookie, const char *orderid, const char *reason){}
void TestRobot::AddPortfolio(
	long row,
	long nrows,
	const char *portfolioName,
	const char *portfolioExch,
	PortfolioStatus portfolioStatus){}
void TestRobot::SetSubscribtionCheckReult(long result){}
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
	const char *orderno){}
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
	long cookie){}
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
	const char *order_close){}
void TestRobot::OrderCancelSucceeded(const char *orderid){}
void TestRobot::OrderCancelFailed(const char *orderid){}
void TestRobot::OrderMoveSucceeded(const char *orderid){}
void TestRobot::OrderMoveFailed(const char *orderid){}


int main(int argc, char **argv)
{
	TestRobot::InitializeApartments();

	TestRobot *robot = new TestRobot();

	printf("SmartCOM3 version: %s\n\n", robot->GetClientVersionString().c_str());

	printf("Connecting...\n");
	robot->Connect("mxdemo.ittrade.ru", 8443, "LOGIN", "PASSWORD");

	printf("Press ENTER to disconnect\n");
	getchar();

	if (robot->IsConnected()) {
		printf("Disconnecting...\n");
		robot->Disconnect();
	} else {
		printf("Not connected\n");
	}

	printf("Press ENTER to exit\n");
	getchar();

	delete robot;

	TestRobot::UninitializeApartments();
	return 0;
}
