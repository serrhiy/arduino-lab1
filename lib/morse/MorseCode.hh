#pragma once

#include "MorseUnit.hh"

#include <stddef.h>
#include <stdint.h>

namespace morse
{

inline constexpr uint8_t MAX_MORSE_CODE_LENGTH = 5;
inline constexpr uint8_t MIN_MORSE_CODE_LENGTH = 1;
inline constexpr char DOT_SYMBOL = '.';
inline constexpr char DASH_SYMBOL = '-';

namespace detail
{

constexpr bool IsValidMorseSymbol(char symbol)
{
    return symbol == DOT_SYMBOL || symbol == DASH_SYMBOL;
}

constexpr uint8_t MorseSymbolToBit(char symbol)
{
    return symbol == DOT_SYMBOL ? 0 : 1;
}

constexpr MorseUnit BitToMorseUnit(uint8_t bit)
{
    return bit == 1 ? MorseUnit::DASH : MorseUnit::DOT;
}

} // namespace detail

class MorseCode final
{
    uint8_t length;
    uint8_t bits;

    class MorseCodeIterator final
    {
        const MorseCode *morse_code;
        uint8_t bit_position;

      public:
        using value_type = MorseUnit;
        using difference_type = ptrdiff_t;

        constexpr MorseCodeIterator(const MorseCode *morse_code, uint8_t bit_position) noexcept
            : morse_code{morse_code}, bit_position{bit_position}
        {
        }

        constexpr value_type operator*() const noexcept
        {
            const uint8_t bit = (morse_code->Bits() >> bit_position) & 0b1;
            return detail::BitToMorseUnit(bit);
        }

        constexpr MorseCodeIterator &operator++() noexcept
        {
            --bit_position;
            return *this;
        }

        constexpr bool operator==(const MorseCodeIterator &other) const noexcept
        {
            return bit_position == other.bit_position;
        }

        constexpr bool operator!=(const MorseCodeIterator &other) const noexcept
        {
            return !(*this == other);
        }
    };

  public:
    constexpr MorseCode(uint8_t length, uint8_t bits) noexcept : length{length}, bits{bits}
    {
    }

    constexpr MorseCodeIterator begin() const noexcept
    {
        return MorseCodeIterator{this, 7};
    }

    constexpr MorseCodeIterator end() const noexcept
    {
        return MorseCodeIterator{this, static_cast<uint8_t>(7 - length)};
    }

    template <uint8_t N> static constexpr MorseCode Construct(const char (&str)[N]) noexcept
    {
        static_assert(N - 1 >= MIN_MORSE_CODE_LENGTH, "morse code is too small");
        static_assert(N - 1 <= MAX_MORSE_CODE_LENGTH, "morse code is too long");

        uint8_t bits = 0;
        for (uint8_t index = 0; index < N - 1; index++)
        {
            if (!detail::IsValidMorseSymbol(str[index]))
            {
                return MorseCode{0, 0};
            }
            const uint8_t bit_position = 7 - index;
            bits |= detail::MorseSymbolToBit(str[index]) << bit_position;
        }
        return MorseCode{static_cast<uint8_t>(N - 1), bits};
    }

    constexpr uint8_t Length() const noexcept
    {
        return length;
    }

    constexpr uint8_t Bits() const noexcept
    {
        return bits;
    }
};

static_assert(MorseCode::Construct("-").Length() == 1);
static_assert(MorseCode::Construct(".-").Length() == 2);
static_assert(MorseCode::Construct(".-").Bits() == 0b01000000);

} // namespace morse
