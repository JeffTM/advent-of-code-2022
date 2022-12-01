#pragma once
#include <fstream>
#include <functional>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

constexpr float PI = 3.1415926535897932f;

constexpr size_t FindFirstEmptyValueNPos = std::numeric_limits<size_t>::max();

struct StringSplitSingleResult
{
    std::string_view First;
    std::string_view Second;

    StringSplitSingleResult(const std::string_view& First, const std::string_view& Second)
        : First(First), Second(Second)
    {}

    bool BothEmpty() const
    {
        return First.empty() && Second.empty();
    }

    bool EitherEmpty() const
    {
        return First.empty() || Second.empty();
    }
};

template <typename ValueType>
struct Vector3
{
    struct Hash
    {
        std::size_t operator()(const Vector3<ValueType>& Vec) const noexcept
        {
            constexpr std::size_t P1 = 73856093;
            constexpr std::size_t P2 = 19349663;
            constexpr std::size_t P3 = 83492791;

            return (Vec.X * P1) ^ (Vec.Y * P2) ^ (Vec.Z * P3);
        }
    };

    constexpr Vector3()
        : X(0), Y(0), Z(0)
    {}

    constexpr explicit Vector3(ValueType All)
        : X(All), Y(All), Z(All)
    {}

    constexpr Vector3(ValueType X, ValueType Y, ValueType Z)
        : X(X), Y(Y), Z(Z)
    {}

    constexpr bool operator==(const Vector3<ValueType>& Other) const
    {
        return this->X == Other.X && this->Y == Other.Y && this->Z == Other.Z;
    }

    constexpr bool operator!=(const Vector3<ValueType>& Other) const
    {
        return !(this->operator==(Other));
    }

    constexpr bool operator<(const Vector3<ValueType>& Other) const
    {
        if (this->X != Other.X)
        {
            return this->X < Other.X;
        }

        if (this->Y != Other.Y)
        {
            return this->Y < Other.Y;
        }

        return this->Z < Other.Z;
    }

    constexpr Vector3<ValueType> operator+(const Vector3<ValueType>& Other) const
    {
        return Vector3<ValueType>(this->X + Other.X, this->Y + Other.Y, this->Z + Other.Z);
    }

    friend std::ostream& operator<<(std::ostream& OutStream, const Vector3<ValueType>& Vec)
    {
        return OutStream << '(' << Vec.X << ", " << Vec.Y << ", " << Vec.Z << ')';
    }

    std::vector<Vector3<ValueType>> GetNeighbors() const
    {
        std::vector<Vector3<ValueType>> Result;
        Result.reserve(26);

        Vector3<ValueType> Offset(-1);
        Result.push_back(this->operator+(Offset));
        do
        {
            if (Offset.Z >= 1)
            {
                Offset.Z = -1;
                if (Offset.Y >= 1)
                {
                    Offset.Y = -1;
                    Offset.X += 1;
                }
                else
                {
                    Offset.Y += 1;
                }
            }
            else
            {
                Offset.Z += 1;
            }

            if (!Offset.IsZero())
            {
                Result.push_back(this->operator+(Offset));
            }
        }
        while (Offset != Vector3<ValueType>(1));

        return Result;
    }

    constexpr bool IsZero() const
    {
        return this->X == 0 && this->Y == 0 && this->Z == 0;
    }

    ValueType X;
    ValueType Y;
    ValueType Z;
};

typedef Vector3<float>   FVector;
typedef Vector3<int32_t> IVector;
typedef Vector3<int64_t> LVector;

template <class ValueType>
size_t FindFirstEmptyValue(const std::vector<ValueType>& V, size_t Start = 0)
{
    for (size_t i = Start; i < V.size(); ++i)
    {
        if (V[i].empty())
        {
            return i;
        }
    }

    return FindFirstEmptyValueNPos;
}

inline bool IsDigit(std::string::value_type C)
{
    return std::isdigit((unsigned char)C) != 0;
}

inline bool IsSpace(std::string::value_type C)
{
    return std::isspace((unsigned char)C) != 0;
}

inline bool TryReadFileLines(const char* File, std::vector<std::string>& Lines)
{
    std::ifstream FileStream(File);

    if (!FileStream)
    {
        return false;
    }

    std::string FileLine;

    while (std::getline(FileStream, FileLine))
    {
        Lines.push_back(FileLine);
    }

    FileStream.close();
    return true;
}

inline bool TryReadWholeFile(const char* File, std::string& Text)
{
    std::ifstream FileStream(File);

    if (!FileStream)
    {
        Text = std::string();

        return false;
    }

    std::stringstream StringStream;
    StringStream << FileStream.rdbuf();

    Text = StringStream.str();;

    FileStream.close();
    return true;
}

inline void ForEachStringSplit(std::string_view S, std::string_view Seperator, std::function<void(std::string_view)> Func)
{
    std::string_view::size_type   SeperatorOffsset = S.find(Seperator);
    std::string_view              Fragment;

    while (SeperatorOffsset != std::string_view::npos)
    {
        Fragment = S.substr(0, SeperatorOffsset);
        if (!Fragment.empty())
        {
            Func(Fragment);
        }
        S.remove_prefix(Fragment.size() + Seperator.size());
        SeperatorOffsset = S.find(Seperator);
    }

    // Handle the remaining string if there is any
    if (!S.empty())
    {
        Func(S);
    }
}

inline std::vector<std::string_view> StringSplit(std::string_view S, std::string_view Seperator)
{
    std::vector<std::string_view> Result;

    ForEachStringSplit(S, Seperator, [&Result](std::string_view Split) { Result.push_back(Split); });

    return Result;
}

inline StringSplitSingleResult StringSplitSingle(std::string_view S, std::string_view Seperator)
{
    const std::string_view::size_type FirstEnd = S.find(Seperator);
    if (FirstEnd == std::string_view::npos)
    {
        return StringSplitSingleResult(S, std::string_view());
    }

    const std::string_view::size_type SecondBegin = FirstEnd + Seperator.size();

    return StringSplitSingleResult(S.substr(0, FirstEnd), S.substr(SecondBegin));
}

inline std::string StringFilterSpace(const std::string_view& S)
{
    std::string Result;

    Result.reserve(S.size());
    for (std::string_view::size_type i = 0; i < S.size(); ++i)
    {
        if (!IsSpace(S[i]))
        {
            Result.push_back(S[i]);
        }
    }

    return Result;
}
