#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
  // Set any pin directions here. PWM output pin needs to be
  // set in an output mode here before using PWM.
  DDRD |= (1 << PORTD3) | (1 << PORTD4);
  DDRB |= (1 << PORTB1); // pin B1 set to output

  // CLAB TASK 1 --------------------------------------
  // Set up Timer1 in a Fast PWM mode (TCCR1A, TCCR1B and ICR1)
  // so that it reaches the max vaule at every 20ms (for servo).
  //  - Set fast PWM mode (#14) (WGM bits), prescaler of 8 (CS bits),
  //  - COM1A1 bit for non-onvertng PWM output (PB1, UNO-9).
  //  - set ICR1 value for TOP value
  TCCR1A = 0b10000010; // fast PWM 14 bit
  TCCR1B = 0b00011000;
  ICR1 = 39999;
  OCR1A = 1000;        // duty cycle 1 to 2ms
  TCCR1B |= _BV(CS11); // turn on timer, prescaler 8
  int i = OCR1A;

  while (1)
  {
    // Change OCR1A register value (Duty cycle) from 1000
    // (0.5ms PWM duty) to 4000 (2ms PWM duty). You can
    // use a for-loop to increment the value (e.g. by 10) with
    // some delay (e.g. 10ms).
    for (i = 800; i <= 5000; i += 10)
    {
      OCR1A = i;
      _delay_ms(10);
    }

    for (i = 5000; i >= 800; i -= 10)
    {
      OCR1A = i;
      _delay_ms(10);
    }

    // You can comment out this part in your demo as it will
    // cause delay between your servo swipe.
    // PORTD |= (1 << PORTD4);
    // _delay_ms(500);

    // PORTD &= ~(1 << PORTD4);
    // _delay_ms(500);
  }
}