#pragma once
#include <string>
#include <algorithm>
#include <magic_enum.hpp>
namespace Creator::Entity::Tags
{
    // Enum class for all setter values
    enum class Setter
    {
        UNKNOWN, 
        SPELLCASTINGABILITY,
        VULNERABILITIES,
        OVERRIDE,
        INFORMATION,
        LEGAL,
        REACTIONS,
        SAVES,
        CONDITIONIMMUNITIES,
        IMMUNITIES,
        SUPPLEMENT,
        ISRITUAL,
        MATERIALCOMPONENT,
        HASMATERIALCOMPONENT,
        HASSOMATICCOMPONENT,
        DURATION,
        TIME,
        SCHOOL,
        HEIGHT,
        NAMES,
        HOMEBREW,
        THIRD_PARTY,
        SECRET,
        EXOTIC,
        STANDARD,
        LEVEL,
        VERSATILE,
        CONTAINER,
        LEAGUE,
        STASH,
        ABBREVIATION,
        EQUIPPABLE,
        RELOAD,
        INTELLIGENCE,
        CHARGES,
        DAMAGE,
        STACKABLE,
        WEIGHT,
        ARMOR,
        AUTHOR,
        NAMES_FORMAT,
        CURSED,
        CATEGORY,
        SYMBOL,
        SCRIPT,
        SLOT,
        SENSES,
        SUPPORTS,
        TYPE,
        HP,
        RARITY,
        WEAPON,
        ENHANCEMENT,
        SPELLCASTINGCLASS,
        ISCONCENTRATION,
        AC,
        NAME_FORMAT,
        RESISTANCES,
        DEXTERITY,
        CHALLENGE,
        STRENGTH,
        SHORT,
        STEALTH,
        COST,
        VALUABLE,
        KEYWORDS,
        DISABLED,
        DOMAINS,
        GENDER,
        ATTUNEMENT,
        URL,
        CONSTITUTION,
        ERRATA,
        CORE,
        WISDOM,
        CHARISMA,
        IMAGE,
        SPEED,
        PLAYTEST,
        LANGUAGES,
        SKILLS,
        OFFICIAL,
        RANGE,
        SIZE,
        INCOMPLETE,
        SOURCEURL,
        ALIGNMENT,
        TRAITS,
        PROFICIENCY,
        ACTIONS,
        RELEASE,
        MONSTER,
        HASVERBALCOMPONENT,
        ALLOW_DUPLICATE,
        SPEAKERS,
        ARMORCLASS,
        HD,
        SETTING,
        AUTHORABBREVIATION,
        AUTHORURL,
        ACTION,
        HEIGHTMODIFIER,
        WEIGHTMODIFIER,
        MULTICLASS_PROFICIENCIES,
        WEIGHTLB,
        COSTCURRENCY,
        WEIGHTEXCLUDEENCUMBRANCE,
        COSTBULK,
        DAMAGETYPE,
        TYPEADDITION,
        ATTUNEMENTADDITION,
        STASHLB,
        STASHWEIGHTLESS,
        COSTOVERRIDE,
        SCHOOLADDITION,
        HASSOMATICCOMPONENTADDITION
    };

    // Get an enum value from string. templated using the enum class name
    template<typename Enum>
    constexpr auto EnumFromString(std::string str)
    {
        constexpr auto safe = [](const auto& c){
            return c == '-' || std::isspace(c);
        };
        std::transform(std::begin(str), std::end(str), std::begin(str), ::toupper);
        std::replace_if(std::begin(str), std::end(str), safe, '_');
        return magic_enum::enum_cast<Enum>(str);
    }
}

// Hasing method for Setter enum class
template<> struct std::hash<Creator::Entity::Tags::Setter>
{
    std::size_t operator()(const Creator::Entity::Tags::Setter& s) const noexcept
    {
        return std::hash<int>{}(static_cast<int>(s));
    }
};