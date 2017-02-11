#include <cctype>
#include <fstream>
#include <cassert>

#include "handler.hpp"

DP::Handler::~Handler() {
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
}

void
DP::Handler::parse(std::istream &stream) {
    parseHelper(stream);
    return;
}

void
DP::Handler::parseHelper(std::istream &stream) {
    delete(scanner);
    scanner = new DP::Scanner(&stream);
    delete(parser);
    parser = new DP::Parser((*scanner), (*this));
    parser->parse();
    return;
}

void
DP::Handler::addStartTag(const std::string &word) {
    nodeIdx++;
    nodes.emplace_back(word);
}

void
DP::Handler::addEndTag(const std::string &word) {
    endTags++;
}

void
DP::Handler::addSentence(const std::string &word) {
    nodes.at(nodeIdx - 1).content = word;
}

void
DP::Handler::addNewline() {
    lines++;
}

std::vector<Node>
DP::Handler::getNodes() {
    return nodes;
}

std::string 
DP::Handler::nodesToString() {
    std::string aux = "";
    for (unsigned i = 0; i < nodes.size(); i++) {
        aux += nodes.at(i).tag + " " + nodes.at(i).content + "\n";
    }
    return aux;
}

std::ostream&
DP::Handler::print(std::ostream &stream) {
    stream << "Number of opening tags: " << nodeIdx << "\n";
    stream << "Number of closing tags: " << endTags << "\n";
    stream << "Number of lines: " << lines << "\n";
    stream << "Tags and content: " << "\n";
    stream << DP::Handler::nodesToString();
    return (stream);
}
