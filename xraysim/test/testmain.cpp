#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <sstream>

#include "../3dio.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(IOTestSuite)
        

BOOST_AUTO_TEST_CASE(TestBasicFieldParsing)
{
    BOOST_TEST_MESSAGE("Testing readVal(istream&)");
    stringstream ss(stringstream::in | stringstream::out);
    ss << "5,3,5";
    BOOST_CHECK_EQUAL(readVal<int>(ss), 5);
}

BOOST_AUTO_TEST_SUITE_END()