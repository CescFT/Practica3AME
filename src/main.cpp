#include <mbed.h>
#include <stdbool.h>

//links de confiança: https://os.mbed.com/cookbook/Bluetooth-Android-Controlled-MBED   /// https://os.mbed.com/handbook/Serial   ///   https://os.mbed.com/questions/83079/Send-data-between-PC-Monitor-and-Bluetoo/

DigitalOut ledVerd(D11); //O0
DigitalOut ledBlau(D10); //O1
DigitalOut ledVermell(D9); //O2
DigitalOut ledGroc(D6); //O3

Serial pc(USBTX, USBRX);
Serial device(D1, D0);

unsigned char receivedvalue;
bool pc_activity;


int main() {

  unsigned char rx;
  device.baud(9600);
    while(1) {
 
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
            }
 
        }
    }
}