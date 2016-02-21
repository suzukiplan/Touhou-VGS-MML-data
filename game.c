/* Main Program of the Touhou BGM on VGS */
/* (C)2013, SUZUKI PLAN */
/* Author: Y.Suzuki Apr-2013 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "vgeapi.h"
#include "vgeint.h"
#include "vgsdec.h"

FILE* vge_fopen(const char*, const char*);

/* Macro */
#define HITCHK(X1, Y1, XS1, YS1, X2, Y2, XS2, YS2) (X1 < X2 + XS2 && X2 < X1 + XS1 && Y1 < Y2 + YS2 && Y2 < Y1 + YS1)
#define TITLE_NUM 10
#define SONG_NUM 107

/* Structure */
struct InputInf {
    int s;
    int cx;
    int cy;
    int dx;
    int dy;
};

/* song data */
struct SongData {
    int id;
    int no;
    int loop;
    int col;
    int dis;
    int played;
    char text[64];
};

/* title data */
struct TitleData {
    int id;
    int songNum;
    char copyright[32];
    char title[80];
    char reserved2[8];
};

/* play list */
struct TitleData _title[TITLE_NUM];
struct SongData _listJ[SONG_NUM];
struct SongData _listE[SONG_NUM];
struct SongData* _list = _listJ;

struct MyList {
    int no;
    int id[3][SONG_NUM];
};

/* Proto types */
static void nextSong(int shuf);
static void myprint(int x, int y, const char* msg, ...);
static void putfontS(int x, int y, const char* msg, ...);
static void putfontSD(int x, int y, const char* msg, ...);
static unsigned short getcode(unsigned char sjis[2]);
static void putkanji(int x, int y, int col, const char* msg, ...);

/* Static variables */
int g_request = 0;
int g_playing = 0;
int g_songChanged = 0;
int g_background = 0;
extern int _forcePause;
extern int _flingY;
extern int _flingX;
static struct MyList _mylist;
static unsigned char* _kanji;
static int _mcur = -1;
static int _listType = 1;
static int _currentTitle = 4;
static char _msg[256];

struct Preferences {
    int currentTitleId;
    int base;
    int localeId;
    int listType;
    int shuf;
    int infy;
    int loop;
    int lock;
    int kobushi;
};
static struct Preferences PRF;

/*
 *----------------------------------------------------------------------------
 * Save play list
 *----------------------------------------------------------------------------
 */
static void savelist()
{
    int i, j, k;
    FILE* fp = vge_fopen("playlist.dat", "wb");
    if (NULL != fp) {
        fwrite(&_mylist.no, 4, 1, fp);
        for (i = 0; i < 3; i++) {
            for (j = 0, k = 0; j < SONG_NUM; j++) {
                if (_mylist.id[i][j]) {
                    k++;
                }
            }
            fwrite(&k, 4, 1, fp);
            for (j = 0; j < SONG_NUM; j++) {
                if (_mylist.id[i][j]) {
                    fwrite(&(_list[j].id), 4, 1, fp);
                }
            }
        }
        fclose(fp);
    }
}

/*
 *----------------------------------------------------------------------------
 * Load play list
 *----------------------------------------------------------------------------
 */
static void loadlist()
{
    int i, j, k, l, m;
    FILE* fp = vge_fopen("playlist.dat", "rb");
    if (NULL != fp) {
        fread(&_mylist.no, 4, 1, fp);
        if (2 < _mylist.no || _mylist.no < 0) {
            _mylist.no = 0;
            fclose(fp);
            return;
        }
        for (i = 0; i < 3; i++) {
            fread(&k, 4, 1, fp);
            if (k < 0 || SONG_NUM < k) {
                memset(&_mylist, 0, sizeof(_mylist));
                fclose(fp);
                return;
            }
            for (j = 0; j < k; j++) {
                fread(&l, 4, 1, fp);
                for (m = 0; m < SONG_NUM; m++) {
                    if (_list[m].id == l) {
                        if (i == _mylist.no) _list[m].dis = 1;
                        _mylist.id[i][m] = 1;
                    }
                }
            }
        }
        fclose(fp);
    }
}

/*
 *----------------------------------------------------------------------------
 * Copy list data
 *----------------------------------------------------------------------------
 */
static void copylist(struct SongData* t, struct SongData* f)
{
    int i;
    for (i = 0; i < SONG_NUM; i++) {
        t[i].id = f[i].id;
        t[i].no = f[i].no;
        t[i].loop = f[i].loop;
        t[i].col = f[i].col;
        t[i].dis = f[i].dis;
        t[i].played = f[i].played;
    }
}

/*
 *----------------------------------------------------------------------------
 * Initialization
 *----------------------------------------------------------------------------
 */
int vge_init()
{
    unsigned int sz;
    char* bin;
    int i, j;
    bin = (char*)vge_getdata(0, &sz);
    memcpy(_listJ, bin, sizeof(_listJ));
    bin = (char*)vge_getdata(1, &sz);
    memcpy(_listE, bin, sizeof(_listE));
    _list = _listJ;
    bin = (char*)vge_getdata(2, &sz);
    memcpy(_title, bin, sizeof(_title));
    for (i = 0; i < SONG_NUM; i++) {
        for (j = 0; j < TITLE_NUM; j++) {
            if ((_list[i].id & 0xFFFF00) >> 8 == _title[j].id) {
                _title[j].songNum++;
                break;
            }
        }
    }
    memset(_msg, 0, sizeof(_msg));
    bin = (char*)vge_getdata(3, &sz);
    if (NULL != bin) {
        if (sizeof(_msg) <= sz) {
            sz = sizeof(_msg) - 1;
        }
        memcpy(_msg, bin, sz);
    } else {
        strcpy(_msg, "Touhou BGM on VGS");
    }
    loadlist();
    _kanji = (unsigned char*)vge_getdata(255, &sz);
    return 0;
}

/*
 *----------------------------------------------------------------------------
 * Termination
 *----------------------------------------------------------------------------
 */
int vge_term()
{
    FILE* fp;
    fp = vge_fopen("preferences.dat", "wb");
    if (NULL != fp) {
        fwrite(&PRF, sizeof(PRF), 1, fp);
        fclose(fp);
    }
    savelist();
    return 0;
}

/*
 *----------------------------------------------------------------------------
 * Main
 *----------------------------------------------------------------------------
 */
