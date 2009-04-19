/*
 * File:   gzutil.hpp
 * Author: uli
 *
 * Created on 18. April 2009, 19:32
 */

#ifndef _GZUTIL_HPP
#define	_GZUTIL_HPP
#include <zlib.h>
#include <iostream>

using namespace std;

typedef unsigned char uchar;

int PipeGZStream(std::istream& inStream, std::ostream& outStream, int CHUNK = 4096)
{
    int have;
    uchar* in = new uchar[CHUNK];
    uchar* out = new uchar[CHUNK];
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = inflateInit (&strm);
    if (ret != Z_OK)
        {
            cerr << "Error in GZ decompression";
        }

    /* decompress until deflate stream ends or end of file */
    do
        {
	    inStream.read((char*)in, CHUNK);
            strm.avail_in = inStream.gcount();
            if (!inStream.good())
                {
                    (void) inflateEnd (&strm);
                    return Z_ERRNO;
                }
            if (strm.avail_in == 0) {break;}
            strm.next_in = in;

            /* run inflate() on input until output buffer not full */
            do
                {
                    strm.avail_out = CHUNK;
                    strm.next_out = out;
                    ret = inflate (&strm, Z_NO_FLUSH);
                    switch (ret)
                        {
                        case Z_NEED_DICT:
                            ret = Z_NEED_DICT; /* and fall through */
                        case Z_DATA_ERROR:
                            ret = Z_DATA_ERROR;
                        case Z_MEM_ERROR:
                            (void) inflateEnd (&strm);
                            return ret;
                        case Z_STREAM_ERROR:
                            return Z_STREAM_ERROR;
                        }
                    have = CHUNK - strm.avail_out;

                    //Write the decompressed data to the output stream
                    outStream.write ((char*)out, have);

                    if (!outStream.good())
                        {
                            (void) inflateEnd (&strm);
                            return Z_ERRNO;
                        }
                }
            while (strm.avail_out == 0);

            /* done when inflate() says it's done */
        }
    while (ret != Z_STREAM_END);

    /* clean up and return */
    (void) inflateEnd (&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

#endif	/* _GZUTIL_HPP */

