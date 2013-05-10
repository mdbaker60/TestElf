#include <bwio.h>	//io library
#include <ts7200.h>	//Predefined constants


void nl(){
	bwputstr(COM2, "\n\r");
}


int main(int argc, char* argv[]){
	//TODO: CLEAN! move time to structure?
	
	
	int in = 1;
	bwsetfifo(COM2, OFF);	
	
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
		//bwputstr(COM2, "Press 0 to quit");
		//nl();
		//in = bwgetc(COM2);
		//if (in == '0') return 0;
		int c;
		int * flags = (int *)(UART2_BASE + UART_FLAG_OFFSET);
		int * data = (int *)(UART2_BASE + UART_DATA_OFFSET);

		*data = 'a';
		while(!( *flags & RXFF_MASK));//While the recieve FIFO is not full.

		while(1){
			//TODO This while loop contains
			//code for printing an input key to the 
			char in;
			if (*flags & RXFF_MASK){
				in = *data;
				if (in == '\r') *data = '\n';
				else if (in == '\b'){
					*data = in;//Move cursor back

					//delete last char
					while (*flags & TXFF_MASK);
					*data = 0x1B;
					while (*flags & TXFF_MASK);
					*data = 0x5B;
					while (*flags & TXFF_MASK);
					*data = 'K';
				} 
				else *data = in;
			}
			//Simple io console test
			//Transmit input, then send it back

		}	
		bwputstr(COM2, "clk: ");
		bwputr(COM2, (unsigned int *)(TIMER3_BASE + VAL_OFFSET));

		
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



