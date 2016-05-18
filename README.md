# SmartCOM3 API C++ connector
ITInvest SmartCOM3 API C++ connector (Windows/Linux & possibly Mac OS X)    
Implemented in raw without using MFC, ATL or IDL		
It's usefull for coding C++ and linking native high performance C/C++ libraries with SmartCOM3 API (e.g. CUDA or OpenCL)
#Tested platforms
####● Windows 7/8 (32/64) + Visual Studio 2012/2013 (MSVC 11.0/12.0)
####● Ubuntu 12/14 & Debian 7/8 (32/64) + Winelib 1.6-1.9 (gcc 4.8-5.0)	
SmartCOM3 lib version: 3.0.162.5805     
Both Windows and Linux builds works well with CUDA and OpenGL native libs       
(inc. CUDA-OpenGL interoperability - tested on nVidia GeForce GTX 680 & Tesla K20Xm)

#Windows
1. Download and install SmartCOM3 API 32 or 64 bit from http://www.itinvest.ru/software/smartcom/
2. Launch Visual Studio and create empty WIN32 project 32 or 64 bit
3. Create directory C:\logs or change default path in TestRobot constructor
4. Just add sources and build project

#Linux
####Installation
1. Create Wine prefix 32 or 64 bit
2. Download corresponding SmartCOM3 API from http://www.itinvest.ru/software/smartcom/
3. Install it:      
    e.g. "wine msiexec /i /path/to/smartcom/setup.msi"    
    or just register dll like		
    32 bit: "wine regsvr32 /i /path/to/smartcom_32.dll"		
    64 bit: "wine64 regsvr32 /i /path/to/smartcom_64.dll"	
4. Add cyrillic locale ru_RU.utf8

####Building     
Notes:      
1. Add "-D_FORCENAMELESSUNION" compiler flag (VARIANTs support)        
2. Link with libole32, liboleaut32 and libuuid      
3. If you building shared library, add position independent flag to compiler "-fPIC"     
```
$ mkdir build
$ cd build
$ wineg++ -Wall -std=c++1y -c -D_FORCENAMELESSUNION ../SmartCOM3.cpp ../TestRobot.cpp
$ wineg++ -o "SmartCOM3"  ./SmartCOM3.o ./TestRobot.o    -lole32 -loleaut32 -luuid
$ ls
$ SmartCOM3.exe  SmartCOM3.exe.so  SmartCOM3.o  TestRobot.o
```
####Launching
Notes about error "wrong binary format"      
1. Check that you link all libs above and they are exist on LD path         
2. Wine prefix and downloaded SmartCOM3 version must be the same architecture (32 or 64 bit)       
```
$ ./SmartCOM3.exe    
or without that launcher script
$ wine SmartCOM3.exe.so
for 64 bit
$ wine64 SmartCOM3.exe.so

for russian support, custom WINEPREFIX & no Wine's debug messages:
$ LANG=ru_RU.utf8 WINEPREFIX=/path/to/prefix WINEDEBUG=-all ./SmartCOM3.exe
```
#Test program output	
####Environment		
    Wine build: wine-1.9.5	
    Platform: x86_64	
    Version: Windows 7	
    Host system: Linux	
    Host version: 3.16.0-4-amd64	
