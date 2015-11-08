//
//  vgs2tar.c
//  VgsBgmPlayer
//
//  Created by Yoji Suzuki on 2015/10/24.
//  Copyright © 2015年 SUZUKI PLAN. All rights reserved.
//

#include "vgs2tar.h"
#include "vgs2pack.h"

struct VgsData {
    unsigned int size;
    char* data;
};

struct VgsTarContext {
    struct VgsTarHeader header;
    struct VgsData** data;
    int dataCount;
};

void* vgs2tar_open(const char* filename)
{
    struct VgsTarContext* context;
    FILE* fp;
    int i;
    int s;
    int t;

    context = (struct VgsTarContext*)malloc(sizeof(struct VgsTarContext));
    if (NULL == context) {
        return NULL;
    }
    memset(context, 0, sizeof(struct VgsTarContext));

    fp = fopen(filename, "rb");
    if (NULL == fp) {
        vgs2tar_close(context);
        printf("fopen error\n");
        return NULL;
    }
    fread(&(context->header), sizeof(struct VgsTarHeader), 1, fp);

    if (memcmp(context->header.eyecatch, "VGSARCH", 8) || context->header.endian != 'L') {
        vgs2tar_close(context);
        fclose(fp);
        printf("invalid header\n");
        return NULL;
    }

    context->dataCount = context->header.page;
    context->dataCount *= 256;
    context->dataCount += context->header.num;

    context->data = (struct VgsData**)malloc(context->dataCount * sizeof(struct VgsData*));
    if (NULL == context->data) {
        vgs2tar_close(context);
        fclose(fp);
        printf("no memory @%d\n", __LINE__);
        return NULL;
    }
    memset(context->data, 0, context->dataCount * sizeof(struct VgsData*));

    for (i = 0; i < context->dataCount; i++) {
        context->data[i] = (struct VgsData*)malloc(sizeof(struct VgsData));
        if (NULL == context->data[i]) {
            vgs2tar_close(context);
            fclose(fp);
            printf("no memory @%d\n", __LINE__);
            return NULL;
        }
        fread(&(context->data[i]->size), 4, 1, fp);
        context->data[i]->data = (char*)malloc(context->data[i]->size);
        if (NULL == context->data[i]->data) {
            vgs2tar_close(context);
            fclose(fp);
            printf("no memory @%d\n", __LINE__);
            return NULL;
        }
        for (t = 0; t < context->data[i]->size; t += s) {
            s = (int)fread(&(context->data[i]->data[t]), 1, context->data[i]->size - t, fp);
            if (s < 1) {
                vgs2tar_close(context);
                fclose(fp);
                printf("invalid data\n");
                return NULL;
            }
        }
    }

    fclose(fp);
    return context;
}

int vgs2tar_count(void* context)
{
    struct VgsTarContext* c = (struct VgsTarContext*)context;
    if (NULL == c) return 0;
    return c->dataCount;
}

char* vgs2tar_get(void* context, int index, int* size)
{
    struct VgsTarContext* c = (struct VgsTarContext*)context;
    if (NULL == c || NULL == c->data) {
        *size = 0;
        return NULL;
    }
    if (c->dataCount <= index) {
        *size = 0;
        return NULL;
    }
    *size = c->data[index]->size;
    return c->data[index]->data;
}

void vgs2tar_close(void* context)
{
    struct VgsTarContext* c = (struct VgsTarContext*)context;
    int i;
    if (NULL == c) return;
    if (NULL != c->data) {
        for (i = 0; i < c->dataCount; i++) {
            if (c->data[i]) {
                if (c->data[i]->data) {
                    free(c->data[i]->data);
                }
                free(c->data[i]);
            }
        }
        free(c->data);
    }
    free(c);
}