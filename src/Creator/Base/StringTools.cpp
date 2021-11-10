#include <Creator/Base/StringTools.hpp>

std::ostream& writeString(std::ostream& out, std::string const& s)
{
    for (auto ch : s)
    {
        switch (ch)
        {
                //case '\'':
                //   out << "\\'";
                //   break;

                //case '\"':
                //   out << "\\\"";
                //   break;

            case '\?':
                out << "\\?";
                break;

            case '\\':
                out << "\\\\";
                break;

            case '\a':
                out << "\\a";
                break;

            case '\b':
                out << "\\b";
                break;

            case '\f':
                out << "\\f";
                break;

                //case '\n':
                //   out << "\\n";
                //   break;

            case '\r':
                out << "\\r";
                break;

                //case '\t':
                //   out << "\\t";
                //   break;

            case '\v':
                out << "\\v";
                break;

            default:
                out << ch;
        }
    }

    return out;
}

void InplaceCapitalize(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void InplaceUnderscoreWhitespace(std::string& str)
{
    std::replace_if(
        str.begin(), str.end(), [](const auto& c) {
            return std::isspace(c);
        },
        '_');
}

bool SafeCompareString(std::string str1, std::string str2, CompareOpts opts)
{
    if (opts & CompareOpts::OnlyAlpha)
    {
        str1.erase(std::remove_if(str1.begin(), str1.end(), [](const auto& c) {
            return !std::isalpha(c);
        }),
            str1.end());
        str2.erase(std::remove_if(str2.begin(), str2.end(), [](const auto& c) {
            return !std::isalpha(c);
        }),
            str2.end());
    }
    if (opts & CompareOpts::IgnoreCase)
    {
        InplaceCapitalize(str1);
        InplaceCapitalize(str2);
    }
    if (opts & CompareOpts::Whitepace)
    {
        InplaceUnderscoreWhitespace(str1);
        InplaceUnderscoreWhitespace(str2);
    }
    return str1 == str2;
}

int operator&(const CompareOpts& op1, const CompareOpts& op2)
{
    return static_cast<int>(op1) & static_cast<int>(op2);
}
int operator|(const CompareOpts& op1, const CompareOpts& op2)
{
    return static_cast<int>(op1) | static_cast<int>(op2);
}