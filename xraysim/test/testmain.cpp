#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#define BOOST_TEST_LOG_LEVEL message
#include <boost/test/included/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/random.hpp>

#include <iostream>
#include <sstream>

#include "../3dio.hpp"

#define TEST_NUMBERS 100 //How many numbers to test one time

using namespace std;
using namespace boost;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(IOTestSuite)

BOOST_AUTO_TEST_CASE(init)
{
    unit_test_log.set_threshold_level( log_messages );
}

/**
 * Tests readNextVal()
 * Test parsing of streams into numbers
 */
BOOST_AUTO_TEST_CASE(TestInternalFieldParsing)
{
    BOOST_TEST_MESSAGE("Testing readNextVal():");
    stringstream ss(stringstream::in | stringstream::out); //Buffers the comma-separated integers

    /**
     * Generate TEST_NUMBERS integers and save them in an array and the stringstream
     */
    BOOST_TEST_MESSAGE("    Testing integer parsing:");
    mt19937 intRng(time(0)); //Init a MT19937 PRNG (warning: low entropy seed)
    uint32_t intNumbers[TEST_NUMBERS];
    for(int i = 0; i < TEST_NUMBERS; i++)
        {
            uint32_t rand = intRng(); //Generate a random number
            intNumbers[i] = rand;
            ss << rand << ',';
        }
    //Check if the parsing leads to the same results
    for(int i = 0; i < TEST_NUMBERS; i++)
        {
            //readNextVal parses the next number each iteration
            BOOST_CHECK_EQUAL(readNextVal<uint32_t>(ss), intNumbers[i]);
        }

    /**
     * Do the same with doubles
     */
    BOOST_TEST_MESSAGE("    Testing double parsing:");
    //Generate a special-distributed PRNG
    boost::uniform_real<> uniReal(0.0,1000.0);
    boost::variate_generator<mt19937&, uniform_real<> > doubleRng(intRng, uniReal);

    //Generate the numbers
    double doubleNumbers[TEST_NUMBERS];
    for(int i = 0; i < TEST_NUMBERS; i++)
        {
            double rand = doubleRng(); //Generate a random number
            doubleNumbers[i] = rand;
            ss << rand << ',';
        }
    //Check if the parsing leads to the same results
    for(int i = 0; i < TEST_NUMBERS; i++)
        {
            //readNextVal parses the next number each iteration
            BOOST_CHECK_EQUAL(readNextVal<double>(ss), doubleNumbers[i]);
        }

}

BOOST_AUTO_TEST_SUITE_END()