
# Bithumb Pro C++ API

#### Installation
    git clone https://github.com/bithumb-pro/bthmcpp.git

#### Dependencies
	
	jsoncpp-1.8.3
	libcurl-7.56.0
	libwebsockets-3.0.0



Depended shared libraries and their headers are included in the repository's lib directory 

use -I<include path> to include header paths for compiler to look for headers 

and -L<lib path> and -l<libname> for linker to link against shared libraries.

	libcurl_dir=../lib/libcurl-7.56.0
	libcurl_include=${libcurl_dir}/include
	libcurl_lib=${libcurl_dir}/lib
	
	jsoncpp_dir=../lib/jsoncpp-1.8.3
	jsoncpp_include=${jsoncpp_dir}/include
	jsoncpp_src=${jsoncpp_dir}/src
	
	libwebsockets_dir=../lib/libwebsockets
	libwebsockets_include=${libwebsockets_dir}/include
	libwebsockets_lib=${libwebsockets_dir}/lib
	
	libbthmcpp_dir=../lib/libbthmcpp
	libbthmcpp_include=${libbthmcpp_dir}/include
	libbthmcpp_lib=${libbthmcpp_dir}/lib



.
Then compile like this:


	g++ -I$(libcurl_include) -I$(jsoncpp_include) -I$(libwebsockets_include) -I$(libbthmcpp_include) \
	example.cpp \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	-L$(libbthmcpp_lib) \
	-lcurl -lcrypto -lwebsockets -lbthmcpp -o example





And export LD\_LIBRARY\_PATH and run like this:

	libcurl_dir=../lib/libcurl-7.56.0
	libcurl_lib=${libcurl_dir}/lib

	libwebsockets_dir=../lib/libwebsockets
	libwebsockets_lib=${libwebsockets_dir}/lib

	libbthmcpp_dir=../lib/libbthmcpp
	libbthmcpp_lib=${libbthmcpp_dir}/lib

	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$libcurl_lib:$libwebsockets_lib:$libbthmcpp_lib

	./example 





You can refer to the following Makefile to get a better picture...

	https://github.com/bithumb-pro/bthmcpp/blob/master/example/Makefile


#### To Build Example
	
	cd example
	make example

---
## Coding with libBthmCPP

#### Headers to include

	#include "bthmcpp.h"	
	#include "bthmcpp_websocket.h"
	#include <json/json.h>


#### Init
	string api_key 		= API_KEY;
	string secret_key = SECRET_KEY;
	BthmCPP::init( api_key , secret_key );

---
#### Example : Get Server Time.
	
	Json::Value result;
	BthmCPP::get_serverTime( result ) ;

#### Example : Get all Instruments Info.

	Json::Value result;
	BthmCPP::get_instruments( result );

#### Example: Get Account 
	
	Json::Value result;
	BthmCPP::get_account( "spot", "", result );
	
#### Example: Get Depth of single pair
	
	Json::Value result;
	BthmCPP::get_depth( "RNT-USDT", result ) ;
	

#### Example: Placing a LIMIT order
	
	Json::Value result;
	BthmCPP::send_order( "BNBETH", "BUY", "LIMIT", "GTC", 20 , 0.00380000, "",0,0, recvWindow, result );

#### Example: Placing a MARKET order

	long recvWindow = 10000;
	Json::Value result;
	BthmCPP::send_order( "RNT-USDT", "buy", "limit", 1, 0.04, result );

#### Example: Check an order's status

	Json::Value result;
	BthmCPP::get_order( "RNT-USDT", 54774415237087232, result ); 

#### Example: Cancel an order

	Json::Value result;
	BthmCPP::cancel_order("RNT-USDT", order_id, result);

#### Example: Getting list of open orders for specific pair
	
	Json::Value result;
	BthmCPP::get_openOrders( "RNT-USDT", result ) ;

#### Example: Get all account orders; active, canceled, or filled.
	
	Json::Value result;
	BthmCPP::get_allOrders( "RNT-USDT", "traded", "thisweek", 1, 50, result ); 

#### Example : Get all trades history
	
	Json::Value result;
	BthmCPP::get_myTrades( "RNT-USDT", 10, 1554618565000, result );

#### Example: Getting 24hr ticker price change statistics for a symbol
	
	Json::Value result;
	BthmCPP::get_24hr( "RNT-USDT", result ) ;

#### Example: Get Kline/candlestick data for a symbol
	
	Json::Value result;
	BthmCPP::get_klines( "RNT-USDT", "m1", 1555239630, 1555249630, result );

---

### Websocket Endpoints ###


#### Example: Maintain Market Depth Cache Locally via Web Socket
	
	
[example_depthCache.cpp](https://github.com/bithumb-pro/bthmcpp/blob/master/example/example_depthCache.cpp)

#### Example: KLine/Candlestick Cache
	

[example_klines.cpp](https://github.com/bithumb-pro/bthmcpp/blob/master/example/example_klines.cpp)

#### Example: Aggregated Trades and update via Web Socket

[example_lastTrades.cpp](https://github.com/bithumb-pro/bthmcpp/blob/master/example/example_lastTrades.cpp)


	


