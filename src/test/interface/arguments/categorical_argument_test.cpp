#include <cmdstan/arguments/categorical_argument.hpp>
#include <cmdstan/arguments/singleton_argument.hpp>
#include <stan/callbacks/stream_writer.hpp>
#include <stan/callbacks/writer.hpp>
#include <gtest/gtest.h>

class CmdStanArgumentsCategoricalArgument : public testing::Test {
 public:
  void SetUp() { arg = new cmdstan::categorical_argument; }
  void TearDown() { delete (arg); }

  cmdstan::argument *arg;
  std::stringstream ss;
};

TEST_F(CmdStanArgumentsCategoricalArgument, Constructor) {
  // test fixture would have created the argument.
}

TEST_F(CmdStanArgumentsCategoricalArgument, name) {
  EXPECT_EQ("", arg->name());
}

TEST_F(CmdStanArgumentsCategoricalArgument, description) {
  EXPECT_EQ("", arg->description());
}

TEST_F(CmdStanArgumentsCategoricalArgument, print) {
  // FIXME: write test
}

TEST_F(CmdStanArgumentsCategoricalArgument, print_help) {
  // FIXME: write test
}

TEST_F(CmdStanArgumentsCategoricalArgument, parse_args) {
  bool return_value;
  std::vector<std::string> args;
  bool help_flag;
  stan::callbacks::stream_writer out(ss);
  stan::callbacks::writer err;

  return_value = false;
  args.clear();
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_FALSE(help_flag);
  EXPECT_EQ(0U, args.size());

  return_value = false;
  args.clear();
  args.push_back("help");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_TRUE(help_flag);
  EXPECT_EQ(0U, args.size());

  return_value = false;
  args.clear();
  args.push_back("help-all");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_TRUE(help_flag);
  EXPECT_EQ(0U, args.size());
}

TEST_F(CmdStanArgumentsCategoricalArgument, parse_args_unexpected) {
  bool return_value;
  std::vector<std::string> args;
  bool help_flag;
  stan::callbacks::stream_writer out(ss);
  stan::callbacks::writer err;

  return_value = false;
  args.clear();
  args.push_back("foo=bar");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_FALSE(help_flag);
  EXPECT_EQ(1U, args.size());

  return_value = false;
  args.clear();
  args.push_back("help");
  args.push_back("foo=bar");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_FALSE(help_flag);
  EXPECT_EQ(2U, args.size());

  return_value = false;
  args.clear();
  args.push_back("foo=bar");
  args.push_back("help");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_TRUE(help_flag);
  EXPECT_EQ(0U, args.size());

  return_value = false;
  args.clear();
  args.push_back("foo");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value);
  EXPECT_FALSE(help_flag);
  EXPECT_EQ(1U, args.size());
}

TEST_F(CmdStanArgumentsCategoricalArgument, parse_args_with_1_singleton) {
  bool return_value;
  std::vector<std::string> args;
  bool help_flag;
  stan::callbacks::stream_writer out(ss);
  stan::callbacks::writer err;

  dynamic_cast<cmdstan::categorical_argument *>(arg)->subarguments().push_back(
      new cmdstan::singleton_argument<std::string>("foo"));

  return_value = false;
  args.clear();
  args.push_back("foo");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value) << "called with 'foo'";
  EXPECT_FALSE(help_flag) << "called with 'foo'";

  return_value = false;
  args.clear();
  args.push_back("bar");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value) << "called with 'bar'";
  EXPECT_FALSE(help_flag) << "called with 'bar'";

  return_value = false;
  args.clear();
  args.push_back("help");
  args.push_back("foo");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value) << "called with 'foo help'";
  EXPECT_TRUE(help_flag) << "called with 'foo help'";

  return_value = false;
  args.clear();
  args.push_back("help");
  args.push_back("bar");
  help_flag = false;
  return_value = arg->parse_args(args, out, err, help_flag);

  EXPECT_TRUE(return_value) << "called with 'bar help'";
  EXPECT_FALSE(help_flag) << "called with 'bar help'";
}

TEST_F(CmdStanArgumentsCategoricalArgument, arg) {
  EXPECT_EQ(0, arg->arg(""));
  EXPECT_EQ(0, arg->arg("foo"));
}
