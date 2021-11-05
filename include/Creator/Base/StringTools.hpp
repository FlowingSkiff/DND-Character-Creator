#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>


// safely writes string to out stream by protecting special characters
std::ostream& writeString(std::ostream& out, std::string const& s);

// Removes special quotation marks in string with ASCII characters
std::string ReplaceSpecialInString(std::string str);

// Capitalizes a string inplace by reference
void InplaceCapitalize(std::string& str);

// Replaces all whitespace with underscores inplace by reference
void InplaceUnderscoreWhitespace(std::string& str);


// Compare options to be used with Safe compare string
enum class CompareOpts {
    Whitepace = 1,
    IgnoreCase = 2,
    OnlyAlpha = 4,
    Default = Whitepace | IgnoreCase | OnlyAlpha
};
// overload for the bitwise and for compare options
int operator&(const CompareOpts& op1, const CompareOpts& op2);
// overload for the bitwise or for compare options
int operator|(const CompareOpts& op1, const CompareOpts& op2);

/**
 * @brief Compares two string objects. Removes spaces and non-alpha characters. Case In-sensitive
 * 
 * @param str1 
 * @param str2 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool SafeCompareString(std::string str1, std::string str2, CompareOpts opts = CompareOpts::Default);