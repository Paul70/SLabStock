#include <gtest/gtest.h>
#include <cstdlib>

int main(int argc, char** argv)
{
  // Set PYTHONHOME relative to current directory
  //setenv("PYTHONHOME", ".venv", 1);
  // Set PYTHONPATH relative to current directory
  //setenv("PYTHONPATH", ".venv/lib/python3.10/site-packages", 1);

  ::testing::InitGoogleTest(&argc, argv);
  auto result = RUN_ALL_TESTS();
  return result;
}
