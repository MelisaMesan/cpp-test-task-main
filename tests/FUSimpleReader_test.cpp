#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include "../repository/FUSimpleReader.hpp"
#include "../repository/FUReader.hpp"
#include "../Types/TY_Blob.hpp"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>

TEST(FUSimpleReader_test, TestNoContent)
{
    using namespace functions::repository::simple;
    xercesc::XMLPlatformUtils::Initialize();
    auto content = TY_Blob();
    std::vector<SimpleFunction> functions;
    try
    {
        functions = readRepo<SimpleElement, SimpleFunction>(content, "test");
    }
    catch (...)
    {
    }
    EXPECT_EQ(0, functions.size());
}

TEST(FUSimpleReader_test, TestContentFromFile)
{
    using namespace functions::repository::simple;
    xercesc::XMLPlatformUtils::Initialize();
    std::ifstream file("../tabfiles/simple.tab");
    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    std::string fileContent = contentStream.str();
    TY_Blob content = TY_Blob();
    content.setContent(fileContent.c_str());
    std::vector<SimpleFunction> functions;

    try
    {
        functions = readRepo<SimpleElement, SimpleFunction>(content, "test");
    }
    catch (...)
    {
    }
    EXPECT_EQ(4, functions.size());
    EXPECT_EQ(ST_String("stringLength...f2128203875h-1761480648.5_1"), functions[0].id);
    EXPECT_EQ(ST_String("0.1"), functions[0].source);
    EXPECT_EQ(ST_String("stringLength...f2128203875h-1761480648.6_1"), functions[1].id);
    EXPECT_EQ(ST_String("1.1"), functions[1].source);
}
