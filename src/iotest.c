#include <bwio.h>	//io library
#include <ts7200.h>	//Predefined constants
void nl(){
	bwputstr(COM2, "\n\r");
}


int main(int argc, char* argv[]){
	char str[] = "str[]\n\r";
	char y = 'c';
	bwsetfifo(COM2, OFF);	
	bwputstr(COM2, str);
	bwputstr(COM2, "argument\n\r");
	nl();
	bwputc(COM2, 'c');
	bwputx(COM2, 'c');
	bwputr(COM2, 0);
	return 0;
}



