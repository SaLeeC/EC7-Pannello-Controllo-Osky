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



void MenuMotore()
{
  byte MLPulsanteCorrente = 255;

  byte NMenu = 1;
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
  
  tft.setTextColor(MenuColor[NMenu], BLACK);
  tft.drawRoundRect(0, hSUBT[0]-10, Width, 180, 3, MenuColor[NMenu]);
  tft.setCursor(5,hSUBT[0]+35);
  tft.print(tARGOMENTO[2]);
  tft.setCursor(5,hSUBT[0]+65);
  tft.print(tARGOMENTO[3]);
  tft.setCursor(5,hSUBT[0]+95);
  tft.print(tARGOMENTO[4]);
  while ((MLPulsanteCorrente == 255) || (MLPulsanteCorrente == NMenu))
  {
    MLPulsanteCorrente = ControllaPulsanti();
    //Aspetta e aspettando aggiorna i dati
  }
}

