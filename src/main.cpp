#include <mbed.h>
#include <stdbool.h>
#include <stdio.h>



DigitalOut ledVerd(D11); //O0
DigitalOut ledBlau(D10); //O1
DigitalOut ledVermell(D9); //O2
DigitalOut ledGroc(D6); //O3

Serial pc(USBTX, USBRX);
Serial device(D1, D0);

unsigned char receivedvalue;
bool pc_activity/*, introduceData=false*/, esperat=false;
unsigned char rx;


void send_bytes(uint8_t len ,uint8_t data)
{
    device.putc(len);
    while(len>0) {
        device.putc(data);
        len--;
    }
}

void recieve_bytes(){
    if(pc.readable()) {
            rx = pc.getc();
            device.putc(rx);
            pc.printf("\n\nreceived : %x",rx);
            pc_activity = !pc_activity;
        }
 
        if(device.readable()) {
            rx =device.getc();
            pc.printf("\n Received %x \nSending : %x",rx,rx);
            switch (rx) {
                case 49: //1
                    ledVermell.write(ledVermell.read() == 1 ? 0 : 1);
                    break;
                case 50: //2
                    ledVerd.write(ledVerd.read() == 1 ? 0 : 1);
                    break;
                case 51: //3
                    ledGroc.write(ledGroc.read() == 1 ? 0 : 1);
                    break;
                case 52: //4
                    ledBlau.write(ledBlau.read() == 1 ? 0 : 1);
                    break;
                case 48: //0 --> TOT OK
                case 53: //5
                    pc.printf("Puc continuar jugant!");
                    /*introduceData=true;*/
                    break;
                case 55: //7 ---> nivell passat
                    pc.printf("ENHORABONA! Següent nivell!\n");
                    break;
                case 56: //8 --> game over
                    pc.printf("GAME OVER. Ben jugat!\n\n\n");
                    break;
                case 57: //9 --> INPUT KO.
                    pc.printf("ERROR: Input no correcte.\n");
                    /*introduceData=true;*/
                    break;

            }
        }

}

int main() {

  
  unsigned char color;

  device.baud(9600);
    while(1) {

        recieve_bytes();
        
        /*if(introduceData){
            pc.printf("Introdueix color (Vermell: r,Verd: g,Blau: b,Groc: y):  ");
            scanf("%c", &color);
            send_bytes(1, color);
            introduceData=false;
        }*/
        
        
       
        

    }
}