#include "text_utils.hpp"

#include <cctype>

namespace dict {

std::string toLower(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (std::size_t i = 0; i < s.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(s[i]);
        if (c < 0x80) {
            out += static_cast<char>(std::tolower(c));
        } else if (c == 0xD0 && i + 1 < s.size()) {
            // Cyrillic capitals live in U+0401 and U+0410..U+042F (lead byte 0xD0).
            const unsigned char d = static_cast<unsigned char>(s[++i]);
            if (d >= 0x90 && d <= 0x9F) {          // А-П -> а-п
                out += static_cast<char>(0xD0);
                out += static_cast<char>(d + 0x20);
            } else if (d >= 0xA0 && d <= 0xAF) {   // Р-Я -> р-я
                out += static_cast<char>(0xD1);
                out += static_cast<char>(d - 0x20);
            } else if (d == 0x81) {                // Ё -> ё
                out += static_cast<char>(0xD1);
                out += static_cast<char>(0x91);
            } else {
                out += static_cast<char>(c);
                out += static_cast<char>(d);
            }
        } else {
            out += static_cast<char>(c);
        }
    }
    return out;
}

std::string trim(const std::string& s) {
    std::size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    return s.substr(b, e - b);
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> parts;
    std::size_t start = 0;
    while (true) {
        const std::size_t pos = s.find(delimiter, start);
        if (pos == std::string::npos) {
            parts.push_back(s.substr(start));
            break;
        }
        parts.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    return parts;
}

std::string join(const std::vector<std::string>& parts, const std::string& separator) {
    std::string out;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i) out += separator;
        out += parts[i];
    }
    return out;
}

}  // namespace dict
