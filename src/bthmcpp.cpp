

/*
	Author: xyzhu
	Date  : 2019/05/05
	
	C++ library for Bithumb Pro API.
*/


#include "bthmcpp.h"
#include "bthmcpp_logger.h"
#include "bthmcpp_utils.h"


string BthmCPP::api_key = "";
string BthmCPP::secret_key = "";
CURL* BthmCPP::curl = NULL;


//---------------------------------
void 
BthmCPP::init( string &api_key, string &secret_key ) 
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	BthmCPP::curl = curl_easy_init();
	BthmCPP::api_key = api_key;
	BthmCPP::secret_key = secret_key;
}


void
BthmCPP::cleanup()
{
	curl_easy_cleanup(BthmCPP::curl);
	curl_global_cleanup();
}


//------------------
//GET /serverTime
//------------
void 
BthmCPP::get_serverTime( Json::Value &json_result) 
{
	BthmCPP_logger::write_log( "<BthmCPP::get_serverTime>" ) ;

	string url(BITHUMB_HOST);  
	url += "/serverTime";

	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_serverTime> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_serverTime> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_serverTime> Failed to get anything." ) ;
	}
}

//------------------
//GET /get_instruments
//------------
void 
BthmCPP::get_instruments( Json::Value &json_result )
{
	BthmCPP_logger::write_log( "<BthmCPP::get_instruments>" ) ;

	string url(BITHUMB_HOST);  
	url += "/spot/config";

	string str_result;
	curl_api( url, str_result ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_instruments> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_instruments> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_instruments> Failed to get anything." ) ;
	}
}


//--------------------
// Get Market Depth
/*
GET /spot/orderBook

Name	Type		Mandatory	Description
symbol	STRING		YES	

*/

void 
BthmCPP::get_depth( 
	const char *symbol, 
	Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_depth>" ) ;

	string url(BITHUMB_HOST);  
	url += "/spot/orderBook?";

	string querystring("symbol=");
	querystring.append( symbol );

	url.append( querystring );
	BthmCPP_logger::write_log( "<BthmCPP::get_depth> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    	reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_depth> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_depth> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_depth> Failed to get anything." ) ;
	}
}


//--------------------
// Get Last 100 Trades list
/*

GET /spot/trades

Name		Type	Mandatory	Description
symbol		STRING	YES	
*/

void 
BthmCPP::get_lastTrades( 
	const char *symbol, 
	Json::Value &json_result 
) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_lastTrades>" ) ;

	string url(BITHUMB_HOST);  
	url += "/spot/trades?";

	string querystring("symbol=");
	querystring.append( symbol );

	url.append( querystring );
	BthmCPP_logger::write_log( "<BthmCPP::get_lastTrades> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;
	
	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    	reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_lastTrades> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_lastTrades> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_lastTrades> Failed to get anything." ) ;
	}
}


//--------------------
// Get 24hr ticker price change statistics
/*
Name	Type	Mandatory	Description
symbol	STRING	YES	
*/
void 
BthmCPP::get_24hr( const char *symbol, Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_24hr>" ) ;

	string url(BITHUMB_HOST);  
	url += "/spot/ticker?";

	string querystring("symbol=");
	querystring.append( symbol );
	
	url.append( querystring );
	BthmCPP_logger::write_log( "<BthmCPP::get_24hr> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
	    		reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_24hr> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_24hr> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_24hr> Failed to get anything." ) ;
	}
}


//-----------------
/*

Get KLines( Candle stick / OHLC )
GET /spot/kline

Name		Type	Mandatory	Description
symbol		STRING	YES	
interval	STRING	YES	
startTime	LONG	NO	
endTime		LONG	NO	

*/

