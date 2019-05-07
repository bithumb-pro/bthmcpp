
#include <map>
#include <vector>
#include <string>


#include "bthmcpp.h"
#include "bthmcpp_websocket.h"
#include <json/json.h>

#define API_KEY 		"19"
#define SECRET_KEY		"4dd1b9b5b24911a3be9d1e16acb5541bffe4862cfb7eef0b3a52296687aeb157"


// Some code to make terminal to have colors
#define KGRN "\033[0;32;32m"
#define KCYN "\033[0;36m"
#define KRED "\033[0;32;31m"
#define KYEL "\033[1;33m"
#define KBLU "\033[0;32;34m"
#define KCYN_L "\033[1;36m"
#define KBRN "\033[0;33m"
#define RESET "\033[0m"


using namespace std;

map < string, map <string,double> >  userBalance;
map < long, map<string,double> > klinesCache;

//------------------
void print_klinesCache() {

	map < long, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = klinesCache.begin() ; it_i != klinesCache.end() ; it_i++ ) {

		long start_of_candle 		= (*it_i).first;
		map <string,double> candle_obj 	= (*it_i).second;

		cout << "s:" << start_of_candle << ",";
		cout << "o:" << candle_obj["o"] << ",";
		cout << "h:" << candle_obj["h"] << ",";
		cout << "l:" << candle_obj["l"] << ",";
		cout << "c:" << candle_obj["c"] << ",";
		cout << "v:" << candle_obj["v"] ;
		cout << " " << endl;

	}
}

//---------------
void print_userBalance() {

	map < string, map<string,double> >::iterator it_i;

	cout << "==================================" << endl;
	
	for ( it_i = userBalance.begin() ; it_i != userBalance.end() ; it_i++ ) {

		string symbol 			= (*it_i).first;
		map <string,double> balance 	= (*it_i).second;

		cout << "Symbol :" << symbol << ", ";
		printf("Free   : %.08f, ", balance["f"] );
		printf("Locked : %.08f " , balance["l"] );
		cout << " " << endl;

	}

}

//---------------------------
/*
	Examples of how to use BthmCPP Bithumb Pro API library
	Simply uncomment out the code and compile with : 
	
	make example

	and run with

	./example.run.sh
*/

//--------------------------

int main() {


	string api_key 		= API_KEY;
	string secret_key 	= SECRET_KEY;
	BthmCPP::init( api_key , secret_key );

	/*
		The Json::value object each element can be access like hash map <>, 
		or vector <> if it is Json::array
	*/
	Json::Value result;
	
	//------------------------------------
	// Example : Get Server Time.
	// BthmCPP::get_serverTime( result ) ;
	// cout << result << endl;
	//*/

	/*-------------------------------------------------------------*/
	// Example : Get all Instruments Info
	// BthmCPP::get_instruments( result );
	// cout << result << endl;
	

	/*-------------------------------------------------------------		
	// Example: Get Depth of single pair
	BthmCPP::get_depth( "RNT-USDT", result ) ;
	cout << result << endl;
	*/

	
	//*-------------------------------------------------------------*/
	// Example: Placing a LIMIT order
	// BthmCPP::send_order( "RNT-USDT", "buy", "limit", 1, 0.04, result );
	// long long order_id = atol(result["data"]["orderId"].asString().c_str());

	// cout << result << endl;
	

	/*-------------------------------------------------------------
	// Example: Placing a MARKET order
	BthmCPP::send_order( "RNT-USDT", "buy", "market", 20, 0, result );
	cout << result << endl;
	*/

	/*-------------------------------------------------------------	*/
	// Example: Cancel an order
	// BthmCPP::cancel_order("RNT-USDT", order_id, result);
	// cout << result << endl;


	/*-------------------------------------------------------------
	// Example: Getting list of open orders for specific pair
	/*
	BthmCPP::get_openOrders( "RNT-USDT", result ) ;
	cout << result << endl;
	

	/*-------------------------------------------------------------
	// Example: Get account single order;.
	BthmCPP::get_order( "RNT-USDT", 54774415237087232, result ); 
	cout << result << endl;	 

	/*-------------------------------------------------------------
	// Example: Get all account orders; active, canceled, or filled.
	BthmCPP::get_allOrders( "RNT-USDT", "traded", "thisweek", 1, 50, result ); 
	cout << result << endl;
	

	/*-------------------------------------------------------------
	// Example : Get all trades history
	
	BthmCPP::get_myTrades( "RNT-USDT", 10, 1554618565000, result );
	cout << result << endl;	 
	

		
	/*-------------------------------------------------------------
	/**/
	// Example: Getting 24hr ticker price change statistics for a symbol
	// BthmCPP::get_24hr( "RNT-USDT", result ) ;
	// cout << result << endl;
	 
	
	/*-------------------------------------------------------------   
	/*
	// Example: Get Kline/candlestick data for a symbol
	   BthmCPP::get_klines( "RNT-USDT", "m1", 1555239630, 1555249630, result );
	   cout << result << endl;
	*/


	/*-------------------------------------------------------------  
	/* Websockets Endpoints */


	// User Balance
	/*
	BthmCPP::get_account( "spot", "", result );
	cout << result << endl;
	Json::Value data = result["data"];
	int ret = atoi(result["code"].asString().c_str());
	if (ret == 0)
	{
		for ( int i  = 0 ; i < data.size() ; i++ ) 
		{
			string symbol = data[i]["coinType"].asString();
			userBalance[symbol]["f"] = atof( data[i]["count"].asString().c_str() );
			userBalance[symbol]["l"] = atof( data[i]["frozen"].asString().c_str() );
		}
	}
	
	print_userBalance();
	*/

	return 0;
}