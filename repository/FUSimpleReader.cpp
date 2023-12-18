#include "FUSimpleReader.hpp"
#include "FUReader.hpp"
#include "utils.hpp"
#include <algorithm>
#include <array>

namespace functions::repository::simple
{
    void SimpleFunction::set(enum SimpleElement elem, const char *string)
    {
        switch (elem)
        {
        case SimpleElement::source:
            source.set(string);
            break;

        default:
            break;
        }
    }

    SimpleElement SimpleFunction::toElement(std::string_view name)
    {
        auto lowerCaseName = utils::toLower(name);

#define X(x)                 \
    {                        \
        #x, SimpleElement::x \
    }
        constexpr std::array<std::pair<std::string_view, SimpleElement>, static_cast<size_t>(SimpleElement::unknown) - 1> lookup = {{
            X(functions),
            X(function),
            X(id),
            X(source),
        }};
#undef X
        const auto it = std::find_if(lookup.begin(), lookup.end(),
                                     [lowerCaseName](auto x)
                                     { return !strcmp(lowerCaseName.c_str(), x.first.data()); });
        return it == lookup.end() ? SimpleElement::unknown : it->second;
    }
} //namespace functions::repository::simple

