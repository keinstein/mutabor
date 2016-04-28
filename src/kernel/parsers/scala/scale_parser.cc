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
#line 60 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:408

#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scale_lexer.h"

#ifdef _
#undef _
#endif
#define _ _mut

// fix the interface to the scanner
#ifdef yylex
#undef yylex
#endif
#define yylex(x,y) lexer.get_token()

#if 0
#ifdef DEBUG
#define YYDEBUG 1
#endif
#endif

#line 75 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:408


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
#line 161 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:474

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
  scale_parser::scale_parser (scale_lexer & lexer_yyarg, interval_pattern & result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      result (result_yyarg)
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
      case 16: // "double"
      case 53: // float
        value.move< double > (that.value);
        break;

      case 15: // "integer"
      case 52: // integer
        value.move< int32_t > (that.value);
        break;

      case 24: // "interval"
      case 25: // "bare interval"
      case 26: // "bare interval with description"
      case 27: // "interval with leading space and description"
      case 41: // interval
      case 42: // interval3
      case 43: // interval2
      case 44: // interval1
        value.move< scala_parser::interval > (that.value);
        break;

      case 9: // "string token"
      case 10: // "floating point number"
      case 11: // "integer number"
      case 12: // "white space token"
      case 13: // "comment"
      case 14: // "single comment line"
      case 17: // "single space"
      case 18: // "whitespace"
      case 19: // "description"
      case 20: // "first element of description"
      case 21: // "character string with newline"
      case 22: // "one of several tokens that can be in a string"
      case 23: // "character string"
      case 39: // comment
      case 40: // comment1
      case 46: // name
      case 47: // name_start
      case 48: // string_element
      case 49: // string1
      case 51: // string
      case 54: // single_space
      case 55: // space
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
      case 16: // "double"
      case 53: // float
        value.copy< double > (that.value);
        break;

      case 15: // "integer"
      case 52: // integer
        value.copy< int32_t > (that.value);
        break;

      case 24: // "interval"
      case 25: // "bare interval"
      case 26: // "bare interval with description"
      case 27: // "interval with leading space and description"
      case 41: // interval
      case 42: // interval3
      case 43: // interval2
      case 44: // interval1
        value.copy< scala_parser::interval > (that.value);
        break;

      case 9: // "string token"
      case 10: // "floating point number"
      case 11: // "integer number"
      case 12: // "white space token"
      case 13: // "comment"
      case 14: // "single comment line"
      case 17: // "single space"
      case 18: // "whitespace"
      case 19: // "description"
      case 20: // "first element of description"
      case 21: // "character string with newline"
      case 22: // "one of several tokens that can be in a string"
      case 23: // "character string"
      case 39: // comment
      case 40: // comment1
      case 46: // name
      case 47: // name_start
      case 48: // string_element
      case 49: // string1
      case 51: // string
      case 54: // single_space
      case 55: // space
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
            case 9: // "string token"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 407 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 10: // "floating point number"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 414 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 11: // "integer number"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 421 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 12: // "white space token"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 428 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 13: // "comment"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 435 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 14: // "single comment line"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 442 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 15: // "integer"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 449 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 16: // "double"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 456 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 17: // "single space"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 463 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 18: // "whitespace"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 470 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 19: // "description"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 477 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 20: // "first element of description"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 484 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 21: // "character string with newline"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 491 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 22: // "one of several tokens that can be in a string"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 498 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 23: // "character string"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 505 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 24: // "interval"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 512 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 25: // "bare interval"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 519 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 26: // "bare interval with description"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 526 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 27: // "interval with leading space and description"

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 533 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 39: // comment

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 540 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 40: // comment1

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 547 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 41: // interval

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 554 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 42: // interval3

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 561 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 43: // interval2

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 568 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 44: // interval1

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< scala_parser::interval > (); }
#line 575 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 46: // name

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 582 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 47: // name_start

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 589 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 48: // string_element

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 596 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 49: // string1

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 603 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 51: // string

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 610 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 52: // integer

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< int32_t > (); }
#line 617 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 53: // float

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< double > (); }
#line 624 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 54: // single_space

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 631 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
        break;

      case 55: // space

#line 122 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:617
        { yyoutput << yysym.value.template as< std::string > (); }
#line 638 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:617
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
    #line 53 "/home/tschlemmer/Entwicklung/mutabor-build/debug/../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:725
{
	// intial location
	yyla.location.begin.filename = yyla.location.end.filename = &lexer.get_filename();
}

