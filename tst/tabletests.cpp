#include <Wordset.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <convert.hpp>
#include <string>

namespace {
namespace proj3 = shindler::ics46::project3;

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

TEST_CASE("Hash:dbc:Expect5553", "[Required][Hash]") {
    const static unsigned int BASE = 37;
    const static unsigned int MOD = 100000;
    auto hashValue = proj3::polynomialHashFunction("dbc", BASE, MOD);
    size_t shouldBe = 4 * BASE * BASE + 2 * BASE + 3;
    REQUIRE(hashValue == shouldBe);
}

TEST_CASE("Table:SingleInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("dbc");
    REQUIRE(wordSet.contains("dbc"));
    REQUIRE(wordSet.capacity() == 11);
}

TEST_CASE("Table:MultiInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.capacity() == 11);
}

// this test case is not required, in the sense
// that it is not a prerequisite to grading part 1.
// However, I am providing it in hopes that it helps
// you to test your code.
// The functionality is still needed for full credit!
TEST_CASE("Table:MultiInsertWithResize:ExpectInTableAndResizedTable",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sunday"));
    REQUIRE(wordSet.capacity() == 23);
}

// TEST_CASE("Table:MultiInsertWithRecursiveResize:ExpectDoubleResize", "[Table][Insert][Resize]") {
//     const static size_t INITIAL_CAPACITY = 11;
//     proj3::WordSet wordSet(INITIAL_CAPACITY);

//     // Initial set of inserts to force first resize to 23
//     wordSet.insert("a");
//     wordSet.insert("b");
//     wordSet.insert("c");
//     wordSet.insert("ab");
//     wordSet.insert("ba");
//     wordSet.insert("cab");
//     wordSet.insert("abc");
//     wordSet.insert("acb");
//     wordSet.insert("bac");
//     wordSet.insert("zzz");  // high hash values
//     wordSet.insert("yyy");
//     wordSet.insert("xxz");

//     // These extra ones will be inserted during or right after resize to 23
//     wordSet.insert("zzzabc");   // collisions likely with "zzz"
//     wordSet.insert("abczzz");
//     wordSet.insert("cbazzz");

//     // At this point we will very likely hit EvictThreshold during rehashing
//     wordSet.insert("evictme");
//     wordSet.insert("pleaseevict");
//     wordSet.insert("recursiveevict");

//     // Should have caused a second resize to 47
//     REQUIRE(wordSet.capacity() > 23);    // should be 47
//     REQUIRE(wordSet.capacity() == 47);

//     // All these should be in the set
//     REQUIRE(wordSet.contains("a"));
//     REQUIRE(wordSet.contains("cab"));
//     REQUIRE(wordSet.contains("zzz"));
//     REQUIRE(wordSet.contains("recursiveevict"));
// }

// TEST_CASE("Resize from 11 to 23 to 47 due to rehash eviction", "[Table][Resize][Evict]") {
//     const static size_t INITIAL_CAPACITY = 11;
//     proj3::WordSet wordSet(INITIAL_CAPACITY);

//     // These create the initial collision cluster that will fill up index 6 in H1
//     wordSet.insert("ba");          // H1(23) = 6
//     wordSet.insert("cab");         // H1(23) = 6
//     wordSet.insert("pleaseevict"); // H1(23) = 6
//     wordSet.insert("xxz");         // H1(23) = 6
//     wordSet.insert("abc");         // H1(23) = 20

//     // Now force a resize to 23 by crossing load threshold
//     wordSet.insert("zzz");
//     wordSet.insert("yyy");
//     wordSet.insert("zzzabc");

//     // This string, during rehash into capacity 23, will trigger another eviction chain
//     // because it hashes to already-colliding spots.
//     wordSet.insert("evictme");

//     // Force the rehash eviction overflow by pushing it further
//     wordSet.insert("recursiveevict"); // H1(23) = 0 (same as "evictme" in H2)

//     // Verify final table size has grown to 47
//     REQUIRE(wordSet.capacity() == 47);

//     // Ensure key strings are still present
//     REQUIRE(wordSet.contains("pleaseevict"));
//     REQUIRE(wordSet.contains("recursiveevict"));
//     REQUIRE(wordSet.contains("ba"));
//     REQUIRE(wordSet.contains("evictme"));
// }



}  // namespace
