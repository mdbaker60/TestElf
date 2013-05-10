#include <bwio.h>	//io library
#include <ts7200.h>	//Predefined constants


void nl(){
	bwputstr(COM2, "\n\r");
}


int main(int argc, char* argv[]){
	//TODO: CLEAN! move time to structure?
	
	
	int in = 1;
	bwsetfifo(COM2, OFF);	
	//bwputstr(COM2, str);
	//bwputstr(COM2, "argument\n\r");
	//nl();
	//bwputc(COM2, 'c');
	//bwputx(COM2, 'c');
	//bwputr(COM2, 0);
	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + MODE_MASK) = 0;
	
	//Load the initial timer value
	*(unsigned int *)(TIMER3_BASE + LDR_OFFSET) = 0xFFFFFFFF;
	//2 kHz mode (...?)
	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + CLKSEL_MASK) = 0;
	//Start the timer (...?)
	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + ENABLE_MASK) = 1;
	
	//bwputc(COM2, (char)clk);
	
		bwputstr(COM2, "clk: ");
		bwputr(COM2, (unsigned int *)(TIMER3_BASE + VAL_OFFSET));
		//bwputstr(COM2, "Press 0 to quit");
		//nl();
		//in = bwgetc(COM2);
		
		bwputstr(COM2, "TEST");
		bwputc(COM2, 0x1B);
		bwputc(COM2, 0x5B);
		bwputc(COM2, '2');
		bwputc(COM2, 'J');
	return 0;
}



