

libcurl_dir=../lib/libcurl-7.56.0
libcurl_lib=${libcurl_dir}/lib

libwebsockets_dir=../lib/libwebsockets
libwebsockets_lib=${libwebsockets_dir}/lib

libbthmcpp_dir=../lib/libbthmcpp
libbthmcpp_lib=${libbthmcpp_dir}/lib

export SSL_CERT_FILE=`pwd`/cacert.pem
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$libcurl_lib:$libwebsockets_lib:$libbthmcpp_lib

./example_template $@