void 
BthmCPP::get_klines( 
	const char *symbol, 
	const char *interval, 
	time_t startTime, 
	time_t endTime,  
	Json::Value &json_result ) 
{		

	BthmCPP_logger::write_log( "<BthmCPP::get_klines>" ) ;

	string url(BITHUMB_HOST);  
	url += "/spot/kline?";

	string querystring("symbol=");
	querystring.append( symbol );

	querystring.append( "&type=" );
	querystring.append( "m1" );

	if ( startTime > 0 && endTime > 0 ) {

		querystring.append("&start=");
		querystring.append( to_string( startTime ) );

		querystring.append("&end=");
		querystring.append( to_string( endTime ) );
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_klines> startTime or endTime error." ) ;
		return;
	}

	url.append( querystring );
	BthmCPP_logger::write_log( "<BthmCPP::get_klines> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api( url, str_result ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
	    	json_result.clear();	
			reader.parse( str_result , json_result );
	    		
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_klines> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_klines> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_klines> Failed to get anything." ) ;
	}
}


//--------------------
// Get current account information. (SIGNED)
/*
POST /spot/assetList

Parameters:
Name		Type	Mandatory	Description
asset_type	STRING	YES	
coin_type	STRING	NO
*/


void 
BthmCPP::get_account( const char * asset_type, const char * coin_type, Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_account>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::get_account> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BITHUMB_HOST);
	url += "/spot/assetList";

	string action = "POST";
	
	post_data.clear();

	post_data["assetType"] = asset_type;
	if (strlen(coin_type))
	{
		post_data["coinType"] = coin_type;
	}

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);

	BthmCPP_logger::write_log( "<BthmCPP::get_account> url = |%s|" , url.c_str() ) ;
		
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_string , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_account> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_account> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_account> Failed to get anything." ) ;
	}

	BthmCPP_logger::write_log( "<BthmCPP::get_account> Done.\n" ) ;

}



//--------------------
// Get trades for a specific account and symbol. (SIGNED)
/*
POST /spot/myTrades
Name		Type	Mandatory	Description
symbol		STRING	YES	
limit		INT		YES
start		LONG    YES	
*/

void 
BthmCPP::get_myTrades( 
	const char *symbol,
	int limit,
	long long start,
	Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_myTrades>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BITHUMB_HOST);
	url += "/spot/myTrades";

	string action = "POST";

	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["limit"] = to_string(limit);
	post_data["startTime"] = to_string(start);

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);

	BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header , post_string , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> Failed to get anything." ) ;
	}

	BthmCPP_logger::write_log( "<BthmCPP::get_myTrades> Done.\n" ) ;

}


//--------------------
// Open Orders (SIGNED)
/*
POST /spot/openOrders

Name		Type	Mandatory	Description
symbol		STRING	YES	
*/

void 
BthmCPP::get_openOrders( 
	const char *symbol, 
	Json::Value &json_result 
) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_openOrders>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BITHUMB_HOST);
	url += "/spot/openOrders";

	string action = "POST";

	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["page"] = to_string(1);
	post_data["count"] = to_string(50);

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);

	BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> url = |%s|, post_data = |%s|" , url.c_str(), post_string.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_string , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> Failed to get anything." ) ;
	}
	
	BthmCPP_logger::write_log( "<BthmCPP::get_openOrders> Done.\n" ) ;

}



//--------------------
// All Orders (SIGNED)
/*
POST /spot/orderList

Name		Type	Mandatory	Description
symbol		STRING	YES	
status		STRING	YES	
queryRange	STRING	YES		
page		LONG	NO	
count		LONG	NO	
*/

void 
BthmCPP::get_allOrders( 
	const char *symbol, 
	const char *status,
	const char *range,
	int page,
	int count,
	Json::Value &json_result 
) 

{	

	BthmCPP_logger::write_log( "<BthmCPP::get_allOrders>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> API Key and Secret Key has not been set." ) ;
		return ;
	}


	string url(BITHUMB_HOST);
	url += "/spot/orderList";

	string action = "POST";

	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["status"] = status;
	post_data["queryRange"] = range;
	post_data["page"] = "1";
	post_data["count"] = "50";

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);
		
	BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_string , action ) ;


	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> Failed to get anything." ) ;
	}
	
	BthmCPP_logger::write_log( "<BthmCPP::get_allOrders> Done.\n" ) ;

}

