#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
#include <tiffio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <numeric>
#include <vector>
#include <iostream>
#include "MyTagReader.h"
#include "MyTagWriter.h"

int main(int argc, char **argv)
{
    std::string fname("jackson.tiff");
    tdir_t dirnum=69;
    // BG::tiff_read_image(fname.c_str(), img, dirnum);
    TagViewData *tvd = nullptr;
    try {
        MyTagReader tagAdder(fname.c_str(), dirnum);
        tvd = new TagViewData(tagAdder.size());
        tagAdder.apply(*tvd);

    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

    try {
        JS_TIFF_EXT::augment_libtiff_with_custom_tags(); // we only need to register the tags for writing
        MyTagWriter tagWriter(fname.c_str());
        tagWriter.write(*tvd);
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
        std::cout << "Exception Caught!" << std::endl;
    }



/*

    TIFF *image;
    uint32 width, height;
    int r1,c1, t1, imagesize;
    int nsamples;
    unsigned char *scanline=NULL;

    uint16 BitsPerSample;           // normally 8 for grayscale image
    uint16 SamplesPerPixel;         // normally 1 for grayscale image
    uint16 i;

    //std::string fname("example3.tiff");
    // Open the TIFF image
    if((image = TIFFOpen(fname.c_str(), "r")) == NULL){
        fprintf(stderr, "Could not open incoming image\n");
        exit(42);
    }
    int N_tags = TIFFGetTagListCount(image);
    std::vector<uint32> tag_index(N_tags);
    std::vector<std::stringstream> tag_vec(N_tags);
    std::generate(tag_index.begin(), tag_index.end(), [n = 0, &image]() mutable {
        return TIFFGetTagListEntry(image, n++);
    });

    std::for_each(tag_index.begin(), tag_index.end(), [n=0](const uint32& tmptag) mutable {
        std::cout << "index: " << n++ << "\t value: " << tmptag << std::endl;
    });
    // Find the width and height of the image
    TIFFGetField(image, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(image, TIFFTAG_IMAGELENGTH, &height);
    TIFFGetField(image, TIFFTAG_BITSPERSAMPLE, &BitsPerSample);
    TIFFGetField(image, TIFFTAG_SAMPLESPERPIXEL, &SamplesPerPixel);
    imagesize = height * width + 1;	//get image size

    //allocate memory for reading tif image
    scanline = (unsigned char *)_TIFFmalloc(SamplesPerPixel*width);
    if (scanline == NULL){
        fprintf (stderr,"Could not allocate memory!\n");
        exit(0);
    }

    fprintf(stderr,"W=%i H=%i BitsPerSample=%i SamplesPerPixel=%i\n", width, height,BitsPerSample,SamplesPerPixel);
    for (r1 = 0; r1 < height; r1++)
    {
        TIFFReadScanline(image, scanline, r1, 0);
        for (c1 = 0; c1 < width; c1++)
        {
            t1 = c1*SamplesPerPixel;

            for(i=0; i<SamplesPerPixel; i++)
                printf("%u \t", *(scanline + t1+i));
            printf("\n");
        }
    }

    _TIFFfree(scanline); //free allocate memory

    TIFFClose(image);

 */

}