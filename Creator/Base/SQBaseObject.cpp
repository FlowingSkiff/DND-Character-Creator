#include "SQBaseObject.hpp"
#include "LoggingTools.hpp"
#include "StringTools.hpp"
#include "XMLTools.hpp"
namespace Creator::Entity
{
    /// -------------------- BASE --------------------
    std::string SQObject::GetReadFormat() const
    {
        return "(id, name, description, short_description)";
    }
    std::string SQObject::GetWriteFormat() const
    {
        return "(name, description, short_description)";
    }

    SQObject::SQObject(Type _type): type(_type)
    {

    }

    SQObject::SQObject(Type _type, tinyxml2::XMLElement* node): type(_type)
    {
        name = ReplaceSpecialInString(node->FindAttribute("name")->Value());
        source = ReplaceSpecialInString(node->FindAttribute("source")->Value());
        external_id = node->FindAttribute("id")->Value();
    }

    Factory::Maptype SQObject::GetMemberMap()
    {
        using namespace Tags;
        return {};
    }

    
    std::ostream& SQObject::WriteToStream(std::ostream& os) const
    {
        os  << std::boolalpha
            << "id: " << id << '\n'
            << "name: " << name << '\n'
            << "description: " << description << '\n'
            << "short_description: " << short_description << '\n'
            << "source: " << source << '\n'
            << "external_id: " << external_id << '\n'
            << "type: " << static_cast<int>(type) << '\n'
            << "compendium display: " << display_in_compendium << '\n';
        return os;
    }

    /// -------------------- SheetDisplay --------------------
    
    SheetDisplay::SheetDisplay(tinyxml2::XMLElement* node)
    {
        BuildSheetAttributes(node->FirstChildElement("sheet"));
    }

    void SheetDisplay::BuildSheetAttributes(tinyxml2::XMLElement* node)
    {
        if (node)
        {
            auto att = node->FirstAttribute();
            while(att)
            {
                if (SafeCompareString(att->Name(), "alt", CompareOpts::Default))
                    sheet_alt_title = att->Value();
                else if (SafeCompareString(att->Name(), "usage", CompareOpts::Default))
                    sheet_usage = att->Value();
                else if (SafeCompareString(att->Name(), "display", CompareOpts::Default))
                    sheet_display = att->BoolValue();
                else if (SafeCompareString(att->Name(), "action", CompareOpts::Default))
                    sheet_action = att->Value();
                else if (SafeCompareString(att->Name(), "name", CompareOpts::Default))
                    sheet_name = att->Value();
                else
                    LogWarn("Unhandled sheet attribute: {}", att->Name());
                att = att->Next();

            }
            if (auto desc = node->FirstChildElement())
            {
                if (auto desctext = desc->GetText())
                    sheet_description = desctext;
            }
        }
    }

    /// -------------------- Select --------------------
    bool Select::Construct(tinyxml2::XMLElement* node)
    {
        if (SafeCompareString(node->Name(), "select", CompareOpts::Default))
        {
            auto att = node->FirstAttribute();
            while(att)
            {
                if (SafeCompareString(att->Name(), "default-behavior", CompareOpts::Default))
                    select_default_behaviour = att->Value();
                if (SafeCompareString(att->Name(), "default-behaviour", CompareOpts::Default))
                    select_default_behaviour = att->Value();
                else if (SafeCompareString(att->Name(), "level", CompareOpts::Default))
                    select_level = att->Value();
                else if (SafeCompareString(att->Name(), "requirements", CompareOpts::Default))
                    select_requirements = att->Value();
                else if (SafeCompareString(att->Name(), "optional", CompareOpts::Default))
                    select_optional = att->Value();
                else if (SafeCompareString(att->Name(), "default", CompareOpts::Default))
                    select_default = att->Value();
                else if (SafeCompareString(att->Name(), "number", CompareOpts::Default))
                    select_number = att->Value();
                else if (SafeCompareString(att->Name(), "prepared", CompareOpts::Default))
                    select_prepared = att->Value();
                else if (SafeCompareString(att->Name(), "spellcasting", CompareOpts::Default))
                    select_spellcasting = att->Value();
                else if (SafeCompareString(att->Name(), "supports", CompareOpts::Default))
                    select_supports = att->Value();
                else if (SafeCompareString(att->Name(), "allowReplace", CompareOpts::Default))
                    select_allowReplace = att->Value();
                else if (SafeCompareString(att->Name(), "name", CompareOpts::Default))
                    select_name = att->Value();
                else if (SafeCompareString(att->Name(), "type", CompareOpts::Default))
                {
                    select_type = att->Value();
                    if (SafeCompareString(select_type, "List", CompareOpts::Default))
                    {
                        auto list_obj = node->FirstChildElement();
                        while(list_obj)
                        {
                            if (auto text = list_obj->GetText())
                            {
                                select_list_values.emplace_back(text);
                            }
                            list_obj = list_obj->NextSiblingElement();
                        }
                    }
                }
                else
                    LogWarn("Unexpected select attribute {}", att->Name());
                att = att->Next();
            }
            return true;
        }
        return false;
    }

