%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int DP::Scanner::yylex( DP::Parser::semantic_type * const lval, DP::Parser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = DP::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="DP::Scanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"<" {
        return(token::TAG_BEGIN_START);
    }

">" {
        return(token::TAG_END);
    }

"</" {
        return(token::TAG_END_START);
    }

[ \t]+

[a-zA-Z ]+  {
               yylval->build<std::string>(yytext);
               return(token::SENTENCE);
            }

\n          {
               loc->lines();
               return(token::NEWLINE);
            }

.
        
%%


