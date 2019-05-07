
#include <map>
#include <vector>
#include <string>


#include "bthmcpp.h"
#include "bthmcpp_websocket.h"
#include <json/json.h>



using namespace std;

map < string, map <double,double> >  depthCache;
map < long long, Json::Value > history;
string code;
long long ver;

//------------------------------
void print_depthCache() {

	map < string, map <double,double> >::iterator it_i;

	for ( it_i = depthCache.begin() ; it_i != depthCache.end() ; it_i++ ) {
			
		string bid_or_ask = (*it_i).first ;
		cout << bid_or_ask << endl ;
		cout << "Price             Qty" << endl ;		

		map <double,double>::reverse_iterator it_j;

		for ( it_j = depthCache[bid_or_ask].rbegin() ; it_j != depthCache[bid_or_ask].rend() ; it_j++ ) {

			double price = (*it_j).first;
			double qty   = (*it_j).second;
			printf("%.08f          %.08f\n", price, qty );
		}
	}
}


void modify_depth(Json::Value json_result)
{
	for (int i = 0 ; i < json_result["data"]["b"].size() ; i++ ) {
		double price = atof( json_result["data"]["b"][i][0].asString().c_str());
		double qty 	 = atof( json_result["data"]["b"][i][1].asString().c_str());
		if ( qty == 0.0 ) {
			depthCache["bids"].erase(price);
		} else {
			depthCache["bids"][price] = qty;
		}
	}
	for (int i = 0 ; i < json_result["data"]["s"].size() ; i++ ) {
		double price = atof( json_result["data"]["s"][i][0].asString().c_str());
		double qty 	 = atof( json_result["data"]["s"][i][1].asString().c_str());
		if ( qty == 0.0 ) {
			depthCache["asks"].erase(price);
		} else {
			depthCache["asks"][price] = qty;
		}
	}		

}

void rest_set_depth(Json::Value result)
{
	
	ver = atol(result["data"]["ver"].asString().c_str());
 		
	for ( int i = 0 ; i < result["data"]["s"].size(); i++ ) {

		double price = atof( result["data"]["s"][i][0].asString().c_str() );
		double qty   = atof( result["data"]["s"][i][1].asString().c_str() );
		depthCache["asks"][price] = qty;
	}
	for  ( int i = 0 ; i < result["data"]["b"].size() ; i++ ) {

		double price = atof( result["data"]["b"][i][0].asString().c_str() );
		double qty   = atof( result["data"]["b"][i][1].asString().c_str() );
		depthCache["bids"][price] = qty;
	}
	print_depthCache();	

}

//-------------
int ws_depth_onData( Json::Value &json_result ) {
	
	int i;
	int code = atoi(json_result["code"].asString().c_str());
	if (code == 7)
	{

		long long new_ver  = atol(json_result["data"]["ver"].asString().c_str());
		string symbol 	   = json_result["data"]["symbol"].asString();
		cout << "ver : " << ver << " new ver : " << new_ver << endl;


		history[new_ver] = json_result;

		if ( new_ver == ver + 1 ) {

			modify_depth(json_result);
			print_depthCache();
			ver = new_ver;
			history.clear();
		} else {

			Json::Value result;

			BthmCPP::get_depth( symbol.c_str(), result ) ;
			long long tmp_ver		 = atol(result["data"]["ver"].asString().c_str());

			map < long long, Json::Value >::iterator it_h;

			it_h = history.find(tmp_ver);
			if (it_h != history.end())
			{
				rest_set_depth(result);
				for ( ; it_h != history.end(); ++it_h) 
				{	
					long long m_ver = (*it_h).first;
					cout << "now sync ver : " << m_ver << endl;

					Json::Value history_result = (*it_h).second;
					modify_depth(history_result);
				}

				cout << "history version sync success ! " << tmp_ver << endl;

				ver = tmp_ver;

			}
		}
	}
}


//---------------------------
/*
	To compile, type
	make example_depthCache

*/
//--------------------------


int main() {


	string api_key 		= "";
	string secret_key 	= "";
	BthmCPP::init( api_key , secret_key );

	Json::Value result;

	string symbol = "RNT-USDT";
	BthmCPP::get_depth( symbol.c_str(), result ) ;
	rest_set_depth(result);

	BthmCPP_websocket::init( "{'cmd':'subscribe','args':['ORDERBOOK:RNT-USDT']}" );
 	BthmCPP_websocket::connect_endpoint( ws_depth_onData , "/message/realtime"); 
	
	BthmCPP_websocket::enter_event_loop(); 
	
}