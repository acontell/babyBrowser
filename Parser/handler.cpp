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
DP::Handler::addStartTag() {
    startTags++;
}

void
DP::Handler::addEndTag() {
    endTags++;
}

void
DP::Handler::addSentence(const std::string &word) {
    paragraphs += word;
    nParagraphs++;
}

void
DP::Handler::addNewline() {
    lines++;
}

std::ostream&
DP::Handler::print(std::ostream &stream) {
    stream << "Is it well-formed? " << ((startTags - endTags) == 0 ? "YES" : "NO") << "\n";
    stream << "Number of opening tags: " << startTags << "\n";
    stream << "Number of closing tags: " << endTags << "\n";
    stream << "Number of paragraphs: " << nParagraphs << "\n";
    stream << "Number of lines: " << lines << "\n";
    stream << "Ps content: " << paragraphs;
    return (stream);
}
