#pragma once

#include <bitset>
#include <iostream>

#include "Utils.h"

namespace Day3
{
    inline uint8_t ItemIndex(char Item)
    {
        constexpr char UpperOffset = 'A' - 26;
        constexpr char LowerOffset = 'a';

        return static_cast<uint8_t>(Item <= 'Z' ? Item - UpperOffset : Item - LowerOffset);
    }

    inline uint8_t ItemPriority(char Item)
    {
        return ItemIndex(Item) + 1;
    }

    inline void Part1()
    {
        uint32_t SumPriorities = 0;

        ForEachFileLine("Inputs/day3.txt", [&SumPriorities](const std::string& Rucksack)
        {
            std::bitset<52> LeftCompartment;

            for (size_t i = 0; i < Rucksack.size() / 2; ++i)
            {
                LeftCompartment.set(ItemIndex(Rucksack[i]));
            }

            for (size_t i = Rucksack.size() / 2; i < Rucksack.size(); ++i)
            {
                if (LeftCompartment[ItemIndex(Rucksack[i])])
                {
                    SumPriorities += ItemPriority(Rucksack[i]);

                    //std::cout << "Found " << Rucksack[i] << " with score " << static_cast<uint16_t>(ItemPriority(Rucksack[i])) << std::endl;

                    return;
                }
            }
        });

        std::cout << "Part 1: " << SumPriorities << std::endl;
    }

    inline void Part2()
    {
        uint32_t SumPriorities = 0;

        int8_t BatchCounter = 0;

        std::bitset<52> FirstElf;
        std::bitset<52> CommonItems;

        ForEachFileLine("Inputs/day3.txt", [&SumPriorities, &BatchCounter, &FirstElf, &CommonItems](const std::string& Rucksack)
        {
            if (BatchCounter == 0)
            {
                for (char Item : Rucksack)
                {
                    FirstElf.set(ItemIndex(Item));
                }

                ++BatchCounter;
            }
            else if (BatchCounter == 1)
            {
                for (char Item : Rucksack)
                {
                    if (FirstElf[ItemIndex(Item)])
                    {
                        CommonItems.set(ItemIndex(Item));
                    }
                }

                ++BatchCounter;
            }
            else
            {
                for (char Item : Rucksack)
                {
                    if (CommonItems[ItemIndex(Item)])
                    {
                        SumPriorities += ItemPriority(Item);

                        //std::cout << "Found " << Item << " with score " << static_cast<uint16_t>(ItemPriority(Item)) << std::endl;

                        break;
                    }
                }

                BatchCounter = 0;

                FirstElf.reset();
                CommonItems.reset();
            }
        });

        if (BatchCounter != 0)
        {
            std::cout << "ERROR: number of elves is not a multiple of 3" << std::endl;
        }

        std::cout << "Part 2: " << SumPriorities << std::endl;
    }
}
