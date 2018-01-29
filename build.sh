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

install_dependencies() {

    if [ -d "./dependencies" ] ; then
        echo "dependencies folder exist"
    else
        mkdir dependencies
    fi

    cd ./dependencies
    #clone ezmq-protocol-cpp
    git clone git@github.sec.samsung.net:RS7-EdgeComputing/protocol-ezmq-cpp.git
    cd ./protocol-ezmq-cpp

    # Build ezmq-protocol-cpp for given architecture [x86/x86_64/arm/arm64/armhf]
    echo -e "${GREEN}Installing ezmq library and its dependencies${NO_COLOUR}"
    if [ "x86" == ${EZMQ_TARGET_ARCH} ]; then
        ./build.sh --with_dependencies=true --target_arch=x86
    elif [ "x86_64" == ${EZMQ_TARGET_ARCH} ]; then
        ./build.sh --with_dependencies=true --target_arch=x86_64
    elif [ "arm" == ${EZMQ_TARGET_ARCH} ]; then
        ./build.sh --with_dependencies=true --target_arch=arm
    elif [ "arm64" == ${EZMQ_TARGET_ARCH} ]; then
        ./build.sh --with_dependencies=true --target_arch=arm64
    elif [ "armhf" == ${EZMQ_TARGET_ARCH} ]; then
        ./build.sh --with_dependencies=true --target_arch=armhf
    fi
    echo -e "${GREEN}Installation of ezmq library and its dependencies done${NO_COLOUR}"
}

build_x86() {
    echo -e "Building for x86"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_OS=linux TARGET_ARCH=x86
}

build_x86_64() {
    echo -e "Building for x86_64"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_OS=linux TARGET_ARCH=x86_64
}

build_arm() {
    echo -e "Building for arm"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_ARCH=arm TC_PREFIX=/usr/bin/arm-linux-gnueabi- TC_PATH=/usr/bin/
}

build_arm64() {
    echo -e "Building for arm64"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_ARCH=arm64 TC_PREFIX=/usr/bin/aarch64-linux-gnu- TC_PATH=/usr/bin/
}

build_armhf() {
    echo -e "Building for armhf"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_ARCH=armhf TC_PREFIX=/usr/bin/arm-linux-gnueabihf- TC_PATH=/usr/bin/
}

build_armhf_qemu() {
    echo -e "Building for armhf-qemu"
    if [ ${EZMQ_WITH_DEP} = true ]; then
        install_dependencies
    fi
    cd $PROJECT_ROOT
    scons TARGET_ARCH=armhf
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
    echo -e "${BLUE}Usage:${NO_COLOUR} ./build.sh <option>"
    echo -e "${GREEN}Options:${NO_COLOUR}"
    echo "  --target_arch=[x86|x86_64|arm|arm64|armhf|armhf-qemu]        :  Choose Target Architecture"
    echo "  --with_dependencies=(default: false)                         :  Build cezmq with its dependency ezmq"
    echo "  -c                                                           :  Clean ezmq Repository and its dependencies"
    echo "  -h / --help                                                  :  Display help and exit"
    echo -e "${GREEN}Examples: ${NO_COLOUR}"
    echo -e "${BLUE}  build:-${NO_COLOUR}"
    echo "  $ ./build.sh --target_arch=x86_64"
    echo "  $ ./build.sh --with_dependencies=true --target_arch=x86_64 "
    echo -e "${BLUE}  clean:-${NO_COLOUR}"
    echo "  $ ./build.sh -c"
    echo -e "${BLUE}  help:-${NO_COLOUR}"
    echo "  $ ./build.sh -h"
    echo -e "${GREEN}Notes: ${NO_COLOUR}"
    echo "  - While building newly for any architecture use -with_dependencies=true option."
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
                if [ ${EZMQ_WITH_DEP} = true ]; then
                    echo -e "${BLUE}Build with depedencies${NO_COLOUR}"
                elif [ ${EZMQ_WITH_DEP} = false ]; then
                    echo -e "${BLUE}Build without depedencies${NO_COLOUR}"
                else
                    echo -e "${BLUE}Build without depedencies${NO_COLOUR}"
                    shift 1; exit 0
                fi
                shift 1;
                ;;
            --target_arch=*)
                EZMQ_TARGET_ARCH="${1#*=}";
                if [ "x86" == ${EZMQ_TARGET_ARCH} ]; then
                    build_x86; exit 0;
                elif [ "x86_64" == ${EZMQ_TARGET_ARCH} ]; then
                    build_x86_64; exit 0;
                elif [ "arm" == ${EZMQ_TARGET_ARCH} ]; then
                    build_arm; exit 0;
                elif [ "arm64" == ${EZMQ_TARGET_ARCH} ]; then
                    build_arm64; exit 0;
                elif [ "armhf" == ${EZMQ_TARGET_ARCH} ]; then
                    build_armhf; exit 0;
                elif [ "armhf-qemu" == ${EZMQ_TARGET_ARCH} ]; then
                    build_armhf_qemu; exit 0;
                else
                    echo -e "${RED}Not a supported architecture${NO_COLOUR}"
                    usage; exit 1;
                    fi
                    shift 1
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
