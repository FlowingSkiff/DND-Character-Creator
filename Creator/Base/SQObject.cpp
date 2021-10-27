#include "SQObject.hpp"
#include "StringTools.hpp"
#include "XMLTools.hpp"
#include "LoggingTools.hpp"
#include "TagEnums.hpp"
#include "CreatorFactory.hpp"
namespace Creator::Entity
{
    /// -------------------- SPELL --------------------

    Spell::Spell(int argc, char** argv, char** colz): SQObject(Type::Spell)
    {
        type = Type::Spell;
        for (int i = 0; i < argc; ++i)
        {
            std::string col = colz[i];
            if (SafeCompareString(col, "id"))
                id = std::stoi(argv[i]);
            else if (SafeCompareString(col, "name"))
                name = argv[i];
            else if (SafeCompareString(col, "description"))
                description = argv[i];
            else if (SafeCompareString(col, "short_description"))
                short_description = argv[i];
            else if (SafeCompareString(col, "isRitual"))
                is_ritual = std::stoi(argv[i]);
            else if (SafeCompareString(col, "isConcentration"))
                is_concentration = std::stoi(argv[i]);
            else if (SafeCompareString(col, "hasVerbalComponent"))
                has_verbal_component = std::stoi(argv[i]);
            else if (SafeCompareString(col, "hasSomanticComponent"))
                has_somantic_component = std::stoi(argv[i]);
            else if (SafeCompareString(col, "hasMaterialComponent"))
                has_material_component = argv[i];
            else if (SafeCompareString(col, "materialComponent"))
                material_component = argv[i];
            else if (SafeCompareString(col, "range"))
                range = argv[i];
            else if (SafeCompareString(col, "duration"))
                duration = argv[i];
            else if (SafeCompareString(col, "time"))
                time = argv[i];
            else if (SafeCompareString(col, "school"))
                school = argv[i];
            else if (SafeCompareString(col, "level"))
                level = std::stoi(argv[i]);
            else if (SafeCompareString(col, "keywords"))
                keywords = argv[i];
        }
    }

