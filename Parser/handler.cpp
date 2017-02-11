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
    if (!stream.good() && stream.eof()) {
        return;
    }
    //else
    parse_helper(stream);
    return;
}

void
DP::Handler::parse_helper(std::istream &stream) {

    delete(scanner);
    try {
        scanner = new DP::Scanner(&stream);
    } catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate scanner: (" <<
                ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }

    delete(parser);
    try {
        parser = new DP::Parser((*scanner) /* scanner */,
                (*this) /* driver */);
    } catch (std::bad_alloc &ba) {
        std::cerr << "Failed to allocate parser: (" <<
                ba.what() << "), exiting!!\n";
        exit(EXIT_FAILURE);
    }
    const int accept(0);
    if (parser->parse() != accept) {
        std::cerr << "Parse failed!!\n";
    }
    return;
}

void
DP::Handler::add_upper() {
    uppercase++;
    chars++;
    words++;
}

void
DP::Handler::add_lower() {
    lowercase++;
    chars++;
    words++;
}

void
DP::Handler::add_word(const std::string &word) {
    words++;
    chars += word.length();
    for (const char &c : word) {
        if (islower(c)) {
            lowercase++;
        } else if (isupper(c)) {
            uppercase++;
        }
    }
}

void
DP::Handler::add_newline() {
    lines++;
    chars++;
}

void
DP::Handler::add_char() {
    chars++;
}

std::ostream&
DP::Handler::print(std::ostream &stream) {
    stream << red << "Results: " << norm << "\n";
    stream << blue << "Uppercase: " << norm << uppercase << "\n";
    stream << blue << "Lowercase: " << norm << lowercase << "\n";
    stream << blue << "Lines: " << norm << lines << "\n";
    stream << blue << "Words: " << norm << words << "\n";
    stream << blue << "Characters: " << norm << chars << "\n";
    return (stream);
}
