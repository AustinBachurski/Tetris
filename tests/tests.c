#include "unity/unity.h"

#include "randombag/randombag.h"


void setUp(void)
{ }

void tearDown(void)
{ }

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(random_bag_produces_complete_set);

    return UNITY_END();
}

