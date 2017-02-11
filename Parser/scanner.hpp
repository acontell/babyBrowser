#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace DP {

    class Scanner : public yyFlexLexer {
    public:

        Scanner(std::istream *in) : yyFlexLexer(in) {
            loc = new DP::Parser::location_type();
        };

        virtual ~Scanner() {
            delete loc;
        };

        //get rid of override virtual function warning
        using FlexLexer::yylex;

        virtual
        int yylex(DP::Parser::semantic_type * const lval,
                DP::Parser::location_type *location);
        // YY_DECL defined in mc_lexer.l
        // Method body created by flex in mc_lexer.yy.cc

    private:
        /* yyval ptr */
        DP::Parser::semantic_type *yylval = nullptr;
        /* location ptr */
        DP::Parser::location_type *loc = nullptr;
    };

} /* end namespace DP */

#endif /* END __SCANNER_HPP__ */
