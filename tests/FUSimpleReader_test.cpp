#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include "../repository/FUSimpleReader.hpp"
#include "../Types/TY_Blob.hpp"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>


TEST(FUSimpleReader_test, TestNoContent)
{
    xercesc::XMLPlatformUtils::Initialize();
    auto content = TY_Blob();
    functions::repository::simple::Functions functions;

    try
    {
        functions = functions::repository::simple::readRepo(content, "test");
    }
    catch (...)
    {
    }

    EXPECT_EQ(0, functions.size());
}

TEST(FUSimpleReader_test, TestContentFromFile)
{
    xercesc::XMLPlatformUtils::Initialize();
    std::ifstream file("../tabfiles/simple.tab");
    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    std::string fileContent = contentStream.str();
    TY_Blob content = TY_Blob();
    content.setContent(fileContent.c_str());
    functions::repository::simple::Functions functions;

    try
    {
        functions = functions::repository::simple::readRepo(content, "test");
    }
    catch (...)
    {
    }

    EXPECT_EQ(4, functions.size());
    EXPECT_EQ(ST_String("stringLength...f2128203875h-1761480648.5_1"), functions[0].id);
    EXPECT_EQ(ST_String("0.1"), functions[0].source);
    EXPECT_EQ(ST_String("1.1"), functions[1].source);
}

