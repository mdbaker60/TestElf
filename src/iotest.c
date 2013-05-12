#include <bwio.h>	//io library
#include <ts7200.h>	//Predefined constants


void nl(){
	//TODO REMOVE
	bwputstr(COM2, "\n\r");
}
void putc(int channel, char c){
	
	int* data;
	int* flags;
	
	switch(channel){
	case 1:
		data  = (int *)(UART1_BASE + UART_DATA_OFFSET);
		flags = (int *)(UART1_BASE + UART_FLAG_OFFSET);
		break;
	case 2:
		data  = (int *)(UART2_BASE + UART_DATA_OFFSET);
		flags = (int *)(UART2_BASE + UART_FLAG_OFFSET);
		break;

	}
	//Change this to if
	//Return error when TXFF_MASK is not set
	while(!(*flags & TXFE_MASK));
	*data = c;
}
void putstr(int channel, char* str){
	while(*str){
		putc(channel, *str);
		str++;
	}
}

void clkinit(){

	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + MODE_MASK) = 0;
	//Load the initial timer value
	*(unsigned int *)(TIMER3_BASE + LDR_OFFSET) = 0xFFFFFFFF;
	//2 kHz mode (...?)
	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + CLKSEL_MASK) = 1;
	//Start the timer (...?)
	*(unsigned int *)(TIMER3_BASE + CRTL_OFFSET + ENABLE_MASK) = 1;
}

void trainCommand(){
	//Set rate
	int * high, *low;
	high = (int *)(UART1_BASE + UART_LCRM_OFFSET); 
	low =  (int *)(UART1_BASE + UART_LCRL_OFFSET);
	*high = 0x0;
	*low = 0xC4;
	int i;
	//Initalize the UART1 control
	int * line = (int *)(UART1_BASE + UART_LCRH_OFFSET);	
	int buf = *line;
	//buf = buf | WLEN_MASK;
	buf = buf & ~PEN_MASK;
	buf = buf | STP2_MASK;
	*line = buf;
	//TODO Temporary
	//putc(1, 0x1);
	putc(1, 5);	
	for (i = 0; i < 99999; i++);
	putc(1, 48);
	putstr(2, "Press q to stop train.");
	while(1){
		if (*(int *)(UART2_BASE + UART_FLAG_OFFSET) & RXFF_MASK){
			if(*(int *)(UART2_BASE + UART_DATA_OFFSET) == 'q') break;	
		} 
	}
	putc(1, 0);
	for (i = 0; i < 1500; i++);
	putc(1, 48);
}
int main(int argc, char* argv[]){

	clkinit();	
	int in = 1;
	bwsetfifo(COM2, OFF);	
	bwsetfifo(COM1, OFF);	
	int c;
	int * flags = (int *)(UART2_BASE + UART_FLAG_OFFSET);
	int * data = (int *)(UART2_BASE + UART_DATA_OFFSET);
	//char * clk = "clk: \0";
	putstr(2, "clk: \n");
	//Train command
	trainCommand();
	while(0){
		int i;
		/*
		for(i = 0; i <=4; i++){
		while (*flags & TXFF_MASK);
		*data = clk[i];

		}*/
		//TODO This while loop contains
		//code for printing an input key to the 
		char in;
		if (*flags & RXFF_MASK){
			in = *data;
			if (in == '\r'){
			//Stay on the current line, but delete it, thus
			//	move cursor home (later to end of terminal prompt)
			//	delete everything past the cursor
			while (*flags & TXFF_MASK);
			*data = 0x1B;
			while (*flags & TXFF_MASK);
			*data = 0x5B;
			while (*flags & TXFF_MASK);
			*data = 0x38;
			while (*flags & TXFF_MASK);
			*data = 0x30;
			while (*flags & TXFF_MASK);
			*data = 'D';
			while (*flags & TXFF_MASK);
			*data = 0x1B;
			while (*flags & TXFF_MASK);
			*data = 0x5B;
			while (*flags & TXFF_MASK);
			*data = 'K';
			}
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
	}	
	return 0;
}

