#pragma once
#include <string>
#include <vector>

namespace dict {

// Lower-cases ASCII and Cyrillic (UTF-8) text. Other bytes are left untouched.
std::string toLower(const std::string& s);
std::string trim(const std::string& s);
std::vector<std::string> split(const std::string& s, char delimiter);
std::string join(const std::vector<std::string>& parts, const std::string& separator);

}  // namespace dict
