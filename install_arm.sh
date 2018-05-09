#!/bin/bash

USR_LIB_DIR=/usr/local/lib
USR_INC_DIR=/usr/local/include
KEYWORD_EZMQ_C=protocol-ezmq-c

# COPY shared library to /usr/local/lib
sudo cp out/linux/armhf/release/libcezmq.so /usr/local/lib

# COPY header file to /usr/local/include/opcua-c
sudo rm -rf $USR_INC_DIR/$KEYWORD_EZMQ_C
sudo mkdir $USR_INC_DIR/$KEYWORD_EZMQ_C
sudo cp -rf ./include/* $USR_INC_DIR/$KEYWORD_EZMQ_C/
