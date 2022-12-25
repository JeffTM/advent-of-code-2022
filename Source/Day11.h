#pragma once

#include <algorithm>
#include <iostream>

#include "Utils.h"

namespace Day11
{
    enum class EOperation : uint8_t
    {
        Add = 0,
        Multiply,
        Square
    };

    class Monkey
    {
    public:
        Monkey(const std::vector<int64_t>& InItems, EOperation InOperation, int32_t InOperand, int32_t InTestDivisibleBy, uint32_t InTrueThrowTarget, uint32_t InFalseThrowTarget)
            : Items(InItems), Operation(InOperation), Operand(InOperand), TestDivisibleBy(InTestDivisibleBy), TrueThrowTarget(InTrueThrowTarget), FalseThrowTarget(InFalseThrowTarget), PostOperation(0)
        {}

        uint32_t GetThrowTarget(int64_t& Item) const
        {
            if (this->Operation == EOperation::Add)
            {
                Item += this->Operand;
            }
            else if (this->Operation == EOperation::Multiply)
            {
                Item *= this->Operand;
            }
            else
            {
                Item *= Item;
            }
            
            if (this->PostOperation <= 0)
            {
                Item /= 3;
            }
            else if (Item >= this->ModThreshold)
            {
                Item %= this->PostOperation;
            }

            return (Item % this->TestDivisibleBy == 0) ? this->TrueThrowTarget : this->FalseThrowTarget;
        }

        int32_t GetTestDivisibleBy() const
        {
            return this->TestDivisibleBy;
        }

        void SetPart2CommonMultiple(int64_t InCommonMultiple)
        {
            this->PostOperation = InCommonMultiple;
        }

        static constexpr int64_t ModThreshold = 2147483648; // 2^31

        std::vector<int64_t> Items;

    protected:
        EOperation Operation;
        int32_t Operand;

        int32_t TestDivisibleBy;
        uint32_t TrueThrowTarget;
        uint32_t FalseThrowTarget;

        // <= 0 means divide by 3 for part 1. Otherwise mod the answer by this number for part 2
        int64_t PostOperation;
    };

    inline void SetPart2CommonMultiple(std::vector<Monkey>& Monkeys)
    {
        int32_t CommonMultiple = 1;

        for (const Monkey& Monk : Monkeys)
        {
            CommonMultiple *= Monk.GetTestDivisibleBy();
        }

        for (Monkey& Monk : Monkeys)
        {
            Monk.SetPart2CommonMultiple(CommonMultiple);
        }
    }

    inline std::vector<Monkey> GetTestInput(bool bIsPart2)
    {
        std::vector<Monkey> Monkeys;

        Monkeys.reserve(4);
        Monkeys.push_back(Monkey({79, 98}, EOperation::Multiply, 19, 23, 2, 3));
        Monkeys.push_back(Monkey({54, 65, 75, 74}, EOperation::Add, 6, 19, 2, 0));
        Monkeys.push_back(Monkey({79, 60, 97}, EOperation::Square, 0, 13, 1, 3));
        Monkeys.push_back(Monkey({74}, EOperation::Add, 3, 17, 0, 1));

        if (bIsPart2)
        {
            SetPart2CommonMultiple(Monkeys);
        }

        return Monkeys;
    }

    inline std::vector<Monkey> GetInput(bool bIsPart2)
    {
        std::vector<Monkey> Monkeys;

        Monkeys.reserve(8);
        Monkeys.push_back(Monkey({64, 89, 65, 95}, EOperation::Multiply, 7, 3, 4, 1));
        Monkeys.push_back(Monkey({76, 66, 74, 87, 70, 56, 51, 66}, EOperation::Add, 5, 13, 7, 3));
        Monkeys.push_back(Monkey({91, 60, 63}, EOperation::Square, 0, 2, 6, 5));
        Monkeys.push_back(Monkey({92, 61, 79, 97, 79}, EOperation::Add, 6, 11, 2, 6));
        Monkeys.push_back(Monkey({93, 54}, EOperation::Multiply, 11, 5, 1, 7));
        Monkeys.push_back(Monkey({60, 79, 92, 69, 88, 82, 70}, EOperation::Add, 8, 17, 4, 0));
        Monkeys.push_back(Monkey({64, 57, 73, 89, 55, 53}, EOperation::Add, 1, 19, 0 ,5));
        Monkeys.push_back(Monkey({62}, EOperation::Add, 4, 7, 3, 2));

        if (bIsPart2)
        {
            SetPart2CommonMultiple(Monkeys);
        }

        return Monkeys;
    }

    inline uint64_t RunSimulation(bool bIsPart2, bool bUseTestInput = false)
    {
        std::vector<Monkey> Monkeys = bUseTestInput ? GetTestInput(bIsPart2) : GetInput(bIsPart2);

        const int32_t NumRounds = bIsPart2 ? 10000 : 20;

        std::vector<uint64_t> InspectionCounts(Monkeys.size());

        for (int32_t RoundCounter = 0; RoundCounter < NumRounds; ++RoundCounter)
        {
            for (std::size_t CurrentMonkeyIndex = 0; CurrentMonkeyIndex < Monkeys.size(); ++CurrentMonkeyIndex)
            {
                for (int64_t& CurrentItem : Monkeys[CurrentMonkeyIndex].Items)
                {
                    const uint32_t ThrowTarget = Monkeys[CurrentMonkeyIndex].GetThrowTarget(CurrentItem);
                    Monkeys[ThrowTarget].Items.push_back(CurrentItem);

                    ++InspectionCounts[CurrentMonkeyIndex];
                }

                Monkeys[CurrentMonkeyIndex].Items.clear();
            }
        }

        std::nth_element(InspectionCounts.begin(), InspectionCounts.begin() + 1, InspectionCounts.end(), std::greater());

        /*
        for (uint32_t Count : InspectionCounts)
        {
            std::cout << Count << ' ';
        }
        std::cout << std::endl;
        */

        return InspectionCounts[0] * InspectionCounts[1];
    }

    inline void Part1()
    {
        std::cout << "Part 1: " << RunSimulation(false) << std::endl;
    }

    inline void Part2()
    {
        std::cout << "Part 2: " << RunSimulation(true) << std::endl;
    }
}
