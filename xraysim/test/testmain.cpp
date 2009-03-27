#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#define BOOST_TEST_LOG_LEVEL message
#include <boost/test/included/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>

#include <iostream>
#include <sstream>

#include "../3dio.hpp"

#define TEST_NUMBERS 100 //How many numbers to test one time

using namespace std;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE(IOTestSuite)

BOOST_AUTO_TEST_CASE(init)
{
    unit_test_log.set_threshold_level( log_messages );
}

BOOST_AUTO_TEST_CASE(TestBasicFieldParsing)
{
    BOOST_TEST_MESSAGE("Testing readVal():");
    stringstream ss(stringstream::in | stringstream::out);
    BOOST_TEST_MESSAGE("Testing readVal():");
    //Generate TEST_NUMBERS integers
    ss << "5,3,5";
    BOOST_CHECK_EQUAL(readVal<int>(ss), 5);
}

BOOST_AUTO_TEST_SUITE_END()