#include <string.h>
#include "CppUTest/TestHarness.h"
extern "C" {
#include "anagrams.h"
}

bool test_anagrams_item_existing(anagrams_t *anagrams, const char *item)
{
    for (int i = 0; i < anagrams_get_amount(anagrams); i++) {
        if (0 == strncmp(item, anagrams_get_item(anagrams, i), anagrams_get_length(anagrams)))
            return true;
    }

    return false;
}

TEST_GROUP(anagrams)
{
    void setup() {}
    void teardown() {}
};

TEST(anagrams, empty_input)
{
    anagrams_t * anagrams = anagrams_create("");
    STRCMP_EQUAL("", anagrams_get_item(anagrams, 0));
    anagrams_destroy(anagrams);
}

TEST(anagrams, one_char)
{
    anagrams_t *anagrams = anagrams_create("a");
    STRCMP_EQUAL("a", anagrams_get_item(anagrams, 0));
    anagrams_destroy(anagrams);

    anagrams = anagrams_create("b");
    STRCMP_EQUAL("b", anagrams_get_item(anagrams, 0));
    anagrams_destroy(anagrams);

}

TEST(anagrams, two_char)
{
    anagrams_t *anagrams = anagrams_create("ab");
    CHECK(test_anagrams_item_existing(anagrams, "ab"));
    CHECK(test_anagrams_item_existing(anagrams, "ba"));
    anagrams_destroy(anagrams);


}

TEST(anagrams, three_char)
{
    anagrams_t *anagrams = anagrams_create("abc");
    CHECK(test_anagrams_item_existing(anagrams, "abc"));
    CHECK(test_anagrams_item_existing(anagrams, "acb"));
    CHECK(test_anagrams_item_existing(anagrams, "bac"));
    CHECK(test_anagrams_item_existing(anagrams, "bca"));
    CHECK(test_anagrams_item_existing(anagrams, "cab"));
    CHECK(test_anagrams_item_existing(anagrams, "cba"));

    anagrams_destroy(anagrams);
}

IGNORE_TEST(anagrams, long_string)
{
    anagrams_t *anagrams = anagrams_create("appreciation");
    CHECK(test_anagrams_item_existing(anagrams, "appreciation"));

    anagrams_destroy(anagrams);
}

