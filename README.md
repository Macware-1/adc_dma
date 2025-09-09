How to compile (on linux platform):
There are two ways to compile and generate firmware file

Install compiler and generate firmware
1). go to compile_tools folder
2). RUN chmod +x requirements.sh 
3). RUN "sudo ./requirements.sh" 
4). RUN "cd .."
5). RUN "make clean && make"
6). .elf and .bin files will be available in build folder


Compile with docker:
1). go to compile_tools folder
2). RUN chmod +x compile_with_docker.sh
3). .elf and .bin files will be available in build folder

How to compile(on windows):
1). In powershell or command prompt
2). Download and install "arm-gnu-toolchain-14.3.rel1-mingw-w64-x86_64-arm-none-eabi.exe" from 
    https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
3). Add path "$env:Path += ";C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\14.3 rel1\bin"
4). verify if installed properly "arm-none-eabi-gcc --version"
5). RUN ".\build_firmware.ps1 release"

Compile with docker:
same as in linux with docker desktop
