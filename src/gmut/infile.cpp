// InFile, R.Krauße
// Klasse für Arbeit mit Textdatei

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "InFile.h"
#include "GrafKern.h"

char TrennZeichen[] = " \t",
     ZahlZeichen[] = "0123456789.",
     SignZeichen[] = "+-[](){}@=>,",
     HexaZeichen[] = "0123456789ABCDEFabcdef",
     StringZeichen[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_ÄÖÜäöüß";

#define HEX_ZEICHEN '#'
#define REM_ZEICHEN '"'

TTokenType InFile::ReadToken(char *str, int max)
{
  if ( TokenType >= TT_EOF ) return TokenType;
  if ( !CheckNewToken() ) return TokenType;
  char b = s[0];
  int i = 0;
  Long = 0; Double = 0;
  if ( b == HEX_ZEICHEN ) // Hexa-Zahl
  {
    TokenType = TT_LONG;
    String[i++] = b; s++;
    while ( strchr(HexaZeichen, b = s[0]) )
    {
      String[i++] = b; s++;
      if ( b <= '9' ) b -= '0'; else b = b & 0x1F + 9;
      Long = Long * 16 + b;
    }
  }
  else if ( strchr(ZahlZeichen, b ) ) // Zahl
  {
    TokenType = TT_LONG;
    char Point = 0;
    double digit = 1.0;
    while ( strchr(ZahlZeichen, b = s[0]) )
    {
      String[i++] = b; s++;
      if ( b == '.' && Point ) // 2 Punkte in Zahl
        fatal_error(80, Line);
      if ( b == '.' )
      {
        Point = 1;
        Double = (double)Long;
        TokenType = TT_DOUBLE;
      }
      else
        if ( Point )
          { digit = digit / 10; Double += digit * (b -'0'); }
        else
          Long = Long * 10 + (b - '0');
    }
    if ( !Point ) Double = (double) Long;
  }
  else if ( strchr(SignZeichen, b ) ) // Sign
  {
    TokenType = TT_SIGN;
    String[i++] = b; s++;
    if ( b == '-' && s[0] == '>' ) // für '->' nur 'p' 
      { s++; String[0] = 'p'; }
    Long = b;
  }
  else if ( strchr(StringZeichen, b ) ) // String
  {
    TokenType = TT_STRING;
    while ( strchr(StringZeichen, b = s[0]) )
    {
      String[i++] = b; s++;
    }
  }
  else
    fatal_error(2, b, Line);  // unbekanntes Zeichen
  String[i] = 0;
  if ( str )
    if ( max ) strncpy(str, String, max);
    else strcpy(str, String);
  return TokenType;
}

char InFile::NewLine()
// liest neue Zeile in s
{
  if ( eof() ) { TokenType = TT_EOF; return 0; }
  if ( bad() ) { TokenType = TT_ERROR; return 0; }
  getline(s1, LMAX_LINE);
  Line++;
  if ( bad() ) { TokenType = TT_ERROR; return 0; }
  s = s1;
  return 1;
}

char InFile::CheckNewToken()
// liest, bis 1. Zeichen eines Tokens gefunden
{
  char RemMode = 0;
  while ( 1 )
  {
    if ( !s[0] )
    {
      if ( !NewLine() )
        if ( RemMode ) fatal_error(5);
        else return 0;
    }
    else if ( s[0] == REM_ZEICHEN )
    {
      RemMode = !RemMode; s++;
    }
	 else if ( strchr(TrennZeichen, s[0]) || RemMode )
      s++;
    else if ( !RemMode )
      return 1;
  }
}

