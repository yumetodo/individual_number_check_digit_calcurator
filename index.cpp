/*
License: Boost Software License 1.0
See http://www.boost.org/LICENSE_1_0.txt
Copyright © 2018 yumetodo <yume-wikijp@live.jp>
*/
#include <string>
#include <utility>
#include <numeric>
#include "register_optional.hpp"

class IndividualNumberCheckDigitCalcurator{
public:
    static std::optional<int> calcCheckDigit(const std::string& n) noexcept {
        if (11 != n.size()) return std::nullopt;
        for(auto e : n) if(e < '0' || '9' < e) return std::nullopt;
        const std::uint8_t r = std::accumulate(n.rbegin(), n.rend(), std::pair<int, int>{}, [](const auto& s, const char& e) -> std::pair<int, int>{
            return {s.first + (e - '0') * ((5 < s.second) ? s.second - 4 : s.second + 2), s.second + 1};
        }).first % 11;
        return (0 == r || 1 == r) ? 0 : 11 - r;
    }
};
EMSCRIPTEN_BINDINGS(my_class_example) {
    emscripten::class_<IndividualNumberCheckDigitCalcurator>("IndividualNumberCheckDigitCalcurator")
        .constructor<>()
        .class_function("calcCheckDigit", &IndividualNumberCheckDigitCalcurator::calcCheckDigit);
    register_optional<int>("optional<int>");
}

