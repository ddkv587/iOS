//
//  Shader.fsh
//  ImageBrowser
//
//  Created by ddk on 2017/2/11.
//  Copyright © 2017年 ddk. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
