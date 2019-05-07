
/*
	Author: xyzhu
	Date  : 2019/05/05
	
	C++ library for Bithumb Pro API.
*/


#ifndef BTHMCPP_H
#define BTHMCPP_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <exception>

#include <curl/curl.h>
#include <json/json.h>

#include <functional>


#define BITHUMB_HOST "https://global-openapi.bithumb.pro/openapi/v1"


using namespace std;


static map<string, string> post_data;
typedef function<bool(pair<string, string>, pair<string, string>)> comparator;

comparator compFunctor =
			[](std::pair<string, string> elem1 ,pair<string, string> elem2)
			{
				return elem1.first < elem2.first;
			};

class BthmCPP {

	static string api_key;
	static string secret_key;
	static CURL* curl;

	

	public:


		static void curl_api( string &url, string &result_json );
		static void curl_api_with_header( string &url, string &result_json , vector <string> &extra_http_header, string &post_data, string &action );
		static size_t curl_cb( void *content, size_t size, size_t nmemb, string *buffer ) ;
		
		static void init( string &api_key, string &secret_key);
		static void cleanup();

		static string sign(map<string, string> post_data);

		// Public API
		static void get_serverTime( Json::Value &json_result); 	
		static void get_instruments( Json::Value &json_result );

		static void get_depth( const char *symbol, Json::Value &json_result );
		static void get_lastTrades( const char *symbol, Json::Value &json_result ); 
		static void get_24hr( const char *symbol, Json::Value &json_result ); 
		static void get_klines( const char *symbol, const char *interval, time_t startTime, time_t endTime,  Json::Value &json_result );


		// API + Secret keys required
		static void get_account( const char * asset_type , const char * coin_type, Json::Value &json_result );
		
		static void get_myTrades( 
			const char *symbol, 
			int limit,
			long long start,
			Json::Value &json_result 
		);
		
		static void get_openOrders(  
			const char *symbol, 
			Json::Value &json_result 
		) ;
		

		static void get_allOrders(   
			const char *symbol, 
			const char *status,
			const char *range,
			int page,
			int count,
			Json::Value &json_result 
		);


		static void send_order( 
			const char *symbol, 
			const char *side,
			const char *type,
			double quantity,
			double price,
			Json::Value &json_result ) ;


		static void get_order( 
			const char *symbol, 
			long long orderId,
			Json::Value &json_result ); 


		static void cancel_order( 
			const char *symbol, 
			long orderId,
			Json::Value &json_result 
		);

};


#endif
