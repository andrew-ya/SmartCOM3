# SmartCOM3 API C++ connector
ITInvest SmartCOM3 API C++ connector (Windows/Linux & possibly Mac OS X)    
Implemented in raw without using MFC, ATL or IDL		
It's usefull for coding C++ and linking native high performance C/C++ libraries with SmartCOM3 API (e.g. CUDA or OpenCL)
#Tested platforms
###Windows 7/8 (32/64) + Visual Studio 2012/2013 (MSVC 11.0/12.0)
###Ubuntu 12/14 & Debian 7/8 (32/64) + Winelib 1.6-1.8 (gcc 4.8-5.0)	
SmartCOM3 lib version: 3.0.162.5805     
Both Windows and Linux builds works well with CUDA and OpenGL native libs       
(inc. CUDA-OpenGL interoperability - tested on nVidia GeForce GTX 680 & Tesla K20Xm)

# Installation & building
#Windows
1. Download SmartCOM3 API 32 or 64 bit from http://www.itinvest.ru/software/smartcom/
2. Install it
3. Launch Visual Studio and create empty WIN32 project
4. Just add sources and build project

#Linux
###Installation
1. Create Wine prefix 32 or 64 bit
2. Download corresponding SmartCOM3 API from http://www.itinvest.ru/software/smartcom/
3. Install it:      
    e.g. "wine msiexec /i /path/to/smartcom/setup.msi"    
    or just register dll like "wine regsvr32 /i /path/to/smartcom.dll"
4. Setup cyrillic support ru_RU.utf8

###Building     
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
###Launching
Notes about error "wrong binary format"      
1. Check that you link all libs above and they are exist on LD path         
2. Wine prefix and downloaded SmartCOM3 version must be the same architecture (32 or 64 bit)       
```
$ ./SmartCOM3.exe    
or without that launcher script
$ wine SmartCOM3.exe.so

for russian support, custom WINEPREFIX & no Wine's debug messages:
$ LANG=ru_RU.utf8 WINEPREFIX=/path/to/prefix WINEDEBUG=-all ./SmartCOM3.exe
```
#Test program output
```
IStClient::IStClient()
IStClient::InitializeApartments()
IStClient::InitializeApartments() OK
IStClient::IStClient() OK

SmartCOM3 lib version: 3,0,162,5805

Connecting to mxdemo.ittrade.ru:8443 with login XXXXXX, please wait...
Press ENTER to exit
TestRobot::Connected()
TestRobot::AddSymbol() received all of 21749 symbols
TestRobot::AddSymbol() added symbol 'GAZP' with short_name 'ГАЗПРОМ ао'
TestRobot::AddSymbol() added symbol 'ROSN' with short_name 'Роснефть'
TestRobot::AddSymbol() added symbol 'SBER' with short_name 'Сбербанк'
TestRobot::AddSymbol() added symbol 'VTBR' with short_name 'ВТБ ао'

Disconnecting...
TestRobot::Disconnected(Disconnected by user)

IStClient::~IStClient()
IStClient::~IStClient() OK
IStClient::UninitializeApartments()
IStClient::UninitializeApartments() OK
```
#Test program SmartCOM3 log output (level 4)   
```
2016-Mar-22 03:39:03.865905 [TID=24] - INFO : SmartCOM3 client module (v3.0.162.5805) logging started.. 
2016-Mar-22 03:39:03.865949 [TID=24] - INFO : Logging level is set to 4 value. 
2016-Mar-22 03:39:03.865960 [TID=24] - INFO : Using maximum 7 worker threads to process data. 
2016-Mar-22 03:39:03.865968 [TID=24] - INFO : Store logs in C:\\ 
2016-Mar-22 03:39:04.001174 [TID=24] - INFO : Trying to authenticate in mxdemo.ittrade.ru:8443 using SSL connection (login XXXXXX) 
2016-Mar-22 03:39:04.004996 [TID=24] - jelly:  : Trying connect to 213.247.232.236:8443 
2016-Mar-22 03:39:04.046128 [TID=24] - jelly:  : Https channel 0x2719E0 OK.. 
2016-Mar-22 03:39:04.105232 [TID=28] - INFO : Login OK, loading securities.. 
2016-Mar-22 03:39:04.105360 [TID=28] - jelly:  : Trying connect to 213.247.232.236:8090 
2016-Mar-22 03:39:04.105388 [TID=28] - jelly:  : Channel 0x284890 will use async connect mode (140) 
2016-Mar-22 03:39:04.105482 [TID=29] - jelly:  : Destroying https channel..0x2719E0 
2016-Mar-22 03:39:04.117046 [TID=2f] - jelly:  : Http channel 0x284890 OK.. 
2016-Mar-22 03:39:06.444457 [TID=2a] - INFO : Securities table loaded OK 
2016-Mar-22 03:39:06.444520 [TID=2a] - INFO : StServer::GetSymbols method 
2016-Mar-22 03:39:06.525705 [TID=2d] - jelly:  : Destroying http channel..0x284890 
2016-Mar-22 03:39:08.528713 [TID=24] - INFO : Disconnected by user.. 
``` 
#Minimal example        
```
TestRobot *robot = new TestRobot();
robot->Connect("mxdemo.ittrade.ru", 8443, "LOGIN", "PASSWORD");
getchar(); /* waiting 'Connected()' event on success or 'Disconnected()' event on fail */
delete robot;
```
#Note    
Use try-catch around all SmartCOM3 methods for std::runtime_error   
```
try {
	ListenTicks(symbol);
} catch (std::runtime_error &er) {
	printf("error: %s\n", er.what());
}
```
##THE SOFTWARE IS PROVIDED "AS IS",     
##WITHOUT WARRANTY OF ANY KIND    
##TEST ALL FUNCTIONALITY BEFORE PRODUCTION      
#Contact
Feel free for contact        
moex@anton.red russian or english
