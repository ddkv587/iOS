//
//  ImageLib.hpp
//  OpenGL
//
//  Created by ddk on 2017/4/10.
//  Copyright © 2017年 ddk. All rights reserved.
//

#ifndef ImageLib_hpp
#define ImageLib_hpp
#include "ImageParse.h"

class ImageLib
{
public:
    enum EImage_Type
    {
        EImage_Type_Invalid     =  -1,
        EImage_Type_bmp,
        EImage_Type_png,
        EImage_Type_jpeg,
        EImage_Type_jpg,
    };
    
public:
    ImageLib();
    virtual ~ImageLib();
    int LoadImageFile(const char* filePath);
    
private:
    
private:
    void*               m_fileData;
    void*               m_imageData;
    ImageParse*  m_pParse;
};

#endif /* ImageLib_hpp */
