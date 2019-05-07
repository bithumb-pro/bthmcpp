

#include <string>
#include "bthmcpp.h"
#include "bthmcpp_websocket.h"


#include <json/json.h>

#define API_KEY 		"myapikey"
#define SECRET_KEY		"mysecretkey"


//-----------------------------
int ws_lastTrade_OnData( Json::Value &json_result ) {

	cout << json_result << endl;

}

//-------------------------
int main() {

	string api_key = API_KEY;
	string secret_key = SECRET_KEY;

	BthmCPP::init( api_key, secret_key ) ;
	
	BthmCPP_websocket::init( "{'cmd':'subscribe','args':['TRADE:RNT-USDT']}" );
 	BthmCPP_websocket::connect_endpoint( ws_lastTrade_OnData ,"/message/realtime" ); 
	BthmCPP_websocket::enter_event_loop(); 
	
	return 0;

}


