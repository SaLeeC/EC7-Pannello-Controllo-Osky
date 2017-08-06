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




//Controlla la luminosità dei LED del pannello.
//Il controllo avviene tramite un canale PWM al quale, tramite un driver di potenza, 
//è collegato il comune dei LED.
//0 corrisponde alla massima luminostà.
//15 corrisponde ai LED spenti

void SettaLuminositaLED()
{
    analogWrite(PortaLuminositaLED, LuminositaLED*16);
}

