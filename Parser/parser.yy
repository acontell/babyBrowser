%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {DP}
%define parser_class_name {Parser}

%code requires{
   namespace DP {
      class Handler;
      class Scanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { Scanner  &scanner  }
%parse-param { Handler  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "handler.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token               TAG_START
%token               TAG_END
%token <std::string> SENTENCE
%token               NEWLINE

%locations

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : TAG_START   { driver.addStartTag(); }
  | TAG_END     { driver.addEndTag(); }
  | SENTENCE    { driver.addSentence($1); }
  | NEWLINE     { driver.addNewline(); }
  ;

%%


void 
DP::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
