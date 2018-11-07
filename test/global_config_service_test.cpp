#include <gtest/gtest.h>
#include "../src/global_config_service.h"

namespace {
  const char* sampleConfigFilename = "./test/fixtures/sample_config.txt";

  TEST(GlobalConfigService, Get) {
    GlobalConfigService gcs = GlobalConfigService(sampleConfigFilename);
    EXPECT_EQ(gcs.get("SOME_INTEGER_VALUE"), "3");
    EXPECT_EQ(gcs.get("SOME_STRING_VALUE"), "Hello world!");
    EXPECT_EQ(gcs.get("SOME_FLOAT_VALUE"), "3.14");
    EXPECT_EQ(gcs.get("SOME_EMPTY_VALUE"), "");

    // Empty string for missing key
    EXPECT_EQ(gcs.get("NOT_A_REAL_KEY"), "");
  }

  TEST(GlobalConfigService, GetInt) {
    GlobalConfigService gcs = GlobalConfigService(sampleConfigFilename);

    EXPECT_EQ(gcs.getInt("SOME_INTEGER_VALUE"), 3);

    // Non-integer values return zero
    EXPECT_EQ(gcs.getInt("SOME_STRING_VALUE"), 0);
  }

  TEST(GlobalConfigService, GetFloat) {
    GlobalConfigService gcs = GlobalConfigService(sampleConfigFilename);

    EXPECT_FLOAT_EQ(gcs.getFloat("SOME_FLOAT_VALUE"), 3.14);
    EXPECT_FLOAT_EQ(gcs.getFloat("SOME_INTEGER_VALUE"), 3.0);

    // Non-integer values return zero
    EXPECT_FLOAT_EQ(gcs.getFloat("SOME_STRING_VALUE"), 0);
  }
}  // namespace
