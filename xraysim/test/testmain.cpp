#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#define BOOST_TEST_LOG_LEVEL message
#include <boost/test/included/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/random.hpp>

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
BOOST_AUTO_TEST_CASE(TestReadNextVal)
{
    BOOST_TEST_MESSAGE("Testing readNextVal()");
    stringstream ss(stringstream::in | stringstream::out); //Buffers the comma-separated data

    /**
     * Generate TEST_NUMBERS integers and save them in an array and the stringstream
     */
    BOOST_TEST_MESSAGE("    Testing integer parsing");
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
}

/**
 * Tests readMatrix3d()
 * Test reading of 3d matrices
 */
BOOST_AUTO_TEST_CASE(TestReadMatrix3d)
{
    stringstream ss(stringstream::in | stringstream::out); //Buffers the comma-separated integers
    mt19937 intRng(time(0)); //Init a MT19937 PRNG (warning: low entropy seed)

    BOOST_TEST_MESSAGE("Testing readMatrix3d()");

    //Generate a random 10,9,8 matrix
    matrix3d randMatrix(boost::extents[10][9][8]);

    for(int ix = 0; ix < 10; ix++)
        {
            for(int iy = 0; iy < 9; iy++)
                {
                    for(int iz = 0; iz < 8; iz++)
                        {
                            uint32_t rand = intRng();
                            randMatrix[ix][iy][iz] = rand;
                            ss << rand << ',';
                        }
                }
        }

    //Re-read the matrix from the stringstream
    matrix3d rereadMatrix = readMatrix3d(10, 9, 8, ss);

    //Check the equality of the two matrices
    BOOST_CHECK(randMatrix == rereadMatrix);
}

/**
 * Tests readMatrix
 * Test reading of data files
 */
BOOST_AUTO_TEST_CASE(TestReadDataFile)
{
    stringstream ss(stringstream::in | stringstream::out); //Buffers the comma-separated integers
    mt19937 intRng(time(0)); //Init a MT19937 PRNG (warning: low entropy seed)

    BOOST_TEST_MESSAGE("Testing readMatrix()");

    //Generate a random 10,9,8 matrix
    matrix3d randMatrix(boost::extents[10][9][8]);

    ss << 10 << ',' << 9 << ',' << 8 << endl; //Prints out the dimenstion

    for(int ix = 0; ix < 10; ix++)
        {
            for(int iy = 0; iy < 9; iy++)
                {
                    for(int iz = 0; iz < 8; iz++)
                        {
                            uint32_t rand = intRng();
                            randMatrix[ix][iy][iz] = rand;
                            ss << rand << ',';
                        }
                }
        }

    //Re-read the matrix from the stringstream
    matrix3d rereadMatrix = readMatrix(ss);

    //Check the equality of the two matrices
    BOOST_CHECK(randMatrix == rereadMatrix);
}

BOOST_AUTO_TEST_SUITE_END()