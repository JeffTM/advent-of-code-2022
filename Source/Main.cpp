#include <chrono>

#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"

int main()
{
    auto StartTime = std::chrono::steady_clock::now();

    Day1::Part1();
    Day1::Part2();
    Day2::Part1();
    Day2::Part2();
    Day3::Part1();
    Day3::Part2();
    Day4::Part1();
    Day4::Part2();
    Day5::Part1();
    Day5::Part2();
    Day6::Part1();
    Day6::Part2();

    auto EndTime = std::chrono::steady_clock::now();
    auto RunTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(EndTime - StartTime);

    std::cout << "Main runtime: " << RunTime << std::endl;

    return 0;
}
