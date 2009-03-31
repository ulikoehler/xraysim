#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE XRaySim Test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/random.hpp>

#include "../include/matrixtask.hpp"
#include "../include/io_utils.hpp"

#define TEST_NUMBERS 100 //How many numbers to test one time

using namespace std;
using namespace boost;
using namespace boost::unit_test;

//Tests the matrix and 2d matrix classes

BOOST_AUTO_TEST_SUITE (MatrixTestSuite)

BOOST_AUTO_TEST_CASE (init)
{
    unit_test_log.set_threshold_level (log_messages);
}

/**
 * Tests class Matrix3d
 */
BOOST_AUTO_TEST_CASE (TestMatrix2d)
{
    BOOST_TEST_MESSAGE ("Testing class Matrix2d");

    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    const uint xExt = 10;
    const uint yExt = 9;

    Matrix2d randMatrix (xExt, yExt);

    //Fill the matrix
    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    uint rand = intRng ();
                    randMatrix[ix][iy] = rand;
                    //Check if the number is saved correctly
                    BOOST_CHECK_EQUAL (randMatrix[ix][iy], rand);
                }
        }
}

/**
 * Tests class Matrix3d
 */
BOOST_AUTO_TEST_CASE (TestMatrix3d)
{
    BOOST_TEST_MESSAGE ("Testing class Matrix3d");

    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    const uint xExt = 10;
    const uint yExt = 9;
    const uint zExt = 8;

    uint32_t numbers[xExt * yExt * zExt];

    Matrix3d randMatrix (xExt, yExt, zExt);

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            uint rand = intRng ();
                            randMatrix[ix][iy][iz] = rand;
                            numbers[(ix + iy * xExt) * zExt + iz] = rand; //Numbers are stored sequential in numbers
                        }
                }
        }

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            BOOST_CHECK_EQUAL (randMatrix[ix][iy][iz], numbers[(ix + iy * xExt) * zExt + iz]);
                        }
                }
        }
}

BOOST_AUTO_TEST_SUITE_END ()

BOOST_AUTO_TEST_SUITE (IOTestSuite)

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
                    if (!isdigit (noise)) //Break if the generated character is not a number
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
 * Tests readMatrix3d()
 * Test reading of 3d matrices
 */
BOOST_AUTO_TEST_CASE (TestReadMatrix3d)
{
    stringstream ss (stringstream::in | stringstream::out); //Buffers the comma-separated integers
    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    BOOST_TEST_MESSAGE ("Testing readMatrix3d()");

    //Generate a random 10,9,8 matrix
    const uint xExt = 10;
    const uint yExt = 9;
    const uint zExt = 8;

    Matrix3d randMatrix (xExt, yExt, zExt);

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            uint32_t rand = intRng ();
                            randMatrix[ix][iy][iz] = rand;
                            ss << rand << ',';
                        }
                }
        }

    //Re-read the matrix from the stringstream
    Matrix3d rereadMatrix = readMatrix3d (10, 9, 8, ss);

    //Check the equality of the two matrices
    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            BOOST_CHECK_EQUAL (randMatrix[ix][iy][iz], rereadMatrix[ix][iy][iz]);
                        }
                }
        }
}

/**
 * Tests readMatrix()
 * Test reading of data files
 */
BOOST_AUTO_TEST_CASE (TestReadDataFile)
{
    stringstream ss (stringstream::in | stringstream::out); //Buffers the comma-separated integers
    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    BOOST_TEST_MESSAGE ("Testing readMatrix()");

    //Generate a random 10,9,8 matrix
    const uint xExt = 10;
    const uint yExt = 9;
    const uint zExt = 8;
    
    Matrix3d randMatrix (xExt, yExt, zExt);

    ss << xExt << ',' << yExt << ',' << zExt << endl; //Prints out the extents

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            uint32_t rand = intRng ();
                            randMatrix[ix][iy][iz] = rand;
                            ss << rand << ',';
                        }
                }
        }

    //Re-read the matrix from the stringstream
    Matrix3d rereadMatrix = readMatrix (ss);

    //Check the equality of the two matrices
    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            BOOST_CHECK_EQUAL (randMatrix[ix][iy][iz], rereadMatrix[ix][iy][iz]);
                        }
                }
        }
}

/**
 * Tests MatrixTask constructors
 */
BOOST_AUTO_TEST_CASE (TestConstructors)
{
    BOOST_TEST_MESSAGE ("Testing MatrixTask constructors");
    /**
     * Empty constructor
     */
    const uint xExt = 10;
    const uint yExt = 9;
    const uint zExt = 8;

    MatrixTask task1(xExt, yExt, zExt);
    BOOST_TEST_MESSAGE (" Empty matrix constructor passed");
    /**
     * Stream constructor
     * Generates random matrix data first
     */
    mt19937 intRng (time (0)); //Init a MT19937 PRNG (warning: low entropy seed)

    stringstream ss (stringstream::in | stringstream::out); //Buffers the comma-separated data

    ss << xExt << ',' << yExt << ',' << zExt << endl; //Prints out the extents

    for (int ix = 0; ix < xExt; ix++)
        {
            for (int iy = 0; iy < yExt; iy++)
                {
                    for (int iz = 0; iz < zExt; iz++)
                        {
                            ss << intRng () << ',';
                        }
                }
        }
    MatrixTask task2 (ss);
    BOOST_TEST_MESSAGE (" Stream constructor passed");
}

BOOST_AUTO_TEST_SUITE_END ()

BOOST_AUTO_TEST_SUITE (OperationsTestSuite)

BOOST_AUTO_TEST_SUITE_END ()