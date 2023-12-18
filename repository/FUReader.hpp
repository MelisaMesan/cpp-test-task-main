#ifndef E2ERUNTIME_FUREADER_HPP
#define E2ERUNTIME_FUREADER_HPP

#include "../String/ST_String.hpp"
#include "../Types/TY_Blob.hpp"

template <typename Elem, typename Func>
std::vector<Func> readRepo(const TY_Blob &data, std::string_view repo);

#endif // E2ERUNTIME_FUREADER_HPP

