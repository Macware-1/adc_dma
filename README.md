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

