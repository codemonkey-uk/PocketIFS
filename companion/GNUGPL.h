//GNUGPL
/*
Copyright (C) yyyy  name of author

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
http://www.gnu.org.ru/copyleft/gpl.txt
*/

/*
Example 1 (c) 1999 Joe Shmoe
Example is free software, & comes with ABSOLUTELY NO WARRANTY.
See the terms of the GNU General Public License for details.
*/
inline std::string GNUGPLmsgEnglish(
  std::string name,
  std::string ver,
  std::string date,
  std::string author)
{
return name + ' ' + ver + " (c) " + date + ' ' + author + ".\n" + name + " is free software, & comes with ABSOLUTELY NO WARRANTY.\nSee the terms of the GNU General Public License for details.";
}