#ifndef __DPHANDLER_HPP__
#define __DPHANDLER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#include "scanner.hpp"
#include "parser.tab.hh"
#include "node.hpp"
#include <vector>

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
        std::vector<Node> getNodes();
        std::ostream& print(std::ostream &stream);
    private:
        void parseHelper(std::istream &stream);
        std::string nodesToString();
        std::size_t nodeIdx = 0;
        std::size_t endTags = 0;
        std::size_t lines = 0;
        std::vector<Node> nodes;
        DP::Parser *parser = nullptr;
        DP::Scanner *scanner = nullptr;
    };

} /* end namespace DP */
#endif /* END __HANDLER_HPP__ */
