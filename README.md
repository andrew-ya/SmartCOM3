## SmartCOM3 API C++ connector
ITInvest SmartCOM3 API C++ connector (Windows/Linux & possibly Mac OS X)    
Implemented in raw without using MFC or ATL		
It's usefull for coding C++ and linking native high performance C/C++ libraries with SmartCOM3 API (e.g. CUDA or OpenCL)
## Tested platforms
##### ● Windows 7/8 (32/64) + Visual Studio 2012/2013 (MSVC 11.0/12.0)
##### ● Ubuntu 12/14/16 & Debian 7/8 (32/64) + Winelib 1.6-1.9 (gcc 4.8-5.3)	
SmartCOM3 lib version: 3.0.162.5805     

Both Windows and Linux builds works well with CUDA and OpenGL native libs       
(inc. CUDA-OpenGL interoperability - tested on nVidia GeForce GTX 680 & Tesla K20Xm)

## Contents
- [Windows](#windows)
- [Linux](#linux)
- [Test program output](#test-program-output)
- [Test program SmartCOM3 log output](#test-program-smartcom3-log-output-level-4)
- [Minimal example](#minimal-example)
- [Library settings](#library-settings)
- [Error handling](#error-handling)
- [Multithreading warning](#multithreading-warning)
- [ITInvest history bars](#itinvest-history-bars)
- [Date & time helper functions](#date--time-helper-functions-smartcom3enumsh)
- [Building bars from bars](#building-bars-from-bars)
- [Building bars from ticks](#building-bars-from-ticks)
- [Contact](#contact)
   
## Windows
1. Download and install SmartCOM3 API 32 or 64 bit from http://www.itinvest.ru/software/smartcom/
2. Launch Visual Studio and create empty WIN32 project 32 or 64 bit
3. Create directory C:\logs or change default path in TestRobot constructor
4. Just add sources and build project

## Linux
##### (full description https://github.com/antonred/SmartCOM3/blob/master/README_WINE.md)
##### Installation
1. Add cyrillic locale ru_RU.UTF-8
2. Download 32 or 64 bit SmartCOM3 API from http://www.itinvest.ru/software/smartcom/
3. Install it:      
    e.g. "WINEARCH=win64 WINEPREFIX=~/prefix wine msiexec /i /path/to/smartcom/setup.msi /quiet /qn"    
    or just register dll like		
    32 bit: "WINEARCH=win32 WINEPREFIX=~/prefix wine regsvr32 /i /path/to/smartcom_32.dll"		
    64 bit: "WINEARCH=win64 WINEPREFIX=~/prefix wine64 regsvr32 /i /path/to/smartcom_64.dll"	

##### Building     
Notes:      
1. Add "-D_FORCENAMELESSUNION" compiler flag (VARIANTs support)        
2. Link with libole32, liboleaut32 and libuuid      
3. If you building shared library, add position independent flag to compiler "-fPIC"     
```
$ mkdir build
$ cd build
$ wineg++ -Wall -std=c++1y -c -D_FORCENAMELESSUNION ../SmartCOM3.cpp ../TestRobot.cpp
$ wineg++ -o "TestRobot"  ./SmartCOM3.o ./TestRobot.o    -lole32 -loleaut32 -luuid
$ ls
$ TestRobot.exe  TestRobot.exe.so  SmartCOM3.o  TestRobot.o
```
##### Launching
Notes about error "wrong binary format"      
1. Check that you link all libs above and they are exist on LD path         
2. WINE **prefix and** downloaded **SmartCOM3** version must be the same architecture **(32 or 64 bit)**       
```
$ ./TestRobot.exe    
or without that launcher script
$ wine TestRobot.exe.so
for 64 bit
$ wine64 TestRobot.exe.so

for russian support, custom WINEPREFIX & no Wine's debug messages:
$ LANG=ru_RU.UTF-8 WINEPREFIX=/path/to/prefix WINEDEBUG=-all ./TestRobot.exe
```
## Test program output	
##### Environment		
    Wine build: wine-1.9.5	
    Platform: x86_64	
    Version: Windows 7	
    Host system: Linux	
    Host version: 3.16.0-4-amd64	
##### Output		
```
TestRobot::TestRobot()
TestRobot::GetClientVersionString() Success SmartCOM3 dll version: 3,0,162,5805
TestRobot::ConfigureClient() Success
TestRobot::ConfigureServer() Success
TestRobot::Connect() Connecting to mx.ittrade.ru:8443 with login XXXXXX, please wait...
TestRobot::TestRobot() OK

Press ENTER to exit

TestRobot::Connected()
TestRobot::AddSymbol() received all of 22600 symbols
TestRobot::AddSymbol() added symbol 'GAZP' with short_name 'ГАЗПРОМ ао'
TestRobot::AddSymbol() added symbol 'ROSN' with short_name 'Роснефть'
TestRobot::AddSymbol() added symbol 'SBER' with short_name 'Сбербанк'
TestRobot::AddSymbol() added symbol 'VTBR' with short_name 'ВТБ ао'
TestRobot::ListenTicks(GAZP) Success
TestRobot::GetSymbols() Success
TestRobot::AddPortfolio(1/4) name BPXXXXX-FX-01 exchage CETS status Broker
TestRobot::AddPortfolio(2/4) name BPXXXXX-MO-01 exchage MON status ReadOnly
TestRobot::AddPortfolio(3/4) name BPXXXXX-MS-01 exchage EQ status Broker
TestRobot::AddPortfolio(4/4) name BPXXXXX-RF-01 exchage RTS_FUT status Broker
TestRobot::GetPortfolioList() Success
TestRobot::AddTick(GAZP) 21.06.2016 15:59:40 143.57000 180 157098 Sell
TestRobot::AddTick(GAZP) 21.06.2016 15:59:40 143.55000 500 157099 Sell
TestRobot::AddTick(GAZP) 21.06.2016 15:59:40 143.55000 20 157100 Buy
TestRobot::AddTick(GAZP) 21.06.2016 15:59:41 143.59000 10 157105 Buy

TestRobot::~TestRobot()
TestRobot::~TestRobot() Disconnecting...
TestRobot::Disconnected(Disconnected by user)
TestRobot::~TestRobot() OK
```
## Test program SmartCOM3 log output (level 4)   
```
2016-Jun-21 16:02:01.066719 [TID=1aa] - INFO : SmartCOM3 client module (v3.0.162.5805) logging started.. 
2016-Jun-21 16:02:01.066765 [TID=1aa] - INFO : Logging level is set to 4 value. 
2016-Jun-21 16:02:01.066774 [TID=1aa] - INFO : Using maximum 7 worker threads to process data. 
2016-Jun-21 16:02:01.066782 [TID=1aa] - INFO : Store logs in C:\logs\ 
2016-Jun-21 16:02:01.094257 [TID=1aa] - INFO : Trying to authenticate in mx.ittrade.ru:8443 using SSL connection (login XXXXXX)
2016-Jun-21 16:02:01.112897 [TID=1aa] - jelly:  : Trying connect to 213.59.8.133:8443 
2016-Jun-21 16:02:01.162103 [TID=1aa] - jelly:  : Https channel 0x271B70 OK.. 
2016-Jun-21 16:02:01.213248 [TID=1b5] - INFO : Login OK, loading securities.. 
2016-Jun-21 16:02:01.213377 [TID=1b5] - jelly:  : Trying connect to 213.59.8.133:48091 
2016-Jun-21 16:02:01.213406 [TID=1b5] - jelly:  : Channel 0x284B40 will use async connect mode (140) 
2016-Jun-21 16:02:01.213487 [TID=1b4] - jelly:  : Destroying https channel..0x271B70 
2016-Jun-21 16:02:01.225003 [TID=1bd] - jelly:  : Http channel 0x284B40 OK.. 
2016-Jun-21 16:02:07.821963 [TID=1b4] - INFO : Securities table loaded OK 
2016-Jun-21 16:02:07.822023 [TID=1b4] - INFO : StServer::GetSymbols method 
2016-Jun-21 16:02:08.024374 [TID=1b4] - INFO : StServer::ListenTicks method (Symbol: GAZP) 
2016-Jun-21 16:02:08.024573 [TID=1b4] - jelly:  : Trying connect to 213.59.8.133:48091 
2016-Jun-21 16:02:08.024625 [TID=1b4] - jelly:  : Channel 0x462FE00 will use async connect mode (136) 
2016-Jun-21 16:02:08.024756 [TID=1b4] - INFO : StServer::GetPrortfolioList method 
2016-Jun-21 16:02:08.024860 [TID=1b5] - jelly:  : Destroying http channel..0x284B40 
2016-Jun-21 16:02:08.039057 [TID=1bd] - jelly:  : Http channel 0x462FE00 OK.. 
2016-Jun-21 16:02:12.450707 [TID=1aa] - jelly:  : Destroying http channel..0x462FE00 
2016-Jun-21 16:02:12.450875 [TID=1aa] - INFO : Disconnected by user.. 
``` 
## Minimal example        
```
TestRobot *robot = new TestRobot();
robot->Connect("mxdemo.ittrade.ru", 8443, "LOGIN", "PASSWORD");
getchar(); /* waiting 'Connected()' event on success or 'Disconnected()' event on fail */
delete robot;
```
## Library settings
Before first call **Connect** method you may configure SmartCOM3 library and then call **ConfigureLibrary** to apply:
#### ● Log files path
void **SetLogPath**(std::string path); // e.g. "C:\\\\logs"		
*default: "%APPDATA%\\\\IT Invest"*
#### ● Logging level
void **SetLogLevel**(uint8_t level);	
*default: 2*
#### t: true*
#### ● Asynchronous mode for PlaceOrder/CancelOrder/MoveOrder methods
void **SetAsyncConnectionMode**(bool async);	
*default: true*
#### ● Disconnect after server response timeout in seconds (1..60 secs)
void **SetDisconnectTimeout**(uint8_t timeout);		
*default: 2*
#### ● Apply all settings above
ErrorCode **ConfigureLibrary**();
## Error handling    
All SmartCOM3 methods return ErrorCode for user side error handling:   
```
ErrorCode er = ListenTicks(symbol);
if (er != ErrorCode_Success) {
	printf("ListenTicks(%s) error: %s\n", symbol, GetErrorCodeString(er));
	switch (er) {
	case ErrorCode_SecurityNotFound: ... break;
	case ErrorCode_NotConnected: ... break;
	...
	default: ...
	}
}
```
Possible output: ListenTicks(SYMB) error: SecurityNotFound		

For error description call GetErrorCodeString(code).	
	
Error codes (ErrorCode enum in SmartCOM3enums.h):
```
ErrorCode_Success
ErrorCode_SecurityNotFound
ErrorCode_PortfolioNotFound
ErrorCode_NotConnected
ErrorCode_BadParameters
ErrorCode_InternalError
ErrorCode_ExchangeNotAccessible
```
## Multithreading warning
**1. Native SmartCOM3 methods are thread safe.**		
**2. Callbacks served from different threads - you may need synchronization.**		
## TInvest history bars
##### TInvest SmartCOM3 history bars date & time as result of GetBars have CLOSE date & time with some bugs.
**Test for all intervals GetBars(from 06.07.2016 10:04:20, 1 pcs) result:**
```
   1Min | 06.07.2016 10:05:00 <- rounded precisely to the end
   5Min | 06.07.2016 10:05:00
  10Min | 06.07.2016 10:10:00
  15Min | 06.07.2016 10:15:00
  30Min | 06.07.2016 10:30:00
  1Hour | 06.07.2016 11:00:00
  2Hour | 06.07.2016 12:00:00
  4Hour | 06.07.2016 12:00:00
    Day | 06.07.2016 23:59:59 <- not rounded to the end of frame
   Week | 08.07.2016 23:59:59 <- friday
  Month | 31.07.2016 23:59:59
Quarter | 30.09.2016 23:59:59
   Year | 31.12.2016 23:59:59
```
## Date & time helper functions (SmartCOM3enums.h)
1. Rounding AddBar fast but dangerous to same time frame (up to 00 secs):  
   time_t **RoundBarFast**(time_t)  
2. Rounding AddBar to same or higher time frame:  
   time_t **RoundBarDatetime**(BarInterval, time_t, DatetimeType)  
3. Rounding AddTick, AddQuote etc to some time frame:  
   time_t **RoundTickDatetime**(BarInterval, time_t, DatetimeType)  
   
**Rounding to WEEK OPEN/CLOSE rounds date & time to last/next Monday 00:00:00**
   
## Building bars  
**WARNING! LOW PERFORMANCE AT INTERVALS >= 2HOUR**  
### ilding bars from bars  
E.g. building 5MIN bars from 1MIN bars:
```
GetBars(..., BarInterval_1Min, ...);
...
void AddBar(..., time_t datetime1min, ...) { // 07.07.2016 12:27:00 - 1MIN CLOSE
  time_t datetime5min =
    RoundBarDatetime(BarInterval_5Min, datetime1min, OPEN_DATE); // 07.07.2016 12:25:00 - 5MIN OPEN
  datetime5min =
    RoundBarDatetime(BarInterval_5Min, datetime1min, CLOSE_DATE); // 07.07.2016 12:30:00 - 5MIN CLOSE
}
```
### Building bars from ticks
E.g. building 5MIN bars:
```
ListenTicks(...);
...
void AddTick(..., time_t datetime, ...) { // 07.07.2016 12:31:11
  time_t datetime5min =
    RoundTickDatetime(BarInterval_5Min, datetime, OPEN_DATE); // 07.07.2016 12:30:00 - 5MIN OPEN
  datetime5min =
    RoundTickDatetime(BarInterval_5Min, datetime, CLOSE_DATE); // 07.07.2016 12:35:00 - 5MIN CLOSE
}
```

### THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    
### TEST ALL FUNCTIONALITY BEFORE PRODUCTION      

## Contact
Feel free for contact        
moex@anton.red russian or english
