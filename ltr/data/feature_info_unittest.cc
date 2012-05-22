// Copyright 2012 Yandex School Practice

#include <stdlib.h>
#include <string>

#include "gtest/gtest.h"

#include "ltr/data/feature_info.h"

using ltr::FeatureInfo;
using ltr::NominalFeatureValues;

// The fixture for testing (contains data for tests).
class FeaturesInfoTest : public ::testing::Test {
    protected:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

// tests.

TEST_F(FeaturesInfoTest, TestingBasicOperations) {
  FeatureInfo info1(5, ltr::NUMERIC);
  for (size_t i = 0; i < 5; i++)
    EXPECT_EQ(info1.getFeatureType(i), ltr::NUMERIC);

  NominalFeatureValues values;
  values[235] = "fdsf";
  values[65342] = "645333gf";
  info1.addFeature(ltr::NOMINAL, values);

  EXPECT_EQ(info1.getFeatureType(5), ltr::NOMINAL);
  EXPECT_EQ(info1.getFeatureValues(5), values);

  FeatureInfo info2;
  info2.setFeatureCount(5, ltr::NUMERIC);

  EXPECT_FALSE(info2 == info1);
  info2.addFeature(ltr::NOMINAL, values);

  EXPECT_EQ(info1, info2);
}
