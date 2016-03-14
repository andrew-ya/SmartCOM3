# SmartCOM3 C++ connector
ITInvest SmartCOM3 API C++ connector (Windows/Linux and possibly Mac OS X)    
It's usefull for coding C++ and linking native high performance C/C++ libraries with SmartCOM3 API (e.g. CUDA or OpenCL)
#Tested platforms
Windows 7/8 (32/64) + Visual Studio 2012/2013 (MSVC 11.0/12.0)

Ubuntu 12/14 & Debian 7/8 (32/64) + Winelib 1.6-1.8 (gcc 4.8-5.0)

Both Windows and Linux builds works well with CUDA and OpenGL native libs (inc. CUDA-OpenGL interoperability)

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
mkdir build
cd build
wineg++ -std=c++1y -c -D_FORCENAMELESSUNION -MMD -MP -MF"SmartCOM3.d" -MT"SmartCOM3.d" -o "SmartCOM3.o" "../SmartCOM3.cpp"
wineg++ -std=c++1y -c -D_FORCENAMELESSUNION -MMD -MP -MF"SmartCOM3enums.d" -MT"SmartCOM3enums.d" -o "SmartCOM3enums.o" "../SmartCOM3enums.cpp"
wineg++ -std=c++1y -c -D_FORCENAMELESSUNION -MMD -MP -MF"Test.d" -MT"Test.d" -o "Test.o" "../Test.cpp"
wineg++ -o "SmartCOM3" ./SmartCOM3.o ./SmartCOM3enums.o ./Test.o -lole32 -loleaut32 -luuid
```
###Launching
Notes about error "wrong binary format"      
1. Check that you link all libs above and they are exist on LD path         
2. Wine prefix and downloaded SmartCOM3 version must be the same architecture (32 or 64 bit)       
```
env LANG=ru_RU.utf8 ./SmartCOM3.exe    
or directly without launcher script
env LANG=ru_RU.utf8 wine SmartCOM3.exe.so
```
#Test program output
```
IStClient::InitializeApartments()
IStClient::InitializeApartments() OK
IStClient::IStClient()
IStClient::IStClient() OK
SmartCOM3 version: 3,0,162,5805

Connecting to mxdemo.ittrade.ru:8443 with login XXXXXX
Press ENTER to disconnect
TestRobot::Connected()
TestRobot::AddSymbol(6A.CME.H2015) 1 of 21304
TestRobot::AddSymbol(6A.CME.M2015) 2 of 21304
TestRobot::AddSymbol(6A.CME.U2014) 3 of 21304
TestRobot::AddSymbol(6A.CME.Z2014) 4 of 21304
TestRobot::AddSymbol(6B.CME.H2015) 5 of 21304
TestRobot::AddSymbol(6B.CME.H2016) 6 of 21304
TestRobot::AddSymbol(6B.CME.H2017) 7 of 21304
TestRobot::AddSymbol(6B.CME.H2018) 8 of 21304
TestRobot::AddSymbol(6B.CME.M2015) 9 of 21304
TestRobot::AddSymbol(6B.CME.M2016) 10 of 21304
.....
TestRobot::AddSymbol() added 21304 of 21304

Disconnecting...
TestRobot::Disconnected(Disconnected by user)
Press ENTER to exit

IStClient::~IStClient()
IStClient::~IStClient() OK
IStClient::UninitializeApartments()
IStClient::UninitializeApartments() OK
```
#Test program SmartCOM3 log output (level 5)   
```
2016-Mar-08 17:14:42.903952 [TID=9] - INFO : SmartCOM3 client module (v3.0.162.5805) logging started.. 
2016-Mar-08 17:14:42.904203 [TID=9] - INFO : Logging level is set to 5 value. 
2016-Mar-08 17:14:42.904219 [TID=9] - INFO : Using maximum 7 worker threads to process data. 
2016-Mar-08 17:14:42.904227 [TID=9] - INFO : Store logs in C:\\ 
2016-Mar-08 17:14:43.026583 [TID=9] - INFO : Trying to authenticate in mxdemo.ittrade.ru:8443 using SSL connection (login XXXXXX) 
2016-Mar-08 17:14:43.068353 [TID=9] - jelly:  : Trying connect to 213.247.232.236:8443 
2016-Mar-08 17:14:43.081546 [TID=9] - jelly:  : Http channel 0x2719E0 socket connected OK.. (136) 
2016-Mar-08 17:14:43.112965 [TID=9] - jelly:  : SSL handshake for channel 0x2719E0 OK, encrypted method is DHE-RSA-AES256-SHA 
2016-Mar-08 17:14:43.113149 [TID=9] - jelly:  : ConnectionManager registered new connection 0x2719E0 
2016-Mar-08 17:14:43.113183 [TID=9] - jelly:  : Https channel 0x2719E0 OK.. 
2016-Mar-08 17:14:43.168635 [TID=d] - INFO : Login OK, loading securities.. 
2016-Mar-08 17:14:43.168757 [TID=d] - jelly:  : Trying connect to 213.247.232.236:8090 
2016-Mar-08 17:14:43.168787 [TID=d] - jelly:  : Channel 0x284890 will use async connect mode (140) 
2016-Mar-08 17:14:43.168830 [TID=d] - jelly:  : ConnectionManager registered new connection 0x284890 
2016-Mar-08 17:14:43.168877 [TID=17] - jelly:  : Https channel 0x2719E0 closed by server... 
2016-Mar-08 17:14:43.168903 [TID=17] - jelly:  : ConnectionManager unregister connection 0x2719E0 
2016-Mar-08 17:14:43.168915 [TID=17] - jelly:  : Destroying https channel..0x2719E0 
2016-Mar-08 17:14:43.168965 [TID=17] - jelly:  : Https channel 0x2719E0 socket closed.. (136) 
2016-Mar-08 17:14:43.174086 [TID=32] - jelly:  : Garbage collect: release resource 0x2719E0.. 
2016-Mar-08 17:14:43.180487 [TID=32] - jelly:  : Http channel 0x284890 async socket connected OK.. (140) 
2016-Mar-08 17:14:43.180509 [TID=32] - jelly:  : Http channel 0x284890 OK.. 
2016-Mar-08 17:14:44.878641 [TID=31] - INFO : Securities table loaded OK 
2016-Mar-08 17:14:44.878703 [TID=31] - INFO : StServer::GetSymbols method 
2016-Mar-08 17:14:44.950272 [TID=30] - jelly:  : Http channel 0x284890 closed by server... 
2016-Mar-08 17:14:44.950308 [TID=30] - jelly:  : ConnectionManager unregister connection 0x284890 
2016-Mar-08 17:14:44.950319 [TID=30] - jelly:  : Destroying http channel..0x284890 
2016-Mar-08 17:14:44.950363 [TID=30] - jelly:  : Http channel 0x284890 socket closed.. (140) 
2016-Mar-08 17:14:45.050556 [TID=32] - jelly:  : Garbage collect: release resource 0x284890.. 
2016-Mar-08 17:14:49.980986 [TID=9] - TRACE : StServer::disconnect method 
2016-Mar-08 17:14:50.957624 [TID=9] - INFO : Disconnected by user.. 
```
#Before production     
##THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    
##TEST ALL FUNCTIONALITY YOU ARE USING  
#Contact
Feel free for contact me on moex@anton.red russian or english