#line 760 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:725

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
            symbol_type yylookahead (yylex (lexer, result));
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
      case 16: // "double"
      case 53: // float
        yylhs.value.build< double > ();
        break;

      case 15: // "integer"
      case 52: // integer
        yylhs.value.build< int32_t > ();
        break;

      case 24: // "interval"
      case 25: // "bare interval"
      case 26: // "bare interval with description"
      case 27: // "interval with leading space and description"
      case 41: // interval
      case 42: // interval3
      case 43: // interval2
      case 44: // interval1
        yylhs.value.build< scala_parser::interval > ();
        break;

      case 9: // "string token"
      case 10: // "floating point number"
      case 11: // "integer number"
      case 12: // "white space token"
      case 13: // "comment"
      case 14: // "single comment line"
      case 17: // "single space"
      case 18: // "whitespace"
      case 19: // "description"
      case 20: // "first element of description"
      case 21: // "character string with newline"
      case 22: // "one of several tokens that can be in a string"
      case 23: // "character string"
      case 39: // comment
      case 40: // comment1
      case 46: // name
      case 47: // name_start
      case 48: // string_element
      case 49: // string1
      case 51: // string
      case 54: // single_space
      case 55: // space
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
  case 2:
#line 137 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { YYACCEPT; }
#line 920 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 3:
#line 139 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        std::swap(result.name,yystack_[2].value.as< std::string > ());
		result.count=yystack_[0].value.as< int32_t > ();
		if (!result.count) {  YYACCEPT; }
		result.intervals.reserve(result.count);
		}
#line 931 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 5:
#line 147 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(result.comment1,yystack_[0].value.as< std::string > ()); }
#line 937 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 7:
#line 149 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(result.comment2,yystack_[0].value.as< std::string > ()); }
#line 943 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 9:
#line 152 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
 	        std::swap(result.count_comment,yystack_[0].value.as< std::string > ());
                }
#line 951 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 10:
#line 155 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
	        result.intervals.push_back(yystack_[0].value.as< scala_parser::interval > ());
	        if (result.count == result.intervals.size()) { YYACCEPT; }
		}
#line 960 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 11:
#line 161 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 966 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 12:
#line 162 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
 	        std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ());
		yylhs.value.as< std::string > () += "\n" + yystack_[0].value.as< std::string > ();
		}
#line 975 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 13:
#line 167 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 981 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 14:
#line 168 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 987 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 15:
#line 171 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[1].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[1].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().comment,yystack_[1].value.as< scala_parser::interval > ().comment);
		}
#line 997 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 16:
#line 176 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[1].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[1].value.as< scala_parser::interval > ().data;
                std::swap(yylhs.value.as< scala_parser::interval > ().comment,yystack_[1].value.as< scala_parser::interval > ().comment);
                std::swap(yylhs.value.as< scala_parser::interval > ().description,yystack_[0].value.as< std::string > ()); }
#line 1007 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 17:
#line 183 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type; yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data; }
#line 1013 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 18:
#line 184 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type;
		yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data;
		std::swap(yylhs.value.as< scala_parser::interval > ().comment,yystack_[1].value.as< std::string > ());
		}
#line 1023 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 19:
#line 191 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type; yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data; }
#line 1029 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 20:
#line 192 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > ().type = yystack_[0].value.as< scala_parser::interval > ().type; yylhs.value.as< scala_parser::interval > ().data = yystack_[0].value.as< scala_parser::interval > ().data; }
#line 1035 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 21:
#line 195 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[0].value.as< int32_t > ()); }
#line 1041 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 22:
#line 196 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[2].value.as< int32_t > (),yystack_[0].value.as< int32_t > ()); }
#line 1047 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 23:
#line 197 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< scala_parser::interval > () = scala_parser::interval(yystack_[0].value.as< double > ()); }
#line 1053 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 27:
#line 206 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > ().clear(); }
#line 1059 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 28:
#line 207 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); }
#line 1065 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 29:
#line 208 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1071 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 30:
#line 211 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap (yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1077 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 31:
#line 212 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap (yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1083 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 32:
#line 213 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap (yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1089 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 33:
#line 214 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap (yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1095 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 34:
#line 215 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "/"; }
#line 1101 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 35:
#line 216 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "/"; }
#line 1107 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 36:
#line 219 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1113 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 37:
#line 220 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "!"; }
#line 1119 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 38:
#line 221 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "!"; }
#line 1125 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 39:
#line 225 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ());  }
#line 1131 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 40:
#line 226 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1137 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 44:
#line 234 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); }
#line 1143 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 45:
#line 237 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		errno = 0;
		long n = strtol (yystack_[0].value.as< std::string > ().c_str(), NULL, 10);
		if (! (0x80000000l+n >= 0 && n <= 0x7fFFffFFl && errno != ERANGE))
		lexer.error (yystack_[0].location, "integer is out of range");
		yylhs.value.as< int32_t > () = n;
		}
