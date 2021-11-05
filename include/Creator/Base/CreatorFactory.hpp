#pragma once
#include <tinyxml2.h>
#include <unordered_map>
#include "TagEnums.hpp"
#include <variant>
#include <string>

namespace Creator::Entity {
namespace Factory {
    using Booltype = bool* const;
    using Texttype = std::string* const;
    using Inttype = int* const;
    using Nametype = std::vector<std::string>* const;
    using Settype = std::variant<Inttype, Booltype, Texttype, Nametype>;
    using Maptype = std::unordered_map<Tags::Setter, Settype>;
}// namespace Factory

void SetterFactory(Factory::Maptype map, tinyxml2::XMLElement* node);
}// namespace Creator::Entity