    std::ostream& Select::WriteToStream(std::ostream& os) const
    {
        os  << std::boolalpha << "Type: SELECT\n"
            << "Default Behavior: " << select_default_behaviour << '\n'
            << "Default: " << select_default << '\n'
            << "Requirements: " << select_requirements << '\n'
            << "Optional: " << select_optional << '\n'
            << "Level: " << select_level << '\n'
            << "Number: " << select_number << '\n'
            << "Prepared: " << select_prepared << '\n'
            << "Spellcasting: " << select_spellcasting << '\n'
            << "Supports: " << select_supports << '\n'
            << "AllowReplace: " << select_allowReplace << '\n'
            << "Name: " << select_name << '\n'
            << "Type: " << select_type << '\n';
        for (const auto& s : select_list_values)
            os << s << '\n';
        return os;
    }

    /// -------------------- Stat --------------------
    bool Stat::Construct(tinyxml2::XMLElement* node)
    {
        if (SafeCompareString(node->Name(), "stat", CompareOpts::Default))
        {
            auto att = node->FirstAttribute();
            while(att)
            {
                if (SafeCompareString(att->Name(), "id", CompareOpts::Default))
                    stat_id = att->Value();
                else if (SafeCompareString(att->Name(), "inline", CompareOpts::Default))
                    stat_inline = att->Value();
                else if (SafeCompareString(att->Name(), "alt", CompareOpts::Default))
                    stat_alt = att->Value();
                else if (SafeCompareString(att->Name(), "requirements", CompareOpts::Default))
                    stat_requirements = att->Value();
                else if (SafeCompareString(att->Name(), "bonus", CompareOpts::Default))
                    stat_bonus = att->Value();
                else if (SafeCompareString(att->Name(), "level", CompareOpts::Default))
                    stat_level = att->Value();
                else if (SafeCompareString(att->Name(), "maximum", CompareOpts::Default))
                    stat_maximum = att->Value();
                else if (SafeCompareString(att->Name(), "equipped", CompareOpts::Default))
                    stat_equipped = att->Value();
                else if (SafeCompareString(att->Name(), "value", CompareOpts::Default))
                    stat_value = att->Value();
                else if (SafeCompareString(att->Name(), "name", CompareOpts::Default))
                    stat_name = att->Value();
                else
                    LogWarn("Unexpected stat attribute {}", att->Name());
                att = att->Next();
            }
            return true;
        }
        return false;
    }

    std::ostream& Stat::WriteToStream(std::ostream& os) const
    {
        return os << std::boolalpha << "Type: STAT\n"
                  << "ID: " << stat_id << '\n'
                  << "Inline: " << stat_inline << '\n'
                  << "Alt: " << stat_alt << '\n'
                  << "Requirements: " << stat_requirements << '\n'
                  << "Bonus: " << stat_bonus << '\n'
                  << "Level: " << stat_level << '\n'
                  << "Max: " << stat_maximum << '\n'
                  << "Equpped: " << stat_equipped << '\n'
                  << "value: " << stat_value << '\n'
                  << "Name: " << stat_name << '\n';
    }

