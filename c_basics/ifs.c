#include "munit.h"

const char* get_temperature_status(int temp) {
    if (temp < 70) {
        return "too cold";
    } else if (temp > 90) {
        return "too hot";
    } else {
        return "just right";
    }
}

// Test: Cold
static MunitResult test_cold(const MunitParameter params[], void* data) {
    const char* result = get_temperature_status(50);
    munit_assert_string_equal(result, "too cold");
    return MUNIT_OK;
}

// Test: Hot
static MunitResult test_hot(const MunitParameter params[], void* data) {
    const char* result = get_temperature_status(100);
    munit_assert_string_equal(result, "too hot");
    return MUNIT_OK;
}

// Test: Just right
static MunitResult test_just_right(const MunitParameter params[], void* data) {
    const char* result = get_temperature_status(70);
    munit_assert_string_equal(result, "just right");
    return MUNIT_OK;
}

// Test: Just right 2
static MunitResult test_just_right2(const MunitParameter params[], void* data) {
    const char* result = get_temperature_status(75);
    munit_assert_string_equal(result, "just right");
    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { "/test_cold", test_cold, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_hot", test_hot, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_just_right", test_just_right, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_just_right2", test_just_right2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } // End marker
};

static const MunitSuite test_suite = {
    "/get_temperature_status",  // Name
    test_suite_tests,           // Tests
    NULL,                       // Suites (none nested)
    1,                          // Iterations
    MUNIT_SUITE_OPTION_NONE     // Options
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
