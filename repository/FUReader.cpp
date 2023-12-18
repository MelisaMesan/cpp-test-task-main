#include "FUSimpleReader.hpp"
#include "FUSReplaceReader.hpp"
#include "FUReader.hpp"
#include "../XML/XML_Parser.hpp"
#include "utils.hpp"
#include "../Types/TY_Blob.hpp"
#include <array>
#include <algorithm>

namespace functions::repository::basic
{

#define STRINGIFY_ENUM(x) #x

    template <typename BasicElement, typename BasicFunction>
    class BasicReader : public XML_Parser
    {
    public:
        bool startElementChar(const char *, const char *localName, const char *, const xercesc::Attributes &) override;
        bool endElementChar(const char *, const char *, const char *) override;
        bool charactersChar(const char *, const char *, const char *, const char *chars, const unsigned int) override;

        std::vector<BasicFunction> read(const TY_Blob &data, std::string_view repo) &&;

    private:
        std::vector<BasicFunction> m_functions;
        std::vector<BasicElement> m_elementStack;
        BasicFunction *m_currentFunction{nullptr};
        void errorMessage(const M_SystemMessage &message) override;
        ST_String m_repository;
    };

    template <typename BasicElement, typename BasicFunction>
    void BasicReader<BasicElement, BasicFunction>::errorMessage(const M_SystemMessage &message)
    {
        throw message;
    }

    template <typename BasicElement, typename BasicFunction>
    std::vector<BasicFunction> BasicReader<BasicElement, BasicFunction>::read(const TY_Blob &data, std::string_view repo) &&
    {
        m_repository.set(repo);
        m_functions.clear();
        m_elementStack.clear();
        m_elementStack.push_back(BasicElement::document);

        parseBlob(&data);

        return std::move(m_functions);
    }

    template <typename BasicElement, typename BasicFunction>
    bool BasicReader<BasicElement, BasicFunction>::startElementChar(const char *, const char *localName, const char *, const xercesc::Attributes &)
    {
        auto previousElement = m_elementStack.back();
        auto currentElement = BasicFunction::toElement(localName);
        m_elementStack.push_back(currentElement);

        if (currentElement == BasicElement::unknown)
        {
            utils::unexpectedElement(localName, m_repository.c_str());
        }

        switch (previousElement)
        {
        case BasicElement::document:
        {
            if (currentElement != BasicElement::functions)
            {
                utils::unexpectedElement(localName, STRINGIFY_ENUM(BasicElement::functions), m_repository.c_str());
            }
            break;
        }
        case BasicElement::functions:
        {
            if (currentElement != BasicElement::function)
            {
                utils::unexpectedElement(localName, STRINGIFY_ENUM(BasicElement::function), m_repository.c_str());
            }
            break;
        }
        case BasicElement::function:
        {
            if (currentElement < BasicElement::id || currentElement >= BasicElement::unknown)
            {
                utils::unexpectedElement(localName, m_repository.c_str());
            }
            break;
        }
        default:
        {
            utils::unexpectedChild(localName, m_repository.c_str());
        }
        }
        return true;
    }

    template <typename BasicElement, typename BasicFunction>
    bool BasicReader<BasicElement, BasicFunction>::charactersChar(const char *, const char *, const char *, const char *chars, const unsigned int)
    {
        auto currentElement = m_elementStack.back();
        if (currentElement == BasicElement::id)
        {
            if (auto it = std::ranges::find_if(m_functions,
                                               [&chars](auto function)
                                               { return !strcmp(chars, function.id.c_str()); });
                it != m_functions.end())
            {
                utils::fatal("lm::duplicated_function_id", fmt::format("Function with ID '{}' duplicated in {}.", chars, m_repository.c_str()));
            }
            m_functions.emplace_back(BasicFunction());
            m_currentFunction = &m_functions.back();
            m_currentFunction->id.set(chars);
        }
        else
        {
            m_currentFunction->set(currentElement, chars);
        }

        return true;
    }

    template <typename BasicElement, typename BasicFunction>
    bool BasicReader<BasicElement, BasicFunction>::endElementChar(const char *, const char *, const char *)
    {
        m_elementStack.pop_back();
        return true;
    }

}

template <typename Elem, typename Func>
std::vector<Func> readRepo(const TY_Blob &data, std::string_view repo)
{
    return functions::repository::basic::BasicReader<Elem, Func>{}.read(data, repo);
}

template std::vector<functions::repository::simple::SimpleFunction> readRepo<functions::repository::simple::SimpleElement, functions::repository::simple::SimpleFunction>(const TY_Blob &, std::string_view);
template std::vector<functions::repository::replace::ReplaceFunction> readRepo<functions::repository::replace::ReplaceElement, functions::repository::replace::ReplaceFunction>(const TY_Blob &, std::string_view);


