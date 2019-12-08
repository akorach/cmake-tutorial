// A simple program that computes the square root of a number
#include "MinimalistConfig.h"

#include "MathFunctions.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << argv[0] << " Version " << Minimalist_VERSION_MAJOR << "."
                  << Minimalist_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // calculate square root
    const double outputValue = MathFunctions::sqrt(inputValue);

    std::cout << "The square root of " << inputValue << " is " << outputValue
              << std::endl;
    return 0;
}
