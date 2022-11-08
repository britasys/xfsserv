#include "gtest_wfs_structures.hpp"
#include "gtest_wfscam_structures.hpp"
#include "gtest_wfsapi_structures.hpp"

#pragma comment(lib, "gtest")

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}