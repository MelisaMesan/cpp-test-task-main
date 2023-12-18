#ifndef E2ERUNTIME_FUSREPLACEREADER_HPP
#define E2ERUNTIME_FUSREPLACEREADER_HPP

#include "../String/ST_String.hpp"

class TY_Blob;

namespace functions::repository::replace
{
    enum class ReplaceElement
    {
        document,
        functions,
        function,
        id,
        source,
        pattern,
        replacement,
        unknown
    };

    struct ReplaceFunction
    {
        ST_String id;
        ST_String source;
        ST_String pattern;
        ST_String replacement;
        void set(enum ReplaceElement elem, const char *string);
        static ReplaceElement toElement(std::string_view name);
    };

} // namespace functions::repository::replace

#endif // E2ERUNTIME_FUSREPLACEREADER_HPP



