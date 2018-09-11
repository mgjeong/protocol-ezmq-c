###############################################################################
# Copyright 2017 Samsung Electronics All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###############################################################################

#!/bin/bash
set +e
#Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NO_COLOUR="\033[0m"

PROJECT_ROOT=$(pwd)
DEP_ROOT=$(pwd)/dependencies
EZMQ_TARGET_ARCH="$(uname -m)"
EZMQ_WITH_DEP=false
EZMQ_BUILD_MODE="release"
EZMQ_WITH_SECURITY=true

PROTOCOL_EZMQ_CPP_VERSION=v1.0_rc1

RELEASE="1"
LOGGING=false

install_dependencies() {
    if [ -d "./dependencies" ] ; then
        echo "dependencies folder exist"
    else
        mkdir dependencies
    fi

    cd ./dependencies
    if [ -d "./protocol-ezmq-cpp" ] ; then
        echo "protocol-ezmq-cpp library folder exist"
    else
        git clone git@github.sec.samsung.net:RS7-EdgeComputing/protocol-ezmq-cpp.git
    fi
    
    # Build ezmq-protocol-cpp for given architecture [x86/x86_64/arm/arm64/armhf]
    cd ./protocol-ezmq-cpp
	 echo -e "${GREEN}Checkout ezmq release 1.0 version${NO_COLOUR}"
	 git checkout ${PROTOCOL_EZMQ_CPP_VERSION}
    echo -e "${GREEN}Installing ezmq library and its dependencies${NO_COLOUR}"
    ./build_auto.sh --with_dependencies=${EZMQ_WITH_DEP} --target_arch=${EZMQ_TARGET_ARCH} --build_mode=${EZMQ_BUILD_MODE} --with_security=${EZMQ_WITH_SECURITY}
    echo -e "${GREEN}Installation of ezmq library and its dependencies done${NO_COLOUR}"
}

build_native() {
    if [ "armhf-native" = ${EZMQ_TARGET_ARCH} ]; then
        scons TARGET_OS=linux TARGET_ARCH=armhf RELEASE=${RELEASE} LOGGING=${LOGGING}         
    else
        scons TARGET_OS=linux TARGET_ARCH=${EZMQ_TARGET_ARCH} RELEASE=${RELEASE} LOGGING=${LOGGING}   
    fi
}

build_arm() {
    scons TARGET_ARCH=arm TC_PREFIX=/usr/bin/arm-linux-gnueabi- TC_PATH=/usr/bin/ RELEASE=${RELEASE} LOGGING=${LOGGING}
}

build_arm64() {
    scons TARGET_ARCH=arm64 TC_PREFIX=/usr/bin/aarch64-linux-gnu- TC_PATH=/usr/bin/ RELEASE=${RELEASE} LOGGING=${LOGGING}
}

build_armhf() {
   scons TARGET_ARCH=armhf TC_PREFIX=/usr/bin/arm-linux-gnueabihf- TC_PATH=/usr/bin/ RELEASE=${RELEASE} LOGGING=${LOGGING}
}

build_armhf_qemu() {
    scons TARGET_ARCH=armhf RELEASE=${RELEASE} LOGGING=${LOGGING}
    if [ -x "/usr/bin/qemu-arm-static" ]; then
        echo -e "${BLUE}qemu-arm-static found, copying it to current directory${NO_COLOUR}"
        cp /usr/bin/qemu-arm-static .
    else
        echo -e "${RED}No qemu-arm-static found${NO_COLOUR}"
        echo -e "${BLUE} - Install qemu-arm-static and build again${NO_COLOUR}"
    fi
}

clean_ezmq() {
    echo -e "Cleaning ${BLUE}${PROJECT_ROOT}${NO_COLOUR}"
    echo -e "Deleting  ${RED}${PROJECT_ROOT}/out/${NO_COLOUR}"
    echo -e "Deleting  ${RED}${PROJECT_ROOT}/.sconsign.dblite${NO_COLOUR}"
    rm -r "${PROJECT_ROOT}/out/" "${PROJECT_ROOT}/.sconsign.dblite"
    find "${PROJECT_ROOT}" -name "*.memcheck" -delete -o -name "*.gcno" -delete -o -name "*.gcda" -delete -o -name "*.os" -delete -o -name "*.o" -delete
    echo -e "Deleting  ${RED}${PROJECT_ROOT}/dependencies/${NO_COLOUR}"
    rm -rf ./dependencies/protocol-ezmq-cpp
    echo -e "Finished Cleaning ${BLUE}${EZMQ}${NO_COLOUR}"
}

