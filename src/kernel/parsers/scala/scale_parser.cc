// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

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

#line 37 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "../../mutabor/src/kernel/parsers/scala/scale_parser.hh"

// User implementation prologue.

#line 51 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:407
// Unqualified %code blocks.
#line 61 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:408

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

#line 76 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:408


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
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 33 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:474
namespace mutabor { namespace scala_parser {
#line 162 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:474

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
    : state (empty)
  {}

  inline
  scale_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  scale_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  scale_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  scale_parser::symbol_number_type
  scale_parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
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
      case 75: // nospace_float
      case 76: // float
        value.move< double > (that.value);
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 69: // ratio_start
      case 73: // nospace_integer
      case 74: // integer
        value.move< int32_t > (that.value);
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 58: // interval
      case 59: // interval2
      case 60: // interval1
        value.move< scala_parser::interval > (that.value);
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 61: // key
      case 62: // key1
        value.move< scala_parser::key > (that.value);
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 65: // scala_float
      case 66: // scala_float1
        value.move< scala_parser::scala_value<double>  > (that.value);
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 63: // scala_int
      case 64: // scala_int1
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
      case 55: // comment
      case 56: // comment_line
      case 67: // lazy_string
      case 70: // string_element
      case 72: // string
      case 77: // space
      case 78: // garbage
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty;
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
      case 75: // nospace_float
      case 76: // float
        value.copy< double > (that.value);
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 69: // ratio_start
      case 73: // nospace_integer
      case 74: // integer
        value.copy< int32_t > (that.value);
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 58: // interval
      case 59: // interval2
      case 60: // interval1
        value.copy< scala_parser::interval > (that.value);
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 61: // key
      case 62: // key1
        value.copy< scala_parser::key > (that.value);
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 65: // scala_float
      case 66: // scala_float1
        value.copy< scala_parser::scala_value<double>  > (that.value);
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 63: // scala_int
      case 64: // scala_int1
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
      case 55: // comment
      case 56: // comment_line
      case 67: // lazy_string
      case 70: // string_element
      case 72: // string
      case 77: // space
      case 78: // garbage
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
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 5: // "string token"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 451 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 6: // "text after the last interval"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 458 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 7: // "floating point number"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 465 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 8: // "integer number"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 472 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 9: // "white space"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 479 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 10: // "comment"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 486 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 11: // "single comment line"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 493 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 12: // "integer (with leadig white space)"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 500 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 13: // "integer"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 507 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 14: // "integer /"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 514 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 15: // "double (with leadig white space)"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 521 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 16: // "double"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 528 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 17: // "whitespace"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 535 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 18: // "character string with newline"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 542 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 19: // "(non)empty character string with newline"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 549 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 20: // "one of several tokens that can be in a string"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 556 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 21: // "interval"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 563 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 22: // "bare interval"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 570 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 23: // "bare interval with description"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 577 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 24: // "scala int value"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 584 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 25: // "scala int value without comment"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 591 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 26: // "scala double value"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 598 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 27: // "scala double value without comment"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 605 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 28: // "key"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 612 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 29: // "key without comment"

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 619 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 55: // comment

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 626 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 56: // comment_line

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 633 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 58: // interval

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 640 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 59: // interval2

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 647 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 60: // interval1

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 654 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 61: // key

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 661 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 62: // key1

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::key > (); }
#line 668 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 63: // scala_int

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 675 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 64: // scala_int1

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<int32_t>  > (); }
#line 682 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 65: // scala_float

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 689 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 66: // scala_float1

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::scala_value<double>  > (); }
#line 696 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 67: // lazy_string

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 703 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 69: // ratio_start

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 710 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 70: // string_element

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 717 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 72: // string

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 724 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 73: // nospace_integer

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 731 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 74: // integer

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 738 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 75: // nospace_float

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 745 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 76: // float

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 752 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 77: // space

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 759 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 78: // garbage

