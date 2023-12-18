#ifndef E2ERUNTIME_FUSIMPLEREADER_HPP
#define E2ERUNTIME_FUSIMPLEREADER_HPP

#include "../String/ST_String.hpp"

namespace functions::repository::simple
{

    enum class SimpleElement
    {
        document,
        functions,
        function,
        id,
        source,
        unknown
    };

    struct SimpleFunction
    {
        ST_String id;
        ST_String source;
        void set(enum SimpleElement elem, const char *string);
        static SimpleElement toElement(std::string_view name);
    };

} // namespace functions::repository::simple

#endif // E2ERUNTIME_FUSIMPLEREADER_HPP