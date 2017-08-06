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


void MenuRound(byte xNMenu)
{
  tft.fillRoundRect(0, 0, Width, 28, 3, MenuColor[xNMenu]);
  tft.setTextColor(BLACK, MenuColor[xNMenu]);
  tft.setCursor(CentraTesto(tTITOLO[xNMenu], Width, lFontBase, tSIZE),3);
  tft.setTextSize(tSIZE);
  tft.print(tTITOLO[xNMenu]);
}

byte ControllaPulsanti()
{
  //Controlla i pulsanti e restituisce il numero del pulsante premuto o 255 se 
  //non è premuto alcun pulsante
  byte CPcc = 0;
  for (CPcc = 0; (CPcc < NumPulsanti) & (digitalRead(Pulsanti[CPcc]) == LOW); CPcc++)
  {
  }
  if (CPcc < NumPulsanti)
  {
    //Attendi che il pulsante venga rilasciato (la pausa serve come debounce)
    while (digitalRead(Pulsanti[CPcc]) == HIGH)
    {
      delay(50);
    }
  }
  else
  {
    CPcc=255;
  }
  return (CPcc);
}

int CentraTesto(String CTTesto, int CTDisplayX, byte CTFontX, byte CTFontSize)
{
  return((CTDisplayX-(CTTesto.length()*(CTFontX+1)*CTFontSize))/2);
  
}

