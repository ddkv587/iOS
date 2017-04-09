//
//  MacroDefine.h
//  OpenGL
//
//  Created by ddk on 2017/4/10.
//  Copyright © 2017年 ddk. All rights reserved.
//

#ifndef MacroDefine_h
#define MacroDefine_h

#define BSWAP_32(x)  \
                (int) ( ( ( (int)(x)  & 0xFF000000 ) >>  24 ) | \
                            ( ( (int)(x)  & 0x00FF0000 ) >>  16 )  |\
                            ( ( (int)(x)  & 0x0000FF00 ) >>  8 )  |\
                            ( ( (int)(x)  & 0x000000FF ) <<  24 ) \
                        )

#endif /* MacroDefine_h */