#line 128 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 766 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
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
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

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
    #line 54 "/home/tschlemmer/Entwicklung/mutabor-build/debug/../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:725
{
	// intial location
	yyla.location.begin.filename = yyla.location.end.filename = &lexer.get_filename();
}

#line 888 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:725

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
    if (yyempty)
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
        yyempty = false;
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

    // Discard the token being shifted.
    yyempty = true;

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
      case 75: // nospace_float
      case 76: // float
        yylhs.value.build< double > ();
        break;

      case 12: // "integer (with leadig white space)"
      case 13: // "integer"
      case 14: // "integer /"
      case 69: // ratio_start
      case 73: // nospace_integer
      case 74: // integer
        yylhs.value.build< int32_t > ();
        break;

      case 21: // "interval"
      case 22: // "bare interval"
      case 23: // "bare interval with description"
      case 58: // interval
      case 59: // interval2
      case 60: // interval1
        yylhs.value.build< scala_parser::interval > ();
        break;

      case 28: // "key"
      case 29: // "key without comment"
      case 61: // key
      case 62: // key1
        yylhs.value.build< scala_parser::key > ();
        break;

      case 26: // "scala double value"
      case 27: // "scala double value without comment"
      case 65: // scala_float
      case 66: // scala_float1
        yylhs.value.build< scala_parser::scala_value<double>  > ();
        break;

      case 24: // "scala int value"
      case 25: // "scala int value without comment"
      case 63: // scala_int
      case 64: // scala_int1
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
      case 55: // comment
      case 56: // comment_line
      case 67: // lazy_string
      case 70: // string_element
      case 72: // string
      case 77: // space
      case 78: // garbage
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
#line 145 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
                   if (result.count != keys.keys.size()) {
			   error(yystack_[0].location,_mut("Too few keys have been provided."));
                           YYERROR;
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
#line 1075 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 5:
#line 152 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { lexer.pop_state(scale_lexer::in_garbage); }
#line 1081 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 6:
#line 156 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
                   if (result.count != result.intervals.size()) {
			   error(yystack_[0].location,_mut("Too few intervals have been provided."));
                           YYERROR;
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
#line 1093 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 7:
#line 163 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { lexer.pop_state(scale_lexer::in_garbage); }
#line 1099 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 8:
#line 166 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { lexer.push_state(scale_lexer::in_string); }
#line 1105 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 9:
#line 166 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	                std::swap(result.name,yystack_[0].value.as< std::string > ());
		        lexer.push_state(scale_lexer::in_integer);
		}
#line 1114 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 10:
#line 172 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		if (!result.count) {  lexer.push_state(scale_lexer::in_garbage); }
		else {
			result.intervals.reserve(result.count);
                        lexer.push_state(scale_lexer::in_interval);
		}
		}
#line 1126 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 11:
#line 181 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
			lexer.push_state(scale_lexer::in_integer);
                }
#line 1134 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 12:
#line 191 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
			lexer.pop_state(scale_lexer::in_integer);
			std::swap(keys.count,yystack_[6].value.as< scala_parser::scala_value<int32_t>  > ());
		        std::swap(keys.first_key,yystack_[5].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.last_key,yystack_[4].value.as< scala_parser::scala_value<int32_t>  > ());
		        std::swap(keys.reference,yystack_[3].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.anchor,yystack_[2].value.as< scala_parser::scala_value<int32_t>  > ());
                        std::swap(keys.reference_frequency,yystack_[1].value.as< scala_parser::scala_value<double>  > ());
                        std::swap(keys.repetition_interval,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ());
			if (!keys.count.value) {  lexer.push_state(scale_lexer::in_garbage); }
 		        else {
			       keys.keys.reserve(keys.count.value);
		               lexer.push_state(scale_lexer::in_key);
		       }
		}
#line 1154 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 14:
#line 209 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        keys.keys.push_back(yystack_[0].value.as< scala_parser::key > ());
	        if (keys.count == keys.keys.size()) {
			lexer.pop_state(scale_lexer::in_key);
			lexer.push_state(scale_lexer::in_garbage);
		}
		}
