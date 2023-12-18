#include "FUSReplaceReader.hpp"
#include "utils.hpp"
#include <algorithm>
#include <array>

namespace functions::repository::replace
{
    void ReplaceFunction::set(enum ReplaceElement elem, const char *string)
    {
        switch (elem)
        {
        case ReplaceElement::source:
            source.set(string);
            break;
        case ReplaceElement::pattern:
            pattern.set(string);
            break;
        case ReplaceElement::replacement:
            replacement.set(string);
        default:
            break;
        }
    }

    ReplaceElement ReplaceFunction::toElement(std::string_view name)
    {
        auto lowerCaseName = utils::toLower(name);

#define X(x)                  \
    {                         \
        #x, ReplaceElement::x \
    }
        constexpr std::array<std::pair<std::string_view, ReplaceElement>, static_cast<size_t>(ReplaceElement::unknown) - 1> lookup = {{X(functions),
                                                                                                                                       X(function),
                                                                                                                                       X(id),
                                                                                                                                       X(source),
                                                                                                                                       X(pattern),
                                                                                                                                       X(replacement)}};
#undef X
        const auto it = std::find_if(lookup.begin(), lookup.end(),
                                     [lowerCaseName](auto x)
                                     { return !strcmp(lowerCaseName.c_str(), x.first.data()); });
        return it == lookup.end() ? ReplaceElement::unknown : it->second;
    }
} //namespace functions::repository::replace