//
// Created by James Sherman on 2/19/18.
//

#ifndef TIFFREADER_TAGVIEWDATA_H
#define TIFFREADER_TAGVIEWDATA_H


#include <string>
#include <tiff.h>
#include <vector>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
#include "TagStruct.h"

typedef std::unique_ptr< TagBase > UPTagBase;


class TagViewData {
public:
    using Img = boost::gil::gray16_image_t;


    TagViewData(size_t n): m_tag_index(n), m_tags(n) {}

    void readTags(TIFF *tp){
        std::generate(m_tag_index.begin(), m_tag_index.end(), [n = 0, tp]() mutable {
            return TIFFGetTagListEntry(tp, n++);
        });

        std::transform(m_tag_index.begin(), m_tag_index.end(), m_tags.begin(), [tp](uint32 idx){
            return GetTag(tp, idx);
        });
    }

    void writeTags(TIFF *tp){
        for_each(m_tags.begin(), m_tags.end(), [tp](const UPTagBase &bp){
            bp->write_tag(tp);
        });
    }

    Img &getImg(){
        return m_img;
    }

    auto getView(void){
        checkView( boost::gil::view(m_img) );
        return boost::gil::view(m_img);
    }

    template <typename View>
    void checkView(View vs){
        BOOST_STATIC_ASSERT(boost::gil::tiff_write_support<View>::is_supported);
    }


private:
    std::vector<uint32> m_tag_index;
    std::vector<UPTagBase> m_tags;
    Img m_img;

};


#endif //TIFFREADER_TAGVIEWDATA_H
