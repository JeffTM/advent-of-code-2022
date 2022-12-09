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

namespace Math
{
    template<typename T>
    T Clamp(T X, T Min, T Max)
    {
        return X < Min ? Min : Max < X ? Max : X;
    }

    template<typename T>
    int Signum(T X)
    {
        return (T(0) < X) - (X < T(0));
    }
}

template <typename ValueType>
struct Vector2
{
    struct Hash
    {
        std::size_t operator()(const Vector2<ValueType>& Vec) const noexcept
        {
            constexpr std::size_t P1 = 73856093;
            constexpr std::size_t P2 = 19349663;

            return (Vec.X * P1) ^ (Vec.Y * P2);
        }
    };

    constexpr Vector2()
        : X(0), Y(0)
    {}

    constexpr explicit Vector2(ValueType All)
        : X(All), Y(All)
    {}

    constexpr Vector2(ValueType X, ValueType Y)
        : X(X), Y(Y)
    {}

    constexpr bool operator==(const Vector2<ValueType>& Other) const
    {
        return this->X == Other.X && this->Y == Other.Y;
    }

    constexpr bool operator!=(const Vector2<ValueType>& Other) const
    {
        return !(this->operator==(Other));
    }

    constexpr bool operator<(const Vector2<ValueType>& Other) const
    {
        if (this->X != Other.X)
        {
            return this->X < Other.X;
        }

        return this->Y < Other.Y;
    }

    constexpr Vector2<ValueType> operator+(const Vector2<ValueType>& Other) const
    {
        return Vector2<ValueType>(this->X + Other.X, this->Y + Other.Y);
    }

    constexpr void operator+=(const Vector2<ValueType>& Other)
    {
        this->X += Other.X;
        this->Y += Other.Y;
    }

    constexpr Vector2<ValueType> operator-(const Vector2<ValueType>& Other) const
    {
        return Vector2<ValueType>(this->X - Other.X, this->Y - Other.Y);
    }

    constexpr Vector2<ValueType> operator/(ValueType Scalar) const
    {
        return Vector2<ValueType>(this->X / Scalar, this->Y / Scalar);
    }

    friend std::ostream& operator<<(std::ostream& OutStream, const Vector2<ValueType>& Vec)
    {
        return OutStream << '(' << Vec.X << ", " << Vec.Y << ')';
    }

    constexpr bool AnyZero() const
    {
        return this->X == 0 || this->Y == 0;
    }

    constexpr Vector2<ValueType> Clamp(ValueType Min, ValueType Max) const
    {
        return Vector2<ValueType>(Math::Clamp(this->X, Min, Max), Math::Clamp(this->Y, Min, Max));
    }

    constexpr bool IsZero() const
    {
        return this->X == 0 && this->Y == 0;
    }

    constexpr Vector2<ValueType> Signum() const
    {
        return Vector2<ValueType>(Math::Signum(this->X), Math::Signum(this->Y));
    }

    constexpr ValueType SizeSquared() const
    {
        return this->X * this->X + this->Y * this->Y;
    }

    ValueType X;
    ValueType Y;
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

    constexpr void operator+=(const Vector3<ValueType>& Other)
    {
        this->X += Other.X;
        this->Y += Other.Y;
        this->Z += Other.Z;
    }

    constexpr Vector3<ValueType> operator-(const Vector3<ValueType>& Other) const
    {
        return Vector3<ValueType>(this->X - Other.X, this->Y - Other.Y, this->Z - Other.Z);
    }

