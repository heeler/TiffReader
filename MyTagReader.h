//
// Created by James Sherman on 2/13/18.
//

#ifndef TIFFREADER_TIFFREADER_H
#define TIFFREADER_TIFFREADER_H

#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
#include <boost/gil/image.hpp>
#include <iostream>
#include <sstream>
#include "TagStruct.h"
#include "CustomTiffTags.h"
#include "TagViewData.h"

namespace BG = boost::gil;
namespace BGD = boost::gil::detail;


typedef BGD::tiff_reader TIFFBaseReader;

class MyTagReader : public TIFFBaseReader {
    int N_tags;
public:

    MyTagReader(const char *fname, tdir_t dirnum=0) :
            TIFFBaseReader(fname, dirnum),
            N_tags(TIFFGetTagListCount(TIFFBaseReader::_tp))
    {}

    int size(){ return N_tags; }

    void apply(TagViewData &tvd){
        BOOST_STATIC_ASSERT(boost::gil::tiff_read_support<TagViewData::Img>::is_supported);
        tvd.readTags(_tp);
        try {
            TIFFBaseReader::read_image(tvd.getImg());
        } catch (std::runtime_error &e){
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    }

    ~MyTagReader(){
        std::cout << "MyTagReader in Destructor!" << std::endl;
    }
};


#endif //TIFFREADER_TIFFREADER_H
