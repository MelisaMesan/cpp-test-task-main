#include <gtest/gtest.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include "../repository/FUSReplaceReader.hpp"
#include "../Types/TY_Blob.hpp"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>


TEST(FUSReplaceReader_test, TestNoContent)
{
    xercesc::XMLPlatformUtils::Initialize();
    auto content = TY_Blob();
    functions::repository::replace::Functions functions;
    try
    {
        functions = functions::repository::replace::readRepo(content, "test");
    }
    catch (...)
    {
    }

    EXPECT_EQ(0, functions.size());
}


TEST(FUSReplaceReader_test, TestContentFromFile)
{
    xercesc::XMLPlatformUtils::Initialize();
    std::ifstream file("../tabfiles/replace.tab");
    std::ostringstream contentStream;
    contentStream << file.rdbuf();
    std::string fileContent = contentStream.str();
    TY_Blob content = TY_Blob();
    content.setContent(fileContent.c_str());
    functions::repository::replace::Functions functions;


    try
    {
        functions = functions::repository::replace::readRepo(content, "test");
    }
    catch (...)
    {
    }

    EXPECT_EQ(2, functions.size());
    EXPECT_EQ(ST_String("replace...f_653960456h1121717696.7_1"), functions[0].id);
    EXPECT_EQ(ST_String("0"), functions[0].source);
    EXPECT_EQ(ST_String("value...f_653960456h1121717696.8_1"), functions[0].pattern);
    EXPECT_EQ(ST_String("value...f_653960456h1121717696.9_1"), functions[0].replacement);
    EXPECT_EQ(ST_String("replace...f_653960456h771489301.7_1"), functions[1].id);
    EXPECT_EQ(ST_String("0"), functions[1].source);
    EXPECT_EQ(ST_String("value...f_653960456h771489301.8_1"), functions[1].pattern);
    EXPECT_EQ(ST_String("value...f_653960456h771489301.9_1"), functions[1].replacement);
}