int vge_loop()
{
    static const char* tn[4] = {"TRI", "SAW", "SQ", "NOZ"};
    static int isFirst = 1;
    static double base = 4.0;
    static double baseX = 0.0;
    static double move = 0;
    static double moveX = 0;
    static int pageChange = 0;
    static int push = 0;
    static int pflag = 0;
    static int touch_off = 0;
    static int px, py;
    static int paused = 1;
    static int infy = 0;
    static int shuf = 0;
    static int loop = 1;
    static int focus = 0;
    static int interval = 0;
    static int playwait = 0;
    static int whourai = 120;
    static int playing = 0;
    static int interval2 = 0;
    static int slide;
    static int slideX;
    static int touchSB = 0;
    static struct InputInf pi;
    static int editmode = 0;
    static int touching = 0;
    static int selectTime = 0;
    static int selectSong = -1;
    static int kobushi;
    struct InputInf ci;
    int i, j, k;
    int ii;
    int iii;
    unsigned int u;
    int dp;
    int bmin;
    int songNum;
    int playingTitle;

    /* preferences */
    if (isFirst) {
        /* load preferences and setup */
        isFirst = 0;
        memset(&PRF, 0, sizeof(PRF));
        PRF.listType = 1;
        PRF.currentTitleId = 0x60;
        PRF.loop = 1;
        FILE* fp = vge_fopen("preferences.dat", "rb");
        if (NULL != fp) {
            fread(&PRF, 1, sizeof(PRF), fp);
            fclose(fp);
        }
        base = (double)PRF.base;
        if (PRF.localeId) {
            _list = _listE;
        } else {
            _list = _listJ;
        }
        for (i = 0; i < TITLE_NUM; i++) {
            if (_title[i].id == PRF.currentTitleId) break;
        }
        if (i == TITLE_NUM) {
            _currentTitle = 0;
        } else {
            _currentTitle = i;
        }
        if (PRF.listType) {
            _listType = 1;
        } else {
            _listType = 0;
        }
        if (PRF.shuf) {
            shuf = 1;
        } else {
            shuf = 0;
        }
        if (PRF.infy) {
            infy = 1;
        } else {
            infy = 0;
        }
        if (PRF.loop < 1) {
            PRF.loop = 1;
        } else if (3 < PRF.loop) {
            PRF.loop = 3;
        }
        loop = PRF.loop;
        if (0 != PRF.lock && 1 != PRF.lock) {
            PRF.lock = 0;
        }
        kobushi = PRF.kobushi;
        if (0 != PRF.kobushi && 1 != PRF.kobushi) {
            PRF.kobushi = 0;
            kobushi = 0;
        }
    } else {
        /* store preferences */
        PRF.base = (int)base;
        if (_list == _listE) {
            PRF.localeId = 1;
        } else {
            PRF.localeId = 0;
        }
        PRF.currentTitleId = _title[_currentTitle].id;
        PRF.listType = _listType;
        PRF.shuf = shuf;
        PRF.infy = infy;
        PRF.loop = loop;
        PRF.kobushi = kobushi;
    }

    /* calc bmin */
    if (_listType) {
        songNum = _title[_currentTitle].songNum;
    } else {
        songNum = SONG_NUM;
    }
    bmin = -(songNum * 20 - 106 + _listType * 40);

    /* Play after wait */
    if (playwait) {
        playwait--;
        if (0 == playwait) {
            g_songChanged++;
            g_playing = 1;
            vge_bplay(_list[_mcur].no);
            vgsdec_set_value(_psg, VGSDEC_REG_KOBUSHI, kobushi);
            focus = 1;
            whourai = 120;
            playing = 1;
        }
    }

    /* get touch state */
    vge_touch(&ci.s, &ci.cx, &ci.cy, &ci.dx, &ci.dy);
    if (ci.s) {
        focus = 0;
        vge_rand();
        pflag = 1;
        if (0 == touching) {
            if (!_listType && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 224, 130, 16, 190)) {
                touching = 1;
            } else if (_listType && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 0, 300, 240, 20)) {
                touching = 3;
            } else {
                touching = 2;
            }
        }
    } else if (pflag) {
        pflag = 0;
        push = 1;
        ci.s = 1;
        ci.cx = px;
        ci.cy = py;
        slide = 0;
        slideX = 0;
    } else {
        selectSong = -1;
        touching = 0;
        pflag = 0;
        push = 0;
        slide = 0;
        slideX = 0;
    }

    /* page change */
    if (_listType) {
        if (PRF.lock && -1 != _mcur) {
            playingTitle = (_list[_mcur].id & 0xFFFF00) >> 8;
            if (playingTitle != _title[_currentTitle].id) {
                /* check pop count of right */
                for (i = 0, iii = _currentTitle; playingTitle != _title[iii].id; i++) {
                    iii++;
                    if (TITLE_NUM <= iii) iii = 0;
                }
                /* check pop count of left */
                for (ii = 0, iii = _currentTitle; playingTitle != _title[iii].id; ii++) {
                    iii--;
                    if (iii < 0) iii = TITLE_NUM - 1;
                }
                /* set auto focus direction */
                if (ii < i) {
                    pageChange = 1;
                } else {
                    pageChange = -1;
                }
            }
        }
        if (!pageChange) {
            if (80.0 < baseX) {
                pageChange = 1;
            } else if (baseX < -80.0) {
                pageChange = -1;
            }
        }
        if (pageChange) {
            if (0 < pageChange) {
                if (baseX < 240.0) {
                    double mv = (240 - baseX) / 6.66666;
                    if ((0 < mv && mv < 1.0) || (mv < 0 && -1.0 < mv)) {
                        baseX = 240;
                    } else {
                        baseX += mv;
                    }
                } else {
                    _currentTitle--;
                    if (_currentTitle < 0) {
                        _currentTitle = TITLE_NUM - 1;
                    }
                    pageChange = 0;
                    baseX = 0;
                    moveX = 0;
                    slideX = 0;
                }
            } else {
                if (-240 < baseX) {
                    double mv = (-240 - baseX) / 6.66666;
                    if ((0 < mv && mv < 1.0) || (mv < 0 && -1.0 < mv)) {
                        baseX = -240;
                    } else {
                        baseX += mv;
                    }
                } else {
                    _currentTitle++;
                    if (TITLE_NUM <= _currentTitle) {
                        _currentTitle = 0;
                    }
                    pageChange = 0;
                    baseX = 0;
                    moveX = 0;
                    slideX = 0;
                }
            }
        }
    }

    /* move list (left & right) */
    if (_flingX) {
        if (0 == PRF.lock) {
            if (_listType && abs(_flingY) < abs(_flingX) && 100 < abs(_flingX)) {
                if (_flingX < 0) {
                    pageChange = -1;
                } else {
                    pageChange = 1;
                }
            }
        }
        _flingX = 0;
    }
    if (!pageChange) {
        if (_listType) {
            if (0 == slide && 0 == slideX) {
                if (4 < abs(ci.dx) && abs(ci.dy) < abs(ci.dx)) {
                    slideX = 1;
                }
            }
        } else {
            baseX = 0;
            moveX = 0;
            slideX = 0;
        }
        if (slideX && 0 == PRF.lock) {
            moveX += ci.cx - pi.cx;
            push = 0;
            touch_off = 1;
            slide = 0;
        } else {
            moveX = 0;
        }
        if (moveX) {
            double mv = moveX / 6.66666;
            if ((0 < mv && mv < 1.0) || (mv < 0 && -1.0 < mv)) mv = moveX;
            moveX -= mv;
            baseX += mv;
        } else if (baseX) {
            double mv = baseX / 6.66666;
            if ((0 < mv && mv < 1.0) || (mv < 0 && -1.0 < mv)) {
                baseX = 0;
            } else {
                baseX -= mv;
            }
        }
    }

    /* move list (up & down) */
    if (slide == 0) {
        if (4 < ci.dy || ci.dy < -4) {
            if (!slideX) {
                slide = 1;
            }
        }
    }
    if (slide) {
        move += ci.cy - pi.cy;
        push = 0;
        touch_off = 1;
    } else {
        move = 0;
    }
    if (move) {
        double mv = move / 6.66666;
        if ((0 < mv && mv < 1.0) || (mv < 0 && -1.0 < mv)) mv = move;
        move -= mv;
        base += mv;
        if (100 < base) {
            base = 100;
            move = 0;
            _flingY = 0;
        } else if (base < bmin - 100) {
            base = bmin - 100;
            move = 0;
            _flingY = 0;
        }
    }
    if (ci.s == 0 && touch_off) {
        touch_off = 0;
    }
    memcpy(&pi, &ci, sizeof(ci));

