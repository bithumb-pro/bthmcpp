
#include <map>
#include <vector>
#include <string>


#include "bthmcpp.h"
#include "bthmcpp_websocket.h"
#include <json/json.h>



using namespace std;
map < long,   map <string,double> >  aggTradeCache;

#define API_KEY 		""
#define SECRET_KEY		""

//---------------
void print_lastTradeCache() {

	map < long, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = aggTradeCache.begin() ; it_i != aggTradeCache.end() ; it_i++ ) {

		long aggTradeId 		 = (*it_i).first;
		map <string,double> aggtrade_obj = (*it_i).second;

		cout << "AggtradeId:" << aggTradeId << ", ";
		printf("p: %.08f, ", aggtrade_obj["p"] );
		printf("q: %.08f " , aggtrade_obj["q"] );
		cout << " " << endl;

	}
}



//-----------
int ws_lastTrade_OnData( Json::Value &json_result ) {

	int code = atoi(json_result["code"].asString().c_str());
	if (code == 7)
	{
		long long ver  = atol(json_result["data"]["ver"].asString().c_str());
		aggTradeCache[ver]["p"] = atof( json_result["data"]["p"].asString().c_str() );
		aggTradeCache[ver]["q"] = atof( json_result["data"]["v"].asString().c_str() );
			
		print_lastTradeCache();
	}
}


//---------------------------
/*
	To compile, type
	make example_lastTrades
*/

//--------------------------

int main() {

	string api_key 		= API_KEY;
	string secret_key 	= SECRET_KEY;
	BthmCPP::init( api_key , secret_key );

	Json::Value result;
	
	//  Last 100 Trades 
	BthmCPP::get_lastTrades( "RNT-USDT", result ); 

	int code = atoi(result["code"].asString().c_str());

	Json::Value data = result["data"];
	
	for ( int i = 0 ; i < data.size() ; i++ ) {
		long long ver = atol(data[i]["ver"].asString().c_str());
		aggTradeCache[ver]["p"] =  atof( data[i]["v"].asString().c_str() );
 		aggTradeCache[ver]["q"] =  atof( data[i]["v"].asString().c_str() );
 	}

	print_lastTradeCache();

	BthmCPP_websocket::init( "{'cmd':'subscribe','args':['TRADE:RNT-USDT']}" );
 	BthmCPP_websocket::connect_endpoint( ws_lastTrade_OnData ,"/message/realtime" ); 
	BthmCPP_websocket::enter_event_loop(); 
	
	return 0;
}