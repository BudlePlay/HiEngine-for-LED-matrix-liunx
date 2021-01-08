//g++ -o test test.cpp -lwiringPi -lwiringPiDev

#include <iostream>
#include <tuple>
using namespace std;

#include <wiringPi.h>

#define R1 17
#define R2 23
#define G1 18
#define G2 24
#define B1 22
#define B2 25

#define A 7
#define B 8
#define C 9

#define CLK 3
#define LATCH 4
#define OE 2

unsigned char screen[16][32];

void clk(){
    digitalWrite(CLK,1);
    delayMicroseconds(10);
    digitalWrite(CLK,0);
}
void latch(){
    digitalWrite(LATCH,1);
    delayMicroseconds(10);
    digitalWrite(LATCH,0);
}
tuple<unsigned char, unsigned char, unsigned char> bits_from_int(unsigned char x){
    return tuple<unsigned char, unsigned char, unsigned char>(x&1, x&2, x&4);
}
void set_row(unsigned char row){
    tuple<unsigned char, unsigned char, unsigned char>result=bits_from_int(row);
    digitalWrite(A,get<0>(result));
    digitalWrite(B,get<1>(result));
    digitalWrite(C,get<2>(result));
}
void set_color_top(unsigned char color){
    tuple<unsigned char, unsigned char, unsigned char>result=bits_from_int(color);
    digitalWrite(R1,get<0>(result));
    digitalWrite(G1,get<1>(result));
    digitalWrite(B1,get<2>(result));
}
void set_color_bottom(unsigned char color){
    tuple<unsigned char, unsigned char, unsigned char>result=bits_from_int(color);
    digitalWrite(R2,get<0>(result));
    digitalWrite(G2,get<1>(result));
    digitalWrite(B2,get<2>(result));
}
void refresh(){
    for(int row=0;row<8;row++){
        digitalWrite(OE,1);
        set_color_top(0);
        set_row(row);
        for(int col=0;col<32;col++){
            set_color_top(screen[row][col]);
            set_color_bottom(screen[row+8][col]);
            clk();
        }
        latch();
        digitalWrite(OE,0);
        delay(1);
    }
}
void set_pixel(unsigned char x, unsigned char y, unsigned char color){
    screen[y][x]=color;
}

int main(){
    if(wiringPiSetupGpio()<0) return 1;

    pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT);
    pinMode(G1,OUTPUT);
    pinMode(G2,OUTPUT);
    pinMode(B1,OUTPUT);
    pinMode(B2,OUTPUT);

    pinMode(A,OUTPUT);
    pinMode(B,OUTPUT);
    pinMode(C,OUTPUT);
    
    pinMode(CLK,OUTPUT);
    pinMode(LATCH,OUTPUT);
    pinMode(OE,OUTPUT);

    // for(int i=0;i<32;i++) for(int j=0;j<16;j++) set_pixel(i,j,7);
    set_pixel(0,0,1);
    set_pixel(4,0,2);
    set_pixel(31,15,7);

    while(1){
        refresh();
    }

    return 0;
}