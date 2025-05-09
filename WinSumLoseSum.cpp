#include "WinSumLoseSum.h"
using namespace std;

Optional<Set<int>> makeTarget(const Set<int>& elems, int target) {
    if (target == 0) return {}; // Can always make 0 with empty set
    if (elems.isEmpty()) return Nothing;

    int elem = elems.first();
    Set<int> rest = elems;
    rest.remove(elem);

    // Try including the element
    Optional<Set<int>> withElem = makeTarget(rest, target - elem);
    if (withElem != Nothing) {
        Set<int> result = withElem.value(); // Access the value directly
        result.add(elem);
        return result;
    }

    // Try excluding the element
    Optional<Set<int>> withoutElem = makeTarget(rest, target);
    if (withoutElem != Nothing) return withoutElem;

    return Nothing;
}






/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

/* Custom test: includes both positive and negative numbers. */
STUDENT_TEST("Works with negative numbers") {
    Set<int> nums = {-3, 1, 2, 5};
    EXPECT_EQUAL(makeTarget(nums, 4), {-3, 2, 5});
    EXPECT_EQUAL(makeTarget(nums, 0), {});
    EXPECT_EQUAL(makeTarget(nums, 100), Nothing);
}



/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Works for an empty set of numbers.") {
    /* Can make 0, but not others. */
    EXPECT_EQUAL(makeTarget({ },  0), {});
    EXPECT_EQUAL(makeTarget({ },  1), Nothing);
    EXPECT_EQUAL(makeTarget({ }, -1), Nothing);
}

PROVIDED_TEST("Works for a one-element (singleton) set.") {
    /* Can make 0 and 137, but not others. */
    EXPECT_EQUAL(makeTarget({ 137 }, 0),   {});
    EXPECT_EQUAL(makeTarget({ 137 }, 137), {137});
    EXPECT_EQUAL(makeTarget({ 137 }, 1),   Nothing);
    EXPECT_EQUAL(makeTarget({ 137 }, -1),  Nothing);
}

PROVIDED_TEST("Works for a two-element (doubleton) set.") {
    EXPECT_EQUAL(makeTarget({ 1, 2 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 0), {});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 2), {2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 3), {1, 2});
    EXPECT_EQUAL(makeTarget({ 1, 2 }, 4), Nothing);
}

PROVIDED_TEST("Works for a three-element set.") {

    /* Can make 0, 1, 3, 4, 5, 7, and 8, but not others. */
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 }, -1), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  0), {});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  1), {1});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  2), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  3), {3});
    EXPECT_NOT_EQUAL(makeTarget({ 1, 3, 4 }, 4), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  5), {1, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  6), Nothing);
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  7), {3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  8), {1, 3, 4});
    EXPECT_EQUAL(makeTarget({ 1, 3, 4 },  9), Nothing);
}
