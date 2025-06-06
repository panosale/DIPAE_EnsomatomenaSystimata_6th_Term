// DIPAE - Enosmatomena Systimata - 6o Eksamino
// Alevropoulos Panagiotis
// AM: 2022005
// Askisi: 7.2
#include <main_.h>
#include <flex_lcd_sim.h>

// Standard Eisodoi & Eksodoi
#use standard_io (A)
#use standard_io (B)
#use standard_io (C)

// Orismos ton thiron me ti thesi tous sti mnimi
#byte PORTA         =0xF80    
#byte PORTB         =0xF81
#byte PORTC         =0xF82
#byte PORTD         =0xF83
#byte PORTE         =0xF84

int8  des=0;
int8 seconds=0;
int8 sec_set_counter = 20;
int8 minute=0;
int8 hour=12;
int8 counter;
int1 flag=0;

// Dilosi synartiseon eksipiretisis
void timer0_int(void);
void init (void);

void main()
{
   init();
   lcd_gotoxy(1,1);
   lcd_putc("Timer:");
   while (1) { 
      if (flag) {
         lcd_gotoxy(4,2);
         printf (lcd_putc, "%02d:%02d:%02d",hour,minute,seconds );
         flag = 0;
      }          
   }
}

// Orismos synartiseon 
#INT_TIMER0    // Diakopi me ypsili protereotita
void timer0_int(void){
   set_timer0(5536); // Arxiki timi tou metriti
   sec_set_counter--;
   if ((sec_set_counter == 0)){
      sec_set_counter = 1;
      if ((bit_test(PORTD,3) == 1) && (bit_test(PORTD,2) == 1)) {
         seconds++; // Afksanei kathe 1/10 sec
         flag = 1;
         if (seconds > 59) {
            seconds = 0;
            minute++;
            if (minute > 59) {
               minute = 0;
               hour++;
            }
            if (hour >23) {
               hour = 0;
            }
         }
      }
      if((bit_test(PORTD,3) == 1) && (bit_test(PORTD,1) == 1)) {
         seconds--;
         flag = 1;
         if (seconds > 59) {
            seconds = 59;
            minute--;
         }
         if (minute > 59) { // Meionei kathe 1 sec
            minute = 59;
            hour--;
         }
         if(hour > 23) {
            hour = 23;
         }               
      }   
   }
   counter--; // Kathe 200 * 5 msec = 1 sec
   if (counter == 0) {
      counter = 200;
      if (bit_test(PORTD,3) == 0) {
         seconds++; // Afksanei kathe 1 sec
         flag = 1;
         if (seconds > 59) {
            seconds = 0;
            minute++;
            if (minute > 59) {
               minute = 0;
               hour++;
            }
            if (hour >23) {
               hour = 0;
            }               
         }              
      }   
   }                       
}                     
void init (void) {
   set_tris_b(0x00); // Orismos PORTD san EKSODO (0)
   set_tris_d(0xff);
   lcd_init();
   counter = 200; // Arxiki timi tou counter
   seconds = 0;
   sec_set_counter = 1;
   minute =0;
   hour = 12;
   des =0;
   flag = 0;
   SETUP_TIMER_0(T0_INTERNAL | T0_DIV_1 );
   set_timer0(5536);   //  Arxiki timi tou hardware metriti 
   enable_interrupts(GLOBAL); // Energopoiisi ton interrupts genika
   enable_interrupts(INT_TIMER0);
}

