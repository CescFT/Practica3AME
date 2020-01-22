#include <mbed.h>
#include <stdbool.h>

//links de confiança: https://os.mbed.com/cookbook/Bluetooth-Android-Controlled-MBED   /// https://os.mbed.com/handbook/Serial   ///   https://os.mbed.com/questions/83079/Send-data-between-PC-Monitor-and-Bluetoo/

DigitalOut ledVerd(D11); //O0
DigitalOut ledBlau(D10); //O1
DigitalOut ledVermell(D9); //O2
DigitalOut ledGroc(D6); //O3

Serial pc(USBTX, USBRX);
Serial device(PC_6, PA_12);

unsigned char receivedvalue;
bool pc_activity;

void send_bytes(uint8_t len ,uint8_t data)
{
    device.putc(len);
    while(len>0) {
        device.putc(data);
        len--;
    }
}

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
                case 49:
                    send_bytes(1,rx);
                    break;
                case 50:
                    send_bytes(2,rx);
                    break;
                case 51:
                    send_bytes(3,rx);
                    break;
                case 52:
                    send_bytes(4,rx);
                    break;
            }
 
        }
    }
}