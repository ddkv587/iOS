//
//  ImageParse.h
//  OpenGL
//
//  Created by ddk on 2017/4/10.
//  Copyright © 2017年 ddk. All rights reserved.
//

#ifndef ImageParse_h
#define ImageParse_h

class ImageParse
{
public:
    virtual int ParseImage(unsigned char *dstImageData, int &width, int &heigth, const unsigned char* srcFileData, int dataLen) = 0;
};

class PngParse : public ImageParse
{
    enum EPng_ChunkType
    {
        EPng_ChunkType_INVALID = -1,
        EPng_ChunkType_IHDR = 0x49484452,
        EPng_ChunkType_PLTE,
        EPng_ChunkType_IDAT,
        EPng_ChunkType_IEND,
    };
    
    struct Png_Block
    {
        int length;
        EPng_ChunkType chunkTypeCode;
        unsigned char *chunkData;
        int crc;
    };
public:
    PngParse() {}
    virtual ~PngParse() {}
    int ParseImage(unsigned char *dstImageData, int &width, int &heigth, const unsigned char* srcFileData, int dataLen);
};

class BmpParse : public ImageParse
{
public:
    BmpParse() {}
    virtual ~BmpParse() {};
    int ParseImage(unsigned char *dstImageData, int &width, int &heigth, const unsigned char* srcFileData, int dataLen);
};

#endif /* IImageParse_h */
