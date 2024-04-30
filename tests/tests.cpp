#include <gtest/gtest.h>

extern "C" {
    #include "includes.h"
}

TEST(GarbageCollector, TestingAutoMemset)
{
    void* obj = f_malloc(10);
    for (int i = 0; i < 10; i++)
        EXPECT_EQ(*((char*)(obj) + i), 0) << "Char " << i << " was not equal 0 when allocating"; // Excpect are prefered, as they do NOT generate fatal errors
    f_free_ref(&obj);
    EXPECT_TRUE(obj == nullptr) << "f_free_ref did not work";
}

TEST(Logging, GetGoodInfos)
{
    testing::internal::CaptureStdout();
    debug("This is a %s", "test");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output.substr(output.find("]")), "] \x1B[90m[  DEBUG  ]\x1B[0m This is a test") << "Formating error";
}

TEST(HelpTests, BasicUsage)
{
    testing::internal::CaptureStdout();
    int output = usage("FILENAME", "", 42);
    std::string sout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(sout, "USAGE: FILENAME <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n") << "STDOUT is invalid !";
    EXPECT_EQ(output, 42) << "Error code is invalid !";
}