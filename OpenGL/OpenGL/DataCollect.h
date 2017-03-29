//
//  DataCollect.h
//  OpenGL
//
//  Created by ddk on 2017/3/23.
//  Copyright © 2017年 ddk. All rights reserved.
//

#ifndef     __DATACOLLECT_H__
#define    __DATACOLLECT_H__

#include <GL/glew.h>

GLfloat vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // 右上
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f    // 左上
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

#endif /* DataCollect_h */