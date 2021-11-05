#include <Creator/DescriptionTools.hpp>
#include <fmt/format.h>
#include <regex>
#include <Creator/Base/LoggingTools.hpp>

namespace Creator {
[[nodiscard]] static inline std::string FormatHeading(const std::string& name, const int& level = 1)
{
    return fmt::format("<h{}>{}</h{}>\n", level, name, level);
}

std::string FormatDescription(const std::string& name, std::string desc, const std::unordered_map<std::string, std::shared_ptr<Entity::SQObject>>& id_map, const int& level)
{
#ifdef __DEBUG
    assert(level > 0, "Bad level");
#endif
    using namespace std::string_literals;
    static const std::string head = R"..(<!DOCTYPE html>
        <html>
            <head>
                <style>
                    .indent{
                        margin-left:20px;
                    }
                </style>
            </head>
            <body>
                )..";

    static const std::string tail = R"..(
            </body>
        </html>)..";

    const std::regex element_tag_expr(R"..(<div element="([^"]*)"/>)..");
    auto div_begin = std::sregex_iterator(desc.begin(), desc.end(), element_tag_expr);
    auto div_end = std::sregex_iterator();
    for (auto i = div_begin; i != div_end; ++i)
    {
        std::smatch element_tag = *i;
        const auto start_index = desc.find(element_tag[0].str());
        const auto end_index = element_tag[0].str().size();
        const auto& item = id_map.at(element_tag[1]);
        const auto replace_str = FormatDescription(item->name, item->description, id_map, level + 1);
        desc.replace(start_index, end_index, replace_str);
    }
    if (level == 1)
        return fmt::format("{}{}<hr>\n<div>{}</div>{}", head, FormatHeading(name, level), desc, tail);
    else
        return fmt::format("<div>{}<hr>\n{}</div>", FormatHeading(name, level + 1), desc);
}

}// namespace Creator