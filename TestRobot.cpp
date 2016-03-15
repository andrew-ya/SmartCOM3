

#include "SmartCOM3.h"
#include <map>
#include <string>
#include <stdlib.h>
#include <assert.h>


using namespace SmartCOM3;


class TestRobot : public SmartCOM3::IStClient
{
public:
	std::map<std::string,std::string> symbols;
public:
	TestRobot()
	{
		symbols["SBER"] = "";
		symbols["VTBR"] = "";
		symbols["GAZP"] = "";
		symbols["ROSN"] = "";
	}
private:
	void Connected()
	{
		printf("TestRobot::Connected()\n");
		this->GetSymbols();
	}
	void Disconnected(const char *reason)
	{
		printf("TestRobot::Disconnected(%s)\n", reason);
	}
	void UpdateQuote(
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
	void UpdateBidAsk(
		const char *symbol,
		long row,
		long nrows,
		double bid,
		double bidsize,
		double ask,
		double asksize){}
	void AddTick(
		const char *symbol,
		time_t datetime,
		double price,
		double volume,
		const char *tradeno,
		OrderAction action){}
	void AddBar(
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
	void SetPortfolio(
		const char *portfolio,
		double cash,
		double leverage,
		double comission,
		double saldo){}
	void AddTrade(
		const char *portfolio,
		const char *symbol,
		const char *orderid,
		double price,
		double amount,
		time_t datetime,
		const char *tradeno){}
	void UpdateOrder(
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
	void UpdatePosition(
		const char *portfolio,
		const char *symbol,
		double avprice,
		double amount,
		double planned){}
	void AddTickHistory(
		long row,
		long nrows,
		const char *symbol,
		time_t datetime,
		double price,
		double volume,
		const char *tradeno,
		OrderAction action){}
	void AddSymbol(
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
		}
	}
	void OrderSucceeded(long cookie, const char *orderid){}
	void OrderFailed(long cookie, const char *orderid, const char *reason){}
	void AddPortfolio(
		long row,
		long nrows,
		const char *portfolioName,
		const char *portfolioExch,
		PortfolioStatus portfolioStatus){}
	void SetSubscribtionCheckReult(long result){}
	void SetMyTrade(
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
	void SetMyOrder(
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
	void SetMyClosePos(
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
	void OrderCancelSucceeded(const char *orderid){}
	void OrderCancelFailed(const char *orderid){}
	void OrderMoveSucceeded(const char *orderid){}
	void OrderMoveFailed(const char *orderid){}
};


int main(int argc, char **argv)
{
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

	TestRobot *robot = new TestRobot();

	printf("SmartCOM3 lib version: %s\n\n", robot->GetClientVersionString().c_str());

	robot->ConfigureClient(
		"CalcPlannedPos=no;"
		"asyncSocketConnectionMode=yes;"
		"logLevel=5;"
		"logFilePath=C:\\;");

	robot->ConfigureServer(
		"pingTimeout=2;"
		"logLevel=5;"
		"logFilePath=C:\\");

	printf("Connecting to %s:%d with login %s\n", server, port, login);
	robot->Connect(server, port, login, password);

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
