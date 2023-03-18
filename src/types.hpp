#pragma once

template<typename T>
// std::string -> T map alias
using Dictionary = std::unordered_map<std::string, T>;