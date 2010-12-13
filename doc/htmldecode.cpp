/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers
//  This is discussed in the "Quick Start" chapter in the Spirit User's Guide.
//
//  [ JDG 5/10/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
//#include <boost/spirit/core.hpp>
//#include <boost/spirit/actor/push_back_actor.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
//using namespace boost::spirit;

///////////////////////////////////////////////////////////////////////////////
//
//  Our comma separated list parser
//
///////////////////////////////////////////////////////////////////////////////

void print_char(wchar_t c) {
  if (c < (1 << 7)) cout.put(char(c));
  else if (c < (1 << 12 )) {
    cout.put((c >> 6) | 0xc0);
    cout.put((c & 0x3f) | 0x80);
  } else if (c < (1<<17)) {
    cout.put((c >> 12) | 0xe0);
    cout.put(((c >> 6) & 0x3f) | 0x80);
    cout.put((c & 0x3f) | 0x80);
  } else if ( c < (1<<22)) {
    cout.put(( c >> 18) | 0xf0);
    cout.put(((c >> 12) & 0x3f) | 0x80);
    cout.put(((c >> 6) & 0x3f) | 0x80);
    cout.put((c & 0x3f) | 0x80);
  } else if ( c < (1 << 27)) {
    cout.put(( c >> 24) | 0xf8);
    cout.put((( c >> 18) & 0x3f) | 0x80);
    cout.put(((c >> 12) & 0x3f) | 0x80);
    cout.put(((c >> 6) & 0x3f) | 0x80);
    cout.put((c & 0x3f) | 0x80);
  } else {
    cout.put(( c >> 30) | 0xfc);
    cout.put((( c >> 24) & 0x3f) | 0x80);
    cout.put((( c >> 18) & 0x3f) | 0x80);
    cout.put(((c >> 12) & 0x3f) | 0x80);
    cout.put(((c >> 6) & 0x3f) | 0x80);
    cout.put((c & 0x3f) | 0x80);
  }
}

char const * parse_hex(char const * str) {
        wchar_t c = 0;
        while (*str != ';') {
                if (!*str) exit(0);
                if (*str < '0') { 
                        std::cerr << "Error parsing number "<< *str; 
                        exit(1);
                } else if (*str <= '9')  
                        c = ((c << 4) | (*str - '0'));
                else if (*str < 'A') {
                        std::cerr << "Error parsing number "<< *str; 
                        exit(1);
                } else if (*str <= 'F')
                        c = ((c << 4) | (*str - 'A' + 10));
                else if (*str < 'a') {
                        std::cerr << "Error parsing number"<< *str; 
                        exit(1);
                } else if (*str <= 'f')
                        c = ((c << 4) | (*str - 'a' + 10));
                else {
                        std::cerr << "Error parsing number"<< *str; 
                        exit(1);
                }                
                ++str;
        }
        print_char(c);
        return str;
}

char const * parse_dec(char const * str) {
        wchar_t c = 0;
        while (*str != ';') {
                if (!*str) exit(0);
                if (*str < '0') { 
                        std::cerr << "Error parsing number"<< *str; 
                        exit(1);
                } else if (*str <= '9')  
                        c = ((c * 10) + (*str - '0'));
                else {
                        std::cerr << "Error parsing number"<< *str; 
                        exit(1);
                }                
                str;
        }
        print_char(c);
        return ++str;
}


void parse_numbers(char const* str)
{
        while (*str) {
                if (*str == '&') {
                        ++str;
                        if (*str != '#') 
                                print_char('&');
                        else {
                                ++str;
                                if (*str == 'x' || *str == 'X') 
                                        str = parse_hex(++str);
                                else str = parse_dec(str);
                        }
//		 rule<> r1, r2, r3;
//		 r1 = anychar_p[&print_char];
//		 r2 = ch_p('&') >> '#' >> ( ('x' >> hex_p[&print_char]) | uint_p[&print_char]) >> ';';
//		 r3 = *(lexeme_d[r2 | r1 ]); 
                }
                else print_char(*str);
                ++str;
        }
        return;
}

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
    string str;
    while (getline(cin, str))
    {
      parse_numbers(str.c_str());
      cout << endl;
    }
    return 0;
}
