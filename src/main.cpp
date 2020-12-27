#include <gameboy.h>
#include <iostream>

int main(int argc, char **argv){
    if(argc != 2){
    	std::cout<<"NO ROM !"<<std::endl;
    	return 1;
    }
    GB::Gameboy gb = GB::Gameboy(argv[1]);
    return 0;
}
