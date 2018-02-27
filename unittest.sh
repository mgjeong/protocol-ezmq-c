#!/bin/bash
./build_auto.sh --target_arch=x86_64 --with_dependencies=true

cd out/linux/x86_64/release/unittests

#set ezmq library path
export LD_LIBRARY_PATH=$PWD/../../../../../dependencies/protocol-ezmq-cpp/out/linux/x86_64/release/

#cezmq_api_test
./cezmq_api_test

#cezmq_pub_test
./cezmq_pub_test

#cezmq_sub_test
./cezmq_sub_test

#cezmq_event_test
./cezmq_event_test

#cezmq_reading_test
./cezmq_reading_test

#cezmq_bytedata_test
./cezmq_bytedata_test

