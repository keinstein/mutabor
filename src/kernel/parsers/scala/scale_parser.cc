// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.hh"

// User implementation prologue.

#line 51 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 61 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:413

#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scale_lexer.h"
#include "src/kernel/parsers/scala/scala-inlines.h"
#ifdef _
#undef _
#endif
#define _ _mut
#define YY_ _mut

// fix the interface to the scanner
#ifdef yylex
#undef yylex
#endif
#define yylex(x,y,z) lexer.get_token()

#if 0
#ifdef DEBUG
#define YYDEBUG 1
#endif
#endif

#line 76 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 33 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:479
namespace mutabor { namespace scala_parser {
#line 162 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  scale_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  scale_parser::scale_parser (scale_lexer & lexer_yyarg, interval_pattern & result_yyarg, keymap & keys_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      result (result_yyarg),
      keys (keys_yyarg)
  {}

  scale_parser::~scale_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  scale_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  scale_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  scale_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  scale_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  scale_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  scale_parser::symbol_number_type
  scale_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  scale_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  scale_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 15: // "double (with leadig white space)"
      case 16: // "double"
      case 80: // nospace_float
      case 81: // float
        value.move< double > (that.value);
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 74: // ratio_start
      case 78: // nospace_integer
      case 79: // integer
        value.move< int32_t > (that.value);
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 60: // interval
      case 61: // interval2
      case 62: // interval1
        value.move< scala_parser::interval > (that.value);
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 63: // key
      case 64: // key1
        value.move< scala_parser::key > (that.value);
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 70: // scala_float
      case 71: // scala_float1
        value.move< scala_parser::scala_value<double>  > (that.value);
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 68: // scala_int
      case 69: // scala_int1
        value.move< scala_parser::scala_value<int32_t>  > (that.value);
        break;

      case 5: // "string token"
      case 6: // "text after the last interval"
      case 7: // "floating point number"
      case 8: // "integer number"
      case 9: // "white space"
      case 10: // "comment"
      case 11: // "single comment line"
      case 17: // "whitespace"
      case 18: // "character string with newline"
      case 19: // "(non)empty character string with newline"
      case 20: // "one of several tokens that can be in a string"
      case 30: // "The whole text after the file end"
      case 57: // comment
      case 58: // comment_line
      case 72: // lazy_string
      case 75: // string_element
      case 77: // string
      case 82: // space
      case 83: // garbage
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  scale_parser::stack_symbol_type&
  scale_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 15: // "double (with leadig white space)"
      case 16: // "double"
      case 80: // nospace_float
      case 81: // float
        value.copy< double > (that.value);
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 74: // ratio_start
      case 78: // nospace_integer
      case 79: // integer
        value.copy< int32_t > (that.value);
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 60: // interval
      case 61: // interval2
      case 62: // interval1
        value.copy< scala_parser::interval > (that.value);
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 63: // key
      case 64: // key1
        value.copy< scala_parser::key > (that.value);
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 70: // scala_float
      case 71: // scala_float1
        value.copy< scala_parser::scala_value<double>  > (that.value);
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 68: // scala_int
      case 69: // scala_int1
        value.copy< scala_parser::scala_value<int32_t>  > (that.value);
        break;

      case 5: // "string token"
      case 6: // "text after the last interval"
      case 7: // "floating point number"
      case 8: // "integer number"
      case 9: // "white space"
      case 10: // "comment"
      case 11: // "single comment line"
      case 17: // "whitespace"
      case 18: // "character string with newline"
      case 19: // "(non)empty character string with newline"
      case 20: // "one of several tokens that can be in a string"
      case 30: // "The whole text after the file end"
      case 57: // comment
      case 58: // comment_line
      case 72: // lazy_string
      case 75: // string_element
      case 77: // string
      case 82: // space
      case 83: // garbage
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  scale_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  scale_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 5: // "string token"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 467 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 6: // "text after the last interval"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 474 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 7: // "floating point number"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 481 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 8: // "integer number"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 488 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 9: // "white space"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 495 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 10: // "comment"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 502 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 11: // "single comment line"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 509 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 12: // "integer (with leadig white space)"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 516 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 13: // "integer"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 523 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 14: // "integer /"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 530 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 15: // "double (with leadig white space)"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 537 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 16: // "double"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 544 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 17: // "whitespace"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 551 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 18: // "character string with newline"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 558 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 19: // "(non)empty character string with newline"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 565 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 20: // "one of several tokens that can be in a string"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 572 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 21: // "interval"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 579 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 22: // "bare interval"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 586 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 23: // "bare interval with description"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 593 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 24: // "scala int value"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 600 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 25: // "scala int value without comment"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 607 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 26: // "scala double value"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 614 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 27: // "scala double value without comment"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 621 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 28: // "key"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 628 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 29: // "key without comment"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 635 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 30: // "The whole text after the file end"

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 642 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 57: // comment

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 649 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 58: // comment_line

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 656 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 60: // interval

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 663 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 61: // interval2

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 670 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 62: // interval1

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 677 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 63: // key

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 684 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 64: // key1

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 691 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 68: // scala_int

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 698 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 69: // scala_int1

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 705 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 70: // scala_float

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 712 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 71: // scala_float1

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 719 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 72: // lazy_string

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 726 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 74: // ratio_start

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 733 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 75: // string_element

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 740 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 77: // string

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 747 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 78: // nospace_integer

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 754 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 79: // integer

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 761 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 80: // nospace_float

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 768 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 81: // float

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< double > (); }
#line 775 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 82: // space

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 782 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;

