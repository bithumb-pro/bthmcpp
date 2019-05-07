



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



%: %.cpp
	@echo -n "\nMaking $@\n\n\n"
	g++ -std=c++11 -I$(libcurl_include) -I$(jsoncpp_include) -I$(libwebsockets_include) -I$(libbthmcpp_include) \
	$@.cpp \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	-L$(libbthmcpp_lib) \
	-lcurl -ljsoncpp  -lcrypto -lwebsockets -lbthmcpp -o $@

	cat run.template.sh  | sed s/%executable%/$@/ > $@.run.sh
	chmod 755 $@.run.sh


