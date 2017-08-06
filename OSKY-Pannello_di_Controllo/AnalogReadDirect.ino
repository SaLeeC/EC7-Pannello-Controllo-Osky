/*
 * OSKY Pannello di Controllo

    Copyright (C) {2016}  {SaLe}

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

For any problems or questions please conctact at 20824335+SaLeeC@users.noreply.github.com
 */


float ADCFirstREAD(uint8_t Modo, uint8_t Canale, uint8_t VRiferimento)


/* 
 **********************************************************************************
La presente versione si prefige di realizare un canale di accesso 
alle risorse del sistema ADC del ATmega2560 trascurando i processi 
di sincronizzazione dell'acquisizione e di ottimizzazione dei consumi.
Il processo di acuisizione è effettuato in modalità free running

Il processo prevede che venga configurata la modalità di funzionamento tramite la
chiamata della ADCFirstREAD()

Letture successive possono essere fatte con la ADCRead() (da implemetare)

La funzione restituisce il valore in MILLIVOLT con il segno coerente al valore letto
Nel caso si imposti la Vref esterna, viene restituito il numero di COUNT

*/

/* 
 **********************************************************************************
PARAMETRI:
Modo 
per processore 2560
01 Da accesso ai singoli ingressi in modalità SBILANCIATA 
10 Da accesso a coppie di ingressi in modalità BILANCIATA gain X1
100 Da accesso a coppie di ingressi in modalità BILANCIATA gain x10 o x200

Canale
00-07 o 00-15 in funzione del processore - Valore che, tramite la tabella 
        di indirizzamento di ogni singolo Modo da accesso ad un singolo 
        canale (piedino Analog input) in modalità sbilanciata o ad una coppia 
        di canali  (2 piedini Analog input) in modalità bilanciata

Vref
0 - Vref interna OFF e Vref proveniente da un circuito esterno 
1 - Vref = Vcc
2 - Vref = 1,1 (se prevista dall acircuiteria interna del processore)
3 - Vref = 2.56 (se prevista dall acircuiteria interna del processore)

*/


