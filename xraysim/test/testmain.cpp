#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#define BOOST_TEST_LOG_LEVEL message
#include <boost/test/included/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/random.hpp>

#include "../include/3dops.hpp"


#define TEST_NUMBERS 100 //How many numbers to test one time

using namespace std;
using namespace boost;
using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE (IOTestSuite)

BOOST_AUTO_TEST_CASE (init)
{
    unit_test_log.set_threshold_level (log_messages);
}

/**
 * Tests readNextVal()
 * Test parsing of streams into numbers
 */
BOOST_AUTO_TEST_CASE (TestReadNextVal)
{
    BOOST_TEST_MESSAGE ("Testing readNextVal()");
    stringstream ss (stringstream::in | stringstream::out); //Bduffers the comma-separated data

    /**
     * Generate TEST_NUMBERS integers and save them in an array and the stringstream
     */
    BOOST_TEST_MESSAGE ("    Testing integer parsing");
    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)
    uint32_t intNumbers[TEST_NUMBERS];
    for (int i = 0; i < TEST_NUMBERS; i++)
        {
            uint32_t rand = intRng (); //Generate a random number
            intNumbers[i] = rand;
            ss << rand << ',';
        }
    //Check if the parsing leads to the same results
    for (int i = 0; i < TEST_NUMBERS; i++)
        {
            //readNextVal parses the next number each iteration
            //Test if it's equal to the number saved in the array
            BOOST_CHECK_EQUAL (readNextVal (ss), intNumbers[i]);
        }

    /**
     * Do the same with 'noise characters)
     */
    BOOST_TEST_MESSAGE ("    Testing noisy integer parsing");
    for (int i = 0; i < TEST_NUMBERS; i++)
        {
            uint32_t rand = intRng (); //Generate a random number
            intNumbers[i] = rand;
            //Add a noise character
            //Generate characters until a character is not a number
            char noise;
            while (true) //Generate characters
                {
                    noise = intRng () % 256;
                    if (!isdigit(noise)) //Break if the generated character is not a number
                        {
                            break;
                        } 
                }
            ss << noise << rand << ',';
        }
    //Check if the parsing leads to the same results
    for (int i = 0; i < TEST_NUMBERS; i++)
        {
            //readNextVal parses the next number each iteration
            //Test if it's equal to the number saved in the array
            //Throws a bad_lexical_cast if the noise isn't recognized
            BOOST_CHECK_EQUAL (readNextVal (ss), intNumbers[i]);
        }
}

/**
 * Tests readMatrix
 * Test reading of data files
 */
BOOST_AUTO_TEST_CASE (TestReadDataFile)
{
    stringstream ss (stringstream::in | stringstream::out); //Buffers the comma-separated integers
    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    BOOST_TEST_MESSAGE ("Testing readMatrix()");

    //Generate a random 10,9,8 matrix
    Matrix3d randMatrix (boost::extents[10][9][8]);

    ss << 10 << ',' << 9 << ',' << 8 << endl; //Prints out the extents

    for (int ix = 0; ix < 10; ix++)
        {
            for (int iy = 0; iy < 9; iy++)
                {
                    for (int iz = 0; iz < 8; iz++)
                        {
                            uint32_t rand = intRng ();
                            randMatrix[ix][iy][iz] = rand;
                            ss << rand << ',';
                        }
                }
        }

    //Re-read the matrix from the stringstream
    MatrixTask task(ss);

    //Check the equality of the two matrices
    BOOST_CHECK (randMatrix == task.getMatrix());
}

BOOST_AUTO_TEST_SUITE_END ()

BOOST_AUTO_TEST_SUITE (OperationsTestSuite)
/**
 * Tests if matrixExtents() leads to the correct results
 */
BOOST_AUTO_TEST_CASE(TestGetMatrixExtents)
{
    mt19937 intRng(time (0)); //Init a MT19937 PRNG (warning: low entropy seed)
    //Generate a random 12,21,5 matrix (randomly choosen extents)
    const int ix = 12; //X Extent
    const int iy = 21; //Y Extent
    const int iz = 5; //Z Extent

    Matrix3d randMatrix (boost::extents[ix][iy][iz]);
    
    for (int ix = 0; ix < 10; ix++)
        {
            for (int iy = 0; iy < 9; iy++)
                {
                    for (int iz = 0; iz < 8; iz++)
                        {
                            uint32_t rand = intRng ();
                            randMatrix[ix][iy][iz] = rand;
                        }
                }
        }

    //Get the extents and test their correctness
    struct Vector3d dimVector = matrixExtents(randMatrix);
    BOOST_CHECK_EQUAL(dimVector.x, ix);
    BOOST_CHECK_EQUAL(dimVector.y, iy);
    BOOST_CHECK_EQUAL(dimVector.z, iz);
}
        
BOOST_AUTO_TEST_SUITE_END ()