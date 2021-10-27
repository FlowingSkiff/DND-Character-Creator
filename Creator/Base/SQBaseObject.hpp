#pragma once
#include <string>
#include <vector>
#include <tinyxml2.h>
#include "CreatorFactory.hpp"
namespace Creator::Entity
{
    

    // Replace Magic_item, Armor, Weapon all into Weapon
    enum class Type
    {
        None = -1,                       // TODO: Implement into structure
        General,                         // TODO: Implement into structure
        Archetype_Feature,               // TODO: Implement into structure
        Archetype,                       // TODO: Implement into structure
        Class_Feature,                   // TODO: Implement into structure
        Spell,                           // DONE
        Race,                            // TODO: Implement into structure
        Magic_Item,                      // TODO: Implement into structure
        Sub_Race,                        // TODO: Implement into structure
        Option,                          // TODO: Implement into structure
        Armor,                           // TODO: Implement into structure
        Item,                            // TODO: Implement into structure
        Weapon,                          // TODO: Implement into structure
        Class,                           // TODO: Implement into structure
        Ability_Score_Improvement,       // TODO: Implement into structure
        Rule,                            // TODO: Implement into structure
        Source,                          // DONE
        Language,                        // DONE
        Companion,                       // DONE
        Companion_Action,                // DONE
        Background,                      // TODO: Implement into structure
        Deity,                           // DONE
        Feat,                            // DONE
        Feat_Feature,                    // DONE
        Information,                     // DONE
        Race_Variant                     // TODO: Implement into structure
    };

    
    /**
     * @brief Base class for an item which can be displayed on a sheet. Used to 
     *        display alternate descriptions, titles, usages, etc. 
     * 
     */
    struct SheetDisplay
    {
        SheetDisplay() = default;
        SheetDisplay(tinyxml2::XMLElement* node);
        virtual ~SheetDisplay() {}
        bool sheet_display = true;
        std::string sheet_alt_title = "";
        std::string sheet_description = "";
        std::string sheet_usage = "";
        std::string sheet_action = "";
        /**
         * @brief Given the sheet head node from an xml document, it searches and builds the
         *        attributes for the sheet element. Alternate title, description, display
         *        and usage information.
         * 
         * @param node Head of the sheet child element for an element.
         */
        void BuildSheetAttributes(tinyxml2::XMLElement* node);
        virtual std::ostream& WriteToStream(std::ostream& os) const;
    };

    /**
     * @brief Base class for all elements loaded into the program. All elements
     *        should inherit from this class. Virtual functions for IO from 
     *        streams and sqlite3 should be included.
     * 
     */
    struct SQObject
    {
        SQObject() = default;
        SQObject(Type type);
        SQObject(Type type, tinyxml2::XMLElement* node);
        virtual ~SQObject() = default;


        int64_t id = -1;
        std::string name = "NULL";
        std::string description = "NULL";
        std::string short_description = "";
        std::string source = "";
        std::string external_id = "";
        Type type = Type::None;
        bool display_in_compendium = true;

        // Read format for use with sqlite3 db reading
        virtual std::string GetReadFormat() const;
        // writing format for sqlite3 insert
        virtual std::string GetWriteFormat() const;
        // output writing to stream
        virtual std::ostream& WriteToStream(std::ostream&) const;
        // member map for reading from xml setter options
        virtual Factory::Maptype GetMemberMap();
    };

    // TODO: Add in List -> item support for text only selections
    struct Select
    {
        bool Construct(tinyxml2::XMLElement* node);
        std::string select_default_behaviour = "";
        std::string select_level = "";
        std::string select_requirements = "";
        std::string select_optional = "false";
        std::string select_default = "";
        std::string select_number = "1";
        std::string select_prepared = "";
        std::string select_spellcasting = "";
        std::string select_supports = "";
        std::string select_allowReplace = "";
        std::string select_name = "";
        std::string select_type = "";
        std::vector<std::string> select_list_values;
        std::ostream& WriteToStream(std::ostream& os) const;
    };
    struct Stat
    {
        bool Construct(tinyxml2::XMLElement* node);
        std::string stat_id = "";
        std::string stat_inline = "";
        std::string stat_alt = "";
        std::string stat_requirements = "";
        std::string stat_bonus = "";
        std::string stat_level = "";
        std::string stat_maximum = "";
        std::string stat_equipped = "";
        std::string stat_value = "";
        std::string stat_name = "";
        std::ostream& WriteToStream(std::ostream& os) const;
    };
    struct Grant
    {
        bool Construct(tinyxml2::XMLElement* node);
        std::string grant_equipped = "";
        std::string grant_prepared = "";
        std::string grant_spellcasting = "";
        std::string grant_requirements = "";
        std::string grant_level = "";
        std::string grant_id = "";
        std::string grant_name = "";
        std::string grant_type = "";
        std::ostream& WriteToStream(std::ostream& os) const;
    };

    /**
     * @brief 
     * 
     */
    struct RuleBase : public Select, public Stat, public Grant
    {
        enum class RuleType {GENERAL, SELECT, STAT, GRANT};
        RuleType rule_type = RuleType::GENERAL;
        RuleBase(tinyxml2::XMLElement* node);
        std::ostream& ToStream(std::ostream& os) const;
    };

    struct CharacterBase
    {
        virtual ~CharacterBase(){}
        int strength = 8;
        int dexterity = 8;
        int constitution = 8;
        int intelligence = 8;
        int wisdom = 8;
        int charisma = 8;
        std::string ac = "0";
        std::string hp = "0";
        std::string speed = "";
        std::string languages = "";
        std::string skills = "";
        std::string beast_type = "";
        std::string size = "Tiny";
        std::string alignment = "unaligned";
        std::string challenge = "0";
        std::string actions = "";
        std::string traits = "";
        std::string senses = "";
        std::string immunities = "";
        std::string conditionImmunities = "";
        std::string saves = "";
        std::string reactions = "";
        std::string vulnerabilities = "";
        std::string resistances = "";
        virtual std::ostream& WriteToStream(std::ostream& os) const;
    };

    std::vector<RuleBase> GenerateRules(tinyxml2::XMLElement* node);
    std::ostream& operator<<(std::ostream& os, const std::vector<RuleBase>& rhs);
    
    // Streaming overload for fmt and ostream for all inherited SQObjects
    template<typename T, typename = typename std::enable_if<std::is_base_of<SQObject, T>::value>::type>
    std::ostream& operator<<(std::ostream& os, const T& rhs)
    {
        return rhs.WriteToStream(os);
    }
    
} // namespace Creator::Entity
