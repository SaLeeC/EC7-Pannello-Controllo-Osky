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


//Presenta il menu di piè pagina dove sono indicate le funzioni raggiungibili con i 4 tatsi funzione sotto il display


void MenuDiFondo(byte MCorrente, byte MSottomenu)
{
  

  int Fondo, Inchiostro; //Inizializza le variabili locali Fondo e Inchiostro
  byte Offset = MenuNumVoci * MSottomenu; //Individua porzione del vettore MenuVoci considerare
  
  tft.setTextSize(2); //Inizializza il formato del font
  for (byte cc = 0; cc < MenuNumVoci; cc++)
  {
    //Setta i colori del fondo e dell'inchiostro
    Fondo = BLACK;
    Inchiostro = MenuColor[cc + Offset];
    //Se si sta per presentare il menù corrente inverte fondo e inchiostro
    if (cc == MCorrente)
    {
      Fondo = MenuColor[cc + Offset];
      Inchiostro = BLACK;
    }
    //Presenta la voce del menù
    tft.fillRoundRect(((Width/MenuNumVoci)*cc), Higth - 24 , Width/MenuNumVoci-2, 24, 3, Fondo);
    tft.setTextColor(Inchiostro, Fondo);

    tft.setCursor(((Width/MenuNumVoci)*cc)+3,Higth-18);
    tft.print(MenuVoci[cc + Offset]);
  }

}