string
BthmCPP::sign(map<string, string> post_data)
{	

	struct timeval tp;
    gettimeofday(&tp, NULL); 
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	post_data["apiKey"] = api_key;
	post_data["msgNo"] = to_string(ms);
	post_data["timestamp"] = to_string(ms);

	string s;

	set<pair<string, string>, comparator> sorted(
			post_data.begin(), post_data.end(), compFunctor);
	for (pair<string, string> element : sorted)
	{
			s += element.first + "=" + element.second;
			s += "&";
	}
	s.erase(s.length()-1, 1);

	string signature =  hmac_sha256( secret_key.c_str(), s.c_str() );

	cout << s << endl; 

	post_data["signature"] = signature;

	
	cout << signature << endl;

	Json::Value jsonMap;
	map<string, string>::const_iterator it = post_data.begin(), end = post_data.end();
	for ( ; it != end; ++it) {
    	jsonMap[it->first] = it->second;


    	// ^ beware: std::to_string is C++11
	}

	Json::FastWriter fastWriter;
	string output = fastWriter.write(jsonMap);

	cout << output << endl;

	return output;
}



//------------
/*
send order (SIGNED)
POST /spot/placeOrder

Name				Type		Mandatory	Description
symbol				STRING		YES	
side				STRING		YES	
type				STRING		YES	
quantity			DECIMAL		YES	
price				DECIMAL		YES	
*/

void 
BthmCPP::send_order( 
	const char *symbol, 
	const char *side,
	const char *type,
	double quantity,
	double price,
	Json::Value &json_result ) 
{

	BthmCPP_logger::write_log( "<BthmCPP::send_order>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::send_order> API Key and Secret Key has not been set." ) ;
		return ;
	}

	string url(BITHUMB_HOST);
	url += "/spot/placeOrder";

	string action = "POST";

	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["side"] = side;
	post_data["type"] = type;
	post_data["quantity"] = to_string(quantity);
	post_data["price"] = to_string(price);

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);


	BthmCPP_logger::write_log( "<BthmCPP::send_order> url = |%s|, post_data = |%s|" , url.c_str(), post_string.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_string, action ) ;

	if ( str_result.size() > 0 ) {
		cout << str_result << endl;


		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::send_order> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::send_order> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::send_order> Failed to get anything." ) ;
	}
	
	BthmCPP_logger::write_log( "<BthmCPP::send_order> Done.\n" ) ;
	
}


//------------------
/*
// get order (SIGNED)
POST /spot/singleOrder

Name				Type	Mandatory	Description
symbol				STRING	YES	
orderId				LONG	YES
*/

void 
BthmCPP::get_order( 
	const char *symbol, 
	long long orderId,
	Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::get_order>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::get_order> API Key and Secret Key has not been set." ) ;
		return ;
	}

	string url(BITHUMB_HOST);
	url += "/spot/singleOrder";

	string action = "POST";

	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["orderId"] = to_string(orderId);

	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);
		
	BthmCPP_logger::write_log( "<BthmCPP::get_order> url = |%s|" , url.c_str() ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_string , action ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::get_order> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::get_order> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::get_order> Failed to get anything." ) ;
	}

	
	BthmCPP_logger::write_log( "<BthmCPP::get_order> Done.\n" ) ;

}


//------------
/*
POST /spot/cancelOrder
cancel order (SIGNED)

symbol				STRING	YES	
orderId				LONG	YES	

*/

