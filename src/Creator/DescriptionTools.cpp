#include <Creator/DescriptionTools.hpp>
#include <fmt/format.h>

namespace Creator
{
    [[nodiscard]] static inline std::string FormatHeading(const std::string& name, const int& level = 1)
    {
        return fmt::format("<h{}>{}</h{}>\n", level, name, level);
    }

    std::string FormatDescription(const std::string& name, const std::string& desc, const std::unordered_map<std::string, std::shared_ptr<Entity::SQObject>>& id_map)
    {
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
        return fmt::format("{}{}<hr>\n<div>{}</div>{}", head, FormatHeading(name), desc, tail);
    }
    
} // Creator