#line 1166 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 16:
#line 221 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(result.comment1,yystack_[0].value.as< std::string > ()); }
#line 1172 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 18:
#line 223 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(result.comment2,yystack_[0].value.as< std::string > ()); }
#line 1178 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 19:
#line 225 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { lexer.pop_state(scale_lexer::in_integer); }
#line 1184 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 20:
#line 227 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { result.count = yystack_[1].value.as< int32_t > (); }
#line 1190 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 21:
#line 228 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { result.count = yystack_[1].value.as< int32_t > (); std::swap(result.count_comment,yystack_[0].value.as< std::string > ()); }
#line 1196 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 22:
#line 229 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {  lexer.push_state(scale_lexer::in_string); }
#line 1202 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 23:
#line 229 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		result.count = yystack_[3].value.as< int32_t > ();
		std::swap(result.count_comment,yystack_[0].value.as< std::string > ());
		error(yystack_[1].location,_mut("The interval count must be an integer number, not a float."));
		}
#line 1212 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 24:
#line 234 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {  lexer.push_state(scale_lexer::in_string); }
#line 1218 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 25:
#line 234 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		result.count = yystack_[3].value.as< int32_t > ();
		std::swap(result.count_comment,yystack_[0].value.as< std::string > ());
		error(yystack_[1].location,_mut("The interval count must be an integer number, not a ratio."));
		}
#line 1228 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 27:
#line 242 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        result.intervals.push_back(yystack_[0].value.as< scala_parser::interval > ());
	        if (result.count == result.intervals.size()) {
			lexer.pop_state(scale_lexer::in_interval);
			lexer.push_state(scale_lexer::in_garbage);
		}
		}
#line 1240 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 28:
#line 251 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1246 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 29:
#line 252 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
 	        std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ());
		yylhs.value.as< std::string > () += "\n" + yystack_[0].value.as< std::string > ();
		}
#line 1255 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 30:
#line 257 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { lexer.push_state(scale_lexer::in_string); }
#line 1261 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 31:
#line 257 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
			std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ());
		        lexer.pop_state(scale_lexer::in_string);
		}
#line 1270 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 32:
#line 263 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< scala_parser::interval > ().description);
		lexer.pop_state(scale_lexer::in_string);
			}
#line 1281 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 33:
#line 269 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< scala_parser::interval > ().description);
		std::swap(yylhs.value.as< scala_parser::interval > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
			}
#line 1293 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 34:
#line 278 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[1].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[1].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1303 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 35:
#line 283 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > ());
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1313 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 36:
#line 288 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		lexer.error(yystack_[0].location, _mut("An incomplete ratio has been detected, and descriptions must not start with '/'."));
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > ());
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1323 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 37:
#line 295 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > (),yystack_[0].value.as< int32_t > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1332 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 38:
#line 299 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[1].value.as< int32_t > (),yystack_[0].value.as< double > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1341 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 39:
#line 303 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[0].value.as< double > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1350 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 40:
#line 310 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::key > ().type = yystack_[0].value.as< scala_parser::key > ().type;
		yylhs.value.as< scala_parser::key > ().value = yystack_[0].value.as< scala_parser::key > ().value;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< scala_parser::key > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1361 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 41:
#line 316 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::key > ().value = yystack_[0].value.as< scala_parser::key > ().value;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< scala_parser::key > ().description);
		std::swap(yylhs.value.as< scala_parser::key > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1372 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 42:
#line 324 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        yylhs.value.as< scala_parser::key > ().value = yystack_[1].value.as< int32_t > ();
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1382 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 43:
#line 329 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::key > ().type = scala_parser::key::empty;
                std::swap(yylhs.value.as< scala_parser::key > ().description,yystack_[0].value.as< std::string > ());
		}
#line 1391 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 44:
#line 335 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1401 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 45:
#line 340 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< scala_parser::scala_value<int32_t>  > ().description);
		std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1412 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 46:
#line 348 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        yylhs.value.as< scala_parser::scala_value<int32_t>  > ().value = yystack_[1].value.as< int32_t > ();
                std::swap(yylhs.value.as< scala_parser::scala_value<int32_t>  > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1422 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 47:
#line 355 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[0].value.as< scala_parser::scala_value<double>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< scala_parser::scala_value<double>  > ().description);
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1432 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 48:
#line 360 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[0].value.as< scala_parser::scala_value<double>  > ().value;
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< scala_parser::scala_value<double>  > ().description);
		std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().comment,yystack_[1].value.as< std::string > ());
		lexer.pop_state(scale_lexer::in_string);
		}
#line 1443 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 49:
#line 368 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        yylhs.value.as< scala_parser::scala_value<double>  > ().value = yystack_[1].value.as< double > ();
                std::swap(yylhs.value.as< scala_parser::scala_value<double>  > ().description,yystack_[0].value.as< std::string > ());
                lexer.push_state(scale_lexer::in_string);
		}
#line 1453 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 50:
#line 376 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > ().clear(); }
#line 1459 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 51:
#line 377 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); }
#line 1465 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 52:
#line 378 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1471 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 53:
#line 379 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1477 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 56:
#line 386 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< int32_t > () = yystack_[1].value.as< int32_t > (); }
#line 1483 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 57:
#line 389 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); lexer.push_state(scale_lexer::in_string);  }
#line 1489 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 58:
#line 390 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1495 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 61:
#line 397 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); lexer.pop_state(scale_lexer::in_string); }
#line 1501 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 62:
#line 403 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		errno = 0;
		long n = strtol (yystack_[0].value.as< std::string > ().c_str(), NULL, 10);
		if (! (0x80000000l+n >= 0 && n <= 0x7fFFffFFl && errno != ERANGE))
		lexer.error (yystack_[0].location, _mut("integer is out of range"));
		yylhs.value.as< int32_t > () = n;
		}
#line 1513 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 63:
#line 411 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< int32_t > () = yystack_[0].value.as< int32_t > (); }
#line 1519 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 64:
#line 412 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< int32_t > () = yystack_[0].value.as< int32_t > (); }
#line 1525 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 65:
#line 415 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
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
#line 1551 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 66:
#line 437 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< double > () = yystack_[0].value.as< double > (); }
#line 1557 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 67:
#line 438 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< double > () = yystack_[0].value.as< double > (); }
#line 1563 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 68:
#line 441 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1569 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 69:
#line 442 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1575 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 70:
#line 445 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(result.garbage,yystack_[0].value.as< std::string > ()); }
#line 1581 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 71:
#line 446 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { result.garbage += yystack_[1].value.as< std::string > (); }
#line 1587 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;