#ifdef _WIN32
    if (g_mouse_roll) {
        base += g_mouse_roll / 8;
        if (4 < base) base = 4;
        if (base < bmin) base = bmin;
        g_mouse_roll = 0;
    }
#endif

    /* Fling */
    if (touchSB) {
        touchSB--;
        _flingY = 0;
    }
    if (ci.s == 0 && _flingY) {
        double mv = _flingY / 6;
        if (_flingY < 0 && -1 < mv) mv = _flingY;
        if (0 < _flingY && mv < 1) mv = _flingY;
        base += mv;
        _flingY -= (int)mv;
        if (100 < base) {
            base = 100;
            move = 0;
            _flingY = 0;
        } else if (base < bmin - 100) {
            base = bmin - 100;
            move = 0;
            _flingY = 0;
        }
    }

    /* Overscroll */
    if (ci.s == 0) {
        if (base < bmin) {
            double mv = (bmin - base) / 6.66666;
            if (mv < 1) {
                base = bmin;
            } else {
                base += mv;
            }
        }
        if (4 < base) {
            double mv = (base - 4) / 6.66666;
            if (mv < 1) {
                base = 4;
            } else {
                base -= mv;
            }
        }
    }

    /* Auto focus */
    if (focus) {
        if (_listType && ((_list[_mcur].id & 0xFFFF00) >> 8 != _title[_currentTitle].id)) {
            playingTitle = (_list[_mcur].id & 0xFFFF00) >> 8;
            if (playingTitle != _title[_currentTitle].id) {
                /* check pop count of right */
                for (i = 0, iii = _currentTitle; playingTitle != _title[iii].id; i++) {
                    iii++;
                    if (TITLE_NUM <= iii) iii = 0;
                }
                /* check pop count of left */
                for (ii = 0, iii = _currentTitle; playingTitle != _title[iii].id; ii++) {
                    iii--;
                    if (iii < 0) iii = TITLE_NUM - 1;
                }
                /* set auto focus direction */
                if (ii < i) {
                    pageChange = 1;
                } else {
                    pageChange = -1;
                }
            }
        } else {
            if (_listType) {
                for (k = 0, i = 0; i < SONG_NUM; i++) {
                    if ((_list[i].id & 0xFFFF00) >> 8 == _title[_currentTitle].id) {
                        if (i == _mcur) break;
                        k++;
                    }
                }
                j = k * 20 + 130 + (int)base + 40;
                ii = 300;
            } else {
                k = _mcur;
                j = k * 20 + 130 + (int)base;
                ii = 320;
            }
            if (j < 130) {
                i = 130 - j;
                if (10 < i) i = 10;
                base += i;
            } else if (ii < j + 16) {
                i = j + 16 - ii;
                if (10 < i) i = 10;
                base -= i;
            } else {
                focus = 0;
            }
        }
    }

    if (g_background) {
        goto SKIP_DRAW_PROC;
    }

    for (iii = 0; iii < 2; iii++) {
        int bx = (int)baseX;
        int ct = _currentTitle;
        if (iii) {
            if (!_listType || 0 == baseX) {
                break;
            }
            if (0 < baseX) {
                bx -= 240;
                ct--;
                if (ct < 0) ct = TITLE_NUM - 1;
            } else {
                bx += 240;
                ct++;
                if (TITLE_NUM <= ct) ct = 0;
            }
        }
        if (_listType) {
            /* Draw song title */
            putkanji(4 + bx, 134 + (int)base, 255, "%s", _title[ct].title);
            putkanji(236 + bx - ((int)strlen(_title[ct].copyright)) * 4, 152 + (int)base, 255, "%s", _title[ct].copyright);
            if (_title[ct].id == 0x60) {
                putkanji((240 - (((int)strlen(_msg)) * 4)) / 2 + bx, 40 + (int)base, 255, "%s", _msg);
            }
        }
        /* Draw music list */
        for (dp = 0, i = 0, ii = 0; i < SONG_NUM; i++) {
            if (_list[i].dis) {
                _list[i].played = 1;
            }
            if (_listType) {
                if ((_list[i].id & 0xFFFF00) >> 8 != _title[ct].id) {
                    continue;
                }
            }
            dp = _listType * 40 + (ii++) * 20 + 130 + (int)base;
            if (i < SONG_NUM && 114 < dp && dp < 320) {
                if (!editmode && _list[i].dis) {
                    vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 102);
                    vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 104);
                } else {
                    if (_mcur == i) {
                        vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 75);
                        vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 111);
                    } else {
                        if (ci.s && touch_off == 0 && 2 == touching && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, bx, 130, 240, 190) &&
                            HITCHK(4 + bx, dp, 216 + _listType * 16, 16, ci.cx - 4, ci.cy - 4, 8, 8)) {
                            ci.s = 0;
                            if (selectSong != i) {
                                selectTime = 0;
                                selectSong = i;
                            } else {
                                selectTime++;
                            }
                            if (selectTime < 4) {
                                vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, _list[i].col + 4 * _list[i].played);
                                vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 105);
                            } else {
                                vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 60);
                                vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 111);
                                if (push) {
                                    if (editmode) {
                                        push = 0;
                                        vge_eff(2);
                                        _list[i].dis = 1 - _list[i].dis;
                                        _mylist.id[_mylist.no][i] = _list[i].dis;
                                        if (_list[i].dis) {
                                            _list[i].played = 1;
                                        } else {
                                            _list[i].played = 0;
                                        }
                                    } else {
                                        push = 0;
                                        ci.s = 0;
                                        _mcur = i;
                                        paused = 0;
                                        _list[i].played = 1;
                                        vge_bstop();
                                        playwait = 6;
                                        playing = 0;
                                    }
                                }
                            }
                        } else {
                            if (_list[i].dis) {
                                vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 102);
                                vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 104);
                            } else {
                                vge_boxfSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, _list[i].col + 4 * _list[i].played);
                                vge_boxSP(4 + bx, dp, 220 + _listType * 16 + bx, dp + 16, 105);
                            }
                        }
                    }
                }
                if (_list[i].dis) {
                    if (_listType) {
                        putfontSD(8 + bx, dp + 7, "%3d.", _list[i].id & 0xff);
                    } else {
                        putfontSD(8 + bx, dp + 7, "%3d.", ii);
                    }
                    putkanji(26 + bx, dp + 3, 103, "%s", _list[i].text);
                } else {
                    if (_listType) {
                        putfontS(8 + bx, dp + 7, "%3d.", _list[i].id & 0xff);
                    } else {
                        putfontS(8 + bx, dp + 7, "%3d.", ii);
                    }
                    putkanji(27 + bx, dp + 4, 1, "%s", _list[i].text);
                    putkanji(26 + bx, dp + 3, 255, "%s", _list[i].text);
                }
            }
        }
        dp += 20;
        myprint(4 + bx, dp + 5, "Composed by ZUN.");
        if (_listType) {
            putkanji(8 + bx, dp + 15, 255, "This app is an alternative fiction of the Touhou Project.");
            putkanji(140 + bx, dp + 30, 255, "Arranged by Yoji Suzuki.");
            putkanji(100 + bx, dp + 42, 255, "(c)2013, Presented by SUZUKI PLAN.");
        } else {
            putkanji(4 + bx, dp + 15, 255, "This app is an alternative fiction of Touhou Project.");
            vge_putSP(0, 0, 112, 136, 48, 4 + bx, dp + 30);
        }
    }

    /* Scroll bar */
    if (!_listType) {
        vge_boxfSP(224, 130, 240, 320, 103);
        if (1 == touching) {
            touchSB = 30;
            base = ci.cy - 142;
            base *= (-bmin * 100) / 166;
            base /= 100;
            base = 4 - base;
            if (100 < base) {
                base = 100;
                move = 0;
                _flingY = 0;
            } else if (base < bmin - 100) {
                base = bmin - 100;
                move = 0;
                _flingY = 0;
            }
            i = (0 - (int)base + 4) * 100 / (-bmin) * 116 / 100;
            vge_boxfSP(225, 142 + i, 238, 192 + i, 56);
        } else {
            i = (0 - (int)base + 4) * 100 / (-bmin) * 116 / 100;
            vge_boxfSP(225, 142 + i, 238, 192 + i, 108);
        }

        /* Cursor(Top) */
        if (base >= 4) {
            vge_putSP(0, 208, 32, 16, 12, 224, 130);
        } else {
            if (1 == touching && HITCHK(224, 130, 16, 12, ci.cx - 8, ci.cy - 8, 16, 16)) {
                touchSB = 30;
                vge_putSP(0, 176, 32, 16, 12, 224, 130);
                if (push) {
                    base = 4;
                    push = 0;
                }
            } else {
                vge_putSP(0, 144, 32, 16, 12, 224, 130);
            }
        }

        /* Cursor(Bottom) */
        if (base <= bmin) {
            vge_putSP(0, 224, 32, 16, 12, 224, 308);
        } else {
            if (1 == touching && HITCHK(224, 308, 16, 12, ci.cx - 8, ci.cy - 8, 16, 16)) {
                touchSB = 30;
                vge_putSP(0, 192, 32, 16, 12, 224, 308);
                if (push) {
                    base = bmin;
                    push = 0;
                }
            } else {
                vge_putSP(0, 160, 32, 16, 12, 224, 308);
            }
        }
    }

    /* Title list */
    if (_listType) {
        vge_boxfSP(0, 300, 240, 320, 3);
        vge_lineSP(0, 300, 240, 300, 111);
        vge_lineSP(0, 302, 240, 302, 106);
        ii = (240 - TITLE_NUM * 8) / 2;
        j = ii - 1;
        for (i = 0; i < TITLE_NUM; i++, ii += 8) {
            vge_putSP(0, 216, 64, 8, 8, ii, 307);
            if (_currentTitle == i) {
                int bx = (int)baseX / 32;
                if (bx < -8)
                    bx = -8;
                else if (8 < bx)
                    bx = 8;
                vge_putSP(0, 224, 64, 8, 8, ii - bx, 307);
                vge_putSP(0, 224, 64, 8, 8, ii - bx + TITLE_NUM * 8, 307);
                vge_putSP(0, 224, 64, 8, 8, ii - bx - TITLE_NUM * 8, 307);
            }
        }
        vge_boxfSP(0, 307, j, 315, 3);
        vge_boxfSP(ii, 307, 240, 315, 3);
        if (!PRF.lock) {
            /* left button */
            if (0 < pageChange) {
                vge_putSP(0, 16, 192, 16, 16, 0, 304);
            } else {
                if (pageChange) {
                    vge_putSP(0, 0, 192, 16, 16, 0, 304);
                } else {
                    if (0 == touch_off && 3 == touching && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 0, 304, 16, 16)) {
                        vge_putSP(0, 16, 192, 16, 16, 0, 304);
                        if (push) {
                            pageChange = 1;
                        }
                    } else {
                        vge_putSP(0, 0, 192, 16, 16, 0, 304);
                    }
                }
            }
            /* right button */
            if (pageChange < 0) {
                vge_putSP(0, 48, 192, 16, 16, 224, 304);
            } else {
                if (pageChange) {
                    vge_putSP(0, 32, 192, 16, 16, 224, 304);
                } else {
                    if (0 == touch_off && 3 == touching && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 224, 304, 16, 16)) {
                        vge_putSP(0, 48, 192, 16, 16, 224, 304);
                        if (push) {
                            pageChange = -1;
                        }
                    } else {
                        vge_putSP(0, 32, 192, 16, 16, 224, 304);
                    }
                }
            }
        }
    }

    /* Draw play pannel */
    vge_boxfSP(0, 0, 240, 130, 3);
    myprint(22, 2, "Touhou BGM on VGS");
    if (ci.s && touch_off == 0 && HITCHK(0, 0, 24, 12, ci.cx - 4, ci.cy - 4, 8, 8)) {
        if (_list == _listJ) {
            vge_putSP(0, 88, 176, 16, 8, 4, 3);
        } else {
            vge_putSP(0, 104, 176, 16, 8, 4, 3);
        }
        if (push) {
            if (_list == _listJ) {
                _list = _listE;
                copylist(_list, _listJ);
            } else {
                _list = _listJ;
                copylist(_list, _listE);
            }
        }
    } else {
        if (_list == _listJ) {
            vge_putSP(0, 88, 160, 16, 8, 4, 3);
        } else {
            vge_putSP(0, 104, 160, 16, 8, 4, 3);
        }
    }

    /* Configuration */
    if (!editmode) {
        if (ci.s && touch_off == 0 && HITCHK(220, 0, 20, 16, ci.cx - 4, ci.cy - 4, 8, 8)) {
            vge_putSP(0, 72, 176, 16, 8, 222, 3);
            if (push) {
                push = 0;
                editmode = 1;
                paused = 1;
                g_playing = 0;
                vge_bstop();
                _forcePause = 0;
                playing = 0;
                _mcur = -1;
                vge_eff(0);
            }
        } else {
            vge_putSP(0, 72, 160, 16, 8, 222, 3);
        }
    } else {
        if (ci.s && touch_off == 0 && HITCHK(220, 0, 20, 16, ci.cx - 4, ci.cy - 4, 8, 8)) {
            vge_putSP(0, 72, 176, 16, 8, 222, 3);
            if (push) {
                push = 0;
                editmode = 0;
                vge_eff(1);
            }
        } else {
            vge_putSP(0, 72, 160, 16, 8, 222, 3);
        }
    }

    if (editmode) {
        vge_boxfSP(0, 14, 240, 105, 51);
        vge_lineSP(0, 13, 240, 13, 111);
        vge_lineSP(0, 106, 240, 106, 111);
        vge_lineSP(0, 108, 240, 108, 106);
        vge_lineSP(0, 129, 240, 129, 111);
        vge_lineSP(0, 127, 240, 127, 106);

        myprint(8, 20, "CHOOSE A LIST");
        for (i = 0; i < 3; i++) {
            if (i == _mylist.no) {
                vge_boxfSP(20 + i * 70, 32, 80 + i * 70, 50, 58);
                vge_boxSP(20 + i * 70, 32, 80 + i * 70, 50, 63);
            } else {
                if (ci.s && touch_off == 0 && HITCHK(20 + i * 70, 32, 60, 18, ci.cx - 4, ci.cy - 4, 8, 8)) {
                    vge_boxfSP(20 + i * 70, 32, 80 + i * 70, 50, 58);
                    vge_boxSP(20 + i * 70, 32, 80 + i * 70, 50, 63);
                    if (push) {
                        vge_eff(2);
                        _mylist.no = i;
                        for (j = 0; j < SONG_NUM; j++) {
                            _list[j].dis = _mylist.id[_mylist.no][j];
                        }
                    }
                } else {
                    vge_boxfSP(20 + i * 70, 32, 80 + i * 70, 50, 4);
                    vge_boxSP(20 + i * 70, 32, 80 + i * 70, 50, 8);
                }
            }
            myprint(26 + i * 70, 38, "LIST#%d", i + 1);
        }

        for (i = 0, j = 0, k = 0; i < SONG_NUM; i++) {
            if (_list[i].dis) {
                j++;
                _list[i].played = 1;
            } else {
                k++;
                _list[i].played = 0;
            }
        }

        myprint(4, 64, "CHANGE ALL");
        if (k == SONG_NUM) {
            vge_boxfSP(4, 76, 46, 96, 102);
            vge_boxSP(4, 76, 46, 96, 104);
            putkanji(12, 81, 105, "ENABLED");
        } else {
            if (ci.s && touch_off == 0 && HITCHK(4, 76, 42, 20, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_boxfSP(4, 76, 46, 96, 58);
                vge_boxSP(4, 76, 46, 96, 63);
                if (push) {
                    vge_eff(0);
                    for (i = 0; i < SONG_NUM; i++) {
                        _list[i].dis = 0;
                        _mylist.id[_mylist.no][i] = 0;
                    }
                }
            } else {
                vge_boxfSP(4, 76, 46, 96, 4);
                vge_boxSP(4, 76, 46, 96, 8);
            }
            putkanji(12, 81, 111, "ENABLED");
        }

        if (j == SONG_NUM) {
            vge_boxfSP(50, 76, 92, 96, 102);
            vge_boxSP(50, 76, 92, 96, 104);
            putkanji(56, 81, 105, "DISABLED");
        } else {
            if (ci.s && touch_off == 0 && HITCHK(50, 76, 42, 20, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_boxfSP(50, 76, 92, 96, 58);
                vge_boxSP(50, 76, 92, 96, 63);
                if (push) {
                    vge_eff(1);
                    for (i = 0; i < SONG_NUM; i++) {
                        _list[i].dis = 1;
                        _mylist.id[_mylist.no][i] = 1;
                    }
                }
            } else {
                vge_boxfSP(50, 76, 92, 96, 4);
                vge_boxSP(50, 76, 92, 96, 8);
            }
            putkanji(56, 81, 111, "DISABLED");
        }

        myprint(108, 64, "TYPE OF LIST");

        if (_listType) {
            vge_boxfSP(108, 76, 152, 96, 58);
            vge_boxSP(108, 76, 152, 96, 63);
            putkanji(113, 82, 3, "PER TITLE");
        } else {
            if (ci.s && touch_off == 0 && HITCHK(108, 76, 44, 20, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_boxfSP(108, 76, 152, 96, 58);
                vge_boxSP(108, 76, 152, 96, 63);
                if (push) {
                    vge_eff(1);
                    _listType = 1;
                }
            } else {
                vge_boxfSP(108, 76, 152, 96, 4);
                vge_boxSP(108, 76, 152, 96, 8);
            }
        }
        putkanji(112, 81, 111, "PER TITLE");

        if (!_listType) {
            vge_boxfSP(156, 76, 200, 96, 58);
            vge_boxSP(156, 76, 200, 96, 63);
            putkanji(161, 82, 3, "ALL SONGS");
        } else {
            if (ci.s && touch_off == 0 && HITCHK(156, 76, 44, 20, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_boxfSP(156, 76, 200, 96, 58);
                vge_boxSP(156, 76, 200, 96, 63);
                if (push) {
                    vge_eff(1);
                    _listType = 0;
                }
            } else {
                vge_boxfSP(156, 76, 200, 96, 4);
                vge_boxSP(156, 76, 200, 96, 8);
            }
        }
        putkanji(160, 81, 111, "ALL SONGS");

        putfontS(8, 114, "PLEASE TAP A SONG TO ENABLE OR DISABLE.");
        px = ci.cx;
        py = ci.cy;
        return 0;
    }

    /* RegBoard */
    vge_boxfSP(0, 14, 240, 105, 51);
    vge_lineSP(0, 13, 240, 13, 111);
    vge_lineSP(0, 106, 240, 106, 111);
    vge_lineSP(0, 108, 240, 108, 106);
    vge_lineSP(0, 129, 240, 129, 111);
    vge_lineSP(0, 127, 240, 127, 106);
    if (_mcur < 0) {
        putfontS(8, 16, "INDEX     %05d", vgsdec_get_value(_psg, VGSDEC_REG_LENGTH));
    } else {
        if (_list[_mcur].loop) {
            if (infy) {
                putfontS(8, 16, "INDEX     %05d  PLAYING %d", vgsdec_get_value(_psg, VGSDEC_REG_INDEX), vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT) + 1);
            } else {
                if (vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT) < loop) {
                    putfontS(8, 16, "INDEX     %05d  PLAYING %d OF %d", vgsdec_get_value(_psg, VGSDEC_REG_INDEX),
                             vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT) + 1, loop);
                } else {
                    putfontS(8, 16, "INDEX     %05d  FADEOUT", vgsdec_get_value(_psg, VGSDEC_REG_INDEX));
                }
            }
        } else {
            putfontS(8, 16, "INDEX     %05d  ACYCLIC SONG", vgsdec_get_value(_psg, VGSDEC_REG_INDEX));
        }
    }
    if (0 == infy) {
        int ss;
        int sm;
        if (_list[_mcur].loop) {
            int introLen = vgsdec_get_value(_psg, VGSDEC_REG_LOOP_TIME);
            int loopLen = vgsdec_get_value(_psg, VGSDEC_REG_TIME_LENGTH) - introLen;
            ss = introLen + loopLen * loop;
            ss += vgsdec_get_value(_psg, VGSDEC_REG_PLAYING) * 102400;
            ss -= vgsdec_get_value(_psg, VGSDEC_REG_TIME);
            ss -= vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT) * loopLen;
            ss /= 22050;
            if (ss < 0) ss = 0;
            sm = ss / 60;
            ss -= sm * 60;
        } else {
            ss = vgsdec_get_value(_psg, VGSDEC_REG_TIME_LENGTH);
            ss -= vgsdec_get_value(_psg, VGSDEC_REG_TIME);
            ss /= 22050;
            if (ss < 0) ss = 0;
            sm = ss / 60;
            ss -= sm * 60;
        }
        putfontS(8, 24, "LEFT TIME %02d:%02d", sm, ss);
    } else {
        putfontS(8, 24, "LEFT TIME INFINITY");
    }
    /* seek */
    vge_boxSP(12, 34, 235, 42, 53);
    vge_lineSP(12, 34, 12, 42, 48);
    vge_lineSP(12, 34, 235, 34, 48);
    vge_lineSP(16, 37, 229, 37, 53);
    vge_lineSP(16, 39, 229, 39, 48);
    vge_putSP(0, 232, 64, 8, 8, 4, 34);
    if (vgsdec_get_value(_psg, VGSDEC_REG_PLAYING)) {
        u = vgsdec_get_value(_psg, VGSDEC_REG_TIME) / 22050;
        ii = vgsdec_get_value(_psg, VGSDEC_REG_TIME_LENGTH) / 22050;
        i = vgsdec_get_value(_psg, VGSDEC_REG_LOOP_TIME) / 22050;
        j = vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT);
        ii = u * 212 / ii;
        vge_lineSP(16 + ii, 35, 16 + ii, 41, 109);
        vge_lineSP(17 + ii, 35, 17 + ii, 41, 103);

        if (0 == touch_off) {
            if (HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 4, 34, 8, 8)) {
                vge_putSP(0, 240, 64, 8, 8, 4, 34);
                if (push) {
                    ci.s = 0;
                    paused = 0;
                    vge_bstop();
                    playwait = 6;
                    playing = 0;
                    push = 0;
                }
            }
            if (push && HITCHK(ci.cx - 4, ci.cy - 4, 8, 8, 16, 26, 212, 24)) {
                i = ci.cx;
                i -= 16;
                if (i < 0) i = 0;
                if (212 < i) i = 212;
                vgsdec_set_value(_psg, VGSDEC_REG_TIME, vgsdec_get_value(_psg, VGSDEC_REG_TIME_LENGTH) * i / 212);
                push = 0;
            }
        }
    }

    /* piano */
    for (i = 0; i < 6; i++) {
        putfontS(4, 46 + i * 10, "CH%d %s", i, tn[vgsdec_get_value(_psg, VGSDEC_REG_TONE_0 + i)]);
        vge_putSP(0, 0, 208, 200, 8, 36, 46 + i * 10);
        if (vgsdec_get_value(_psg, VGSDEC_REG_VOL_0 + i) != 0 || vgsdec_get_value(_psg, VGSDEC_REG_KEYON_0 + i) != 0) {
            k = vgsdec_get_value(_psg, VGSDEC_REG_KEY_0 + i);
            switch (k % 12) {
                case 0:
                    j = 0;
                    ii = 0;
                    break;
                case 2:
                    j = 0;
                    ii = 1;
                    break;
                case 3:
                    j = 0;
                    ii = 2;
                    break;
                case 5:
                    j = 0;
                    ii = 3;
                    break;
                case 7:
                    j = 0;
                    ii = 4;
                    break;
                case 8:
                    j = 0;
                    ii = 5;
                    break;
                case 10:
                    j = 0;
                    ii = 6;
                    break;
                case 1:
                    j = 1;
                    ii = 0;
                    break;
                case 4:
                    j = 1;
                    ii = 2;
                    break;
                case 6:
                    j = 1;
                    ii = 3;
                    break;
                case 9:
                    j = 1;
                    ii = 5;
                    break;
                case 11:
                    j = 1;
                    ii = 6;
                    break;
                default:
                    j = 0;
                    ii = 0;
            }
            if (0 == j) {
                vge_boxfSP(k / 12 * 28 + ii * 4 + 36, 46 + i * 10, k / 12 * 28 + ii * 4 + 38, 52 + i * 10, 31);
            } else {
                vge_boxfSP(k / 12 * 28 + ii * 4 + 38, 46 + i * 10, k / 12 * 28 + ii * 4 + 40, 51 + i * 10, 31);
            }
        }
    }