####Output		
```
TestRobot::TestRobot()
TestRobot::TestRobot() SmartCOM3 lib version: 3,0,162,5805
TestRobot::TestRobot() Connecting to mxdemo.ittrade.ru:8443 with login XXXXXX, please wait...
TestRobot::TestRobot() OK

Press ENTER to exit

TestRobot::Connected()
TestRobot::AddSymbol() received all of 22000 symbols
TestRobot::AddSymbol() added symbol 'GAZP' with short_name 'ГАЗПРОМ ао'
TestRobot::AddSymbol() added symbol 'ROSN' with short_name 'Роснефть'
TestRobot::AddSymbol() added symbol 'SBER' with short_name 'Сбербанк'
TestRobot::AddSymbol() added symbol 'VTBR' with short_name 'ВТБ ао'
TestRobot::AddPortfolio(1/3) name STXXXXXX-MO-01 exchage MON status Broker
TestRobot::AddPortfolio(2/3) name STXXXXXX-MS-01 exchage EQ status Broker
TestRobot::AddPortfolio(3/3) name STXXXXXX-RF-01 exchage RTS_FUT status Blocked

TestRobot::~TestRobot()
TestRobot::~TestRobot() Disconnecting...
TestRobot::Disconnected(Disconnected by user)
TestRobot::~TestRobot() OK
```
#Test program SmartCOM3 log output (level 4)   
```
2016-Apr-19 17:14:13.177266 [TID=24] - INFO : SmartCOM3 client module (v3.0.162.5805) logging started.. 
2016-Apr-19 17:14:13.177312 [TID=24] - INFO : Logging level is set to 4 value. 
2016-Apr-19 17:14:13.177323 [TID=24] - INFO : Using maximum 7 worker threads to process data. 
2016-Apr-19 17:14:13.177331 [TID=24] - INFO : Store logs in C:\logs\ 
2016-Apr-19 17:14:13.220850 [TID=24] - INFO : Trying to authenticate in mxdemo.ittrade.ru:8443 using SSL connection (login XXXXXX) 
2016-Apr-19 17:14:13.265645 [TID=24] - jelly:  : Trying connect to 213.247.232.236:8443 
2016-Apr-19 17:14:14.331970 [TID=24] - jelly:  : Https channel 0x2719E0 OK.. 
2016-Apr-19 17:14:14.373027 [TID=2e] - INFO : Login OK, loading securities.. 
2016-Apr-19 17:14:14.373155 [TID=2e] - jelly:  : Trying connect to 213.247.232.236:8090 
2016-Apr-19 17:14:14.373192 [TID=2e] - jelly:  : Channel 0x284890 will use async connect mode (140) 
2016-Apr-19 17:14:14.373277 [TID=2e] - jelly:  : Destroying https channel..0x2719E0 
2016-Apr-19 17:14:14.389419 [TID=2f] - jelly:  : Http channel 0x284890 OK.. 
2016-Apr-19 17:14:16.417065 [TID=2d] - INFO : Securities table loaded OK 
2016-Apr-19 17:14:16.417153 [TID=2d] - INFO : StServer::GetSymbols method 
2016-Apr-19 17:14:16.545367 [TID=2d] - INFO : StServer::GetPrortfolioList method 
2016-Apr-19 17:14:16.545488 [TID=2a] - jelly:  : Destroying http channel..0x284890 
2016-Apr-19 17:14:21.551759 [TID=24] - INFO : Disconnected by user.. 
``` 
#Minimal example        
```
TestRobot *robot = new TestRobot();
robot->Connect("mxdemo.ittrade.ru", 8443, "LOGIN", "PASSWORD");
getchar(); /* waiting 'Connected()' event on success or 'Disconnected()' event on fail */
delete robot;
```
#Note    
All SmartCOM3 methods return ErrorCode for user side error handling   
```
ErrorCode er = ListenTicks(symbol);
if (er != ErrorCode_Success) {
	printf("ListenTicks(%s) error: %s\n", symbol, GetErrorCodeString(er));
}
```
Possible output: ListenTicks(SBER) error: NotConnected		
For error description call GetErrorCodeString(code).		
Error codes:
```
ErrorCode_Success
ErrorCode_SecurityNotFound
ErrorCode_PortfolioNotFound
ErrorCode_NotConnected
ErrorCode_BadParameters
ErrorCode_InternalError
ErrorCode_ExchangeNotAccessible
```
###THE SOFTWARE IS PROVIDED "AS IS",     
###WITHOUT WARRANTY OF ANY KIND    
###TEST ALL FUNCTIONALITY BEFORE PRODUCTION      
#Contact
Feel free for contact        
moex@anton.red russian or english