      case 83: // garbage

#line 128 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:636
        { yyoutput << yysym.value.template as< std::string > (); }
#line 789 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  scale_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  scale_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  scale_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  scale_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  scale_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  scale_parser::debug_level_type
  scale_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  scale_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline scale_parser::state_type
  scale_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  scale_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  scale_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  scale_parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 54 "/home/tobias/Entwicklung/mutabor/build/debug/linux-64/../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:741
{
	// intial location
	yyla.location.begin.filename = yyla.location.end.filename = &lexer.get_filename();
}

#line 908 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (lexer, result, keys));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 15: // "double (with leadig white space)"
      case 16: // "double"
      case 80: // nospace_float
      case 81: // float
        yylhs.value.build< double > ();
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 74: // ratio_start
      case 78: // nospace_integer
      case 79: // integer
        yylhs.value.build< int32_t > ();
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 60: // interval
      case 61: // interval2
      case 62: // interval1
        yylhs.value.build< scala_parser::interval > ();
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 63: // key
      case 64: // key1
        yylhs.value.build< scala_parser::key > ();
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 70: // scala_float
      case 71: // scala_float1
        yylhs.value.build< scala_parser::scala_value<double>  > ();
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 68: // scala_int
      case 69: // scala_int1
        yylhs.value.build< scala_parser::scala_value<int32_t>  > ();
        break;

      case 5: // "string token"
      case 6: // "text after the last interval"
      case 7: // "floating point number"
      case 8: // "integer number"
      case 9: // "white space"
      case 10: // "comment"
      case 11: // "single comment line"
      case 17: // "whitespace"
      case 18: // "character string with newline"
      case 19: // "(non)empty character string with newline"
      case 20: // "one of several tokens that can be in a string"
      case 30: // "The whole text after the file end"
      case 57: // comment
      case 58: // comment_line
      case 72: // lazy_string
      case 75: // string_element
      case 77: // string
      case 82: // space
      case 83: // garbage
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 4:
#line 145 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
                   while (keys.keys.size() < (size_t)keys.count.value) {
			   keys.keys.push_back(scala_parser::key());
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
#line 1091 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 151 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		std::swap(keys.garbage,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_garbage);
		}
#line 1100 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 158 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
                   if (result.count != result.intervals.size()) {
			   error(yystack_[0].location,_mut("Too few intervals have been provided."));
                           YYERROR;
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
#line 1112 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 165 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		std::swap(result.garbage,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_garbage);
		}
#line 1121 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 171 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { lexer.push_state(scale_lexer::in_string); }
#line 1127 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 171 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	                std::swap(result.name,yystack_[0].value.as< std::string > ());
		        lexer.push_state(scale_lexer::in_integer);
		}
#line 1136 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 177 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		if (!result.count) {  lexer.push_state(scale_lexer::in_garbage); }
		else {
			result.intervals.reserve(result.count);
                        lexer.push_state(scale_lexer::in_interval);
		}
		}
#line 1148 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 186 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
			lexer.push_state(scale_lexer::in_integer);
                }