#line 1155 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 46:
#line 244 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< int32_t > () = yystack_[0].value.as< int32_t > (); }
#line 1161 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 47:
#line 247 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    {
		errno = 0;
		double value = strtod(yystack_[0].value.as< std::string > ().c_str(), NULL);
		if (! (errno != ERANGE))
		lexer.error (yystack_[0].location, "float is out of range");
		yylhs.value.as< double > () = value;
		}
#line 1173 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 48:
#line 254 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< double > () = yystack_[0].value.as< double > (); }
#line 1179 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 49:
#line 257 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = " "; }
#line 1185 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 50:
#line 258 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = " "; }
#line 1191 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 51:
#line 259 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "\t"; }
#line 1197 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 52:
#line 260 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { yylhs.value.as< std::string > () = "\t"; }
#line 1203 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 54:
#line 264 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[1].value.as< std::string > ()); yylhs.value.as< std::string > () += yystack_[0].value.as< std::string > (); }
#line 1209 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;

  case 55:
#line 265 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:847
    { std::swap(yylhs.value.as< std::string > (),yystack_[0].value.as< std::string > ()); }
#line 1215 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
    break;


#line 1219 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:847
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


  const signed char scale_parser::yypact_ninf_ = -41;

  const signed char scale_parser::yytable_ninf_ = -1;

  const short int
  scale_parser::yypact_[] =
  {
      51,    98,    98,     2,    60,    21,    70,    51,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,    60,   -41,   -41,    16,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,    51,    60,   -41,   -41,   -41,   -41,
     106,   -41,    60,   -41,   -41,   113,   -41,   142,    51,   -41,
     -41,   -41,   124,    51,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   124,   116,   -41,   113,   -41,   -41,   142,   -41,   124,
     -41,   -41,   -41,   -41
  };

  const unsigned char
  scale_parser::yydefact_[] =
  {
       4,     0,     0,     0,     0,     0,     0,     5,    11,    37,
      34,    52,    50,    30,    31,    32,    55,    38,    35,    49,
      51,    36,    39,     0,    14,    53,    33,    13,     1,    43,
      42,    41,     8,     9,     6,     0,    27,     2,    47,    45,
       0,    10,     0,    17,    19,    21,    23,     0,    12,    40,
      44,    54,     0,     7,    28,    29,    18,    15,    16,    25,
      24,     0,     0,    20,    21,    23,    53,     0,     3,     0,
      22,    26,    46,    48
  };

  const signed char
  scale_parser::yypgoto_[] =
  {
     -41,   -41,   -41,   -41,   -41,   -41,     6,   -41,   -41,   -41,
     -36,   -40,   -41,   -41,     4,   -13,   -41,     3,     1,    99,
     -32,   -25,    -6
  };

  const signed char
  scale_parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    52,     6,    48,     8,    41,    42,
      43,    44,    61,    34,    21,    22,    23,    32,    24,    45,
      46,    25,    26
  };

  const unsigned char
  scale_parser::yytable_[] =
  {
      47,    51,    28,    27,    56,    33,     7,    63,    36,    35,
      49,     0,    40,     0,     0,    65,     0,     0,     0,     0,
       0,    29,    66,    11,    12,    30,    50,    10,    11,    12,
      13,    14,    15,    16,    47,    73,    55,    51,    54,    62,
      53,    67,    66,    58,    66,    57,    69,    19,    20,     0,
      18,    31,    19,    20,     0,    69,     1,     0,    62,     0,
      29,    67,     0,    69,    30,     9,    10,    11,    12,    13,
      14,    15,    16,    37,     0,     1,     0,    11,    12,     2,
      38,    39,    16,     0,     0,     0,     0,     0,    17,    18,
      31,    19,    20,     0,     0,     0,     0,     0,     2,     0,
       0,    19,    20,     9,    10,    11,    12,    13,    14,    15,
      16,     1,     0,    11,    12,     0,    38,    39,    16,    59,
      11,    12,    71,    11,    12,    16,    17,    18,     0,    19,
      20,    11,    12,     0,     2,    39,    16,    19,    20,     0,
       0,     0,    60,     0,    19,    20,    64,    19,    20,    11,
      12,    68,    38,    39,    16,    19,    20,     0,     0,     0,
      70,     0,     0,     0,     0,     0,    72,     0,    72,     0,
       0,     0,     0,    19,    20
  };

  const signed char
  scale_parser::yycheck_[] =
  {
       6,    26,     0,     2,    40,     4,     0,    47,     5,     5,
      23,    -1,     6,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,     0,    47,     7,     8,     4,    23,     6,     7,     8,
       9,    10,    11,    12,    40,    67,    35,    62,    35,    45,
      34,    47,    67,    42,    69,    42,    52,    31,    32,    -1,
      29,    30,    31,    32,    -1,    61,     5,    -1,    64,    -1,
       0,    67,    -1,    69,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     3,    -1,     5,    -1,     7,     8,    28,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    31,    32,     5,     6,     7,     8,     9,    10,    11,
      12,     5,    -1,     7,     8,    -1,    10,    11,    12,     6,
       7,     8,     6,     7,     8,    12,    28,    29,    -1,    31,
      32,     7,     8,    -1,    28,    11,    12,    31,    32,    -1,
      -1,    -1,    29,    -1,    31,    32,    47,    31,    32,     7,
       8,    52,    10,    11,    12,    31,    32,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,    -1,
      -1,    -1,    -1,    31,    32
  };

  const unsigned char
  scale_parser::yystos_[] =
  {
       0,     5,    28,    34,    35,    36,    38,    39,    40,     5,
       6,     7,     8,     9,    10,    11,    12,    28,    29,    31,
      32,    47,    48,    49,    51,    54,    55,    51,     0,     0,
       4,    30,    50,    51,    46,    47,    50,     3,    10,    11,
      39,    41,    42,    43,    44,    52,    53,    55,    39,    48,
      50,    54,    37,    39,    50,    51,    43,    50,    51,     6,
      29,    45,    55,    44,    52,    53,    54,    55,    52,    55,
      52,     6,    52,    53
  };

  const unsigned char
  scale_parser::yyr1_[] =
  {
       0,    33,    34,    35,    36,    36,    37,    37,    38,    38,
      38,    39,    39,    40,    40,    41,    41,    42,    42,    43,
      43,    44,    44,    44,    45,    45,    45,    46,    46,    46,
      47,    47,    47,    47,    47,    47,    48,    48,    48,    49,
      49,    50,    50,    50,    51,    52,    52,    53,    53,    54,
      54,    54,    54,    55,    55,    55
  };

  const unsigned char
  scale_parser::yyr2_[] =
  {
       0,     2,     2,     4,     0,     1,     0,     1,     2,     2,
       2,     1,     2,     2,     2,     2,     2,     1,     2,     1,
       2,     1,     3,     1,     1,     1,     2,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     2,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const scale_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of interval list\"",
  "\"\\\\n\"", "\"!\"", "\"/\"", "\"->|\"", "\"' '\"", "\"string token\"",
  "\"floating point number\"", "\"integer number\"",
  "\"white space token\"", "\"comment\"", "\"single comment line\"",
  "\"integer\"", "\"double\"", "\"single space\"", "\"whitespace\"",
  "\"description\"", "\"first element of description\"",
  "\"character string with newline\"",
  "\"one of several tokens that can be in a string\"",
  "\"character string\"", "\"interval\"", "\"bare interval\"",
  "\"bare interval with description\"",
  "\"interval with leading space and description\"", "'!'", "'/'", "'\\n'",
  "' '", "'\\t'", "$accept", "sclfile", "scl_data_start", "start_comment",
  "count_comment", "scl_data", "comment", "comment1", "interval",
  "interval3", "interval2", "interval1", "slash", "name", "name_start",
  "string_element", "string1", "string_end", "string", "integer", "float",
  "single_space", "space", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  scale_parser::yyrline_[] =
  {
       0,   136,   136,   139,   146,   147,   148,   149,   151,   152,
     155,   161,   162,   167,   168,   171,   176,   183,   184,   191,
     192,   195,   196,   197,   200,   201,   202,   206,   207,   208,
     211,   212,   213,   214,   215,   216,   219,   220,   221,   225,
     226,   229,   230,   231,   234,   237,   244,   247,   254,   257,
     258,   259,   260,   263,   264,   265
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
#line 1670 "../../mutabor/src/kernel/parsers/scala/scale_parser.cc" // lalr1.cc:1155
#line 269 "../../mutabor/src/kernel/parsers/scala/scale_parser.yy" // lalr1.cc:1156

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
		void scale_parser::error(location const& l, const std::string & s) {
			std::cerr << l << std::endl << s << std::endl;
		}
	}
}