    Spell::Spell(tinyxml2::XMLElement* node): SQObject(Type::Spell, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (child->GetText())
                {
                    const std::string tmp = child->GetText();
                    classSupport = (tmp.size() > 0) ? tmp : "All";
                }
            }
            else
            {
                LogWarn("Unexpected spell child: {} for spell {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }
    
    std::string Spell::GetReadFormat() const
    {
        LogError("ReadFormat called for Spell called but not implemented");
        return "(id, name, description, short_description, type, isRitual, "
                "isConcentration, hasVerbalComponent, hasSomanticComponent, "
                "hasMaterialComponent, materialComponent, range, duration, "
                "time, school, level, keywords)";
    }
    std::string Spell::GetWriteFormat() const
    {
        LogError("WriteFormat called for Spell called but not implemented");
        return "(name, description, short_description, type, isRitual, "
                "isConcentration, hasVerbalComponent, hasSomanticComponent, "
                "hasMaterialComponent, materialComponent, range, duration, "
                "time, school, level, keywords)";
    }

    
    Factory::Maptype Spell::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::ISRITUAL,              &is_ritual},
            {Setter::ISCONCENTRATION,       &is_concentration},
            {Setter::HASMATERIALCOMPONENT,  &has_material_component},
            {Setter::HASSOMATICCOMPONENT,   &has_somantic_component},
            {Setter::HASVERBALCOMPONENT,    &has_verbal_component},
            {Setter::MATERIALCOMPONENT,     &material_component},
            {Setter::RANGE,                 &range},
            {Setter::DURATION,              &duration},
            {Setter::TIME,                  &time},
            {Setter::SCHOOL,                &school},
            {Setter::LEVEL,                 &level},
            {Setter::KEYWORDS,              &keywords}
        };
    }

    /// -------------------- DEITY --------------------

    Deity::Deity(int argc, char** argv, char** colz): SQObject(Type::Deity)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::string col = colz[i];
            if (SafeCompareString(col, "id"))
                id = std::stoi(argv[i]);
            else if (SafeCompareString(col, "name"))
                name = argv[i];
            else if (SafeCompareString(col, "description"))
                description = argv[i];
            else if (SafeCompareString(col, "short_description"))
                short_description = argv[i];
            else if (SafeCompareString(col, "setting"))
                setting = argv[i];
            else if (SafeCompareString(col, "alignment"))
                alignment = argv[i];
            else if (SafeCompareString(col, "domains"))
                domains = argv[i];
            else if (SafeCompareString(col, "symbol"))
                symbol = argv[i];
            else if (SafeCompareString(col, "gender"))
                gender = argv[i];
            else if (SafeCompareString(col, "sheet_display"))
                sheet_display = std::stoi(argv[i]);
            else if (SafeCompareString(col, "sheet_alt_title"))
                sheet_alt_title = argv[i];
            else if (SafeCompareString(col, "sheet_description"))
                sheet_description = argv[i];
            else if (SafeCompareString(col, "sheet_usage"))
                sheet_usage = argv[i];
            else if (SafeCompareString(col, "sheet_action"))
                sheet_action = argv[i];
            else
                LogWarn("Unexpected column value {} in Deity {}", col, name);
        }
    }

    Deity::Deity(tinyxml2::XMLElement* node): SQObject(Type::Deity, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else
            {
                LogWarn("Unexpected deity child: {} for deity {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Deity::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SETTING, &setting},
            {Setter::ALIGNMENT, &alignment},
            {Setter::DOMAINS, &domains},
            {Setter::SYMBOL, &symbol},
            {Setter::GENDER, &gender}
        };
    }

    
    std::string Deity::GetReadFormat() const
    {
        LogError("ReadFormat called for Deity called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Deity::GetWriteFormat() const
    {
        LogError("WriteFormat called for Deity called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Language --------------------

    Language::Language(int argc, char** argv, char** colz): SQObject(Type::Language)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::string col = colz[i];
            if (SafeCompareString(col, "id"))
                id = std::stoi(argv[i]);
            else if (SafeCompareString(col, "name"))
                name = argv[i];
            else if (SafeCompareString(col, "description"))
                description = argv[i];
            else if (SafeCompareString(col, "short_description"))
                short_description = argv[i];
            else if (SafeCompareString(col, "is_standard"))
                is_standard = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_exotic"))
                is_exotic = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_monster"))
                is_monster = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_secret"))
                is_secret = std::stoi(argv[i]);
            else if (SafeCompareString(col, "speakers"))
                speakers = argv[i];
            else if (SafeCompareString(col, "script"))
                script = argv[i];
            else if (SafeCompareString(col, "supports"))
                supports = argv[i];
            else
                LogWarn("Unexpected column value {} in Language {}", col, name);
        }
    }

    Language::Language(tinyxml2::XMLElement* node): SQObject(Type::Language, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto supp = child->GetText())
                    supports = supp;
            }
            else
            {
                LogWarn("Unexpected language child: {} for language {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Language::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::STANDARD, &is_standard},
            {Setter::MONSTER, &is_monster},
            {Setter::EXOTIC, &is_exotic},
            {Setter::SECRET, &is_secret},
            {Setter::SPEAKERS, &speakers},
            {Setter::SCRIPT, &script}
        };
    }

    
    std::string Language::GetReadFormat() const
    {
        LogError("ReadFormat called for Language called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Language::GetWriteFormat() const
    {
        LogError("WriteFormat called for Language called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Language --------------------

    Source::Source(int argc, char** argv, char** colz): SQObject(Type::Source)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::string col = colz[i];
            if (SafeCompareString(col, "id"))
                id = std::stoi(argv[i]);
            else if (SafeCompareString(col, "name"))
                name = argv[i];
            else if (SafeCompareString(col, "description"))
                description = argv[i];
            else if (SafeCompareString(col, "short_description"))
                short_description = argv[i];
            else if (SafeCompareString(col, "abbreviation"))
                abbreviation = argv[i];
            else if (SafeCompareString(col, "url"))
                url = argv[i];
            else if (SafeCompareString(col, "image"))
                image = argv[i];
            else if (SafeCompareString(col, "errata"))
                errata = argv[i];
            else if (SafeCompareString(col, "author"))
                author = argv[i];
            else if (SafeCompareString(col, "author_abbreviation"))
                author_abbreviation = argv[i];
            else if (SafeCompareString(col, "author_url"))
                author_url = argv[i];
            else if (SafeCompareString(col, "release"))
                release = argv[i];
            else if (SafeCompareString(col, "information"))
                information = argv[i];
            else if (SafeCompareString(col, "is_official"))
                is_official = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_playtest"))
                is_playtest = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_core"))
                is_core = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_incomplete"))
                is_incomplete = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_homebrew"))
                is_homebrew = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_third_party"))
                is_third_party = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_supplement"))
                is_supplement = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_league"))
                is_league = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_legal"))
                is_legal = std::stoi(argv[i]);
            else if (SafeCompareString(col, "is_disabled"))
                is_disabled = std::stoi(argv[i]);
            else
                LogWarn("Unexpected column value {} in Source {}", col, name);
        }
    }

    Source::Source(tinyxml2::XMLElement* node): SQObject(Type::Source, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else
            {
                LogWarn("Unexpected source child: {} for source {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Source::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::ABBREVIATION, &abbreviation},
            {Setter::URL, &url},
            {Setter::IMAGE, &image},
            {Setter::ERRATA, &errata},
            {Setter::AUTHOR, &author},
            {Setter::AUTHORABBREVIATION, &author_abbreviation},
            {Setter::AUTHORURL, &author_url},
            {Setter::RELEASE, &release},
            {Setter::OFFICIAL, &is_official},
            {Setter::CORE, &is_core},
            {Setter::INFORMATION, &information},
            {Setter::PLAYTEST, &is_playtest},
            {Setter::INCOMPLETE, &is_incomplete},
            {Setter::HOMEBREW, &is_homebrew},
            {Setter::THIRD_PARTY, &is_third_party},
            {Setter::SUPPLEMENT, &is_supplement},
            {Setter::LEAGUE, &is_league},
            {Setter::LEGAL, &is_legal},
            {Setter::DISABLED, &is_disabled}
        };
    }

    
    std::string Source::GetReadFormat() const
    {
        LogError("ReadFormat called for Source called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Source::GetWriteFormat() const
    {
        LogError("WriteFormat called for Source called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Information --------------------

    Information::Information(int argc, char** argv, char** colz): SQObject(Type::Information)
    {
        for (int i = 0; i < argc; ++i)
        {
            std::string col = colz[i];
            if (SafeCompareString(col, "id"))
                id = std::stoi(argv[i]);
            else if (SafeCompareString(col, "name"))
                name = argv[i];
            else if (SafeCompareString(col, "description"))
                description = argv[i];
            else if (SafeCompareString(col, "short_description"))
                short_description = argv[i];
            else
                LogWarn("Unexpected column value {} in Information {}", col, name);
        }
    }

    Information::Information(tinyxml2::XMLElement* node): SQObject(Type::Information, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else
            {
                LogWarn("Unexpected information child: {} for information {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Information::GetMemberMap()
    {
        using namespace Tags;
        return {};
    }

    
    std::string Information::GetReadFormat() const
    {
        LogError("ReadFormat called for Information called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Information::GetWriteFormat() const
    {
        LogError("WriteFormat called for Information called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- FEATFEATURE --------------------

    FeatFeature::FeatFeature(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Feat_Feature)
    {
        LogError("Constructor for Feat Feature called but not implemented");
    }

    FeatFeature::FeatFeature(tinyxml2::XMLElement* node): SQObject(Type::Feat_Feature, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
            }
            else if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else
            {
                LogWarn("Unexpected FeatFeature child: {} for FeatFeature {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype FeatFeature::GetMemberMap()
    {
        using namespace Tags;
        return {};
    }

    
    std::string FeatFeature::GetReadFormat() const
    {
        LogError("ReadFormat called for Feat Feature called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string FeatFeature::GetWriteFormat() const
    {
        LogError("WriteFormat called for Feat Feature called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Feat --------------------

    Feat::Feat(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Feat)
    {
        LogError("Constructor for Feat called but not implemented");
    }

    Feat::Feat(tinyxml2::XMLElement* node): SQObject(Type::Feat, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "prerequisite"))
            {
                if (auto* tmp = child->GetText())
                    prerequisite = tmp;
            }
            else if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else
            {
                LogWarn("Unexpected Feat child: {} for Feat {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Feat::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::ALLOW_DUPLICATE, &allow_duplicate}
        };
    }

    
    std::string Feat::GetReadFormat() const
    {
        LogError("ReadFormat called for Feat called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Feat::GetWriteFormat() const
    {
        LogError("WriteFormat called for Feat called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Companion --------------------

    Companion::Companion(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Companion)
    {
        LogError("Constructor for Companion called but not implemented");
    }

    Companion::Companion(tinyxml2::XMLElement* node): SQObject(Type::Companion, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
            }
            else
            {
                LogWarn("Unexpected Companion child: {} for Companion {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Companion::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::STRENGTH, &strength},
            {Setter::DEXTERITY, &dexterity},
            {Setter::CONSTITUTION, &constitution},
            {Setter::INTELLIGENCE, &intelligence},
            {Setter::WISDOM, &wisdom},
            {Setter::CHARISMA, &charisma},
            {Setter::AC, &ac},
            {Setter::HP, &hp},
            {Setter::SPEED, &speed},
            {Setter::LANGUAGES, &languages},
            {Setter::SKILLS, &skills},
            {Setter::TYPE, &beast_type},
            {Setter::SIZE, &size},
            {Setter::ALIGNMENT, &alignment},
            {Setter::CHALLENGE, &challenge},
            {Setter::ACTIONS, &actions},
            {Setter::TRAITS, &traits},
            {Setter::SENSES, &senses},
            {Setter::IMMUNITIES, &immunities},
            {Setter::CONDITIONIMMUNITIES, &conditionImmunities},
            {Setter::SAVES, &saves},
            {Setter::REACTIONS, &reactions},
            {Setter::VULNERABILITIES, &vulnerabilities},
            {Setter::RESISTANCES, &resistances}
        };
    }

    
    std::string Companion::GetReadFormat() const
    {
        LogError("ReadFormat called for Companion called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Companion::GetWriteFormat() const
    {
        LogError("WriteFormat called for Companion called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- CompanionAction --------------------

    CompanionAction::CompanionAction(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Companion_Action)
    {
        LogError("Constructor for Comanion Action called but not implemented");
    }

    CompanionAction::CompanionAction(tinyxml2::XMLElement* node): SQObject(Type::Companion_Action, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else if (SafeCompareString(child->Value(), "setter"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Companion Action child: {} for Companion Action {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype CompanionAction::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::ACTION, &action}
        };
    }

    
    std::string CompanionAction::GetReadFormat() const
    {
        LogError("ReadFormat called for Companion Action called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string CompanionAction::GetWriteFormat() const
    {
        LogError("WriteFormat called for Companion Action called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- AbilityScoreImprovement --------------------

    AbilityScoreImprovement::AbilityScoreImprovement(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Ability_Score_Improvement)
    {
        LogError("Constructor for AbilityScoreImprovement called but not implemented");
    }

    AbilityScoreImprovement::AbilityScoreImprovement(tinyxml2::XMLElement* node): SQObject(Type::Ability_Score_Improvement, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
            }
            else
            {
                LogWarn("Unexpected AbilityScoreImprovement child: {} for AbilityScoreImprovement {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype AbilityScoreImprovement::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::ALLOW_DUPLICATE, &allow_duplicate}
        };
    }

    
    std::string AbilityScoreImprovement::GetReadFormat() const
    {
        LogError("ReadFormat called for AbilityScoreImprovement called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string AbilityScoreImprovement::GetWriteFormat() const
    {
        LogError("WriteFormat called for AbilityScoreImprovement called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Rule --------------------

    Rule::Rule(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Rule)
    {
        LogError("Constructor for Rule called but not implemented");
    }

    Rule::Rule(tinyxml2::XMLElement* node): SQObject(Type::Rule, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else
            {
                LogWarn("Unexpected Rule child: {} for Rule {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Rule::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::KEYWORDS, &keywords}
        };
    }

    
    std::string Rule::GetReadFormat() const
    {
        LogError("ReadFormat called for Rule called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Rule::GetWriteFormat() const
    {
        LogError("WriteFormat called for Rule called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Option --------------------

    Option::Option(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Option)
    {
        LogError("Constructor for Rule called but not implemented");
    }

    Option::Option(tinyxml2::XMLElement* node): SQObject(Type::Option, node), SheetDisplay(node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Option child: {} for Option {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Option::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Option::GetReadFormat() const
    {
        LogError("ReadFormat called for Option called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Option::GetWriteFormat() const
    {
        LogError("WriteFormat called for Option called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- OTHER --------------------

    SQObject* CreateNewObjectFromType(Creator::Entity::Type type, int argc, char** argv, char** colz)
    {
        switch(type)
        {
            case Type::None: 
                return nullptr;
                break;
            case Type::General: 
                return nullptr;
                break;
            case Type::Archetype_Feature: 
                return nullptr;
                break;
            case Type::Archetype: 
                return nullptr;
                break;
            case Type::Class_Feature: 
                return nullptr;
                break;
            case Type::Spell:
                return new Spell(argc, argv, colz);
                break;
            case Type::Race: 
                return nullptr;
                break;
            case Type::Race_Variant:
                return nullptr;
                break;
            case Type::Sub_Race: 
                return nullptr;
                break;
            case Type::Magic_Item:
                return nullptr;
                break;
            case Type::Option: 
                return nullptr;
                break;
            case Type::Armor: 
                return nullptr;
                break;
            case Type::Item: 
                return nullptr;
                break;
            case Type::Weapon: 
                return nullptr;
                break;
            case Type::Class: 
                return nullptr;
                break;
            case Type::Ability_Score_Improvement: 
                return new AbilityScoreImprovement(argc, argv, colz);
                break;
            case Type::Rule:
                return new Rule(argc, argv, colz);
                break;
            case Type::Source: 
                return new Source(argc, argv, colz);
                break;
            case Type::Language: 
                return new Language(argc, argv, colz);
                break;
            case Type::Companion: 
                return new Companion(argc, argv, colz);
                break;
            case Type::Companion_Action:
                return new CompanionAction(argc, argv, colz);
                break;
            case Type::Background: 
                return nullptr;
                break;
            case Type::Deity: 
                return new Deity(argc, argv, colz);
                break;
            case Type::Feat: 
                return new Feat(argc, argv, colz);
                break;
            case Type::Feat_Feature: 
                return new FeatFeature(argc, argv, colz);
                break;
            case Type::Information:
                return new Information(argc, argv, colz);
                break;
            default:
                return nullptr;
        }
        return nullptr;
    }

    /// -------------------- IO --------------------

    
    
    std::ostream& Spell::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "is_ritual: " << is_ritual << '\n'
            << "is_concentration: " << is_concentration << '\n'
            << "has_verbal_component: " << has_verbal_component << '\n'
            << "has_somantic_component: " << has_somantic_component << '\n'
            << "has_material_component: " << has_material_component << '\n'
            << "material_component: " << material_component << '\n'
            << "range: " << range << '\n'
            << "duration: " << duration << '\n'
            << "time: " << time << '\n'
            << "school: " << school << '\n'
            << "level: " << level << '\n'
            << "keywords: " << keywords << '\n'
            << "Class support: " << classSupport << '\n';
        return os;
    }
    std::ostream& Deity::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "setting: " << setting << '\n'
            << "alignment: " << alignment << '\n'
            << "domains: " << domains << '\n'
            << "symbol: " << symbol << '\n'
            << "gender: " << gender << '\n';
        SheetDisplay::WriteToStream(os);
        return os;
    }

    std::ostream& Language::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "is_standard: " << is_standard << '\n'
            << "is_monster: " << is_monster << '\n'
            << "is_exotic: " << is_exotic << '\n'
            << "is_secret: " << is_secret << '\n'
            << "speakers: " << speakers << '\n'
            << "script: " << script << '\n'
            << "supports: " << supports << '\n';
        return os;
    }

    std::ostream& Source::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "abbreviation: " << abbreviation << '\n'
            << "url: " << url << '\n'
            << "image: " << image << '\n'
            << "errata: " << errata << '\n'
            << "author: " << author << '\n'
            << "author_abbreviation: " << author_abbreviation << '\n'
            << "author_url: " << author_url << '\n'
            << "release: " << release << '\n'
            << "is_official: " << is_official << '\n'
            << "is_core: " << is_core << '\n'
            << "is_playtest: " << is_playtest << '\n'
            << "is_incomplete: " << is_incomplete << '\n'
            << "is_homebrew: " << is_homebrew << '\n'
            << "is_third_party: " << is_third_party << '\n'
            << "is_supplement: " << is_supplement << '\n'
            << "is_league: " << is_league << '\n'
            << "is_legal: " << is_legal << '\n'
            << "information: " << information << '\n'
            << "is_disabled: " << is_disabled << '\n';
        return os;
    }

    std::ostream& Information::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        return os;
    }

    std::ostream& FeatFeature::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "requirements: " << requirements << '\n'
            << rules;
        return os;
    }

    std::ostream& Feat::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "prerequisite: " << prerequisite << '\n'
            << "allow duplicate: " << allow_duplicate << '\n';
        os  << rules;
        return os;
    }

    std::ostream& Companion::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "requirements: " << requirements << '\n'
            << rules;
        CharacterBase::WriteToStream(os);
        os  << rules;
        return os;
    }

    std::ostream& CompanionAction::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "action: " << action << '\n'
            << rules << '\n';
        return os;
    }

    std::ostream& AbilityScoreImprovement::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "supports: " << supports << '\n'
            << "allow_duplicate: " << allow_duplicate << '\n';
        SheetDisplay::WriteToStream(os);
        os << rules;
        return os;
    }

    std::ostream& Rule::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os << "keywords: " << keywords << '\n';
        return os;
    }
    std::ostream& Option::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os << rules << '\n';
        return os;
    }
}