#line 1156 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 196 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
			lexer.pop_state(scale_lexer::in_integer);
			std::swap(keys.count,yystack_[6].value.as< scala_parser::scala_value<int32_t>  > ());
		        std::swap(keys.first_key,yystack_[5].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.last_key,yystack_[4].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.anchor,yystack_[3].value.as< scala_parser::scala_value<int32_t>  > ());
		        std::swap(keys.reference,yystack_[2].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.reference_frequency,yystack_[1].value.as< scala_parser::scala_value<double>  > ());
                        std::swap(keys.repetition_interval,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ());
			if (!keys.count.value) {
				lexer.push_state(scale_lexer::in_garbage);
		        }
 		        else {
			       keys.keys.reserve(keys.count.value);
		               lexer.push_state(scale_lexer::in_key);
		       }
		}
#line 1178 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 216 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	                keys.keys.push_back(yystack_[0].value.as< scala_parser::key > ());
			DEBUGLOG(sclparser,"count: %d, size: %d",
		                 keys.count.value,
                                 keys.keys.size());
	                if ((size_t)keys.count.value == keys.keys.size()) {
			       lexer.pop_state(scale_lexer::in_key);
		               lexer.push_state(scale_lexer::in_garbage);
		        }
		}
#line 1193 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 231 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(result.comment1,yystack_[0].value.as< std::string > ()); }
#line 1199 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 233 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(result.comment2,yystack_[0].value.as< std::string > ()); }
#line 1205 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 235 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { lexer.pop_state(scale_lexer::in_integer); }
#line 1211 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 237 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { result.count = yystack_[1].value.as< int32_t > (); }
#line 1217 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 238 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { result.count = yystack_[1].value.as< int32_t > (); std::swap(result.count_comment,yystack_[0].value.as< std::string > ()); }
#line 1223 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 239 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {  lexer.push_state(scale_lexer::in_string); }
#line 1229 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 239 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		result.count = yystack_[3].value.as< int32_t > ();
		std::swap(result.count_comment,yystack_[0].value.as< std::string > ());
		error(yystack_[1].location,_mut("The interval count must be an integer number, not a float."));
		}
#line 1239 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 244 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {  lexer.push_state(scale_lexer::in_string); }
#line 1245 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 244 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		result.count = yystack_[3].value.as< int32_t > ();
		std::swap(result.count_comment,yystack_[0].value.as< std::string > ());
		error(yystack_[1].location,_mut("The interval count must be an integer number, not a ratio."));
		}
#line 1255 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 252 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	        result.intervals.push_back(yystack_[0].value.as< scala_parser::interval > ());
	        if (result.count == result.intervals.size()) {
			lexer.pop_state(scale_lexer::in_interval);
			lexer.push_state(scale_lexer::in_garbage);
		}
		}
#line 1267 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 261 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1273 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 262 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
 	        std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ());
		yylhs.value.as< std::string > () += "\n" + yystack_[0].value.as< std::string > ();
		}
#line 1282 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 267 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { lexer.push_state(scale_lexer::in_string); }
#line 1288 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 267 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
			std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ());
		        lexer.pop_state(scale_lexer::in_string);
		}
#line 1297 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 273 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	        yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< scala_parser::interval > ().description);
		lexer.pop_state(scale_lexer::in_string);
			}
#line 1308 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 279 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< scala_parser::interval > ().description);
		std::swap(yylhs.value.as< scala_parser::interval > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
			}
#line 1320 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 288 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[1].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[1].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1330 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 293 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	        yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > ());
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1340 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 298 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		lexer.error(yystack_[0].location, _mut("An incomplete ratio has been detected, and descriptions must not start with '/'."));
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > ());
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1350 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 305 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > (),yystack_[0].value.as< int32_t > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1359 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 309 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > (),yystack_[0].value.as< double > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1368 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 313 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[0].value.as< double > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1377 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 320 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::key > ().type = yystack_[0].value.as< scala_parser::key > ().type;
		yylhs.value.as< scala_parser::key > ().value = yystack_[0].value.as< scala_parser::key > ().value;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< scala_parser::key > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1388 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 326 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::key > ().type = yystack_[0].value.as< scala_parser::key > ().type;
		yylhs.value.as< scala_parser::key > ().value = yystack_[0].value.as< scala_parser::key > ().value;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< scala_parser::key > ().description);
		std::swap(yylhs.value.as< scala_parser::key > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1400 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 335 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
			lexer.push_state(scale_lexer::in_string);
		}
#line 1408 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 337 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::key > ().type = scala_parser::key::numeric;
	        yylhs.value.as< scala_parser::key > ().value = yystack_[2].value.as< int32_t > ();
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1418 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 342 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
			lexer.push_state(scale_lexer::in_string);
		}