void 
BthmCPP::cancel_order( 
	const char *symbol, 
	long orderId,
	Json::Value &json_result ) 
{	

	BthmCPP_logger::write_log( "<BthmCPP::send_order>" ) ;

	if ( api_key.size() == 0 || secret_key.size() == 0 ) {
		BthmCPP_logger::write_log( "<BthmCPP::send_order> API Key and Secret Key has not been set." ) ;
		return ;
	}

	string url(BITHUMB_HOST);
	url += "/spot/cancelOrder";

	string action = "POST";
	
	post_data.clear();

	post_data["symbol"] = symbol;
	post_data["orderId"] = to_string(orderId); 
	
	string post_string = sign(post_data);

	vector <string> extra_http_header;
	string header_chunk("content-Type: application/json");
	extra_http_header.push_back(header_chunk);

	BthmCPP_logger::write_log( "<BthmCPP::send_order> url = |%s|, post_data = |%s|" , url.c_str(), post_string ) ;
	
	string str_result;
	curl_api_with_header( url, str_result , extra_http_header, post_string, action ) ;

	if ( str_result.size() > 0 ) {
		
		try {
			Json::Reader reader;
			json_result.clear();	
			reader.parse( str_result , json_result );
	    		
	    	} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP::send_order> Error ! %s", e.what() ); 
		}   
		BthmCPP_logger::write_log( "<BthmCPP::send_order> Done." ) ;
	
	} else {
		BthmCPP_logger::write_log( "<BthmCPP::send_order> Failed to get anything." ) ;
	}
	
	BthmCPP_logger::write_log( "<BthmCPP::send_order> Done.\n" ) ;

}


//-----------------
// Curl's callback
size_t 
BthmCPP::curl_cb( void *content, size_t size, size_t nmemb, std::string *buffer ) 
{	
	BthmCPP_logger::write_log( "<BthmCPP::curl_cb> " ) ;

	buffer->append((char*)content, size*nmemb);

	BthmCPP_logger::write_log( "<BthmCPP::curl_cb> done" ) ;
	return size*nmemb;
}


//--------------------------------------------------
void 
BthmCPP::curl_api( string &url, string &result_json ) {
	vector <string> v;
	string action = "GET";
	string post_data = "";

	curl_api_with_header( url , result_json , v, post_data , action );	
} 

//--------------------
// Do the curl
void 
BthmCPP::curl_api_with_header( string &url, string &str_result, vector <string> &extra_http_header , string &post_data , string &action ) 
{

	BthmCPP_logger::write_log( "<BthmCPP::curl_api>" ) ;

	CURLcode res;

	if( BthmCPP::curl ) {
	
		curl_easy_setopt(BthmCPP::curl, CURLOPT_URL, url.c_str() );
		curl_easy_setopt(BthmCPP::curl, CURLOPT_WRITEFUNCTION, BthmCPP::curl_cb);
		curl_easy_setopt(BthmCPP::curl, CURLOPT_WRITEDATA, &str_result );
		curl_easy_setopt(BthmCPP::curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(BthmCPP::curl, CURLOPT_ENCODING, "gzip");

		if ( extra_http_header.size() > 0 ) {
			
			struct curl_slist *chunk = NULL;
			for ( int i = 0 ; i < extra_http_header.size() ;i++ ) {
				chunk = curl_slist_append(chunk, extra_http_header[i].c_str() );
			}
			curl_easy_setopt(BthmCPP::curl, CURLOPT_HTTPHEADER, chunk);
		}

		if ( post_data.size() > 0 || action == "POST" || action == "PUT" || action == "DELETE" ) {

			if ( action == "PUT" || action == "DELETE" ) {
				curl_easy_setopt(BthmCPP::curl, CURLOPT_CUSTOMREQUEST, action.c_str() );
			}
			curl_easy_setopt(BthmCPP::curl, CURLOPT_POSTFIELDS, post_data.c_str() );
 		}
		
		res = curl_easy_perform(BthmCPP::curl);

		/* Check for errors */ 
		if ( res != CURLE_OK ) {
			BthmCPP_logger::write_log( "<BthmCPP::curl_api> curl_easy_perform() failed: %s" , curl_easy_strerror(res) ) ;
		} 	

	}

	BthmCPP_logger::write_log( "<BthmCPP::curl_api> done" ) ;

}