    /// -------------------- Grant --------------------
    bool Grant::Construct(tinyxml2::XMLElement* node)
    {
        if (SafeCompareString(node->Name(), "grant", CompareOpts::Default))
        {
            auto att = node->FirstAttribute();
            while(att)
            {
                if (SafeCompareString(att->Name(), "equipped", CompareOpts::Default))
                    grant_equipped = att->Value();
                else if (SafeCompareString(att->Name(), "prepared", CompareOpts::Default))
                    grant_prepared = att->Value();
                else if (SafeCompareString(att->Name(), "spellcasting", CompareOpts::Default))
                    grant_spellcasting = att->Value();
                else if (SafeCompareString(att->Name(), "requirements", CompareOpts::Default))
                    grant_requirements = att->Value();
                else if (SafeCompareString(att->Name(), "level", CompareOpts::Default))
                    grant_level = att->Value();
                else if (SafeCompareString(att->Name(), "id", CompareOpts::Default))
                    grant_id = att->Value();
                else if (SafeCompareString(att->Name(), "name", CompareOpts::Default))
                    grant_name = att->Value();
                else if (SafeCompareString(att->Name(), "type", CompareOpts::Default))
                    grant_type = att->Value();
                else
                    LogWarn("Unexpected grant attribute {}", att->Name());
                att = att->Next();
            }
            return true;
        }
        return false;
    }

    std::ostream& Grant::WriteToStream(std::ostream& os) const
    {
        return os << std::boolalpha << "Type: GRANT\n"
                  << "Equpped: " << grant_equipped << '\n'
                  << "Prepared: " << grant_prepared << '\n'
                  << "Spellcasting: " << grant_spellcasting << '\n'
                  << "Requirements: " << grant_requirements << '\n'
                  << "Level: " << grant_level << '\n'
                  << "ID: " << grant_id << '\n'
                  << "Name: " << grant_name << '\n'
                  << "Type: " << grant_type << '\n';
    }
    
    /// -------------------- Rule --------------------
    RuleBase::RuleBase(tinyxml2::XMLElement* node)
    {
        if (Select::Construct(node))
            rule_type = RuleType::SELECT;
        else if (Stat::Construct(node))
            rule_type = RuleType::STAT;
        else if (Grant::Construct(node))
            rule_type = RuleType::GRANT;
        else
        {
            rule_type = RuleType::GENERAL;
            LogError("Unexpected rule type {}", node->Name());
        }

    }

    std::ostream& RuleBase::ToStream(std::ostream& os) const
    {
        if (rule_type == RuleType::GRANT)
            Grant::WriteToStream(os);
        else if (rule_type == RuleType::SELECT)
            Select::WriteToStream(os);
        else if (rule_type == RuleType::STAT)
            Stat::WriteToStream(os);
        return os;
    }

    std::vector<RuleBase> GenerateRules(tinyxml2::XMLElement* node)
    {
        std::vector<RuleBase> ret;
        while(node)
        {
            ret.emplace_back(node);
            node = node->NextSiblingElement();
        }
        return ret;
    }

    std::ostream& operator<<(std::ostream& os, const std::vector<RuleBase>& rhs)
    {
        os << "--Rules\n";
        for (const auto& base : rhs)
            base.ToStream(os);
        return os;
    }