#line 1426 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 344 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::key > ().type = scala_parser::key::empty;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1435 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 351 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1445 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 356 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().description);
		std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1456 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 364 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	        yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[1].value.as< int32_t > ();
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1466 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 371 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[0].value.as< scala_parser::scala_value<double>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< scala_parser::scala_value<double>  > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1476 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 376 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[0].value.as< scala_parser::scala_value<double>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< scala_parser::scala_value<double>  > ().description);
		std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1487 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 384 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
	        yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[1].value.as< double > ();
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1497 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 392 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > ().clear(); }
#line 1503 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 393 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); }
#line 1509 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 394 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1515 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 395 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1521 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 402 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int32_t > () = yystack_[1].value.as< int32_t > (); }
#line 1527 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 405 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); lexer.push_state(scale_lexer::in_string);  }
#line 1533 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 406 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1539 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 413 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); lexer.pop_state(scale_lexer::in_string); }
#line 1545 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 419 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		errno = 0;
		long n = strtol (yystack_[0].value.as< std::string > ().c_str(), NULL, 10);
		if (! (0x80000000l+n >= 0 && n <= 0x7fFFffFFl && errno != ERANGE))
		lexer.error (yystack_[0].location, _mut("integer is out of range"));
		yylhs.value.as< int32_t > () = n;
		}
#line 1557 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 427 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int32_t > () = yystack_[0].value.as< int32_t > (); }
#line 1563 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 428 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< int32_t > () = yystack_[0].value.as< int32_t > (); }
#line 1569 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 431 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    {
		errno = 0;
                std::string tmp;
                tmp.reserve(yystack_[0].value.as< std::string > ().length());
                for (std::string::iterator i = yystack_[0].value.as< std::string > ().begin();
		    i != yystack_[0].value.as< std::string > ().end();
		    ++i) {
			switch (*i) {
			case ' ':
		        case '\t':
                            break;
                        default:
                              tmp += *i;

		        }
		}
		double value = strtod(tmp.c_str(), NULL);
		if (! (errno != ERANGE))
		lexer.error (yystack_[0].location, _mut("float is out of range"));
		yylhs.value.as< double > () = value;
		}
#line 1595 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 453 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< double > () = yystack_[0].value.as< double > (); }
#line 1601 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 454 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { yylhs.value.as< double > () = yystack_[0].value.as< double > (); }
#line 1607 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 457 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1613 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 458 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1619 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 461 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1625 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;

  case 75:
#line 462 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:859
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[1].value.as< std::string > (); }
#line 1631 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
    break;


