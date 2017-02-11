#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Parser/handler.hpp"

// Usage: pipe file with html to the executable file. cat myHtml | dp_browser
int
main(const int argc, const char **argv) {
    DP::Handler handler;
    handler.parse(std::cin);
    handler.print(std::cout) << "\n";
    return (EXIT_SUCCESS);
}
