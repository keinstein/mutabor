// InFile, R.Krauße
// Klasse für Arbeit mit Textdatei

#include <fstream.h>

#define LMAX_LINE 200

// InFile ###########################################################
// Klasse für Arbeit mit Textdatei, diverse Lesefunktionen

enum TTokenType { TT_SIGN, TT_STRING, TT_LONG, TT_DOUBLE, TT_EOF, TT_ERROR };

class InFile : public ifstream
{
protected:
  char s1[LMAX_LINE], *s;
  TTokenType TokenType;
  char String[LMAX_LINE];
  long Long;
  double Double;
  int Line;
public:
  InFile(const char *Name) : ifstream(Name, ios::in)
	 { s1[0] = 0; s = s1; TokenType = TT_SIGN; Line = 0; };
  ~InFile() { close(); }
  TTokenType ReadToken(char *str = 0, int max = 0);
  TTokenType GetTokenType() { return TokenType; }
  char *GetString() { return String; }
  char GetSign() { return (char)Long & 0xFF; }
  long GetLong() { return Long; }
  double GetDouble() { return Double; }
  int GetLine() { return Line; }
private:
  char NewLine();
  char CheckNewToken();
};

