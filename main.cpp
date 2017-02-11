#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Parser/mc_driver.hpp"

// Usage: pipe file with html to the executable file. cat myHtml | dp_browser
int
main(const int argc, const char **argv) {
    MC::MC_Driver driver;
    driver.parse(std::cin);
    driver.print(std::cout) << "\n";
    return (EXIT_SUCCESS);
}