#line 1635 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  scale_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  scale_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char scale_parser::yypact_ninf_ = -29;

  const signed char scale_parser::yytable_ninf_ = -1;

  const short int
  scale_parser::yypact_[] =
  {
      30,   -19,   -29,    43,   -29,   -29,   -29,   -29,   121,   -19,
     -29,   -29,   -29,   128,   111,   -29,    25,    37,   -29,   -29,
     -29,   -29,   126,   -29,   -29,    37,    97,   -29,    53,   -29,
     -29,   132,    41,   -29,   128,   128,   -29,    37,   145,   -29,
     -29,   117,   -29,   -29,   -29,   -29,    54,   -29,    31,   -29,
     -29,   -29,   -29,   -29,   -29,   109,   -29,   -29,   -29,   -29,
     -29,   103,   -29,   -29,   -29,    89,   -29,   -29,   -29,   -29,
     -29,   -29,   128,   -29,   -29,    37,    37,   -29,   -29,   -29,
     -19,   -29,   -29,   -29,   128,   -29,   -29,   152,   -19,   128,
     -29,   -29,    22,    17,   -29,   -29,   -29,   -29,    17,   128,
     -29,    37,    56,    37,    37,   -29,   -29,   -29,   -29,   -29
  };

  const unsigned char
  scale_parser::yydefact_[] =
  {
       0,    15,    11,     0,    30,     2,    26,     8,     6,    16,
      28,     3,    13,     0,     4,     1,     0,     0,    74,    69,
      66,    73,     0,    27,    32,     0,     0,    67,     0,    70,
      39,     0,     0,    29,     0,     0,    48,     0,     0,    46,
      47,     0,    14,    40,    44,    42,     0,    61,     0,    31,
      64,    63,     9,    54,    56,     0,    33,    34,    36,    37,
      38,     0,    58,    35,    60,     0,    72,    68,    71,     7,
      75,    49,     0,    50,    41,     0,     0,     5,    62,    65,
      17,    55,    57,    59,     0,    45,    43,     0,    18,     0,
      10,    19,     0,     0,    24,    22,    20,    21,     0,     0,
      51,     0,     0,     0,     0,    52,    12,    53,    25,    23
  };

  const signed char
  scale_parser::yypgoto_[] =
  {
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,     7,    -6,   -29,
     -29,    28,   -29,   -29,    34,   -29,   -29,   -29,   -28,    35,
     -29,   -15,   -24,   -29,   -29,   -29,   -16,     9,    85,    -3,
     -21,   -20,    -8,    77
  };

  const signed char
  scale_parser::yydefgoto_[] =
  {
      -1,     3,    11,     5,     6,    17,    80,    12,    13,    14,
       7,    87,    90,    91,   104,   103,     8,    34,    10,    16,
      23,    24,    25,    42,    43,    76,    75,    44,    35,    36,
      99,   100,    52,    64,    26,    48,    53,    54,    27,    37,
      29,    30,    38,    32
  };

  const unsigned char
  scale_parser::yytable_[] =
  {
      31,    57,    58,    33,    63,    28,    60,    72,     9,    55,
      68,    45,     4,    73,    31,    22,    33,    55,    61,    28,
      65,    41,    50,    59,    19,    49,    21,    47,    33,    55,
      47,    50,    79,     1,     2,    33,    78,    50,    45,    81,
      68,    69,    47,    15,    84,    81,    21,    70,     4,    81,
      56,    85,    86,    50,    77,    94,    89,    51,    47,    95,
      70,    93,    21,    19,    82,    66,    51,    55,    55,    71,
      82,   106,    51,   101,    82,    74,    96,   107,   101,   108,
     109,    68,    33,   105,    92,   102,    62,    88,    51,    50,
     102,    46,    33,    55,    47,    55,    55,    50,    66,     0,
      98,    97,    47,    50,    19,    20,    21,     0,    47,    50,
      19,    20,    66,     0,    47,     0,    67,    18,    66,    20,
      21,     0,    83,    67,    51,    20,    21,    18,    19,    20,
      21,     0,    51,    19,    20,    21,    20,    21,    51,    19,
      20,    66,     4,     0,    51,     0,    67,     0,     4,    39,
      40,     0,     4,    20,    66,    39,    40,     4,     0,     4,
      20,    21
  };

  const signed char
  scale_parser::yycheck_[] =
  {
       8,    25,    26,     9,    28,     8,    26,    35,     1,    17,
      31,    14,    31,    37,    22,     8,    22,    25,    26,    22,
      28,    14,     0,    26,     7,    16,     9,     5,    34,    37,
       5,     0,    48,     3,     4,    41,     5,     0,    41,    55,
      61,     0,     5,     0,    72,    61,     9,     6,    31,    65,
      22,    75,    76,     0,     0,    33,    84,    35,     5,    37,
       6,    89,     9,     7,    55,     9,    35,    75,    76,    34,
      61,    99,    35,    93,    65,    41,    92,   101,    98,   103,
     104,   102,    88,    98,    87,    93,    33,    80,    35,     0,
      98,    14,    98,   101,     5,   103,   104,     0,     9,    -1,
      93,    92,     5,     0,     7,     8,     9,    -1,     5,     0,
       7,     8,     9,    -1,     5,    -1,    31,     6,     9,     8,
       9,    -1,    33,    38,    35,     8,     9,     6,     7,     8,
       9,    -1,    35,     7,     8,     9,     8,     9,    35,     7,
       8,     9,    31,    -1,    35,    -1,    61,    -1,    31,    38,
      39,    -1,    31,     8,     9,    38,    39,    31,    -1,    31,
       8,     9
  };

  const unsigned char
  scale_parser::yystos_[] =
  {
       0,     3,     4,    41,    31,    43,    44,    50,    56,    57,
      58,    42,    47,    48,    49,     0,    59,    45,     6,     7,
       8,     9,    57,    60,    61,    62,    74,    78,    79,    80,
      81,    82,    83,    58,    57,    68,    69,    79,    82,    38,
      39,    57,    63,    64,    67,    79,    83,     5,    75,    77,
       0,    35,    72,    76,    77,    82,    61,    72,    72,    79,
      81,    82,    33,    72,    73,    82,     9,    78,    80,     0,
       6,    69,    68,    72,    64,    66,    65,     0,     5,    76,
      46,    76,    77,    33,    68,    72,    72,    51,    57,    68,
      52,    53,    79,    68,    33,    37,    76,    77,    57,    70,
      71,    81,    82,    55,    54,    71,    68,    72,    72,    72
  };

  const unsigned char
  scale_parser::yyr1_[] =
  {
       0,    40,    41,    41,    42,    42,    43,    43,    45,    46,
      44,    48,    47,    49,    49,    50,    50,    51,    51,    52,
      53,    53,    54,    53,    55,    53,    56,    56,    57,    57,
      59,    58,    60,    60,    61,    61,    61,    62,    62,    62,
      63,    63,    65,    64,    66,    64,    67,    67,    68,    68,
      69,    70,    70,    71,    72,    72,    72,    72,    73,    73,
      74,    75,    75,    76,    76,    77,    78,    79,    79,    80,
      81,    81,    82,    82,    83,    83
  };

  const unsigned char
  scale_parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     3,     1,     3,     0,     0,
       6,     0,     8,     1,     2,     0,     1,     0,     1,     1,
       2,     2,     0,     4,     0,     4,     1,     2,     1,     2,
       0,     3,     1,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     0,     3,     0,     3,     1,     1,     1,     2,
       2,     1,     2,     2,     1,     2,     1,     2,     1,     2,
       2,     1,     2,     1,     1,     2,     1,     1,     2,     1,
       1,     2,     2,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const scale_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined",
  "\"Start token of a .scl file\"", "\"Start token of a .kbm file\"",
  "\"string token\"", "\"text after the last interval\"",
  "\"floating point number\"", "\"integer number\"", "\"white space\"",
  "\"comment\"", "\"single comment line\"",
  "\"integer (with leadig white space)\"", "\"integer\"", "\"integer /\"",
  "\"double (with leadig white space)\"", "\"double\"", "\"whitespace\"",
  "\"character string with newline\"",
  "\"(non)empty character string with newline\"",
  "\"one of several tokens that can be in a string\"", "\"interval\"",
  "\"bare interval\"", "\"bare interval with description\"",
  "\"scala int value\"", "\"scala int value without comment\"",
  "\"scala double value\"", "\"scala double value without comment\"",
  "\"key\"", "\"key without comment\"",
  "\"The whole text after the file end\"", "'!'", "COMMENT_SIGN", "'/'",
  "SLASH", "'\\n'", "NEWLINE", "'.'", "'x'", "'X'", "$accept",
  "scala_file", "kbmfile", "sclfile", "scl_data_start", "$@1", "$@2",
  "kbm_data_start", "$@3", "kbm_data", "start_comment", "count_comment",
  "interval_count", "integer_number", "$@4", "$@5", "scl_data", "comment",
  "comment_line", "$@6", "interval", "interval2", "interval1", "key",
  "key1", "$@7", "$@8", "x", "scala_int", "scala_int1", "scala_float",
  "scala_float1", "lazy_string", "ratio_sign", "ratio_start",
  "string_element", "string_end", "string", "nospace_integer", "integer",
  "nospace_float", "float", "space", "garbage", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  scale_parser::yyrline_[] =
  {
       0,   140,   140,   141,   144,   151,   157,   165,   171,   171,
     170,   186,   186,   215,   216,   230,   231,   232,   233,   235,
     237,   238,   239,   239,   244,   244,   251,   252,   261,   262,
     267,   267,   273,   279,   288,   293,   298,   305,   309,   313,
     320,   326,   335,   335,   342,   342,   349,   349,   351,   356,
     364,   371,   376,   384,   392,   393,   394,   395,   398,   399,
     402,   405,   406,   409,   410,   413,   419,   427,   428,   431,
     453,   454,   457,   458,   461,   462
  };

  // Print the state stack on the debug stream.
  void
  scale_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  scale_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 33 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:1167
} } // mutabor::scala_parser
#line 2111 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:1167
#line 466 "../../../mutabor-git/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:1168

/// \		todo check whether this function is necessary for any system but windows

       /*
 void
yy::calcxx_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
       */

/*
 * \}
 */

namespace mutabor {
	namespace scala_parser {
		inline void scale_parser::error(location const& l, const std::string & s) {
			lexer.error(l,s.c_str());
		}
	}
}