    constexpr Vector3<ValueType> operator/(ValueType Scalar) const
    {
        return Vector3<ValueType>(this->X / Scalar, this->Y / Scalar, this->Z / Scalar);
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

    constexpr bool AnyZero() const
    {
        return this->X == 0 || this->Y == 0 || this->Z == 0;
    }

    constexpr Vector3<ValueType> Clamp(ValueType Min, ValueType Max) const
    {
        return Vector3<ValueType>(Math::Clamp(this->X, Min, Max), Math::Clamp(this->Y, Min, Max), Math::Clamp(this->Z, Min, Max));
    }

    constexpr bool IsZero() const
    {
        return this->X == 0 && this->Y == 0 && this->Z == 0;
    }

    constexpr Vector3<ValueType> Signum() const
    {
        return Vector3<ValueType>(Math::Signum(this->X), Math::Signum(this->Y), Math::Signum(this->Z));
    }

    constexpr ValueType SizeSquared() const
    {
        return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
    }

    ValueType X;
    ValueType Y;
    ValueType Z;
};

template <typename ValueType>
class Matrix2D
{
public:
    using IndexType          = int64_t;
    using ReferenceType      = std::vector<ValueType>::reference;
    using ConstReferenceType = std::vector<ValueType>::const_reference;

    Matrix2D()
        : Dimensioner(0), Values()
    {}

    Matrix2D(IndexType InDimensioner)
        : Dimensioner(InDimensioner), Values()
    {}

    void Append(ValueType Value)
    {
        this->Values.push_back(Value);
    }

    ReferenceType Get(IndexType Row, IndexType Col)
    {
        return this->Values[Col * Dimensioner + Row];
    }

    ConstReferenceType Get(IndexType Row, IndexType Col) const
    {
        return this->Values[Col * Dimensioner + Row];
    }

    IndexType GetDimensioner() const
    {
        return this->Dimensioner;
    }

    IndexType GetRowSize() const
    {
        return this->GetDimensioner();
    }

    IndexType GetColSize() const
    {
        return this->Values.size() / this->GetDimensioner();
    }

    void Set(IndexType Row, IndexType Col, ValueType Value)
    {
        this->Values[Col* Dimensioner + Row] = Value;
    }

    void SetDimensioner(IndexType InDimensioner)
    {
        this->Dimensioner = InDimensioner;
    }

    friend std::ostream& operator<<(std::ostream& OutStream, const Matrix2D<ValueType>& Matrix)
    {
        IndexType ValuesPrinted = 0;

        for (const ValueType& Value : Matrix.Values)
        {
            OutStream << Value;

            ++ValuesPrinted;

            if (Matrix.Dimensioner != 0 && (ValuesPrinted % Matrix.Dimensioner) == 0)
            {
                OutStream << '\n';
            }
            else
            {
                OutStream << ' ';
            }
        }

        return OutStream;
    }

protected:
    IndexType Dimensioner;

    std::vector<ValueType> Values;
};

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

inline bool ForEachFileLine(const char* File, std::function<void(const std::string&)> Func)
{
    std::ifstream FileStream(File);

    if (!FileStream.is_open())
    {
        return false;
    }

    std::string FileLine;

    while (std::getline(FileStream, FileLine))
    {
        Func(FileLine);
    }

    FileStream.close();

    return !FileStream.bad();
}

inline bool TryReadFileLines(const char* File, std::vector<std::string>& Lines)
{
    return ForEachFileLine(File, [&Lines](const std::string& FileLine)
    {
        Lines.push_back(FileLine);
    });
}

inline bool TryReadWholeFile(const char* File, std::string& Text)
{
    std::ifstream FileStream(File);

    if (!FileStream.is_open())
    {
        return false;
    }

    std::stringstream StringStream;
    StringStream << FileStream.rdbuf();

    Text.append(StringStream.str());

    FileStream.close();

    return !FileStream.bad();
}

inline void ForEachStringSplit(std::string_view S, std::string_view Seperator, std::function<void(std::string_view)> Func)
{
    std::string_view::size_type   SeperatorOffset = S.find(Seperator);
    std::string_view              Fragment;

    while (SeperatorOffset != std::string_view::npos)
    {
        Fragment = S.substr(0, SeperatorOffset);
        if (!Fragment.empty())
        {
            Func(Fragment);
        }
        S.remove_prefix(Fragment.size() + Seperator.size());
        SeperatorOffset = S.find(Seperator);
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
