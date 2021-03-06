#include <gtest/gtest.h>
#include <decoder.hpp>
#include <command.hpp>
#include <string.h>

TEST(TestDecoder, TestStandardDecode) {
    char lineArgs[] = "line input test\n";
    Command** cmds = Decoder::decode(lineArgs);
    int argc = 0;
    while(cmds[0]->argv[argc] != NULL)
        argc++;
    ASSERT_EQ(argc, 3) << "argc does not match\n";
    ASSERT_EQ(strcmp(cmds[0]->argv[0], "line"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(cmds[0]->argv[1], "input"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(cmds[0]->argv[2], "test"), 0) << "Parsed args do not match\n";
    ASSERT_TRUE(cmds[0]->outFile == NULL) << "random output file detected\n";
}

TEST(TestDecoder, TestRedirection) {
    char lineArgs[] = "ls -a > output.txt\n";
    Command** cmds = Decoder::decode(lineArgs);
    int argc = 0;
    while(cmds[0]->argv[argc] != NULL)
        argc++;
    ASSERT_EQ(argc, 2) << "argc does not match\n";
    ASSERT_EQ(strcmp(cmds[0]->argv[0], "ls"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(cmds[0]->argv[1], "-a"), 0) << "Parsed args do not match\n";
    ASSERT_EQ(strcmp(cmds[0]->outFile, "output.txt"), 0) << "Parsed outfile does not match\n";
}