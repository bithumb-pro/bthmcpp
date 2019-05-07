


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>

#include <json/json.h>
#include <libwebsockets.h>


#define BINANCE_WS_HOST "global-api.bithumb.pro"
#define BINANCE_WS_PORT 443


using namespace std;

typedef int (*CB)(Json::Value &json_value );


class BinaCPP_websocket {

    static int send_command;
	static int send_ping;
	static string sub_command;
	
	static struct lws_context *context;
	static struct lws_protocols protocols[]; 

	static map <struct lws *,CB> handles ;
	
	public:
		static int  event_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len );
		static void connect_endpoint(
			CB user_cb,
			const char* path
		);
		static void init( string command );
		static void enter_event_loop();

};
