

#include "bthmcpp_websocket.h"
#include "bthmcpp_logger.h"



struct lws_context *BthmCPP_websocket::context = NULL;
struct lws_protocols BthmCPP_websocket::protocols[] =
{
	{
		"example-protocol",
		BthmCPP_websocket::event_cb,
		0,
		65536,
	},
	{ NULL, NULL, 0, 0 } /* terminator */
};

map <struct lws *,CB> BthmCPP_websocket::handles ;

int BthmCPP_websocket::send_command = 0;
int BthmCPP_websocket::send_ping = 0;
string BthmCPP_websocket::sub_command = "";

//--------------------------
int 
BthmCPP_websocket::event_cb( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{

	//struct pss *pss = (struct pss *)user;


	switch( reason )
	{
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			cout << "established !" << endl;
			lws_callback_on_writable( wsi );
			lws_set_timer_usecs(wsi, 5 * LWS_USEC_PER_SEC);
			send_command = 1;
			send_ping = 1;
			break;

		case LWS_CALLBACK_CLIENT_RECEIVE:
			
			/* Handle incomming messages here. */
			try {

				//BthmCPP_logger::write_log("%p %s",  wsi, (char *)in );

				string str_result = string( (char*)in );

				cout << "str_result : " << str_result << endl;
				Json::Reader reader;
				Json::Value json_result;	
				reader.parse( str_result , json_result );

				
				if ( handles.find( wsi ) != handles.end() ) {
					handles[wsi]( json_result );
				}

			} catch ( exception &e ) {
		 		BthmCPP_logger::write_log( "<BthmCPP_websocket::event_cb> Error ! %s", e.what() ); 
			}   	
			break;

		case LWS_CALLBACK_CLIENT_WRITEABLE:
		{

			if (send_command == 0 && send_ping == 1) {
				uint8_t ping[LWS_PRE + 125];
				int m,n=0;
				n = lws_snprintf((char *)ping + LWS_PRE, 125,
                                        "{'cmd':'ping'}");

				lwsl_user("Sending PING %d...\n", n);

				m = lws_write(wsi, ping + LWS_PRE, n, LWS_WRITE_PING);
				if (m < n) {
						lwsl_err("sending ping failed: %d\n", m);

						return -1;
				}
				send_ping = 0;
				lws_callback_on_writable(wsi);

			}
			

			if (send_command == 1) {
				uint8_t ping[LWS_PRE + 125];
				int m,n=0;

				//cout << "sub_command : " << sub_command << endl; 
				n = lws_snprintf((char *)ping + LWS_PRE, 125,
								sub_command.c_str());

				lwsl_user("Sending PING %d...\n", n);

				m = lws_write(wsi, ping + LWS_PRE, n, LWS_WRITE_TEXT);
				if (m < n) {
						lwsl_err("sending subscribe command failed: %d\n", m);

						return -1;
				}
				send_command = 0;
				lws_callback_on_writable(wsi);

			}

			break;
		}
		case LWS_CALLBACK_TIMER:
		{
			send_ping = 1;
			lws_callback_on_writable(wsi);
			lws_set_timer_usecs(wsi, 5 * LWS_USEC_PER_SEC);
			break;
		}

		case LWS_CALLBACK_CLIENT_RECEIVE_PONG:
		{
			lwsl_user("LWS_CALLBACK_CLIENT_RECEIVE_PONG\n");
			lwsl_hexdump_notice(in, len);
			break;
		}

		case LWS_CALLBACK_CLOSED:
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
                         in ? (char *)in : "(null)");

			if ( handles.find( wsi ) != handles.end() ) {
				handles.erase(wsi);
			}
			break;

		default:
			break;
	}

	return 0;
}


//-------------------
void 
BthmCPP_websocket::init( string command ) 
{
	struct lws_context_creation_info info;
	memset( &info, 0, sizeof(info) );

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;
	info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;

	context = lws_create_context( &info );

	sub_command = command;
}


//----------------------------
// Register call backs
void
BthmCPP_websocket::connect_endpoint ( 

		CB cb,
		const char *path

	) 
{
	char ws_path[1024];
	strcpy( ws_path, path );
	
	
	/* Connect if we are not connected to the server. */
	struct lws_client_connect_info ccinfo = {0};
	ccinfo.context 	= context;
	ccinfo.address 	= BITHUMB_WS_HOST;
	ccinfo.port 	= BITHUMB_WS_PORT;
	ccinfo.path 	= ws_path;
	//ccinfo.host 	= lws_canonical_hostname( context );
	ccinfo.host 	= BITHUMB_WS_HOST;
	ccinfo.origin	= BITHUMB_WS_HOST;
	//ccinfo.origin 	= "origin";
	ccinfo.protocol = protocols[0].name;
	ccinfo.ssl_connection = LCCSCF_USE_SSL | LCCSCF_ALLOW_SELFSIGNED | LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;

	struct lws* conn = lws_client_connect_via_info(&ccinfo);
	handles[conn] = cb;

}


//----------------------------
// Entering event loop
void 
BthmCPP_websocket::enter_event_loop() 
{
	while( 1 )
	{	
		try {	
			lws_service( context, 500 );
		} catch ( exception &e ) {
		 	BthmCPP_logger::write_log( "<BthmCPP_websocket::enter_event_loop> Error ! %s", e.what() ); 
		 	break;
		}
	}
	lws_context_destroy( context );
}



