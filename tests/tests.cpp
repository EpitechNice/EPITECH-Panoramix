#include <gtest/gtest.h>

#include "parsing.c"
#include "logging.c"

TEST(HelpTests, BasicUsage)
{
    testing::internal::CaptureStdout();
    int output = usage("FILENAME", "", 42);
    std::string sout = testing::internal::GetCapturedStdout();
    ASSERT_EQ(sout, "USAGE: FILENAME <nb_villagers> <pot_size> <nb_fights> <nb_refills>\n") << "STDOUT is invalid !";
    ASSERT_EQ(output, 42) << "Error code is invalid !";
}

