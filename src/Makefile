

libcurl_dir=../lib/libcurl-7.56.0
libcurl_include=${libcurl_dir}/include
libcurl_lib=${libcurl_dir}/lib

jsoncpp_dir=../lib/jsoncpp-1.8.3
jsoncpp_include=${jsoncpp_dir}/include
jsoncpp_src=${jsoncpp_dir}/src


libwebsockets_dir=../lib/libwebsockets
libwebsockets_include=${libwebsockets_dir}/include
libwebsockets_lib=${libwebsockets_dir}/lib


build_dir=../lib/libbthmcpp/lib
objects=$(build_dir)/jsoncpp.o $(build_dir)/bthmcpp_utils.o $(build_dir)/bthmcpp_logger.o $(build_dir)/bthmcpp.o  $(build_dir)/bthmcpp_websocket.o

build_include=../lib/libbthmcpp/include


$(build_dir)/libbthmcpp.so: $(objects)
	g++ -std=c++0x -I$(libcurl_include) -I$(jsoncpp_include) -I$(libwebsockets_include)  \
	-L$(libcurl_lib) \
	-L$(libwebsockets_lib) \
	$(objects) \
	-shared \
	-lcurl -lcrypto -lwebsockets -fPIC -o $@

	# Make a new copy of the header too
	cp *.h  $(build_include)




$(build_dir)/bthmcpp.o: bthmcpp.cpp bthmcpp.h 
	g++ -std=c++0x -I$(libcurl_include) -I$(jsoncpp_include) -c bthmcpp.cpp  -fPIC   -o $(build_dir)/bthmcpp.o 


$(build_dir)/bthmcpp_websocket.o: bthmcpp_websocket.cpp bthmcpp_websocket.h 
	g++ -std=c++0x -I$(libwebsockets_include) -I$(jsoncpp_include) -c bthmcpp_websocket.cpp  -fPIC   -o $(build_dir)/bthmcpp_websocket.o


$(build_dir)/bthmcpp_logger.o: bthmcpp_logger.cpp bthmcpp_logger.h 
	g++ -std=c++0x -c bthmcpp_logger.cpp  -fPIC   -o $(build_dir)/bthmcpp_logger.o 



$(build_dir)/bthmcpp_utils.o: bthmcpp_utils.cpp bthmcpp_utils.h 
	g++ -std=c++0x -c bthmcpp_utils.cpp -fPIC   -o $(build_dir)/bthmcpp_utils.o 


$(build_dir)/jsoncpp.o: $(jsoncpp_src)/jsoncpp.cpp
	g++ -std=c++0x -I$(jsoncpp_include) -c $(jsoncpp_src)/jsoncpp.cpp -fPIC  -o  $(build_dir)/jsoncpp.o

clean:
	rm $(build_dir)/*.o
	rm $(build_dir)/*.so






