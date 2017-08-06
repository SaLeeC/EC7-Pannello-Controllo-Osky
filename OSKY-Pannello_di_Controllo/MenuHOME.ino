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



//Menu principale

void MenuHome()
{
  byte NMenu = 0;
  tft.fillScreen(BLACK);
  MenuDiFondo(NMenu, 0);
  MenuRound(NMenu);

/*  
  switch (ControllaPulsanti())
  {
    case (0):
      //Se è qui significa che è stato premuto il bottone Home
      //non gestito in quanto siamo già in Home
      break;
    case (1):
      MenuMotore();
      break;
    case (2):
      MenuBatterie();
      break;
    case (3):
      MenuLuminosita();
      tft.setCursor(0,160);
      tft.print("Sono Io");
      break;
  }
//QUANDO TORNA NON RICREA IL MENU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

  
/*
  tft.fillRoundRect(0, 0, Width, 28, 3, MenuColor[NMenu]);
  tft.setTextColor(BLACK, MenuColor[NMenu]);
  tft.setCursor(((Width-(lTITOLO[NMenu]*lFontBase*tSIZE)-lTITOLO[NMenu])/2) ,3);
  tft.setTextSize(tSIZE);
  tft.print(tTITOLO[NMenu]);
*/
}