    std::ostream& CharacterBase::WriteToStream(std::ostream& os) const
    {
        os << "strength: " << strength << '\n'
           << "dexterity: " << dexterity << '\n'
           << "constitution: " << constitution << '\n'
           << "intelligence: " << intelligence << '\n'
           << "wisdom: " << wisdom << '\n'
           << "charisma: " << charisma << '\n'
           << "ac: " << ac << '\n'
           << "hp: " << hp << '\n'
           << "speed: " << speed << '\n'
           << "languages: " << languages << '\n'
           << "skills: " << skills << '\n'
           << "beast_type: " << beast_type << '\n'
           << "size: " << size << '\n'
           << "alignment: " << alignment << '\n'
           << "challenge: " << challenge << '\n'
           << "traits: " << traits << '\n'
           << "actions: " << actions << '\n'
           << "senses: " << senses << '\n'
           << "immunities: " << immunities << '\n'
           << "conditionImmunities: " << conditionImmunities << '\n'
           << "saves: " << saves << '\n'
           << "reactions: " << reactions << '\n'
           << "resistances: " << resistances << '\n'
           << "vulnerabilities: " << vulnerabilities << '\n';
        return os;
    }

    std::ostream& SheetDisplay::WriteToStream(std::ostream& os) const
    {
        os  << "sheet display: " << sheet_display << '\n'
            << "sheet alt title: " << sheet_alt_title << '\n'
            << "sheet description: " << sheet_description << '\n'
            << "sheet usage: " << sheet_usage << '\n'
            << "sheet action: " << sheet_action << '\n'
            << "sheet name: " << sheet_name << '\n';
        return os;
    }

    std::ostream& SpellcastingBase::WriteToStream(std::ostream& os) const
    {
        os  << "is_spellcasting: " << is_spellcasting << '\n';
        if (is_spellcasting)
        {
            os  << "spellcasting_name: " << spellcasting_name << '\n'
                << "spellcasting_ability: " << spellcasting_ability << '\n'
                << "spellcasting_allow_replace: " << spellcasting_allow_replace << '\n'
                << "spellcasting_list: " << spellcasting_list << '\n'
                << "spellcasting_list_known: " << spellcasting_list_known << '\n'
                << "spellcasting_extend: " << spellcasting_extend << '\n'
                << "spellcasting_prepare: " << spellcasting_prepare << '\n'
                << "spellcasting all: " << spellcasting_all << '\n';
            for (const auto& s : spellcasting_extend_list)
                os << "Extend: " << s << '\n';
        }
        return os;
    }

    void SpellcastingBase::Construct(tinyxml2::XMLElement* node)
    {
        if (SafeCompareString(node->Name(), "spellcasting"))
        {
            is_spellcasting = true;
            auto att = node->FirstAttribute();
            while (att)
            {
                if (SafeCompareString(att->Name(), "name"))
                    spellcasting_name = att->Value();
                else if (SafeCompareString(att->Name(), "ability"))
                    spellcasting_ability = att->Value();
                else if (SafeCompareString(att->Name(), "allowReplace"))
                    spellcasting_allow_replace = att->BoolValue();
                else if (SafeCompareString(att->Name(), "prepare"))
                    spellcasting_prepare = att->BoolValue();
                else if (SafeCompareString(att->Name(), "extend"))
                    spellcasting_extend = att->BoolValue();
                else if (SafeCompareString(att->Name(), "all"))
                    spellcasting_all = att->BoolValue();
                else
                    LogWarn("Unexpected spellcasting attribute {}", att->Name());
                att = att->Next();
            }
            auto child = node->FirstChildElement();
            while(child)
            {
                if (SafeCompareString(child->Name(), "list"))
                {
                    if (auto tmp = child->GetText())
                        spellcasting_list = tmp;
                    auto latt = child->FirstAttribute();
                    while(latt)
                    {
                        if (SafeCompareString(latt->Name(), "known"))
                            spellcasting_list_known = latt->BoolValue();
                        latt = latt->Next();
                    }
                }
                else if (SafeCompareString(child->Name(), "extend"))
                {
                    spellcasting_extend_list.emplace_back(child->GetText());
                }
                else
                    LogWarn("Unhandled spellcasting child {}", child->Name());
                child = child->NextSiblingElement();
            }
            
        }
        else
        {
            LogError("Invalid use of SpellcasingBase constructor. Expected head element, received {}", node->Name());
        }
    }
} // namespace Creator::Entity
