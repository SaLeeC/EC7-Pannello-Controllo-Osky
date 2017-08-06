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



//Questa libreria non è inclusa ed è sostituita dalle procedure della AnalogReadDirect
//#include <AMM.h>


// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>



#include <EEPROM.h> //carica la libreria di gestione della EEprom interna

// *** SPFD5408 change -- End

//TFT rimappato per lasciare liberi i canali ADC configurabili con GAIN 
//variabile e come ingressi BILANCIATI.
//Si ricorda che questi pin possono essere rimappati su qualsiasi pin DIGITALE 
//o ANALOGICO
#define LCD_CS A14 // Chip Select goes to Analog 3
#define LCD_CD A13 // Command/Data goes to Analog 2
#define LCD_WR A12 // LCD Write goes to Analog 1
#define LCD_RD A11 // LCD Read goes to Analog 0

#define LCD_RESET A15 // Can alternately just connect to Arduino's reset pin

// Se il display è connesso direttamente alla scheda usare i settaggi che seguono 
// e remmate i precedenti
//#define LCD_CS A3
//#define LCD_CD A2
//#define LCD_WR A1
//#define LCD_RD A0
// optional
//#define LCD_RESET A4


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

#define Width 240
#define Higth 320

#define lFontBase 5
#define lFontAltezza 8

#define MenuNumVoci 4 //Numero delle voci del menù a piè di pagina
#define MenuNumMenu 3 //Numero dei menù di piè di pagina ammessi
#define SubNumVoci 2
#define ArgomentoNumVoci 9

#define PortaLuminositaLED 10 //Definisce la porta PWM che controlla la luminosità dei LED
#define MLuminosita 0 //Cella di memoria dove memorizzare la luminosità corrente dei LED
byte LuminositaLED; //Valori ammessi 0-15

#define PortaPulsante0 18
#define PortaPulsante1 19
#define PortaPulsante2 20
#define PortaPulsante3 21
#define NumPulsanti 4

byte tSIZE = 3;

//Pulsanti
byte Pulsanti[NumPulsanti] = {PortaPulsante0, PortaPulsante1, PortaPulsante2, PortaPulsante3};

//Messaggio di apertura
#define RigheOpen 18
const String tOpen[RigheOpen] = 
               {"TIFEO",
                "SaLe fecit",
                "versione 1.0 05/05/2016",
                "Personalizzazione per",
                "OSKY",
                "Sistema di monitoraggio dei parametri",
                "di funzionamento dell'imbarcazione.",
                "In questa versione il sistema legge e",
                "presenta i dati ma non e' abilitato al",
                "comando dei dispositivi installati a",
                "bordo",
                "Dispositivi interfacciati:",
                "Batteria 1 - Tensione",
                "Batteria 1 - Corrente",
                "Batteria 2 - Tensione",
                "Batteria 2 - Corrente",
                "Motore - Temperatura Testata",
                "Motore - Ore di Moto"
                };
const byte yOpen[RigheOpen] = {3,30,50,60,75,120,130,140,150,160,170,190,200,210,220,230,240,250};

const byte sOpen[RigheOpen] = {3,2,1,1,5,1,1,1,1,1,1,1,1,1,1,1,1,1};

//Titoli dei Menù 
String tTITOLO[MenuNumVoci] = {"HOME", "MOTORE", "BATTERIE", "LUMIN. LED"};

int MenuColor[MenuNumVoci * MenuNumMenu] = {WHITE, MAGENTA, YELLOW, CYAN, 
                                            WHITE, BLACK,   RED,    BLUE,
                                            WHITE, BLACK,   BLACK,  BLACK};

String MenuVoci[MenuNumVoci * MenuNumMenu] = {"Home", "Moto", "Batt", "Lum.",
                                              "Home", "    ", " +  ", "  - ",
                                              "Home", "    ", "    ", "    "};

//Voci dei sottomenù
String tSUBT[SubNumVoci] = {"1", "2"};
byte hSUBT[SubNumVoci] = {50, 170};
byte lSUBT[SubNumVoci] = {tSUBT[0].length(), tSUBT[1].length()};

//Argomenti/voci di ogni sottomenù
String tARGOMENTO[ArgomentoNumVoci] = {"Tens.", "Corr.",
                                       "T.Testa", "Ore Tot.", "Ore Att.",
                                       "Rete", "Barca", 
                                       "Lumin. LED", ""};
//Altre Variabili
boolean RicreaHome = HIGH;
byte MLPulsanteCorrente = 255;


// -- Setup

void setup(void) 
{
  
  Serial.begin(9600);

#ifdef USE_ADAFRUIT_SHIELD_PINOUT

#else

#endif
  tft.width();
  tft.reset();
  tft.begin(0x9341); // SDFP5408
  tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial

  pinMode(PortaLuminositaLED, OUTPUT);
  LuminositaLED = EEPROM.read(MLuminosita);
  analogWrite(PortaLuminositaLED, LuminositaLED);

  for (byte cc = 0; cc < NumPulsanti; cc++)
  {
    pinMode(Pulsanti[cc], INPUT_PULLUP);
  }

  //Prepara la schermata di apertura
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE, BLACK);
  //Presenta la schermata di apertura
  for(int cc=0; cc < RigheOpen; cc++)
  {
    tft.setCursor(CentraTesto(tOpen[cc], Width, lFontBase, sOpen[cc]),yOpen[cc]);
    tft.setTextSize(sOpen[cc]);
    tft.print(tOpen[cc]);
  }
  MenuDiFondo(99, 2);
  while (ControllaPulsanti() !=0)
  {
  }
}

void loop(void) 
{
  if (RicreaHome == HIGH)
  {
    MenuHome();
    RicreaHome = LOW;
  }
  MLPulsanteCorrente = ControllaPulsanti();
  switch (MLPulsanteCorrente)
  {
    case (0):
      break;
    case (1):
      MenuMotore();
      break;
    case (2):
      MLPulsanteCorrente = MenuBatterie();
      break;
    case (3):
      MenuLuminosita();
      RicreaHome = HIGH;
      break;
        
  }

}








