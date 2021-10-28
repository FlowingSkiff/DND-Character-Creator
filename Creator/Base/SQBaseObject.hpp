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
        Archetype_Feature,               // DONE
        Archetype,                       // DONE
        Class_Feature,                   // DONE
        Spell,                           // DONE
        Race,                            // DONE
        Magic_Item,                      // TODO: Implement into structure
        Sub_Race,                        // DONE
        Option,                          // DONE
        Armor,                           // TODO: Implement into structure
        Item,                            // DONE
        Weapon,                          // DONE
        Class,                           // DONE
        Ability_Score_Improvement,       // DONE
        Rule,                            // DONE
        Source,                          // DONE
        Language,                        // DONE
        Companion,                       // DONE
        Companion_Action,                // DONE
        Background,                      // DONE
        Background_Feature,              // DONE
        Deity,                           // DONE
        Feat,                            // DONE
        Feat_Feature,                    // DONE
        Information,                     // DONE
        Race_Variant,                    // DONE
        Racial_Trait                     // DONE
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
        std::string sheet_name = "";
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

    struct SpellcastingBase
    {
        virtual ~SpellcastingBase(){}

        bool is_spellcasting = false;
        std::string spellcasting_name = "";
        std::string spellcasting_ability = "";
        std::string spellcasting_list = "";
        bool spellcasting_allow_replace = false;
        bool spellcasting_list_known = false;
        bool spellcasting_extend = false;
        bool spellcasting_prepare = false;
        bool spellcasting_all = false;
        std::vector<std::string> spellcasting_extend_list;
        virtual std::ostream& WriteToStream(std::ostream& os) const;
        void Construct(tinyxml2::XMLElement* node);
    };

    struct ItemBase
    {
        bool is_stackable = false;
        std::string slot = "";
        std::string proficiency = "";
        std::string weight_lb = "";
        std::string weight = "";
        std::string cost = "";
        std::string cost_currency = "";
        std::string rarity = "Common";
        int bulk_buy = 1;
        bool is_valuable = false;
        std::string category = "";
        std::string keywords = "";
        std::string set_type = "";
        std::string supports = "";
        bool exclude_encumbrance = false;
        std::ostream& WriteToStream(std::ostream& os) const;
        Factory::Maptype& ModifySetMap(Factory::Maptype& map);
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
