#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SongData {
    int id;
    int no;
    int loop;
    int col;
    int dis;
    int played;
    char text[64];
    struct SongData* next;
};
static struct SongData* headS;

struct TitleData {
    int id;
    int reserved;
    char copyright[32];
    char title[80];
    char reserved2[8];
    struct TitleData* next;
};
static struct TitleData* headT;

static int getYearFromBgmNo(int no);
static void trimstring(char* src);
static int make_song_data();
static int make_title_data();

int main(int argc, char* argv[])
{
    FILE* fp;
    int bgmNo;
    int trackNo;
    int year;
    struct SongData* curS;
    struct TitleData* curT;
    char metafile[64];

    if (argc < 2 || strncmp("data/BSLOT", argv[1], 10) != 0) {
        puts("usage: mkmeta bgm-file");
        return 1;
    }
    bgmNo = atoi(&argv[1][10]);
    sprintf(metafile, "data/BSLOT%03d.meta", bgmNo);

    if (make_song_data()) {
        return 2;
    }

    if (make_title_data()) {
        return 3;
    }

    /* search bgm */
    for (curS = headS; curS; curS = curS->next) {
        if (curS->no == bgmNo) break;
    }
    if (!curS) {
        puts("undefined bgm data");
        return 4;
    }

    /*search title */
    for (curT = headT; curT; curT = curT->next) {
        if (curT->id == ((curS->id & 0xffff00) >> 8)) {
            trackNo = curS->id & 0xff;
            year = atoi(&(curT->copyright[3]));
            break;
        }
    }
    if (!curT) {
        puts("undefined title data");
        return 5;
    }

    if (NULL == (fp = fopen(metafile, "wt"))) {
        puts("could not open the meta file");
        return 6;
    }

    fprintf(fp, "format = VGS1.0\n");
    fprintf(fp, "genre = Game Music\n");
    fprintf(fp, "\n");
    fprintf(fp, "Data:\n");
    fprintf(fp, "year = %d\n", year);
    fprintf(fp, "aid = %d\n", curT->id);
    fprintf(fp, "track = %d\n", trackNo);
    fprintf(fp, "album = %s\n", curT->title);
    fprintf(fp, "song = %s\n", curS->text);
    fprintf(fp, "team = 上海アリス幻樂団\n");
    fprintf(fp, "creator = ZUN\n");
    fprintf(fp, "\n");
    fprintf(fp, "Data:\n");
    fprintf(fp, "year = %d\n", getYearFromBgmNo(bgmNo));
    fprintf(fp, "track = %d\n", bgmNo);
    fprintf(fp, "album = 東方BGM on VGS\n");
    fprintf(fp, "team = SUZUKI PLAN\n");
    fprintf(fp, "creator = Yoji Suzuki\n");
    fprintf(fp, "right = 東方Project二次創作\n");

    fclose(fp);
    return 0;
}

static int getYearFromBgmNo(int no)
{
    if (no < 60) return 2013;
    if (no < 69) return 2014;
	if (no < 103) return 2015;
    return 2016;
}

static void trimstring(char* src)
{
    int i, j;
    int len;
    for (i = 0; ' ' == src[i]; i++)
        ;
    if (i) {
        for (j = 0; src[i] != '\0'; j++, i++) {
            src[j] = src[i];
        }
        src[j] = '\0';
    }
    for (len = (int)strlen(src) - 1; 0 <= len && ' ' == src[len]; len--) {
        src[len] = '\0';
    }
}

static int make_song_data()
{
    FILE* fpR;
    char* token[6];
    char buf[1024];
    int tn, i;
    struct SongData dat;
    struct SongData* work;
    struct SongData* cur = NULL;

    fpR = fopen("songlist.txt", "rt");
    if (NULL == fpR) {
        puts("Could not open the songlist.txt file.");
        return 2;
    }

    while (fgets(buf, sizeof(buf), fpR)) {
        memset(token, 0, sizeof(token));
        token[0] = &buf[0];
        for (tn = 1, i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '\n' || buf[i] == '\r') {
                buf[i] = '\0';
                break;
            }
            if ('#' == buf[i]) {
                buf[i] = '\0';
                break;
            }
            if (tn < 6 && ',' == buf[i]) {
                buf[i] = '\0';
                token[tn++] = &buf[i + 1];
            }
        }
        if (tn < 5) continue;
        for (i = 0; i < 5; i++) {
            trimstring(token[i]);
        }
        memset(&dat, 0, sizeof(dat));
        dat.id = (int)strtol(token[0], NULL, 16);
        dat.no = atoi(token[1]);
        dat.loop = atoi(token[2]);
        dat.col = atoi(token[3]);
        strcpy(dat.text, token[4]);
        dat.played = 0;
        dat.dis = 0;
        dat.next = NULL;
        work = (struct SongData*)malloc(sizeof(dat));
        if (NULL == work) {
            puts("no memory");
            return 4;
        }
        memcpy(work, &dat, sizeof(dat));
        if (NULL == cur) {
            headS = work;
            cur = work;
        } else {
            cur->next = work;
            cur = work;
        }
    }

    fclose(fpR);
    return 0;
}

static int make_title_data()
{
    FILE* fpR;
    char* token[3];
    char buf[1024];
    int tn, i;
    struct TitleData dat;
    struct TitleData* work;
    struct TitleData* cur = NULL;

    fpR = fopen("titlelist.txt", "rt");
    if (NULL == fpR) {
        puts("Could not open the titlelist.txt file.");
        return 2;
    }

    while (fgets(buf, sizeof(buf), fpR)) {
        memset(token, 0, sizeof(token));
        token[0] = &buf[0];
        for (tn = 1, i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '\n' || buf[i] == '\r') {
                buf[i] = '\0';
                break;
            }
            if ('#' == buf[i]) {
                buf[i] = '\0';
                break;
            }
            if (tn < 3 && ',' == buf[i]) {
                buf[i] = '\0';
                token[tn++] = &buf[i + 1];
            }
        }
        if (tn < 3) continue;
        for (i = 0; i < 2; i++) {
            trimstring(token[i]);
        }
        memset(&dat, 0, sizeof(dat));
        dat.id = (int)strtol(token[0], NULL, 16);
        strcpy(dat.copyright, token[1]);
        strcpy(dat.title, token[2]);
        dat.next = NULL;
        work = (struct TitleData*)malloc(sizeof(dat));
        if (NULL == work) {
            puts("no memory");
            return 4;
        }
        memcpy(work, &dat, sizeof(dat));
        if (NULL == cur) {
            headT = work;
            cur = work;
        } else {
            cur->next = work;
            cur = work;
        }
    }

    fclose(fpR);
    return 0;
}
