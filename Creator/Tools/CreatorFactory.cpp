#include "CreatorFactory.hpp"
#include "LoggingTools.hpp"
#include "StringTools.hpp"
namespace Creator::Entity
{

    static void ApplySetType(const Tags::Setter& value, Factory::Settype& set, const char* text)
    {
        using namespace Tags;
        switch (value)
        {
            case Setter::OVERRIDE:
            case Setter::LEGAL:
            case Setter::SUPPLEMENT:
            case Setter::ISRITUAL:
            case Setter::HASMATERIALCOMPONENT:
            case Setter::HASSOMATICCOMPONENT:
            case Setter::HOMEBREW:
            case Setter::THIRD_PARTY:
            case Setter::SECRET:
            case Setter::EXOTIC:
            case Setter::STANDARD:
            case Setter::LEAGUE:
            case Setter::STASH:
            case Setter::ATTUNEMENT:
            case Setter::ALLOW_DUPLICATE:
            case Setter::HASVERBALCOMPONENT:
            case Setter::MONSTER:
            case Setter::INCOMPLETE:
            case Setter::OFFICIAL:
            case Setter::PLAYTEST:
            case Setter::DISABLED:
            case Setter::EQUIPPABLE:
            case Setter::ISCONCENTRATION:
            case Setter::CURSED:
            case Setter::VALUABLE:
            case Setter::CORE:
            {
                bool tmp;
                if (text && tinyxml2::XMLUtil::ToBool(text, &tmp))
                    (*std::get<Factory::Booltype>(set)) = tmp;
            }
                break;
            case Setter::UNKNOWN:
            case Setter::SPELLCASTINGABILITY:
            case Setter::VULNERABILITIES:
            case Setter::INFORMATION:
            case Setter::REACTIONS:
            case Setter::SAVES:
            case Setter::CONDITIONIMMUNITIES:
            case Setter::IMMUNITIES:
            case Setter::MATERIALCOMPONENT:
            case Setter::DURATION:
            case Setter::TIME:
            case Setter::SCHOOL:
            case Setter::HEIGHT:
            case Setter::NAMES:
            case Setter::VERSATILE:
            case Setter::CONTAINER:
            case Setter::ABBREVIATION:
            case Setter::CHARGES:
            case Setter::DAMAGE:
            case Setter::STACKABLE:
            case Setter::WEIGHT:
            case Setter::ARMOR:
            case Setter::AUTHOR:
            case Setter::NAMES_FORMAT:
            case Setter::CATEGORY:
            case Setter::SYMBOL:
            case Setter::SCRIPT:
            case Setter::SLOT:
            case Setter::SENSES:
            case Setter::SUPPORTS:
            case Setter::TYPE:
            case Setter::HP:
            case Setter::RARITY:
            case Setter::WEAPON:
            case Setter::ENHANCEMENT:
            case Setter::SPELLCASTINGCLASS:
            case Setter::AC:
            case Setter::NAME_FORMAT:
            case Setter::RESISTANCES:
            case Setter::CHALLENGE:
            case Setter::STEALTH:
            case Setter::SHORT:
            case Setter::COST:
            case Setter::KEYWORDS:
            case Setter::DOMAINS:
            case Setter::GENDER:
            case Setter::URL:
            case Setter::ERRATA:
            case Setter::IMAGE:
            case Setter::SPEED:
            case Setter::LANGUAGES:
            case Setter::SKILLS:
            case Setter::RANGE:
            case Setter::SIZE:
            case Setter::SOURCEURL:
            case Setter::ALIGNMENT:
            case Setter::TRAITS:
            case Setter::PROFICIENCY:
            case Setter::ACTIONS:
            case Setter::RELEASE:
            case Setter::SPEAKERS:
            case Setter::ARMORCLASS:
            case Setter::HD:
            case Setter::SETTING:
            case Setter::AUTHORABBREVIATION:
            case Setter::AUTHORURL:
            case Setter::ACTION:
            case Setter::HEIGHTMODIFIER:
            case Setter::WEIGHTMODIFIER:
            {
                if (text)
                    (*std::get<Factory::Texttype>(set)) = text;
            }
                break;
            case Setter::LEVEL:
            case Setter::RELOAD:
            case Setter::INTELLIGENCE:
            case Setter::STRENGTH:
            case Setter::DEXTERITY:
            case Setter::CONSTITUTION:
            case Setter::WISDOM:
            case Setter::CHARISMA:
            {
                int tmp;
                if (text && tinyxml2::XMLUtil::ToInt(text, &tmp))
                    (*std::get<Factory::Inttype>(set)) = tmp;
            }
                break;
        }
    }

    static void UpdateMapWithSetter(const std::optional<Tags::Setter>& setname, Factory::Maptype& map, const char* text, std::string_view name)
    {
        
        if (setname.has_value())
        {
            if (map.find(setname.value()) == map.end())
            {
                LogWarn("Expected set name: {} but not found", name);
            }
            else
            {
                ApplySetType(setname.value(), map.at(setname.value()), text);
            }
        }
        else
        {
            LogWarn("Encountered bad set name: {}", name);
        }
    }

    /**
     * @brief Sets the values using pointers to the class members inserted into the map.
     * 
     * @param map Map which stores pointers to the class members which could be found in the element.
     * @param node First set element inside the setter child.
     */
    void SetterFactory(Factory::Maptype map, tinyxml2::XMLElement* node)
    {
        while (node)
        {
            if (SafeCompareString(node->Value(), "set", CompareOpts::Default))
            {
                const std::string node_name = node->Attribute("name");
                auto setname = Tags::EnumFromString<Tags::Setter>(node_name);
                UpdateMapWithSetter(setname, map, node->GetText(), node_name);
                auto att = node->FirstAttribute();
                while (att)
                {
                    if (!SafeCompareString(att->Name(), "name", CompareOpts::Default))
                    {
                        const auto attname = Tags::EnumFromString<Tags::Setter>(node_name + std::string(att->Name()));
                        UpdateMapWithSetter(attname, map, att->Value(), node_name);
                    }
                    att = att->Next();
                }
            }
            else
            {
                LogError("Encountered non-set in setter factory for item: {}", node->Value());
            }
            node = node->NextSiblingElement();
        }
    }
}