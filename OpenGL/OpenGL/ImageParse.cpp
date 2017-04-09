//
//  ImageParse.cpp
//  OpenGL
//
//  Created by ddk on 2017/4/10.
//  Copyright © 2017年 ddk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImageParse.h"
#include "MacroDefine.h"

int PngParse::ParseImage(unsigned char *dstImageData, int &width, int &heigth, const unsigned char* srcFileData, int dataLen)
{
    int offset = 8;
    struct Png_Block block;
    const unsigned char* point = srcFileData + offset;

    while( offset < dataLen)
    {
        block.length =  BSWAP_32( *( ( int *) point ) );
        block.chunkTypeCode = (EPng_ChunkType )BSWAP_32( *( (int *) (point + 4) ) );
        block.chunkData = ( unsigned char * )malloc(block.length);
        memcpy( block.chunkData, point + 8, block.length );
        block.crc = *( (int *)point + 8 + block.length );
        
        switch ( block.chunkTypeCode )
        {
            case EPng_ChunkType_IHDR:
                printf("++++++\n");
                break;
            case EPng_ChunkType_IDAT:
                break;
            default:
                break;
        }
        
        block.length = 0;
        block.chunkTypeCode = EPng_ChunkType_INVALID;
        free(block.chunkData);
        block.crc = 0;
    }
    return 0;
}
