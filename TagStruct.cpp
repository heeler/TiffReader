//
// Created by James Sherman on 2/13/18.
//

#include "TagStruct.h"

/*
std::unique_ptr<TagBase> MakeMyTag( ){

}
*/

std::unique_ptr<TagBase> GetTag(TIFF* tp, uint32 idx){
    const TIFFField* tf = TIFFFieldWithTag(tp, idx);
    TIFFDataType dt = TIFFFieldDataType(tf);
    TagBase *rawPtr = nullptr;
    switch (dt) {
        case TIFF_BYTE:         // 8-bit unsigned integer
            rawPtr = new TagVal<uint8, TIFF_BYTE>(tp, tf, idx);
            break;
        case TIFF_ASCII:        // 8-bit bytes w/ last byte null
            rawPtr = new TagVal<char *, TIFF_ASCII>(tp, tf, idx);
            break;
        case TIFF_SHORT:        // 16-bit unsigned integer
            rawPtr = new TagVal<uint16, TIFF_SHORT>(tp, tf, idx);
            break;
        case TIFF_LONG:         // 32-bit unsigned integer
            rawPtr = new TagVal<uint32, TIFF_LONG>(tp, tf, idx);
            break;
        case TIFF_RATIONAL:     // 64-bit unsigned fraction RATIONAL Two 32-bit unsigned integers
            rawPtr = new TagVal<uint64 , TIFF_RATIONAL>(tp, tf, idx);
            break;
        case TIFF_SBYTE:        // !8-bit signed integer
            rawPtr = new TagVal<int8, TIFF_SBYTE>(tp, tf, idx);
            break;
        case TIFF_UNDEFINED:    // !8-bit untyped data => char * ?
            rawPtr = new TagVal<char *, TIFF_UNDEFINED>(tp, tf, idx);
            break;
        case TIFF_SSHORT:       // !16-bit signed integer
            rawPtr = new TagVal<int16, TIFF_SSHORT>(tp, tf, idx);
            break;
        case TIFF_SLONG:        // !32-bit signed integer
            rawPtr = new TagVal<int32, TIFF_SLONG>(tp, tf, idx);
            break;
        case TIFF_SRATIONAL:    // !64-bit signed fraction *
            rawPtr = new TagVal<int64, TIFF_SRATIONAL>(tp, tf, idx);
            break;
        case TIFF_FLOAT:        // !32-bit IEEE floating point
            rawPtr = new TagVal<float, TIFF_FLOAT>(tp, tf, idx);
            break;
        case TIFF_DOUBLE:       // !64-bit IEEE floating point
            rawPtr = new TagVal<double, TIFF_DOUBLE>(tp, tf, idx);
            break;
        case TIFF_IFD:          // %32-bit unsigned integer (offset)
            rawPtr = new TagVal<uint32, TIFF_IFD>(tp, tf, idx);
            break;
        case TIFF_LONG8:        // BigTIFF 64-bit unsigned integer *
            rawPtr = new TagVal<uint64, TIFF_LONG8>(tp, tf, idx);
            break;
        case TIFF_SLONG8:       // BigTIFF 64-bit signed integer
            rawPtr = new TagVal<int64, TIFF_SLONG8>(tp, tf, idx);
            break;
        case TIFF_IFD8:         // BigTIFF 64-bit unsigned integer (offset)
            rawPtr = new TagVal<uint64, TIFF_IFD8>(tp, tf, idx);
            break;
        default:
            std::string msg("TIFF Tag Has type TIFF_NOTYPE!");
            throw TIFFTagException(idx, msg);
    }
    // std::cout << rawPtr->name() << " :  " << rawPtr->valueAsStr() << std::endl;
    return std::unique_ptr<TagBase>(rawPtr);

}
