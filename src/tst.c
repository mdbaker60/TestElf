#include <bwio.h>	//io library
#include <ts7200.h>	//Predefined constants

int main(int argc, char * argv[]){
	//PURPOSE:
	//	Compile
	//	Communicate properly to terminal (COM_2)
	//	Output something to terminal
	char** outString = "Hello\n\r";
	bwsetfifo(2, OFF);
	
	bwputstr(2, "Test");

	return 0;
}



