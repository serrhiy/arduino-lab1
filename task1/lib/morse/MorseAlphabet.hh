#pragma once

#include "MorseCode.hh"

namespace morse
{

namespace detail
{

constexpr char ToLower(char c) noexcept
{
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
}

} // namespace detail

constexpr MorseCode GetMorseCode(char symbol) noexcept
{
    const char normalised = detail::ToLower(symbol);
    switch (normalised)
    {
    case 'a':
        return MorseCode::Construct(".-");
    case 'b':
        return MorseCode::Construct("-...");
    case 'c':
        return MorseCode::Construct("-.-.");
    case 'd':
        return MorseCode::Construct("-..");
    case 'e':
        return MorseCode::Construct(".");
    case 'f':
        return MorseCode::Construct("..-.");
    case 'g':
        return MorseCode::Construct("--.");
    case 'h':
        return MorseCode::Construct("....");
    case 'i':
        return MorseCode::Construct("..");
    case 'j':
        return MorseCode::Construct(".---");
    case 'k':
        return MorseCode::Construct("-.-");
    case 'l':
        return MorseCode::Construct(".-..");
    case 'm':
        return MorseCode::Construct("--");
    case 'n':
        return MorseCode::Construct("-.");
    case 'o':
        return MorseCode::Construct("---");
    case 'p':
        return MorseCode::Construct(".--.");
    case 'q':
        return MorseCode::Construct("--.-");
    case 'r':
        return MorseCode::Construct(".-.");
    case 's':
        return MorseCode::Construct("...");
    case 't':
        return MorseCode::Construct("-");
    case 'u':
        return MorseCode::Construct("..-");
    case 'v':
        return MorseCode::Construct("...-");
    case 'w':
        return MorseCode::Construct(".--");
    case 'x':
        return MorseCode::Construct("-..-");
    case 'y':
        return MorseCode::Construct("-.--");
    case 'z':
        return MorseCode::Construct("--..");
    case '0':
        return MorseCode::Construct("-----");
    case '1':
        return MorseCode::Construct(".----");
    case '2':
        return MorseCode::Construct("..---");
    case '3':
        return MorseCode::Construct("...--");
    case '4':
        return MorseCode::Construct("....-");
    case '5':
        return MorseCode::Construct(".....");
    case '6':
        return MorseCode::Construct("-....");
    case '7':
        return MorseCode::Construct("--...");
    case '8':
        return MorseCode::Construct("---..");
    case '9':
        return MorseCode::Construct("----.");
    default:
        return MorseCode{0, 0};
    }
}

} // namespace morse
