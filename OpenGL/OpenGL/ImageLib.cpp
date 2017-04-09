//
//  ImageLib.cpp
//  OpenGL
//
//  Created by ddk on 2017/4/10.
//  Copyright © 2017年 ddk. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>

#include <iostream>
#include "ImageLib.h"
#include "ImageParse.h"

ImageLib::ImageLib()
{

}

ImageLib::~ImageLib()
{

}

int ImageLib::LoadImageFile(const char *filePath)
{
    FILE *fp  = fopen(filePath, "r");
    struct stat st_file;
    if ( NULL == fp )
    {
        perror("fopen");
  //      goto ERR_RETURN;
        return -1;
    }
    
    if( -1 == stat(filePath, &st_file) )
    {
        perror("stat");
    //    goto ERR_CLOSE;
        return -1;
    }

    m_fileData = malloc(st_file.st_size);
   if( fread(m_fileData, st_file.st_size, 1, fp) <= 0 )
    {
        perror("fread");
        //goto ERR_CLOSE;
        return -1;
    }
    fclose(fp);
        
    int width, heigth;
    ImageParse *parse = new PngParse();
    parse->ParseImage((unsigned char*)m_imageData, width, heigth, (unsigned char *)m_fileData, st_file.st_size);
    
    return 0;
    
ERR_CLOSE:
    fclose(fp);
    
ERR_RETURN:
    return -1;
}
