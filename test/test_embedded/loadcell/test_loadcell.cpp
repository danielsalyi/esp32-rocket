#include "unity.h"
#include "FS.h"
#include "WiFi.h"

#include <loadcell/loadcell.h>


void setUp(void)
{
    // set stuff up here
    loadCell.setup();
}

void tearDown(void)
{
    
    // clean stuff up here
}

void test_measure(void)
{
    // check if the value is within some range
    float value = loadCell.read();
    TEST_ASSERT_GREATER_OR_EQUAL(-50, value);
    TEST_ASSERT_LESS_OR_EQUAL(50, value);
}

void setup(){
    delay(10000);  // 10 seconds delay for recovery after upload
    UNITY_BEGIN();

    RUN_TEST(test_measure);

    // move a servo here

    // RUN_TEST(test_servo);

    // test the load cell here again

    // RUN_TEST(test_measure_under_load);
}

void loop(){

    UNITY_END();
}