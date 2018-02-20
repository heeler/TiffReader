//
// Created by James Sherman on 2/15/18.
//

#ifndef TIFFREADER_CUSTOMTIFFTAGS_H
#define TIFFREADER_CUSTOMTIFFTAGS_H

#include <tiffio.h>
#include <iostream>
#include <vector>





//*************************************************************
//*************************************************************

#define Nof(a) (sizeof(a) / sizeof (a[0]))
#define TIFF_TAG_CUSTOM_JS00 65000
#define TIFF_TAG_CUSTOM_JS01 65001
#define TIFF_TAG_CUSTOM_JS02 65002
#define TIFF_TAG_CUSTOM_JS03 65003
#define TIFF_TAG_CUSTOM_JS04 65004
#define TIFF_TAG_CUSTOM_JS05 65005
#define TIFF_TAG_CUSTOM_JS06 65006
#define TIFF_TAG_CUSTOM_JS07 65007
#define TIFF_TAG_CUSTOM_JS08 65008
#define TIFF_TAG_CUSTOM_JS09 65009

namespace JS_TIFF_EXT {

    static char handle_tag0[20] = {"JS00"}; // whatever you do don't name tags starting with the word Tag
    static char handle_tag1[20] = {"JS01"}; // it causes the pointer to be freed twice (libtiff wierdness)

    static const TIFFFieldInfo xtiffFieldInfo[] = {
            {TIFF_TAG_CUSTOM_JS00, 1, 1, TIFF_ASCII, FIELD_CUSTOM, 0, 0, handle_tag0},
            {TIFF_TAG_CUSTOM_JS01, 1, 1, TIFF_LONG,  FIELD_CUSTOM, 0, 0, handle_tag1}
    };
    // The casts are necessary because the
    // string literals are inherently const,
    // but the definition of TIFFFieldInfo
    // requires a non-const string pointer.
    // The Intel and Microsoft compilers
    // tolerate this, but gcc doesn't.

    static TIFFExtendProc parent_extender = nullptr;  // In case we want a chain of extensions

    static void registerCustomTIFFTags(TIFF *tif)
    {
        /* Install the extended Tag field info */
        // TIFFFieldInfo tmpTFI[] =
        int error = TIFFMergeFieldInfo(tif, xtiffFieldInfo, Nof(xtiffFieldInfo));

        if (parent_extender != nullptr)
            (*parent_extender)(tif);
    }

    static void augment_libtiff_with_custom_tags() {
        static bool first_time = true;
        if (!first_time) return;
        std::cout << "augmenting tag director" << std::endl;
        first_time = false;
        parent_extender = TIFFSetTagExtender(registerCustomTIFFTags);
    }



}

#endif //TIFFREADER_CUSTOMTIFFTAGS_H
