#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include "vgs2tar.h"
#include "vgs2pack.h"

int main()
{
    char path[1024];
    int size;
    char* data;
    FILE* fp;
    struct VgsMetaData* meta;
    void* tar = vgs2tar_open("tohovgs.pkg");
    if (NULL == tar) return -1;
    mkdir("vgspack", 0755);
    for (int i = 0; i < vgs2tar_count(tar); i++) {
        data = vgs2tar_get(tar, i, &size);
        meta = (struct VgsMetaData*)(((char*)data) + sizeof(struct VgsMetaHeader));
        printf("%s %d %s\n", meta->album, (int)ntohs(meta->track), meta->song);
        sprintf(path, "vgspack/%s", meta->album);
        mkdir(path, 0755);
        strcat(path, "/");
        sprintf(path + strlen(path), "%02d_", (int)ntohs(meta->track));
        strcat(path, meta->song);
        strcat(path, ".vgs");
        fp = fopen(path, "wb");
        if (NULL == fp) {
            puts("I/O error.");
            return -1;
        }
        fwrite(data, size, 1, fp);
        fclose(fp);
    }
    vgs2tar_close(tar);
    return 0;
}
