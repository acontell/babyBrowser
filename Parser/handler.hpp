#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "scanner.hpp"
#include "parser.tab.hh"

namespace DP {

    class Handler {
    public:
        Handler() = default;
        virtual ~Handler();
        void parse(std::istream &iss);
        void addStartTag(const std::string &word);
        void addEndTag(const std::string &word);
        void addSentence(const std::string &word);
        void addNewline();
        std::ostream& print(std::ostream &stream);
    private:
        void parseHelper(std::istream &stream);
        std::size_t startTags = 0;
        std::size_t endTags = 0;
        std::size_t nParagraphs = 0;
        std::size_t lines = 0;
        std::string paragraphs = "";
        DP::Parser *parser = nullptr;
        DP::Scanner *scanner = nullptr;
    };

} /* end namespace DP */
#endif /* END __HANDLER_HPP__ */
