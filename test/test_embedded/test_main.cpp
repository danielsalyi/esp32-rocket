#include "unity.h"
#include "FS.h"
#include "WiFi.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    
    // clean stuff up here
}

void test_example(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

void test_example2(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

void setup(){
    delay(5000);  // 5 seconds delay for recovery after upload
    UNITY_BEGIN();

    RUN_TEST(test_example);
}

void loop(){
    RUN_TEST(test_example2);
    UNITY_END();
}