{
  int ADCval;
  float ADCVref;
  
// prescaler settato a 128 for 8Mhz
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
//Free Running mode
  ADCSRB &= (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);
// Allinea il risultato della conversione a DESTRA
  ADMUX  &= ~(1 << ADLAR);

// Setta Vref
// 0 - 00 - Vref interna OFF - Vref esterna
// 1 - 01 - AVCC - Inserire una capacità esterna sul piedino Vref per ridurre la rumorosità
// 2 - 10 - Vref interna 1.1V - Inserire una capacità esterna sul piedino Vref per ridurre la rumorosità
// 3 - 11 - Vref interna 2.56V - Inserire una capacità esterna sul piedino Vref per ridurre la rumorosità

//Setta la Vref e registra il valore in MILLIVOLT prescelto nella variabile di servizio.
//  VRiferimento=VRiferimento << 6;
  ADMUX &= ((VRiferimento & 0x03) << 6);
  ADMUX |= ((VRiferimento & 0x03) << 6);

  ADCVref=1023;
  switch (VRiferimento)
  {
    case 1:
      ADCVref=5000;
      break;
    case 2:
      ADCVref=1100;
      break;
    case 3:
      ADCVref=2560;
      break;
  }
  

//Setta il canale e la modalità prescelta
  switch (Modo)
  {
    
    case 1:
// Ingresso Sbilanciato sul canale "Canale" con guadagno 1x
// Canali da 0 a 15. Per i canali superiori al 7 applica lo split di 2 posizioni del bit di peso 8
      ADCSRB |= (Canale & 0x08);
      ADMUX = ADMUX | (Canale & 0x07);
      break;

    case 10:
/* 
 *  Ingresso BILANCIATO guadagno X1 sui canali (Vedi tabella)
    Canale     MUX5         C+ C-
   00 - 000000 - 0 10000 -  00-01
   01 - 000001 - 0 10001 -        01-01
   02 - 000010 - 0 10010 -  02-01
   03 - 000011 - 0 10011 -  03-01
   04 - 000000 - 0 10100 -  04-01
   05 - 000101 - 0 10101 -  05-01
   06 - 000110 - 0 10110 -  06-01
   07 - 000111 - 0 10111 -  07-01
   08 - 001000 - 0 11000 -  00-02
   09 - 001001 - 0 11001 -  01-02
   10 - 001010 - 0 11010 -        02-02
   11 - 001011 - 0 11011 -  03-02
   12 - 001100 - 0 11100 -  04-02
   13 - 001101 - 0 11101 -  05-02
 
   16 - 010000 - 110000 -  08-09
   17 - 010001 - 110001 -        09-09
   18 - 010010 - 110010 -  10-09
   19 - 010011 - 110011 -  11-09
   20 - 010100 - 110100 -  12-09
   21 - 010101 - 110101 -  13-09
   22 - 010110 - 110110 -  14-09
   23 - 010111 - 110111 -  15-09
   24 - 011000 - 111000 -  08-10
   25 - 011001 - 111001 -  09-10
   26 - 011010 - 111010 -        10-10
   27 - 011011 - 111011 -  11-10
   28 - 011100 - 111100 -  12-10
   29 - 011101 - 111101 -  13-10

*/
      ADCSRB |= (Canale & 0x10 >> MUX5);
      ADMUX = ADMUX | (Canale & 0x0F);
      ADMUX |= (1 << MUX4);
      break;
    
    case(100):
/* 
 *  Ingresso BILANCIATO guadagno X10 o X200 (vedi tabella) sui canali (Vedi tabella)
Canale  C+ C-
   00 - 000000 - 001000 -        00-00 X10
   01 - 000001 - 001001 -  01-00       X10
   02 - 000010 - 001010 -        00-00 X200
   03 - 000011 - 001011 -  01-00       X200
   04 - 000000 - 001100 -        02-02 X10
   05 - 000101 - 001101 -  03-02       X10
   06 - 000110 - 001110 -        02-02 X200
   07 - 000111 - 001111 -  03-02       X200
   08 - 001000 - 101000 -        08-08 X10
   09 - 001001 - 101001 -  09-08       X10
   10 - 001010 - 101010 -        08-08 X200
   11 - 001011 - 101011 -  09-08       X200
   12 - 001100 - 101100 -        10-10 X10
   13 - 001101 - 101101 -  11-10       X10
   14 - 001110 - 101110 -        10-10 X200
   15 - 001111 - 101111 -  11-10       X200
*/
      ADCSRB |= (Canale & 0x08 >> MUX5); //MUX5
      ADMUX = ADMUX | (Canale & 0x07);
      ADMUX |= (1 << MUX3);
      break;
    
  }
  
//Completa l'inizializzazione 
  ADCSRA |= (1 << ADEN);    // Enable the ADC
//Attende la stabilizzazione della Vref.
//  delay(100);
  ADCSRA |= (1 << ADSC);    // Start the ADC conversion
  while(ADCSRA & (1 << ADSC));
  ADCSRA |= (1 << ADSC);    // Start the ADC conversion
  while(ADCSRA & (1 << ADSC));

//Normalizza il risultato in funzione della Vref e della modalità prescelta
  ADCval=ADC;

// Gestione OVERFLOW
  if ((Modo == 1 & (ADCval > 1022)) | (Modo > 1 & ((ADCval>510) & (ADCval < 513))))
  {
    ADCVref = 99999.99;
  }
  else
  {
    if (Modo ==1)
    {
      ADCVref = float(ADCval)*(ADCVref/1023.00);
    }
    else
    {
      if (ADCval > 512)
      {
        ADCVref = float(-1023+ADCval)*(ADCVref/511.00);
      }
      else
      {
        ADCVref = float(ADCval)*(ADCVref/511.00);
      }
    }
    if (Modo==100)
    {
      ADCVref/=10.00;      
      if ((ADMUX & 0x02) == 1)
      {
        ADCVref/=20.0;
      }  
    }
  }
  ADCSRA &= ~(1 << ADEN);      // disable the ADC 
//Restituisce il valore in MILLIVOL (o in COUNT se si usa la Vref esterna)
  return ADCVref;
}

