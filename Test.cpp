
#include "Test.h"

void TestRobot::Connected()
{
	printf("TestRobot::Connected()\n");
	this->GetSymbols();
}
void TestRobot::Disconnected(std::string reason)
{
	printf("TestRobot::Disconnected(%s)\n", reason.c_str());
}
void TestRobot::UpdateQuote(
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
	double theor_price){}
void TestRobot::UpdateBidAsk(
	std::string symbol,
	long row,
	long nrows,
	double bid,
	double bidsize,
	double ask,
	double asksize){}
void TestRobot::AddTick(
	std::string symbol,
	time_t datetime,
	double price,
	double volume,
	std::string tradeno,
	OrderAction action){}
void TestRobot::AddBar(
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
	double open_int){}
void TestRobot::SetPortfolio(
	std::string portfolio,
	double cash,
	double leverage,
	double comission,
	double saldo){}
void TestRobot::AddTrade(
	std::string portfolio,
	std::string symbol,
	std::string orderid,
	double price,
	double amount,
	time_t datetime,
	std::string tradeno){}
void TestRobot::UpdateOrder(
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
	long cookie){}
void TestRobot::UpdatePosition(
	std::string portfolio,
	std::string symbol,
	double avprice,
	double amount,
	double planned){}
void TestRobot::AddTickHistory(
	long row,
	long nrows,
	std::string symbol,
	time_t datetime,
	double price,
	double volume,
	std::string tradeno,
	OrderAction action){}
void TestRobot::AddSymbol(
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
	double strike)
{
	if (row < 10) printf("TestRobot::AddSymbol(%s) %d of %d\n", symbol.c_str(), row + 1, nrows);
	else if (row == 10) printf(".....\n");
	else if (row == nrows - 1) printf("TestRobot::AddSymbol() added %d of %d\n", row + 1, nrows);
}
void TestRobot::OrderSucceeded(long cookie, std::string orderid){}
void TestRobot::OrderFailed(long cookie, std::string orderid, std::string reason){}
void TestRobot::AddPortfolio(
	long row,
	long nrows,
	std::string portfolioName,
	std::string portfolioExch,
	PortfolioStatus portfolioStatus){}
void TestRobot::SetSubscribtionCheckReult(long result){}
void TestRobot::SetMyTrade(
	long row,
	long nrows,
	std::string portfolio,
	std::string symbol,
	time_t datetime,
	double price,
	double volume,
	std::string tradeno,
	OrderAction buysell,
	std::string orderno){}
void TestRobot::SetMyOrder(
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
	long cookie){}
void TestRobot::SetMyClosePos(
	long row,
	long nrows,
	std::string portfolio,
	std::string symbol,
	double amount,
	double price_buy,
	double price_sell,
	time_t postime,
	std::string order_open,
	std::string order_close){}
void TestRobot::OrderCancelSucceeded(std::string orderid){}
void TestRobot::OrderCancelFailed(std::string orderid){}
void TestRobot::OrderMoveSucceeded(std::string orderid){}
void TestRobot::OrderMoveFailed(std::string orderid){}


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