#line 1591 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
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
    if (!yyempty)
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
        if (!yyempty)
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
  scale_parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
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
       - The only way there can be no lookahead present (in yytoken) is
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
    if (yytoken != yyempty_)
      {
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


  const signed char scale_parser::yypact_ninf_ = -53;

  const signed char scale_parser::yytable_ninf_ = -1;

  const short int
  scale_parser::yypact_[] =
  {
       0,    -6,   -53,     8,   -53,   -53,   -53,   -53,   132,    -6,
     -53,   -53,   -53,   141,    90,   -53,    22,    76,   -53,   -53,
     -53,   -53,   -53,   137,   -53,   -53,    76,   108,   -53,   124,
     -53,   -53,   144,    11,   -53,   141,   141,   -53,    76,     4,
     -53,    76,    17,   -53,   -53,    76,    62,   -53,    58,   -53,
     -53,   -53,   -53,   -53,   -53,   126,   -53,   -53,   -53,   -53,
     -53,   114,   -53,   -53,   -53,   125,   -53,   -53,   -53,   -53,
     -53,   -53,   141,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
      -6,   -53,   -53,   -53,   141,    40,    -6,   141,   -53,   -53,
      69,    52,   -53,   -53,   -53,   -53,    52,   141,   -53,    76,
     102,    76,    76,   -53,   -53,   -53,   -53,   -53
  };

  const unsigned char
  scale_parser::yydefact_[] =
  {
       0,    15,    11,     0,    30,     2,    26,     8,     0,    16,
      28,     3,    13,     0,     0,     1,     0,     0,     6,    70,
      65,    62,    69,     0,    27,    32,     0,     0,    63,     0,
      66,    39,     0,     0,    29,     0,     0,    44,     0,     0,
       4,     0,     0,    14,    40,     0,     0,    57,     0,    31,
      60,    59,     9,    50,    52,     0,    33,    34,    36,    37,
      38,     0,    54,    35,    56,     0,    68,    64,    67,     7,
      71,    45,     0,    46,    43,    41,    42,     5,    58,    61,
      17,    51,    53,    55,     0,     0,    18,     0,    10,    19,
       0,     0,    24,    22,    20,    21,     0,     0,    47,     0,
       0,     0,     0,    48,    12,    49,    25,    23
  };

  const signed char
  scale_parser::yypgoto_[] =
  {
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,     6,    -7,   -53,
     -53,    -1,   -53,   -53,    -2,   -31,     1,   -53,   -52,     5,
     -53,   -53,   -53,    12,   -10,   104,    15,   -22,   -26,    -8,
      38
  };

  const signed char
  scale_parser::yydefgoto_[] =
  {
      -1,     3,    11,     5,     6,    17,    80,    12,    13,    14,
       7,    85,    88,    89,   102,   101,     8,    35,    10,    16,
      24,    25,    26,    43,    44,    36,    37,    97,    98,    52,
      64,    27,    48,    53,    54,    28,    38,    30,    31,    39,
      33
  };

  const unsigned char
  scale_parser::yytable_[] =
  {
      32,    60,    34,     1,     2,    72,    49,     9,    15,    55,
      68,    69,    21,    66,    23,    32,    34,    70,    55,    61,
      42,    65,    56,    29,     4,    21,    22,    47,    34,    45,
      55,    57,    58,    55,    63,    34,    71,    55,    29,    68,
      75,    84,    59,    73,   103,    82,    74,     4,    21,    22,
      76,    82,    46,    87,    41,    82,    91,    45,    50,    20,
      79,    22,    77,    78,     0,    99,   104,    81,    70,    50,
      99,     0,     0,    81,    47,     0,    50,    81,    68,    34,
      95,    47,     4,   100,     0,    22,    86,     0,   100,    34,
      40,    55,    51,    55,    55,     0,    19,    96,    21,    22,
      90,    92,    94,    51,   105,    93,   106,   107,    50,    20,
      51,    66,     0,    47,    50,    20,    21,    22,     0,    47,
       4,    20,    21,    66,    50,    50,    50,    41,     0,    47,
      47,    47,    18,    22,    66,    66,    67,     0,    19,    20,
      21,    22,    51,    67,    20,    21,    22,     0,    51,    21,
      22,    20,    21,    66,     0,     0,    62,    83,    51,    51,
      51,     0,     4,     0,     0,    67,     0,     4,     0,     0,
       0,     4
  };

  const signed char
  scale_parser::yycheck_[] =
  {
       8,    27,     9,     3,     4,    36,    16,     1,     0,    17,
      32,     0,     8,     9,     8,    23,    23,     6,    26,    27,
      14,    29,    23,     8,    30,     8,     9,     5,    35,    14,
      38,    26,    27,    41,    29,    42,    35,    45,    23,    61,
      42,    72,    27,    38,    96,    55,    41,    30,     8,     9,
      45,    61,    14,    84,    37,    65,    87,    42,     0,     7,
      48,     9,     0,     5,    -1,    91,    97,    55,     6,     0,
      96,    -1,    -1,    61,     5,    -1,     0,    65,   100,    86,
      90,     5,    30,    91,    -1,     9,    80,    -1,    96,    96,
       0,    99,    34,   101,   102,    -1,     6,    91,     8,     9,
      85,    32,    90,    34,    99,    36,   101,   102,     0,     7,
      34,     9,    -1,     5,     0,     7,     8,     9,    -1,     5,
      30,     7,     8,     9,     0,     0,     0,    37,    -1,     5,
       5,     5,     0,     9,     9,     9,    32,    -1,     6,     7,
       8,     9,    34,    39,     7,     8,     9,    -1,    34,     8,
       9,     7,     8,     9,    -1,    -1,    32,    32,    34,    34,
      34,    -1,    30,    -1,    -1,    61,    -1,    30,    -1,    -1,
      -1,    30
  };

  const unsigned char
  scale_parser::yystos_[] =
  {
       0,     3,     4,    39,    30,    41,    42,    48,    54,    55,
      56,    40,    45,    46,    47,     0,    57,    43,     0,     6,
       7,     8,     9,    55,    58,    59,    60,    69,    73,    74,
      75,    76,    77,    78,    56,    55,    63,    64,    74,    77,
       0,    37,    55,    61,    62,    74,    78,     5,    70,    72,
       0,    34,    67,    71,    72,    77,    59,    67,    67,    74,
      76,    77,    32,    67,    68,    77,     9,    73,    75,     0,
       6,    64,    63,    67,    67,    62,    67,     0,     5,    71,
      44,    71,    72,    32,    63,    49,    55,    63,    50,    51,
      74,    63,    32,    36,    71,    72,    55,    65,    66,    76,
      77,    53,    52,    66,    63,    67,    67,    67
  };

  const unsigned char
  scale_parser::yyr1_[] =
  {
       0,    38,    39,    39,    40,    40,    41,    41,    43,    44,
      42,    46,    45,    47,    47,    48,    48,    49,    49,    50,
      51,    51,    52,    51,    53,    51,    54,    54,    55,    55,
      57,    56,    58,    58,    59,    59,    59,    60,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    65,    65,    66,
      67,    67,    67,    67,    68,    68,    69,    70,    70,    71,
      71,    72,    73,    74,    74,    75,    76,    76,    77,    77,
      78,    78
  };

  const unsigned char
  scale_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     3,     2,     3,     0,     0,
       6,     0,     8,     1,     2,     0,     1,     0,     1,     1,
       2,     2,     0,     4,     0,     4,     1,     2,     1,     2,
       0,     3,     1,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     1,     2,     1,     2,     2,     1,     2,     1,
       1,     2,     1,     1,     2,     1,     1,     2,     2,     1,
       1,     2
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
  "\"key\"", "\"key without comment\"", "'!'", "COMMENT_SIGN", "'/'",
  "SLASH", "'\\n'", "NEWLINE", "'.'", "'x'", "$accept", "scala_file",
  "kbmfile", "sclfile", "scl_data_start", "$@1", "$@2", "kbm_data_start",
  "$@3", "kbm_data", "start_comment", "count_comment", "interval_count",
  "integer_number", "$@4", "$@5", "scl_data", "comment", "comment_line",
  "$@6", "interval", "interval2", "interval1", "key", "key1", "scala_int",
  "scala_int1", "scala_float", "scala_float1", "lazy_string", "ratio_sign",
  "ratio_start", "string_element", "string_end", "string",
  "nospace_integer", "integer", "nospace_float", "float", "space",
  "garbage", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  scale_parser::yyrline_[] =
  {
       0,   140,   140,   141,   144,   152,   155,   163,   166,   166,
     165,   181,   181,   208,   209,   220,   221,   222,   223,   225,
     227,   228,   229,   229,   234,   234,   241,   242,   251,   252,
     257,   257,   263,   269,   278,   283,   288,   295,   299,   303,
     310,   316,   324,   329,   335,   340,   348,   355,   360,   368,
     376,   377,   378,   379,   382,   383,   386,   389,   390,   393,
     394,   397,   403,   411,   412,   415,   437,   438,   441,   442,
     445,   446
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


#line 33 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:1155
} } // mutabor::scala_parser
#line 2068 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:1155
#line 449 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:1156

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
