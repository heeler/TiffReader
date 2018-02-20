//
// Created by James Sherman on 2/13/18.
//

#ifndef TIFFREADER_TIFFWRITER_H
#define TIFFREADER_TIFFWRITER_H

#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
#include <boost/gil/image.hpp>
#include <iostream>
#include <sstream>
#include "TagStruct.h"
#include "CustomTiffTags.h"

namespace BG = boost::gil;
namespace BGD = boost::gil::detail;

typedef BGD::tiff_writer TIFFBaseWriter;

//typedef BGD::tiff_reader_color_convert<BG::default_color_converter> TIFFBaseReader;

class MyTagWriter : public TIFFBaseWriter {
public:

    MyTagWriter(const char *fname) :
            TIFFBaseWriter( std::string(std::string(fname) + ".ext").c_str())
    {
        std::cout << "Constructing MyTagWriter" << std::endl;
    }

    void write( TagViewData &tvd )
    {
        long tmpVal = 10;
        tvd.writeTags(TIFFBaseWriter::_tp);
        TIFFSetField(TIFFBaseWriter::_tp, TIFF_TAG_CUSTOM_JS00, "JS custom tag value!");
        TIFFSetField(TIFFBaseWriter::_tp, TIFF_TAG_CUSTOM_JS01, tmpVal);

        TIFFBaseWriter::apply( tvd.getView() );
    }


    ~MyTagWriter(){
        std::cout << "WritingDirectory" << std::endl;
        // TIFFWriteDirectory(TIFFBaseWriter::_tp);
        std::cout << "MyTagWriter in Destructor!" << std::endl;
    }
};


#endif //TIFFREADER_TIFFWRITER_H
