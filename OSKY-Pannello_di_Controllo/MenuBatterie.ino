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



byte MenuBatterie()
{
  byte MLPulsanteCorrente = 255;

  byte NMenu = 2;
  tft.fillScreen(BLACK);
  MenuDiFondo(NMenu, 0);
  MenuRound(NMenu);
/*     
  tft.fillRoundRect(0, 0, Width, 28, 3, MenuColor[NMenu]);
  tft.setTextColor(BLACK, MenuColor[NMenu]);
  tft.setCursor(((Width-(lTITOLO[NMenu]*lFontBase*tSIZE)-lTITOLO[NMenu])/2) ,3);
  tft.setTextSize(tSIZE);
  tft.print(tTITOLO[NMenu]);
*/
  tft.setTextColor(MenuColor[2], BLACK);
  for(byte i=0; i<2; i++)
  {  
    tft.drawRoundRect(0, hSUBT[i]-10, Width, 110, 3, MenuColor[NMenu]);
    tft.setCursor(((Width-(lSUBT[i]*lFontBase*tSIZE)-lSUBT[i])/2),hSUBT[i]);
    tft.print(tSUBT[i]);
    tft.setCursor(5,hSUBT[i]+35);
    tft.print(tARGOMENTO[0]);
    tft.setCursor(5,hSUBT[i]+65);
    tft.print(tARGOMENTO[1]);
  }
  
  while ((MLPulsanteCorrente == 255) | (MLPulsanteCorrente == NMenu))
  {
    MLPulsanteCorrente = ControllaPulsanti();
    //Aspetta e aspettando aggiorna i dati
  }
  return (MLPulsanteCorrente);
}






void ValoriBatterie()
{
  tft.setTextSize(tSIZE);
  float Volt[2];
  Volt[0] = ADCFirstREAD(1,4,1)/1000;
  Volt[1] = ADCFirstREAD(1,5,1)/1000;
  float Amp[2];
  Amp[0] = (50/65)*ADCFirstREAD(100,0,1);
  Amp[1] = (50/65)*ADCFirstREAD(100,5,1);
  
  for (byte cc=0; cc<2; cc++)
  {
    if ((Volt[cc]<10.8) | (Volt[cc]>14.2))
    {
      tft.setTextColor(RED, BLACK);
    }
    else
    {
      if ((Volt[cc]<11.2) | (Volt[cc]>13.8))
      {
        tft.setTextColor(YELLOW, BLACK);
      }
      else
      {
        tft.setTextColor(GREEN, BLACK);      
      }
    }
    tft.setCursor(145,hSUBT[cc]+35);
    tft.print(Volt[cc], 2);
    tft.print("V");

    if (Amp[cc]<-25)
    {
      tft.setTextColor(RED, BLACK);
    }
    else
    {
      if (Amp[cc]<0.1)
      {
        tft.setTextColor(YELLOW, BLACK);
      }
      else
      {
        tft.setTextColor(GREEN, BLACK);      
      }
    }
tft.setCursor(145,hSUBT[cc]+65);
    tft.print(Amp[cc], 2);
    tft.print("A");    
  }
}