SKIP_DRAW_PROC:

    /* Check all disabled */
    for (i = 0, j = 0; i < SONG_NUM; i++) {
        if (_list[i].dis) {
            j++;
        } else {
            break;
        }
    }
    if (j == SONG_NUM) {
        if (!g_background) putfontS(8, 114, "THE ALL OF SONGS ARE DISABLED.");
        px = ci.cx;
        py = ci.cy;
        return 0;
    }

    /* force pause */
    if (_forcePause) {
        paused = 1;
        g_playing = 0;
        vge_bstop();
        _forcePause = 0;
        playing = 0;
    }

    /* skip buttons in background */
    if (g_background) goto SKIP_DRAW_PROC2;

    /* set X position of the buttons */
    if (_listType) {
        ii = 26;
    } else {
        ii = 0;
    }

    /* LOCK button */
    if (ci.s && touch_off == 0 && HITCHK(-24 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
        vge_putSP(0, 144 - PRF.lock * 24, 176, 24, 12, -24 + ii, 112);
        if (push) {
            PRF.lock = 1 - PRF.lock;
        }
    } else {
        vge_putSP(0, 144 - PRF.lock * 24, 160, 24, 12, -24 + ii, 112);
    }

    /* PLAY button */
    if (paused) {
        if (-1 == _mcur) {
            vge_putSP(0, 120, 32, 24, 12, 2 + ii, 112);
        } else {
            if (ci.s && touch_off == 0 && HITCHK(2 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_putSP(0, 48, 32, 24, 12, 2 + ii, 112);
                if (push) {
                    paused = 0;
                    vge_bresume();
                    playing = 1;
                }
            } else {
                vge_putSP(0, 0, 32, 24, 12, 2 + ii, 112);
            }
        }
    } else {
        /* PAUSE button */
        if (-1 == _mcur) {
            vge_putSP(0, 24, 32, 24, 12, 2 + ii, 112);
        } else {
            if (ci.s && touch_off == 0 && HITCHK(2 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_putSP(0, 72, 32, 24, 12, 2 + ii, 112);
                if (push) {
                    g_playing = 0;
                    paused = 1;
                    vge_bstop();
                    playing = 0;
                }
            } else {
                vge_putSP(0, 24, 32, 24, 12, 2 + ii, 112);
            }
        }
    }

    /* INFINITE button */
    if (ci.s && touch_off == 0 && HITCHK(28 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
        vge_putSP(0, 168, 80, 24, 12, 28 + ii, 112);
        if (push) {
            infy = 1 - infy;
        }
    } else {
        vge_putSP(0, 144 + (1 - infy) * 48, 80, 24, 12, 28 + ii, 112);
    }

    if (!infy) {
        /* SHUFFLE button */
        if (ci.s && touch_off == 0 && HITCHK(54 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
            vge_putSP(0, 168, 96, 24, 12, 54 + ii, 112);
            if (push) {
                shuf = 1 - shuf;
            }
        } else {
            vge_putSP(0, 144 + (1 - shuf) * 48, 96, 24, 12, 54 + ii, 112);
        }
        /* LOOP COUNTER */
        if (-1 == _mcur || (0 <= _mcur && _list[_mcur].loop)) {
            if (ci.s && touch_off == 0 && HITCHK(80 + ii, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
                vge_putSP(0, (loop - 1) * 24, 176, 24, 12, 80 + ii, 112);
                if (push) {
                    loop++;
                    if (3 < loop) loop = 1;
                }
            } else {
                vge_putSP(0, (loop - 1) * 24, 160, 24, 12, 80 + ii, 112);
            }
        }
    }

    /* KOBUSHI button */
    if (ci.s && touch_off == 0 && HITCHK(212, 92, 24, 32, ci.cx - 4, ci.cy - 4, 8, 8)) {
        vge_putSP(0, 24, 216, 24, 12, 240 - 28, 112);
        if (push) {
            kobushi = 1 - kobushi;
            if (vgsdec_get_value(_psg, VGSDEC_REG_PLAYING)) {
                push = 0;
                ci.s = 0;
                paused = 0;
                _list[i].played = 1;
                vge_bstop();
                playwait = 6;
                playing = 0;
            }
        }
    } else {
        vge_putSP(0, 48 - kobushi * 48, 216, 24, 12, 212, 112);
    }

SKIP_DRAW_PROC2:

    // acyclic song
    if (-1 == vgsdec_get_value(_psg, VGSDEC_REG_LOOP_INDEX) && !vgsdec_get_value(_psg, VGSDEC_REG_PLAYING)) {
        if (0 == interval2) {
            interval2 = 1;
            if (shuf) {
                for (i = 0; i < SONG_NUM; i++)
                    if (_list[i].played == 0) break;
                if (SONG_NUM == i) {
                    for (j = 0; j < SONG_NUM; j++) {
                        if (_list[j].dis) {
                            _list[j].played = 1;
                        } else {
                            _list[j].played = 0;
                        }
                    }
                }
            }
        } else {
            interval2++;
            if (60 <= interval2) {
                if (infy == 0) {
                    nextSong(shuf);
                }
                paused = 0;
                playing = 0;
                playwait = 6;
                _list[_mcur].played = 1;
                focus = 1;
                interval = 0;
                interval2 = 0;
            }
        }
    } else {
        interval2 = 0;
    }

    // cyclic songs
    if (-1 != _mcur && 0 == infy && _list[_mcur].loop && loop <= vgsdec_get_value(_psg, VGSDEC_REG_LOOP_COUNT)) {
        if (shuf) {
            for (i = 0; i < SONG_NUM; i++)
                if (_list[i].played == 0) break;
            if (SONG_NUM == i) {
                for (j = 0; j < SONG_NUM; j++) {
                    if (_list[j].dis) {
                        _list[j].played = 1;
                    } else {
                        _list[j].played = 0;
                    }
                }
            }
        }
        if (vgsdec_get_value(_psg, VGSDEC_REG_FADEOUT_COUNTER) == 0) {
            vgsdec_set_value(_psg, VGSDEC_REG_FADEOUT, 1);
            interval = 0;
        }
        if (100 <= vgsdec_get_value(_psg, VGSDEC_REG_FADEOUT_COUNTER)) {
            if (interval < 30) {
                interval++;
            } else {
                nextSong(shuf);
                paused = 0;
                vge_bstop();
                playing = 0;
                playwait = 6;
                _list[_mcur].played = 1;
                focus = 1;
                interval = 0;
            }
        }
    }

    if (g_background) {
        myprint(44, 152, "I'll be background!");
    }

    px = ci.cx;
    py = ci.cy;
    return 0;
}

/*
 *----------------------------------------------------------------------------
 * change to the next song
 *----------------------------------------------------------------------------
 */
static void nextSong(int shuf)
{
    int i;
    int ct = _currentTitle;
    int songTop = 0;

    /* calc songTop */
    if (_listType) {
        for (songTop = 0;; songTop++) {
            if ((_list[songTop].id & 0xFFFF00) >> 8 == _title[ct].id) {
                break;
            }
        }
    }

    if (_listType && shuf && PRF.lock) {
        for (i = 0; i < _title[ct].songNum; i++) {
            if (!_list[songTop + i].played && !_list[songTop + i].dis) {
                break;
            }
        }
        if (i == _title[ct].songNum) {
            for (i = 0; i < _title[ct].songNum; i++) {
                if (!_list[songTop + i].dis) {
                    _list[songTop + i].played = 0;
                }
            }
        }
    }

    if (shuf) {
        /* shuffle mode */
        if (_listType) {
            while (1) {
                for (songTop = 0;; songTop++) {
                    if ((_list[songTop].id & 0xFFFF00) >> 8 == _title[ct].id) {
                        break;
                    }
                }
                for (i = 0; i < _title[ct].songNum; i++) {
                    if (!_list[songTop + i].played && !_list[songTop + i].dis) {
                        break;
                    }
                }
                if (i == _title[ct].songNum) {
                    ct++;
                    if (TITLE_NUM <= ct) {
                        ct = 0;
                    }
                } else {
                    break;
                }
            }
            do {
                _mcur = vge_rand() % _title[ct].songNum;
                _mcur += songTop;
            } while (_list[_mcur].played);
        } else {
            do {
                _mcur = vge_rand() % SONG_NUM;
            } while (_list[_mcur].played);
        }
    } else {
        /* secuencial mode */
        do {
            _mcur++;
            if (SONG_NUM <= _mcur) {
                _mcur = 0;
            }
        } while (_list[_mcur].dis);
        /* current album loop */
        if (_listType && PRF.lock) {
            if ((_list[_mcur].id & 0xFFFF00) >> 8 != _title[ct].id) {
                for (_mcur = songTop; _list[_mcur].dis; _mcur++) {
                    if (SONG_NUM <= _mcur) _mcur = 0;
                }
            }
        }
    }
}

/*
 *----------------------------------------------------------------------------
 * PAUSE procedure (do not use)
 *----------------------------------------------------------------------------
 */
int vge_pause()
{
    return 1;
}

/*
 *----------------------------------------------------------------------------
 * print 8x8 font
 *----------------------------------------------------------------------------
 */
static void myprint(int x, int y, const char* msg, ...)
{
    char buf[256];
    int i;
    int c;
    int d;
    va_list args;

    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    for (i = 0; '\0' != (c = (int)buf[i]); i++, x += 8) {
        c -= 0x20;
        c &= 0x7f;
        d = c >> 5;
        vge_putSPM(0, (c - (d << 5)) << 3, d << 3, 8, 8, x + 1, y + 1, 1);
        vge_putSP(0, (c - (d << 5)) << 3, d << 3, 8, 8, x, y);
    }
}

/*
 *----------------------------------------------------------------------------
 * print 4x8 font
 *----------------------------------------------------------------------------
 */
static void putfontS(int x, int y, const char* msg, ...)
{
    char buf[64];
    int i;
    char c;
    va_list args;

    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    for (i = 0; '\0' != (c = buf[i]); i++) {
        if ('0' <= c && c <= '9') {
            c -= '0';
            vge_putSPM(0, c * 4, 24, 4, 8, x + i * 4 + 1, y + 1, 1);
            vge_putSP(0, c * 4, 24, 4, 8, x + i * 4, y);
        } else if ('A' <= c && c <= 'Z') {
            c -= 'A';
            vge_putSPM(0, 40 + c * 4, 24, 4, 8, x + i * 4 + 1, y + 1, 1);
            vge_putSP(0, 40 + c * 4, 24, 4, 8, x + i * 4, y);
        } else if ('.' == c) {
            vge_putSPM(0, 144, 24, 4, 8, x + i * 4 + 1, y + 1, 1);
            vge_putSP(0, 144, 24, 4, 8, x + i * 4, y);
        } else if (':' == c) {
            vge_putSPM(0, 148, 24, 4, 8, x + i * 4 + 1, y + 1, 1);
            vge_putSP(0, 148, 24, 4, 8, x + i * 4, y);
        }
    }
}

static void putfontSD(int x, int y, const char* msg, ...)
{
    char buf[64];
    int i;
    char c;
    va_list args;

    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    for (i = 0; '\0' != (c = buf[i]); i++) {
        if ('0' <= c && c <= '9') {
            c -= '0';
            vge_putSPM(0, c * 4, 24, 4, 8, x + i * 4 + 1, y + 1, 103);
            vge_putSPM(0, c * 4, 24, 4, 8, x + i * 4, y, 103);
        } else if ('A' <= c && c <= 'Z') {
            c -= 'A';
            vge_putSPM(0, 40 + c * 4, 24, 4, 8, x + i * 4 + 1, y + 1, 103);
            vge_putSPM(0, 40 + c * 4, 24, 4, 8, x + i * 4, y, 103);
        } else if ('.' == c) {
            vge_putSPM(0, 144, 24, 4, 8, x + i * 4 + 1, y + 1, 103);
            vge_putSPM(0, 144, 24, 4, 8, x + i * 4, y, 103);
        } else if ('.' == c) {
            vge_putSPM(0, 148, 24, 4, 8, x + i * 4 + 1, y + 1, 103);
            vge_putSPM(0, 148, 24, 4, 8, x + i * 4, y, 103);
        }
    }
}

static unsigned short getcode(unsigned char sjis[2])
{
    unsigned char jis[2];
    unsigned short ret;
    jis[0] = sjis[0];
    jis[1] = sjis[1];
    if (jis[0] <= 0x9f) {
        jis[0] -= 0x71;
    } else {
        jis[0] -= 0xb1;
    }
    jis[0] *= 2;
    jis[0]++;
    if (jis[1] >= 0x7F) {
        jis[1] -= 0x01;
    }
    if (jis[1] >= 0x9e) {
        jis[1] -= 0x7d;
        jis[0]++;
    } else {
        jis[1] -= 0x1f;
    }
    ret = (jis[0] - 0x21) * 94;
    ret += jis[1] - 0x21;
    return ret;
}

static void putkanji(int x, int y, int col, const char* msg, ...)
{
    char buf[256];
    int i, j, k;
    unsigned char c[2];
    int jis;
    unsigned char bin;
    va_list args;

    va_start(args, msg);
    vsprintf(buf, msg, args);
    va_end(args);

    for (i = 0; '\0' != (c[0] = (unsigned char)buf[i]); i++) {
        if (c[0] & 0x80) {
            c[1] = (unsigned char)buf[i + 1];
            jis = (int)getcode(c);
            jis *= 12;
            for (j = 0; j < 12; j++) {
                bin = _kanji[jis + j];
                for (k = 0; k < 8; k++, bin <<= 1) {
                    if (bin & 0x80) {
                        vge_pixelSP(x + k, y + j, col);
                    }
                }
            }
            x += 8;
            i++;
        } else {
            c[0] -= 0x20;
            vge_putSPM(255, c[0] % 16 * 4, c[0] / 16 * 12, 4, 12, x, y, col);
            x += 4;
        }
    }
}

void get_playing_title(const char** title)
{
    static const char* ns = "";
    if (-1 == _mcur) {
        *title = ns;
    } else {
        *title = _list[_mcur].text;
    }
}
