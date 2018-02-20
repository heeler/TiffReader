//
// Created by James Sherman on 2/13/18.
//

#ifndef TIFFREADER_TAGSTRUCT_H
#define TIFFREADER_TAGSTRUCT_H


#include <string>
#include <tiff.h>
#include <tiffio.h>
#include <stdexcept>
#include <sstream>
#include <iostream>




class TIFFTagException : public std::runtime_error {
   std::string defaultMsg;
    uint32_t e_tag_num;
public:
    explicit TIFFTagException(uint32_t num):
            defaultMsg("Tiff Tag Not Found"),
            std::runtime_error(defaultMsg),
            e_tag_num(num)
    {}

    TIFFTagException(uint32_t num, const std::string &str):
            std::runtime_error(str),
            e_tag_num(num)
    {}

    const char* what() {
        std::stringstream msg;
        msg << std::runtime_error::what() << " For Tag: " << e_tag_num;
        return msg.str().c_str();
    }
};


// pure virtual base class
class TagBase {
protected:
    uint32 t_tag_number;
    std::string t_name;

public:
    std::string name(){ return t_name; }

    virtual std::string valueAsStr() = 0;
    virtual void write_tag(TIFF *) = 0;
    virtual ~TagBase() { std::cout << "TagBase Destructor" << std::endl; };
};


template <typename VAL_TYPE, TIFFDataType T>
class TagVal : public TagBase {
    const TIFFDataType t_dtype = T;
    VAL_TYPE t_value;

public:
    TagVal(TIFF *tf, const TIFFField *tiffField, uint32 tag_num) {
        TagBase::t_tag_number = tag_num;
        TagBase::t_name = TIFFFieldName(tiffField);
        if( TIFFGetField(tf, TagBase::t_tag_number, &t_value) != 1 )
            throw TIFFTagException(TagBase::t_tag_number);
    }
    TagVal(){}

    std::string valueAsStr() override {
        std::stringstream tmp;
        tmp << t_value;
        return tmp.str();
    }

    void write_tag(TIFF *tf) override {
        TIFFSetField(tf, t_tag_number, t_value);
    }

    VAL_TYPE value(void){ return t_value; }

    ~TagVal(){
        std::cout << "Destructing Derived" << std::endl;
    }
};

template <>
class TagVal<char *, TIFFDataType::TIFF_ASCII> : public TagBase {
    const TIFFDataType t_dtype = TIFFDataType::TIFF_ASCII;
    std::string t_value;

    std::string value(void){ return t_name; }

public:
    TagVal(TIFF *tf, const TIFFField *tiffField, uint32 tag_num) {
      t_tag_number = tag_num;
      t_name = TIFFFieldName(tiffField);
      char *tmp_value;
      if( TIFFGetField(tf, t_tag_number, &tmp_value) != 1 ) throw TIFFTagException(t_tag_number);
      t_value = tmp_value;
    }

    std::string valueAsStr() override {
        std::stringstream tmp;
        tmp << t_value;
        return tmp.str();
    }

    void write_tag(TIFF *tf) override {
        TIFFSetField(tf, t_tag_number, t_value.c_str());
    }

    ~TagVal(){
        std::cout << "Derived Destructor" << std::endl;
    }
};


std::unique_ptr<TagBase> GetTag(TIFF* tp, uint32 idx);



/*
class TagSHORT : public TagBase {
    typedef uint16 tag_type
    const TIFFDataType t_dtype = TIFFDataType::TIFF_SHORT;
    tag_type t_value;

    TagSHORT(TIFF *tf, TIFFField *tiffField, uint32 tag_num)
    {
        t_tag_number = tag_num;
        t_name = TIFFFieldName(tiffField);
        if( TIFFGetField(tf, t_tag_number, &t_value) != 1 ) throw TIFFTagException(t_tag_number);
    }

    std::string value(void){ return t_name; }
};

class TagLONG : public TagBase {
    typedef uint32 tag_type
            const TIFFDataType t_dtype = TIFFDataType::TIFF_LONG;
    tag_type t_value;

    TagLONG(TIFF *tf, TIFFField *tiffField, uint32 tag_num)
    {
        t_tag_number = tag_num;
        t_name = TIFFFieldName(tiffField);
        if( TIFFGetField(tf, t_tag_number, &t_value) != 1 ) throw TIFFTagException(t_tag_number);
    }

    std::string value(void){ return t_name; }
};


class TagRATIONAL : public TagBase {
    typedef unsigned double tag_type
            const TIFFDataType t_dtype = TIFFDataType::TIFF_RATIONAL;
    tag_type t_value;

    TagRATIONAL(TIFF *tf, TIFFField *tiffField, uint32 tag_num)
    {
        t_tag_number = tag_num;
        t_name = TIFFFieldName(tiffField);
        if( TIFFGetField(tf, t_tag_number, &t_value) != 1 ) throw TIFFTagException(t_tag_number);
    }

    std::string value(void) { return t_name; }
};

class TagSBYTE : public TagBase {
    typedef int8 tag_type
            const TIFFDataType t_dtype = TIFFDataType::TIFF_SBYTE;
    tag_type t_value;

    TagSBYTE(TIFF *tf, TIFFField *tiffField, uint32 tag_num)
    {
        t_tag_number = tag_num;
        t_name = TIFFFieldName(tiffField);
        if( TIFFGetField(tf, t_tag_number, &t_value) != 1 ) throw TIFFTagException(t_tag_number);
    }

    std::string value(void){ return t_name; }
}

*/

#endif //TIFFREADER_TAGSTRUCT_H
