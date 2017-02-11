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

"<"[a-zA-Z]+">" {
               return(token::TAG_START);
            }

"</"[a-zA-Z]+">" {
               return(token::TAG_END);
             }

[ \t]+

[a-zA-Z ]+  {
               /**
                * Section 10.1.5.1 of the 3.0.2 Bison Manual says the 
                * following should work:
                * yylval.build( yytext );
                * but it doesn't.
                * ref: http://goo.gl/KLn0w2
                */
               yylval->build<std::string>(yytext);
               return(token::SENTENCE);
            }

\n          {
               // Update line number
               loc->lines();
               return(token::NEWLINE);
            }

.
        
%%


