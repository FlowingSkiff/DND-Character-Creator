#pragma once
#include <string>
#include <unordered_map>
#include "Base/SQBaseObject.hpp"
#include <memory>
namespace Creator {
/**
     * @brief Formats an input description if required. Values formated like {{}} are replaced and description divs following 
     *        <div element="ID_###"> are inserted. Formats the desc as
     *        <h1>$name<h1>
     *        <hr>
     *        $desc
     *          
     *        Recursively called for nested element divs
     *  
     * @param name Name of the item/thing to be displayed
     * @param desc Description to be formatted
     * @param id_map global map with ID being the key
     * @return std::string formatted description
     */
std::string FormatDescription(const std::string& name, std::string desc, const std::unordered_map<std::string, std::shared_ptr<Entity::SQObject>>& id_map, const int& level = 1);
}// namespace Creator