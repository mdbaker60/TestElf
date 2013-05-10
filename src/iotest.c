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
		
		//Attempt to erase current line
		//	Esc[80D
		//	ESC[K
		
		//Write a string
		bwputstr(COM2, "TEST");
		
		//Escape sequence (Esc[)
		bwputc(COM2, 0x1B);
		bwputc(COM2, 0x5B);
		//Enter value 80
		bwputc(COM2, 0x38);
		bwputc(COM2, 0x30);
		//Escape Function
		bwputc(COM2, 'D');

		//Escape sequence(ESC[)
		bwputc(COM2, 0x1B);
		bwputc(COM2, 0x5B);
		//Escape Function
		bwputc(COM2, 'K');

		//Did it work?
		nl();
		bwputstr(COM2, "TEST should be gone\r");		
	return 0;
}