usage() {
    echo -e "${BLUE}Usage:${NO_COLOUR} ./build_auto.sh <option>"
    echo -e "${GREEN}Options:${NO_COLOUR}"
    echo "  --target_arch=[x86|x86_64|arm|arm64|armhf|armhf-qemu|armhf-native] :  Choose Target Architecture"
    echo "  --with_dependencies=[true|false](default: false)                   :  Build cezmq with its dependency ezmq"
    echo "  --build_mode=[release|debug](default: release)                     :  Build ezmq library and samples in release or debug mode"
    echo "  --with_security=[true|false](default: true)                        :  Build ezmq library with or without Security feature"
    echo "  -c                                                                 :  Clean ezmq Repository and its dependencies"
    echo "  -h / --help                                                        :  Display help and exit"
    echo -e "${GREEN}Notes: ${NO_COLOUR}"
    echo "  - While building newly for any architecture use -with_dependencies=true option."
    echo "  - Before running script, Make sure libsodium is installed, it can be installed using:"
    echo "    $ sudo apt-get install libsodium-dev"
}

build() {
    echo -e "${GREEN}Target Arch is: $EZMQ_TARGET_ARCH${NO_COLOUR}"
    echo -e "${GREEN}Build mode is: $EZMQ_BUILD_MODE${NO_COLOUR}"
    echo -e "${GREEN}Build with depedencies: ${EZMQ_WITH_DEP}${NO_COLOUR}"
    echo -e "${GREEN}Is security enabled: $EZMQ_WITH_SECURITY${NO_COLOUR}"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    
    if [ "debug" = ${EZMQ_BUILD_MODE} ]; then
        RELEASE="0"
        LOGGING=true
    fi
    
    cd $PROJECT_ROOT
    if [ "x86" = ${EZMQ_TARGET_ARCH} ]; then
         build_native;
    elif [ "x86_64" = ${EZMQ_TARGET_ARCH} ]; then
         build_native;
    elif [ "armhf-native" = ${EZMQ_TARGET_ARCH} ]; then
         build_native;
    elif [ "arm" = ${EZMQ_TARGET_ARCH} ]; then
         build_arm;
    elif [ "arm64" = ${EZMQ_TARGET_ARCH} ]; then
         build_arm64;
    elif [ "armhf" = ${EZMQ_TARGET_ARCH} ]; then
         build_armhf;
    elif [ "armhf-qemu" = ${EZMQ_TARGET_ARCH} ]; then
         build_armhf_qemu; 
    else
         echo -e "${RED}Not a supported architecture${NO_COLOUR}"
         usage; exit 1;
    fi
}

process_cmd_args() {
    if [ "$#" -eq 0  ]; then
        echo -e "No argument.."
        usage; exit 1
    fi

    while [ "$#" -gt 0  ]; do
        case "$1" in
            --with_dependencies=*)
                EZMQ_WITH_DEP="${1#*=}";
                if [ ${EZMQ_WITH_DEP} != true ] && [ ${EZMQ_WITH_DEP} != false ]; then
                    echo -e "${RED}Unknown option for --with_dependencies${NO_COLOUR}"
                    shift 1; exit 0
                fi
                shift 1;
                ;;
            --target_arch=*)
                EZMQ_TARGET_ARCH="${1#*=}";
                shift 1
                ;;
            --build_mode=*)
                EZMQ_BUILD_MODE="${1#*=}";
                shift 1;
                ;;
            --with_security=*)
                EZMQ_WITH_SECURITY="${1#*=}";
                if [ ${EZMQ_WITH_SECURITY} != true ] && [ ${EZMQ_WITH_SECURITY} != false ]; then
                    echo -e "${RED}Unknown option for --with_security${NO_COLOUR}"
                    shift 1; exit 0
                fi              
                shift 1;
                ;; 
            -c)
                clean_ezmq
                shift 1; exit 0
                ;;
            -h)
                usage; exit 0
                ;;
            --help)
                usage; exit 0
                ;;
            -*)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
            *)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
        esac
    done
}

process_cmd_args "$@"
echo -e "Building C ezMQ library("${EZMQ_TARGET_ARCH}").."
build
echo -e "Done building C ezMQ library("${EZMQ_TARGET_ARCH}")"

exit 0
