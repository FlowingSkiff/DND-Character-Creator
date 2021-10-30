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
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
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
            {Setter::KEYWORDS,              &keywords},
            {Setter::SHORT,                 &short_description},
            {Setter::SCHOOLADDITION,        &school_addition},
            {Setter::HASSOMATICCOMPONENTADDITION, &has_somantic_component_addition}
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
            {Setter::GENDER, &gender},
            {Setter::SHORT, &short_description}
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
            {Setter::SCRIPT, &script},
            {Setter::SHORT, &short_description}
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
            {Setter::DISABLED, &is_disabled},
            {Setter::SHORT, &short_description}
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
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                SetterFactory(GetMemberMap(), setter);
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
        return {
            {Setter::SHORT, &short_description}
        };
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
        return {
            {Setter::SHORT, &short_description}
        };
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
            {Setter::ALLOW_DUPLICATE, &allow_duplicate},
            {Setter::SHORT, &short_description}
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
            {Setter::RESISTANCES, &resistances},
            {Setter::SHORT, &short_description}
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
            {Setter::ACTION, &action},
            {Setter::SHORT, &short_description}
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
            {Setter::ALLOW_DUPLICATE, &allow_duplicate},
            {Setter::SHORT, &short_description}
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
            {Setter::KEYWORDS, &keywords},
            {Setter::SHORT, &short_description}
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

    /// -------------------- Background --------------------

    Background::Background(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Background)
    {
        LogError("Constructor for Background called but not implemented");
    }

    Background::Background(tinyxml2::XMLElement* node): SQObject(Type::Background, node), SheetDisplay(node)
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
                LogWarn("Unexpected Background child: {} for Background {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Background::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Background::GetReadFormat() const
    {
        LogError("ReadFormat called for Background called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Background::GetWriteFormat() const
    {
        LogError("WriteFormat called for Background called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- BackgroundFeature --------------------

    BackgroundFeature::BackgroundFeature(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Background_Feature)
    {
        LogError("Constructor for BackgroundFeature called but not implemented");
    }

    BackgroundFeature::BackgroundFeature(tinyxml2::XMLElement* node): SQObject(Type::Background_Feature, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
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
                LogWarn("Unexpected BackgroundFeature child: {} for BackgroundFeature {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype BackgroundFeature::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string BackgroundFeature::GetReadFormat() const
    {
        LogError("ReadFormat called for BackgroundFeature called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string BackgroundFeature::GetWriteFormat() const
    {
        LogError("WriteFormat called for BackgroundFeature called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- ClassFeature --------------------

    ClassFeature::ClassFeature(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Class_Feature)
    {
        LogError("Constructor for ClassFeature called but not implemented");
    }

    ClassFeature::ClassFeature(tinyxml2::XMLElement* node): SQObject(Type::Class_Feature, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
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
            else if (SafeCompareString(child->Value(), "prerequisite"))
            {
                if (auto* tmp = child->GetText())
                    prerequisite = tmp;
            }
            else
            {
                LogWarn("Unexpected ClassFeature child: {} for ClassFeature {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype ClassFeature::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::ALLOW_DUPLICATE, &allow_duplicate},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability}
        };
    }

    
    std::string ClassFeature::GetReadFormat() const
    {
        LogError("ReadFormat called for ClassFeature called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string ClassFeature::GetWriteFormat() const
    {
        LogError("WriteFormat called for ClassFeature called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- ArchetypeFeature --------------------

    ArchetypeFeature::ArchetypeFeature(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Archetype_Feature)
    {
        LogError("Constructor for ArchetypeFeature called but not implemented");
    }

    ArchetypeFeature::ArchetypeFeature(tinyxml2::XMLElement* node): SQObject(Type::Archetype_Feature, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
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
            else if (SafeCompareString(child->Value(), "prerequisite"))
            {
                if (auto* tmp = child->GetText())
                    prerequisite = tmp;
            }
            else
            {
                LogWarn("Unexpected ArchetypeFeature child: {} for ArchetypeFeature {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype ArchetypeFeature::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::ALLOW_DUPLICATE, &allow_duplicate},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability}
        };
    }

    
    std::string ArchetypeFeature::GetReadFormat() const
    {
        LogError("ReadFormat called for ArchetypeFeature called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string ArchetypeFeature::GetWriteFormat() const
    {
        LogError("WriteFormat called for ArchetypeFeature called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- RaceVariant --------------------

    RaceVariant::RaceVariant(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Race_Variant)
    {
        LogError("Constructor for RaceVariant called but not implemented");
    }

    RaceVariant::RaceVariant(tinyxml2::XMLElement* node): SQObject(Type::Race_Variant, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "requirements"))
            {
                if (auto* tmp = child->GetText())
                    requirements = tmp;
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else
            {
                LogWarn("Unexpected RaceVariant child: {} for RaceVariant {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype RaceVariant::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string RaceVariant::GetReadFormat() const
    {
        LogError("ReadFormat called for RaceVariant called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string RaceVariant::GetWriteFormat() const
    {
        LogError("WriteFormat called for RaceVariant called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- RacialTrait --------------------

    RacialTrait::RacialTrait(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Racial_Trait)
    {
        LogError("Constructor for RacialTrait called but not implemented");
    }

    RacialTrait::RacialTrait(tinyxml2::XMLElement* node): SQObject(Type::Racial_Trait, node), SheetDisplay(node)
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
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
            }
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
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
            else if (SafeCompareString(child->Value(), "prerequisite"))
            {
                if (auto* tmp = child->GetText())
                    prerequisite = tmp;
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else
            {
                LogWarn("Unexpected RaceVariant child: {} for RaceVariant {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype RacialTrait::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability}
        };
    }

    
    std::string RacialTrait::GetReadFormat() const
    {
        LogError("ReadFormat called for RacialTrait called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string RacialTrait::GetWriteFormat() const
    {
        LogError("WriteFormat called for RacialTrait called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- SubRace --------------------

    SubRace::SubRace(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Sub_Race)
    {
        LogError("Constructor for SubRace called but not implemented");
    }

    SubRace::SubRace(tinyxml2::XMLElement* node): SQObject(Type::Sub_Race, node), SheetDisplay(node)
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
            else
            {
                LogWarn("Unexpected SubRace child: {} for SubRace {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype SubRace::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::HEIGHT, &height},
            {Setter::HEIGHTMODIFIER, &height_modifier},
            {Setter::WEIGHT, &weight},
            {Setter::WEIGHTMODIFIER, &weight_modifier}
        };
    }

    
    std::string SubRace::GetReadFormat() const
    {
        LogError("ReadFormat called for SubRace called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string SubRace::GetWriteFormat() const
    {
        LogError("WriteFormat called for SubRace called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Archetype --------------------

    Archetype::Archetype(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Archetype)
    {
        LogError("Constructor for Archetype called but not implemented");
    }

    Archetype::Archetype(tinyxml2::XMLElement* node): SQObject(Type::Archetype, node), SheetDisplay(node)
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
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
            }
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
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
            else if (SafeCompareString(child->Value(), "prerequisite"))
            {
                if (auto* tmp = child->GetText())
                    prerequisite = tmp;
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else
            {
                LogWarn("Unexpected Archetype child: {} for Archetype {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Archetype::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability},
            {Setter::SOURCEURL, &source_url},
            {Setter::OVERRIDE, &is_override}
        };
    }

    
    std::string Archetype::GetReadFormat() const
    {
        LogError("ReadFormat called for Archetype called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Archetype::GetWriteFormat() const
    {
        LogError("WriteFormat called for Archetype called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Race --------------------

    Race::Race(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Race)
    {
        LogError("Constructor for Race called but not implemented");
    }

    Race::Race(tinyxml2::XMLElement* node): SQObject(Type::Race, node), SheetDisplay(node)
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
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
            }
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Race child: {} for Race {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Race::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability},
            {Setter::NAMES, &names},
            {Setter::NAMES_FORMAT, &names_format},
            {Setter::HEIGHT, &height},
            {Setter::WEIGHT, &weight},
            {Setter::HEIGHTMODIFIER, &height_modifier},
            {Setter::WEIGHTMODIFIER, &weight_modifier}
        };
    }

    
    std::string Race::GetReadFormat() const
    {
        LogError("ReadFormat called for Race called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Race::GetWriteFormat() const
    {
        LogError("WriteFormat called for Race called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Class --------------------

    Class::Class(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Class)
    {
        LogError("Constructor for Class called but not implemented");
    }

    Class::Class(tinyxml2::XMLElement* node): SQObject(Type::Class, node), SheetDisplay(node)
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
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
            }
            else if (SafeCompareString(child->Value(), "multiclass"))
            {
                multiclass_id = child->Attribute("id");
                auto multiclass_child = child->FirstChildElement();
                while (multiclass_child)
                {
                    if (SafeCompareString(multiclass_child->Value(), "rules"))
                    {
                        multiclass_rules = GenerateRules(multiclass_child->FirstChildElement());
                    }
                    else if (SafeCompareString(multiclass_child->Value(), "requirements"))
                    {
                        if (auto* tmp = multiclass_child->GetText())
                            multiclass_requirements = tmp;
                    }
                    else if (SafeCompareString(multiclass_child->Value(), "prerequisite"))
                    {
                        if (auto* tmp = multiclass_child->GetText())
                            multiclass_prerequisite = tmp;
                    }
                    else if (SafeCompareString(multiclass_child->Value(), "setters"))
                    {
                        auto setter = multiclass_child->FirstChildElement();
                        SetterFactory(GetMemberMap(), setter);
                    }
                    multiclass_child = multiclass_child->NextSiblingElement();
                }
            }
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Class child: {} for Class {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Class::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description},
            {Setter::SPELLCASTINGCLASS, &spellcasting_name},
            {Setter::SPELLCASTINGABILITY, &spellcasting_ability},
            {Setter::HD, &hd},
            {Setter::SOURCEURL, &source_url},
            {Setter::MULTICLASS_PROFICIENCIES, &multiclass_proficiencies}
        };
    }

    
    std::string Class::GetReadFormat() const
    {
        LogError("ReadFormat called for Class called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Class::GetWriteFormat() const
    {
        LogError("WriteFormat called for Class called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Item --------------------

    Item::Item(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Item)
    {
        LogError("Constructor for Item called but not implemented");
    }

    Item::Item(tinyxml2::XMLElement* node): SQObject(Type::Item, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
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
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else if (SafeCompareString(child->Value(), "extract"))
            {
                for (auto extract_child = child->FirstChildElement();
                     extract_child; extract_child = extract_child->NextSiblingElement())
                {
                    extract_item_ids.emplace_back(extract_child->GetText());
                }
            }
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else
            {
                LogWarn("Unexpected Item child: {} for Item {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Item::GetMemberMap()
    {
        using namespace Tags;
        Factory::Maptype tmp = {
            {Setter::CONTAINER, &container},
            {Setter::SHORT, &short_description}
        };
        return ItemBase::ModifySetMap(tmp);
    }

    
    std::string Item::GetReadFormat() const
    {
        LogError("ReadFormat called for Item called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Item::GetWriteFormat() const
    {
        LogError("WriteFormat called for Item called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Weapon --------------------

    Weapon::Weapon(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Weapon)
    {
        LogError("Constructor for Weapon called but not implemented");
    }

    Weapon::Weapon(tinyxml2::XMLElement* node): SQObject(Type::Weapon, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
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
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
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
            else
            {
                LogWarn("Unexpected Weapon child: {} for Weapon {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Weapon::GetMemberMap()
    {
        using namespace Tags;
        Factory::Maptype tmp {
            {Setter::SHORT, &short_description},
            {Setter::DAMAGE, &damage},
            {Setter::DAMAGETYPE, &damage_type},
            {Setter::RANGE, &range},
            {Setter::VERSATILE, &versatile},
            {Setter::RELOAD, &reload}
        };
        return ItemBase::ModifySetMap(tmp);
    }

    
    std::string Weapon::GetReadFormat() const
    {
        LogError("ReadFormat called for Weapon called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Weapon::GetWriteFormat() const
    {
        LogError("WriteFormat called for Weapon called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Weapon --------------------

    Armor::Armor(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Armor)
    {
        LogError("Constructor for Armor called but not implemented");
    }

    Armor::Armor(tinyxml2::XMLElement* node): SQObject(Type::Armor, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
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
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
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
                LogWarn("Unexpected Armor child: {} for Armor {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Armor::GetMemberMap()
    {
        using namespace Tags;
        Factory::Maptype tmp {
            {Setter::SHORT, &short_description},
            {Setter::ARMOR, &armor},
            {Setter::ARMORCLASS, &armor_class},
            {Setter::STRENGTH, &strength},
            {Setter::STEALTH, &stealth}
        };
        return ItemBase::ModifySetMap(tmp);
    }

    
    std::string Armor::GetReadFormat() const
    {
        LogError("ReadFormat called for Armor called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Armor::GetWriteFormat() const
    {
        LogError("WriteFormat called for Armor called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- MagicItem --------------------

    MagicItem::MagicItem(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Magic_Item)
    {
        LogError("Constructor for MagicItem called but not implemented");
    }

    MagicItem::MagicItem(tinyxml2::XMLElement* node): SQObject(Type::Magic_Item, node)
    {
        auto child = node->FirstChildElement();
        while (child)
        {
            if (SafeCompareString(child->Value(), "description"))
            {
                description = ReplaceSpecialInString(DescriptionToString(child));
            }
            else if (SafeCompareString(child->Value(), "sheet"))
            {
                BuildSheetAttributes(child);
            }
            else if (SafeCompareString(child->Value(), "setters"))
            {
                auto setter = child->FirstChildElement();
                const auto old_spellcasting_ability = spellcasting_ability;
                const auto old_spellcasting_name = spellcasting_name; 
                SetterFactory(GetMemberMap(), setter);
                if (old_spellcasting_ability != spellcasting_ability ||
                    old_spellcasting_name != spellcasting_name)
                    is_spellcasting = true;
            }
            else if (SafeCompareString(child->Value(), "compendium"))
            {
                display_in_compendium = child->BoolAttribute("display");
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
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else
            {
                LogWarn("Unexpected MagicItem child: {} for MagicItem {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype MagicItem::GetMemberMap()
    {
        using namespace Tags;
        Factory::Maptype tmp {
            {Setter::SHORT, &short_description},
            {Setter::ARMOR, &armor},
            {Setter::WEAPON, &weapon},
            {Setter::NAME_FORMAT, &name_format},
            {Setter::ATTUNEMENT, &attunement},
            {Setter::CURSED, &cursed},
            {Setter::TYPEADDITION, &type_addition},
            {Setter::ENHANCEMENT, &enhancement},
            {Setter::CHARGES, &charges},
            {Setter::ATTUNEMENTADDITION, &attunement_addition},
            {Setter::STRENGTH, &strength},
            {Setter::STEALTH, &stealth},
            {Setter::RANGE, &range},
            {Setter::DAMAGE, &damage},
            {Setter::EQUIPPABLE, &is_equippable},
            {Setter::STASH, &is_stash},
            {Setter::STASHLB, &stash_weight},
            {Setter::STASHWEIGHTLESS, &is_stash_weightless},
            {Setter::SUPPORTS, &set_supports},
            {Setter::COSTOVERRIDE, &cost_override},
            {Setter::DAMAGETYPE, &damage_type}
        };
        return ItemBase::ModifySetMap(tmp);
    }

    
    std::string MagicItem::GetReadFormat() const
    {
        LogError("ReadFormat called for MagicItem called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string MagicItem::GetWriteFormat() const
    {
        LogError("WriteFormat called for MagicItem called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Append --------------------

    Append::Append(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Append)
    {
        LogError("Constructor for Append called but not implemented");
    }

    Append::Append(tinyxml2::XMLElement* node): SQObject(Type::Append)
    {
        auto att = node->Attribute("id");
        if (att)
            id = att;
        else
            LogError("Expected some id for append");
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
            else
            {
                LogWarn("Unexpected Append child: {} for Append", child->Value());
            }
            child = child->NextSiblingElement();
        }
    }

    std::string Append::GetReadFormat() const
    {
        LogError("ReadFormat called for Append called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Append::GetWriteFormat() const
    {
        LogError("WriteFormat called for Append called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- CompanionTrait --------------------

    CompanionTrait::CompanionTrait(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Companion_Trait)
    {
        LogError("Constructor for CompanionTrait called but not implemented");
    }

    CompanionTrait::CompanionTrait(tinyxml2::XMLElement* node): SQObject(Type::Companion_Trait, node), SheetDisplay(node)
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
                LogWarn("Unexpected CompanionTrait child: {} for CompanionTrait {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype CompanionTrait::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string CompanionTrait::GetReadFormat() const
    {
        LogError("ReadFormat called for CompanionTrait called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string CompanionTrait::GetWriteFormat() const
    {
        LogError("WriteFormat called for CompanionTrait called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- CompanionReaction --------------------

    CompanionReaction::CompanionReaction(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Companion_Reaction)
    {
        LogError("Constructor for CompanionReaction called but not implemented");
    }

    CompanionReaction::CompanionReaction(tinyxml2::XMLElement* node): SQObject(Type::Companion_Reaction, node), SheetDisplay(node)
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
                LogWarn("Unexpected CompanionReaction child: {} for CompanionReaction {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype CompanionReaction::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string CompanionReaction::GetReadFormat() const
    {
        LogError("ReadFormat called for CompanionReaction called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string CompanionReaction::GetWriteFormat() const
    {
        LogError("WriteFormat called for CompanionReaction called but not implemented");
        return "(name, description, short_description)";
    }


    /// -------------------- Support --------------------

    Support::Support(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Support)
    {
        LogError("Constructor for Support called but not implemented");
    }

    Support::Support(tinyxml2::XMLElement* node): SQObject(Type::Support, node)
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
                LogWarn("Unexpected Support child: {} for Support {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Support::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Support::GetReadFormat() const
    {
        LogError("ReadFormat called for Support called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Support::GetWriteFormat() const
    {
        LogError("WriteFormat called for Support called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- WeaponProperty --------------------

    WeaponProperty::WeaponProperty(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Weapon_Property)
    {
        LogError("Constructor for WeaponProperty called but not implemented");
    }

    WeaponProperty::WeaponProperty(tinyxml2::XMLElement* node): SQObject(Type::Weapon_Property, node)
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
                LogWarn("Unexpected WeaponProperty child: {} for WeaponProperty {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype WeaponProperty::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string WeaponProperty::GetReadFormat() const
    {
        LogError("ReadFormat called for WeaponProperty called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string WeaponProperty::GetWriteFormat() const
    {
        LogError("WriteFormat called for WeaponProperty called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Proficiency --------------------

    Proficiency::Proficiency(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Proficiency)
    {
        LogError("Constructor for Proficiency called but not implemented");
    }

    Proficiency::Proficiency(tinyxml2::XMLElement* node): SQObject(Type::Proficiency, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Proficiency child: {} for Proficiency {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Proficiency::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Proficiency::GetReadFormat() const
    {
        LogError("ReadFormat called for Proficiency called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Proficiency::GetWriteFormat() const
    {
        LogError("WriteFormat called for Proficiency called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- BackgroundVariant --------------------

    BackgroundVariant::BackgroundVariant(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Background_Variant)
    {
        LogError("Constructor for BackgroundVariant called but not implemented");
    }

    BackgroundVariant::BackgroundVariant(tinyxml2::XMLElement* node): SQObject(Type::Background_Variant, node), SheetDisplay(node)
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
            else if (SafeCompareString(child->Value(), "supports"))
            {
                if (auto* tmp = child->GetText())
                    supports = tmp;
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected BackgroundVariant child: {} for BackgroundVariant {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype BackgroundVariant::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string BackgroundVariant::GetReadFormat() const
    {
        LogError("ReadFormat called for BackgroundVariant called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string BackgroundVariant::GetWriteFormat() const
    {
        LogError("WriteFormat called for BackgroundVariant called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Grants --------------------

    Grants::Grants(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Grants)
    {
        LogError("Constructor for BackgroundVariant called but not implemented");
    }

    Grants::Grants(tinyxml2::XMLElement* node): SQObject(Type::Grants, node)
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
            else if (SafeCompareString(child->Value(), "spellcasting"))
            {
                SpellcastingBase::Construct(child);
            }
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Grants child: {} for Grants {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Grants::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Grants::GetReadFormat() const
    {
        LogError("ReadFormat called for Grants called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Grants::GetWriteFormat() const
    {
        LogError("WriteFormat called for Grants called but not implemented");
        return "(name, description, short_description)";
    }


    /// -------------------- Internal --------------------

    Internal::Internal(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Internal)
    {
        LogError("Constructor for BackgroundVariant called but not implemented");
    }

    Internal::Internal(tinyxml2::XMLElement* node): SQObject(Type::Internal, node)
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
                LogWarn("Unexpected Internal child: {} for Internal {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Internal::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Internal::GetReadFormat() const
    {
        LogError("ReadFormat called for Internal called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Internal::GetWriteFormat() const
    {
        LogError("WriteFormat called for Internal called but not implemented");
        return "(name, description, short_description)";
    }

    /// -------------------- Dragonmark --------------------

    Dragonmark::Dragonmark(int /*argc*/, char** /*argv*/, char** /*colz*/): SQObject(Type::Dragonmark)
    {
        LogError("Constructor for BackgroundVariant called but not implemented");
    }

    Dragonmark::Dragonmark(tinyxml2::XMLElement* node): SQObject(Type::Dragonmark, node)
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
            else if (SafeCompareString(child->Value(), "rules"))
            {
                rules = GenerateRules(child->FirstChildElement());
            }
            else
            {
                LogWarn("Unexpected Dragonmark child: {} for Dragonmark {}", child->Value(), node->Attribute("name"));
            }
            child = child->NextSiblingElement();
        }
    }

    Factory::Maptype Dragonmark::GetMemberMap()
    {
        using namespace Tags;
        return {
            {Setter::SHORT, &short_description}
        };
    }

    
    std::string Dragonmark::GetReadFormat() const
    {
        LogError("ReadFormat called for Dragonmark called but not implemented");
        return "(id, name, description, short_description)";
    }
    std::string Dragonmark::GetWriteFormat() const
    {
        LogError("WriteFormat called for Dragonmark called but not implemented");
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
                return new ArchetypeFeature(argc, argv, colz);
                break;
            case Type::Archetype: 
                return new Archetype(argc, argv, colz);
                break;
            case Type::Class_Feature: 
                return new ClassFeature(argc, argv, colz);
                break;
            case Type::Spell:
                return new Spell(argc, argv, colz);
                break;
            case Type::Race: 
                return new Race(argc, argv, colz);
                break;
            case Type::Race_Variant:
                return new RaceVariant(argc, argv, colz);
                break;
            case Type::Racial_Trait:
                return new RacialTrait(argc, argv, colz);
                break;
            case Type::Sub_Race: 
                return new SubRace(argc, argv, colz);
                break;
            case Type::Magic_Item:
                return nullptr;
                break;
            case Type::Option: 
                return new Option(argc, argv, colz);
                break;
            case Type::Armor: 
                return new Armor(argc, argv, colz);
                break;
            case Type::Item: 
                return new Item(argc, argv, colz);
                break;
            case Type::Weapon: 
                return new Weapon(argc, argv, colz);
                break;
            case Type::Class: 
                return new Class(argc, argv, colz);
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
                return new Background(argc, argv, colz);
                break;
            case Type::Background_Feature:
                return new BackgroundFeature(argc, argv, colz);
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
    std::ostream& Background::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os << rules << '\n';
        return os;
    }
    std::ostream& BackgroundFeature::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "supports: " << supports << '\n'
            << rules;
        return os;
    }
    std::ostream& ClassFeature::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "supports: " << supports << '\n'
            << "prerequisites: " << prerequisite << '\n'
            << rules;
        return os;
    }
    std::ostream& ArchetypeFeature::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "supports: " << supports << '\n'
            << "prerequisites: " << prerequisite << '\n'
            << rules;
        return os;
    }
    std::ostream& RaceVariant::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "requirements: " << requirements << '\n'
            << rules;
        return os;
    }
    std::ostream& RacialTrait::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "requirements: " << requirements << '\n'
            << "prerequisite: " << prerequisite << '\n'
            << rules;
        return os;
    }
    std::ostream& SubRace::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "height: " << height << '\n'
            << "weight: " << weight << '\n'
            << "height_modifier: " << height_modifier << '\n'
            << "weight_modifier: " << weight_modifier << '\n'
            << rules;
        return os;
    }
    std::ostream& Archetype::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "supports: " << supports << '\n'
            << "requirements: " << requirements << '\n'
            << "prerequisite: " << prerequisite << '\n'
            << "source_url: " << source_url << '\n'
            << "is_override: " << is_override << '\n'
            << rules;
        return os;
    }
    std::ostream& Race::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "names_format: " <<  names_format << '\n'
            << "height: " <<  height << '\n'
            << "weight: " <<  weight << '\n';

        for (const auto& p : names)
            os << p << '\n';
        os  << rules;
        return os;
    }
    std::ostream& Class::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "hd: " << hd << '\n'
            << "source url: " << source_url << '\n';
        os  << rules;
        os  << "---Muliclass---\n"
            << "multiclass_id: " << multiclass_id << '\n'
            << "multiclass_prerequisite: " << multiclass_prerequisite << '\n'
            << "multiclass_requirements: " << multiclass_requirements << '\n'
            << "multiclass_proficiencies: " << multiclass_proficiencies << '\n'
            << "multiclass_rules: " << multiclass_rules << '\n';
        os  << multiclass_rules;
        return os;
    }

    std::ostream& Item::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        ItemBase::WriteToStream(os);
        os  << "container: " << container << '\n';
        os  << rules;
        if (extract_item_ids.size() > 0)
        {
            os << "Extracts: ---\n";
            for (const auto& s : extract_item_ids)
                os << s << '\n';
        }
        return os;
    }
    std::ostream& Weapon::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        ItemBase::WriteToStream(os);
        os  << "damage: " << damage << '\n'
            << "damage type: " << damage_type << '\n'
            << "range: " << range << '\n'
            << "versatile: " << versatile << '\n'
            << "reload: " << reload << '\n';
        os << rules;
        return os;
    }

    std::ostream& Armor::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        ItemBase::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "armor: " << armor << '\n'
            << "armor_class: " << armor_class << '\n'
            << "strength: " << strength << '\n'
            << "stealth: " << stealth << '\n';
        os << rules;
        return os;
    }
    std::ostream& MagicItem::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        ItemBase::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "equippable: " << is_equippable << '\n'
            << "armor: " << armor << '\n'
            << "enhancement: " << enhancement << '\n'
            << "name_format: " << name_format << '\n'
            << "type_addition: " << type_addition << '\n'
            << "weapon: " << weapon << '\n'
            << "attunement: " << attunement << '\n'
            << "attunement addition: " << attunement_addition << '\n'
            << "charges: " << charges << '\n'
            << "cursed: " << cursed << '\n'
            << "damage: " << damage << '\n'
            << "range: " << range << '\n'
            << "strength: " << strength << '\n'
            << "stealth: " << stealth << '\n'
            << "is_stash: " << is_stash << '\n'
            << "stash_weight: " << stash_weight << '\n'
            << "is_stash_weightless: " << is_stash_weightless << '\n'
            << "supports: " << supports << '\n';
        os << rules;
        return os;
    }
    std::ostream& Append::WriteToStream(std::ostream& os) const
    {
        return os << "--Append: " << id << " to " << supports << "\n";
    }
    std::ostream& CompanionTrait::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << rules;
        return os;
    }
    std::ostream& CompanionReaction::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << rules;
        return os;
    }
    std::ostream& Support::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        return os;
    }
    std::ostream& WeaponProperty::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        return os;
    }
    std::ostream& Proficiency::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "requirements: " << requirements << '\n'
            << "supports: " << supports << '\n';
        os << rules;
        return os;
    }
    std::ostream& BackgroundVariant::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SheetDisplay::WriteToStream(os);
        os  << "supports: " << supports << '\n';
        os << rules;
        return os;
    }
    std::ostream& Grants::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        SpellcastingBase::WriteToStream(os);
        os << rules;
        return os;
    }
    std::ostream& Internal::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        return os;
    }
    std::ostream& Dragonmark::WriteToStream(std::ostream& os) const
    {
        SQObject::WriteToStream(os);
        os << rules;
        return os;
    }
}