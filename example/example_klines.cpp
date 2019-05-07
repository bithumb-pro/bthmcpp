
#include <map>
#include <vector>
#include <string>


#include "bthmcpp.h"
#include "bthmcpp_websocket.h"
#include <json/json.h>



using namespace std;
map < long long,   map <string,double> >  klinesCache;


//------------------
void print_klinesCache() {

	map < long long, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = klinesCache.begin() ; it_i != klinesCache.end() ; it_i++ ) {

		long long timestamp 			= (*it_i).first;
		map <string,double> candle_obj 	= (*it_i).second;

		cout << "t:" << timestamp << ",";
		cout << "o:" << candle_obj["o"] << ",";
		cout << "h:" << candle_obj["h"] << ",";
		cout << "l:" << candle_obj["l"] << ",";
		cout << "c:" << candle_obj["c"] << ",";
		cout << "v:" << candle_obj["v"] ;
		cout << " " << endl;
	}
}

//---------------------------
/*
	To compile, type
	make example_klines
*/

//--------------------------

int main() {

	Json::Value result;
	
	// Klines/CandleStick
	string api_key 		= "";
	string secret_key 	= "";
	BthmCPP::init( api_key , secret_key );

	BthmCPP::get_klines( "RNT-USDT", "m1", 1555239630, 1555249630, result );
	//cout << result << endl;
	
	Json::Value data = result["data"];

	for ( int i = 0 ; i < data.size() ; i++ ) {
 		long long timestamp = atol(data[i]["time"].asString().c_str());
 		klinesCache[timestamp]["o"] = atof( data[i]["o"].asString().c_str() );
 		klinesCache[timestamp]["h"] = atof( data[i]["h"].asString().c_str() );
 		klinesCache[timestamp]["l"] = atof( data[i]["l"].asString().c_str() );
 		klinesCache[timestamp]["c"] = atof( data[i]["c"].asString().c_str() );
 		klinesCache[timestamp]["v"] = atof( data[i]["v"].asString().c_str() );
 	}
	
 	
	print_klinesCache();
 	
	return 0;
}