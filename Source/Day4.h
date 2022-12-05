#pragma once

#include <iostream>

#include "Utils.h"

namespace Day4
{
    struct Range
    {
        int Start;
        int End;

        Range()
            : Start(0), End(0)
        {}

        Range(int Start, int End)
            : Start(Start), End(End)
        {}

        bool FullyContains(const Range& Other) const
        {
            return this->Start <= Other.Start && this->End >= Other.End;
        }

        bool Overlaps(const Range& Other) const
        {
            return this->Start <= Other.End && this->End >= Other.Start;
        }
    };

    struct RangePair
    {
        Range First;
        Range Second;

        RangePair()
            : First(), Second()
        {}

        RangePair(Range First, Range Second)
            : First(First), Second(Second)
        {}

        RangePair(int FirstStart, int FirstEnd, int SecondStart, int SecondEnd)
            : First(FirstStart, FirstEnd), Second(SecondStart, SecondEnd)
        {}

        bool EitherFullyContainsOther() const
        {
            return this->First.FullyContains(this->Second) || this->Second.FullyContains(this->First);
        }

        bool AnyOverlap() const
        {
            return this->First.Overlaps(this->Second);
        }
    };

    RangePair RangePairFromString(const std::string& String)
    {
        StringSplitSingleResult PairSplit        = StringSplitSingle(String, ",");
        StringSplitSingleResult FirstRangeSplit  = StringSplitSingle(PairSplit.First, "-");
        StringSplitSingleResult SecondRangeSplit = StringSplitSingle(PairSplit.Second, "-");

        const int FirstStart  = std::stoi(std::string(FirstRangeSplit.First));
        const int FirstEnd    = std::stoi(std::string(FirstRangeSplit.Second));
        const int SecondStart = std::stoi(std::string(SecondRangeSplit.First));
        const int SecondEnd   = std::stoi(std::string(SecondRangeSplit.Second));

        return RangePair(FirstStart, FirstEnd, SecondStart, SecondEnd);
    }

    inline void Part1()
    {
        uint32_t FullyContainsCount = 0;

        ForEachFileLine("Inputs/day4.txt", [&FullyContainsCount](const std::string& Line)
        {
            if (RangePairFromString(Line).EitherFullyContainsOther())
            {
                ++FullyContainsCount;
            }
        });

        std::cout << "Part 1: " << FullyContainsCount << std::endl;
    }

    inline void Part2()
    {
        uint32_t OverlapCount = 0;

        ForEachFileLine("Inputs/day4.txt", [&OverlapCount](const std::string& Line)
        {
            if (RangePairFromString(Line).AnyOverlap())
            {
                ++OverlapCount;
            }

            /*
            if (RangePairFromString(Line).AnyOverlap())
            {
                std::cout << Line << " overlap" << std::endl;
            }
            else
            {
                std::cout << Line << " NO overlap" << std::endl;
            }
            */
        });

        std::cout << "Part 2: " << OverlapCount << std::endl;
    }
}
