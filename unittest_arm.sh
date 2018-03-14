#!/bin/bash
./build_auto.sh --target_arch=armhf-native --with_dependencies=true

cd out/linux/armhf/release/unittests

#set ezmq library path
export LD_LIBRARY_PATH=$PWD/../../../../../dependencies/protocol-ezmq-cpp/out/linux/armhf/release/

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

