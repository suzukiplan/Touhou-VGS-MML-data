//
//  vgs2tar.h
//  VgsBgmPlayer
//
//  Created by Yoji Suzuki on 2015/10/24.
//  Copyright © 2015年 SUZUKI PLAN. All rights reserved.
//

#ifndef vgs2tar_h
#define vgs2tar_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

void* vgs2tar_open(const char* filename);
int vgs2tar_count(void* context);
char* vgs2tar_get(void* context, int index, int* size);
void vgs2tar_close(void* context);

#ifdef __cplusplus
};
#endif

#endif /* vgs2tar_h */
