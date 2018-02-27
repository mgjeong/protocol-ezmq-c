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

################ C EZMQ build script ##################

import os

Import('env')

cezmq_env = env.Clone()
target_os = cezmq_env.get('TARGET_OS')
target_arch = cezmq_env.get('TARGET_ARCH')

if cezmq_env.get('RELEASE'):
    cezmq_env.AppendUnique(CCFLAGS=['-Os'])
else:
    cezmq_env.AppendUnique(CCFLAGS=['-g'])

cezmq_env.AppendUnique(CPPPATH=[
	'./dependencies/protocol-ezmq-cpp/include',
	'./dependencies/protocol-ezmq-cpp/extlibs/zmq',
	'./dependencies/protocol-ezmq-cpp/extlibs/hippomocks/hippomocks',
	'./dependencies/protocol-ezmq-cpp/protobuf',
	'./include'
])

if cezmq_env.get('RELEASE'):
	cezmq_env.PrependUnique(LIBS=['ezmq'], LIBPATH=[os.path.join('./dependencies/protocol-ezmq-cpp/out/linux/', target_arch, 'release')])
else:
	cezmq_env.PrependUnique(LIBS=['ezmq'], LIBPATH=[os.path.join('./dependencies/protocol-ezmq-cpp/out/linux/', target_arch, 'debug')])

cezmq_env.PrependUnique(LIBS=['protobuf'])

if target_os not in ['windows']:
    cezmq_env.AppendUnique(
        CXXFLAGS=['-O2', '-g', '-Wall', '-fPIC', '-fmessage-length=0', '-std=c++0x', '-I/usr/local/include'])

if target_os not in ['windows']:
    cezmq_env.AppendUnique(LINKFLAGS=['-Wl,--no-undefined'])

if target_os in ['linux']:
    cezmq_env.AppendUnique(LIBS=['pthread'])

if target_os in ['linux']:
    if not env.get('RELEASE'):
        cezmq_env.PrependUnique(LIBS=['gcov'])
        cezmq_env.AppendUnique(CXXFLAGS=['--coverage'])

EZMQ_DIR = '.'
cezmq_env.AppendUnique(cezmq_src = [cezmq_env.Glob(os.path.join(EZMQ_DIR, 'src', '*.cpp'))])

ezmqshared = cezmq_env.SharedLibrary('cezmq', cezmq_env.get('cezmq_src'))
ezmqstatic = cezmq_env.StaticLibrary('cezmq', cezmq_env.get('cezmq_src'))

# Go to build C EZMQ sample apps
if target_os == 'linux':
       SConscript('samples/SConscript')

# Go to build EZMQ unit test cases
if target_os == 'linux':
    if target_arch in ['x86', 'x86_64', 'armhf']:
        SConscript('unittests/SConscript')

