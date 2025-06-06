#include <main_.h>
// Gia oso einai patimeno to BUTTON afksanei to PORTB kata 1 mexri na ftasei sto 0xff (255)
// Molis afisoume to BUTTON meionei to PORTB kata 1 mexri na ftasei sto 0x0 (0)
#use standard_io ( A )
//#use standard_io ( B )
#use standard_io ( C )
#byte PORTA =0xF80
#byte PORTB =0xF81
#byte PORTC =0xF82
#byte PORTD =0xF83
#byte PORTE =0xF84

int8 i = 0;

void testASM(int n) {
   n = n /2;
   #asm
   #endasm
}
void push_button(void);
// INTERRUPTS HANDLING
void init(void);
void diakopi_ext_int1();

void main()
{
   set_tris_b(0xff); // �������� �� ���� B ��� ������ (0)
   set_tris_d(0x00); // �������� �� ���� D ��� �����(1)
   PORTB = 0;   
   init();
   while(TRUE) {}
}

void push_button(void { // Synartisi elegxou patimatos-apeleftherosis tou BUTTON
   while (input(PIN_B4) == 1) {} // To PORT kai to PIN mporoun na allaksoun analoga tin anagki
   delay_ms(50);
   while (input(PIN_B4) == 0) {} // To PORT kai to PIN mporoun na allaksoun analoga tin anagki
   delay_ms(50);   
}

// INTERRUPTS HANDLING
void init(void) {
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT1);
   ext_int_edge(1, L_TO_H);
   
}

#INT_EXT1
void diakopi_ext_int1() {
   if (bit_test(PORTB, 0)) {
      PORTD ^= i;
      if (i>0)
         i--;
      PORTD ^= i;
   }
   else {
      PORTD ^= i;
      if (i<255)
         i++;
      PORTD ^= i;
   }
}



