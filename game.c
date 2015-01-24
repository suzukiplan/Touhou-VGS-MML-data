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

FILE* vge_fopen(const char*, const char*);

/* Macro */
#define HITCHK(X1,Y1,XS1,YS1,X2,Y2,XS2,YS2) (X1<X2+XS2 && X2<X1+XS1 &&  Y1<Y2+YS2 && Y2<Y1+YS1)
#define SONG_NUM 71

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
	int gno;
	int gx;
	int gy;
	int gxs;
	int kage;
	int dis;
	int col;
	int played;
	char text[64];
};

/* play list */
struct SongData _list[SONG_NUM] = {
	// 東方幻想郷(0x40)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	 { 0x4007,  61, 1,  0,  0,  0,  0,  0,  0, 196,  0, "Bad Apple!!" }
	// 東方怪綺談(0x50)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0x5010,  62, 1,  3, 64,176,105,  1,  0, 196,  0, "" }
	,{ 0x5011,  63, 1,  0,  0,  0,  0,  0,  0, 196,  0, "the Grimoire of Alice" }
	// 蓬莱人形(0x59)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0x5901,  59, 0,  3,192,144, 48,  0,  0, 196,  0, "" }
	// 東方紅魔郷(0x60)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0x6001,   0, 1,  1,  0,  0, 64,  0,  0,   7,  0, "" }
	,{ 0x6002,   1, 1,  1,  0, 16,128,  0,  0,   7,  0, "" }
	,{ 0x6003,   2, 1,  1,  0, 32, 56,  0,  0,   7,  0, "" }
	,{ 0x6004,   3, 1,  1,  0, 48, 80,  0,  0,   7,  0, "" }
	,{ 0x6005,   4, 1,  1, 80, 48, 72,  0,  0,   7,  0, "" }
	,{ 0x6006,   5, 1,  1, 64,  0,136,  0,  0,   7,  0, "" }
	,{ 0x6007,   6, 1,  1,128, 16,128,  0,  0,   7,  0, "" }
	,{ 0x6008,   7, 1,  1, 56, 32, 96,  0,  0,   7,  0, "" }
	,{ 0x6009,   8, 1,  1,  0, 64,122,  0,  0,   7,  0, "" }
	,{ 0x600A,   9, 1,  1,152, 32,104,  0,  0,   7,  0, "" }
	,{ 0x600B,  10, 1,  1,128, 64,128,  0,  0,   7,  0, "" }
	,{ 0x600C,  11, 1,  1,152, 48,104,  0,  0,   7,  0, "" }
	,{ 0x600D,  12, 1,  1,104, 80,128,  0,  0,   7,  0, "" }
	,{ 0x600E,  13, 1,  1,  0, 96,108,  0,  0,   7,  0, "" }
	,{ 0x600F,  14, 1,  1,112, 96,136,  0,  0,   7,  0, "" }
	,{ 0x6010,  15, 1,  1,  0,112, 73,  0,  0,   7,  0, "" }
	,{ 0x6011,  16, 1,  1, 80,112,120,  0,  0,   7,  0, "" }
	// 東方妖々夢(0x70)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0x7001,  17, 1,  2,  0,  0,153,  0,  0,  35,  0, "" }
	,{ 0x7002,  18, 1,  2,  0, 16,144,  0,  0,  35,  0, "" }
	,{ 0x7003,  19, 1,  2,144, 16,104,  0,  0,  35,  0, "" }
	,{ 0x7004,  20, 1,  2,160,  0, 72,  0,  0,  35,  0, "" }
	,{ 0x7005,  21, 1,  2,  0, 32,152,  0,  0,  35,  0, "" }
	,{ 0x7006,  22, 1,  2,  0, 48,106,  0,  0,  35,  0, "" }
	,{ 0x7007,  23, 1,  2,  0, 64,156,  0,  0,  35,  0, "" }
	,{ 0x7008,  24, 1,  2,152, 32, 72,  0,  0,  35,  0, "" }
	,{ 0x7009,  25, 1,  2,  0, 80,148,  0,  0,  35,  0, "" }
	,{ 0x700A,  26, 1,  2,  0, 96,148,  0,  0,  35,  0, "" }
	,{ 0x700B,  27, 1,  2,112, 48,139,  0,  0,  35,  0, "" }
	,{ 0x700C,  28, 1,  2,152, 80,104,  0,  0,  35,  0, "" }
	,{ 0x700D,  29, 1,  2,  0,112,192,  0,  0,  35,  0, "" }
	,{ 0x700E,  30, 1,  2,160, 64, 88,  0,  0,  35,  0, "" }
	,{ 0x700F,  31, 1,  2,192,112, 48,  0,  0,  35,  0, "" }
	,{ 0x7010,  32, 1,  2,  0,128,128,  0,  0,  35,  0, "" }
	,{ 0x7011,  33, 1,  2,128,128,120,  0,  0,  35,  0, "" }
	,{ 0x7012,  34, 1,  2,160, 96, 84,  0,  0,  35,  0, "" }
	,{ 0x7013,  35, 1,  2,144,144, 46,  0,  0,  35,  0, "" }
	,{ 0x7014,  36, 1,  2,  0,144,141,  0,  0,  35,  0, "" }
	,{ 0x7015,  37, 1,  2,  0,160,134,  0,  0,  35,  0, "" }
	// 東方永夜抄(0x80)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl tx
	,{ 0x8001,  38, 1,  3,  0,  0,120,  0,  0, 196,  0, "" }
	,{ 0x8002,  39, 1,  3,128,  0,128,  0,  0, 196,  0, "" }
	,{ 0x8003,  40, 1,  3,  0, 16,128,  0,  0, 196,  0, "" }
	,{ 0x8004,  41, 1,  3,128, 16,123,  0,  0, 196,  0, "" }
	,{ 0x8005,  42, 1,  3,  0, 32, 96,  0,  0, 196,  0, "" }
	,{ 0x8006,  43, 1,  3, 96, 32,150,  0,  0, 196,  0, "" }
	,{ 0x8007,  44, 1,  3,  0, 48, 72,  0,  0, 196,  0, "" }
	,{ 0x8008,  45, 1,  3, 72, 48,160,  0,  0, 196,  0, "" }
	,{ 0x8009,  46, 1,  3,  0, 64,136,  0,  0, 196,  0, "" }
	,{ 0x800A,  47, 1,  3,144, 64,105,  0,  0, 196,  0, "" }
	,{ 0x800B,  48, 1,  3,  0, 80,169,  0,  0, 196,  0, "" }
	,{ 0x800C,  49, 1,  3,  0, 96,148,  0,  0, 196,  0, "" }
	,{ 0x800D,  50, 1,  3,152, 96, 80,  0,  0, 196,  0, "" }
	,{ 0x800E,  51, 1,  3,  0,112,168,  0,  0, 196,  0, "" }
	,{ 0x800F,  52, 1,  3,  0,128,138,  0,  0, 196,  0, "" }
	,{ 0x8010,  53, 1,  3,168,112, 80,  0,  0, 196,  0, "" }
	,{ 0x8011,  54, 1,  3,  0,144,148,  0,  0, 196,  0, "" }
	,{ 0x8012,  55, 1,  3,144,128,106,  0,  0, 196,  0, "" }
	,{ 0x8013,  56, 1,  3,152,144, 34,  0,  0, 196,  0, "" }
	,{ 0x8014,  57, 1,  3,  0,160,141,  0,  0, 196,  0, "" }
	,{ 0x8015,  58, 1,  3,144,160, 70,  0,  0, 196,  0, "" }
	// 東方花映塚(0x90)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0x9001,  70, 1,  1,120,160,128,  0,  0,  35,  0, "" }
	,{ 0x9004,  66, 1,  1,  0,128, 87,  0,  0,  35,  0, "" }
	,{ 0x900B,  60, 1,  3,  0,192, 56,  0,  0,  35,  0, "       (ShortVersion)" }
	// 東方風神録(0xA0)
	//    id    sn lp  gn  gx  gy  xs  kf  df  col, pl  tx
	,{ 0xA003,  69, 1,  1, 88,128,141,  0,  0,   7,  0, "" }
	,{ 0xA006,  64, 1,  3, 64,192,120,  0,  0,   7,  0, "" }
	,{ 0xA007,  65, 1,  3,  0,208,186,  0,  0,   7,  0, "" }
	,{ 0xA00E,  67, 1,  1,  0,144,142,  0,  0,   7,  0, "" }
	,{ 0xA00F,  68, 1,  1,  0,160,118,  0,  0,   7,  0, "" }
};

struct MyList {
	int no;
	int id[3][SONG_NUM];
};
struct MyList _mylist;

/* Proto types */
static void myprint(int x,int y,const char* msg,...);
static void myprintD(int x,int y,const char* msg,...);
static void myprint2(int x,int y,const char* msg,...);
static void putfontS(int x,int y,const char* msg,...);
static void putfontSD(int x,int y,const char* msg,...);

/* Static variables */
int g_request=0;
int g_playing=0;
extern int _forcePause;
extern int _flingY;

/*
 *----------------------------------------------------------------------------
 * Save play list
 *----------------------------------------------------------------------------
 */
static void savelist()
{
	int i,j,k;
	FILE* fp=vge_fopen("playlist.dat","wb");
	if(NULL!=fp) {
		fwrite(&_mylist.no,4,1,fp);
		for(i=0;i<3;i++) {
			for(j=0,k=0;j<SONG_NUM;j++) {
				if(_mylist.id[i][j]) {
					k++;
				}
			}
			fwrite(&k,4,1,fp);
			for(j=0;j<SONG_NUM;j++) {
				if(_mylist.id[i][j]) {
					fwrite(&(_list[j].id),4,1,fp);
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
	int i,j,k,l,m;
	FILE* fp=vge_fopen("playlist.dat","rb");
	if(NULL!=fp) {
		fread(&_mylist.no,4,1,fp);
		if(2<_mylist.no || _mylist.no<0) {
			_mylist.no=0;
			fclose(fp);
			return;
		}
		for(i=0;i<3;i++) {
			fread(&k,4,1,fp);
			if(k<0 || SONG_NUM<k) {
				memset(&_mylist,0,sizeof(_mylist));
				fclose(fp);
				return;
			}
			for(j=0;j<k;j++) {
				fread(&l,4,1,fp);
				for(m=0;m<SONG_NUM;m++) {
					if(_list[m].id==l) {
						if(i==_mylist.no) _list[m].dis=1;
						_mylist.id[i][m]=1;
					}
				}
			}
		}
		fclose(fp);
	}
}

/*
 *----------------------------------------------------------------------------
 * Initialization
 *----------------------------------------------------------------------------
 */
int vge_init()
{
	loadlist();
	return 0;
}

/*
 *----------------------------------------------------------------------------
 * Termination
 *----------------------------------------------------------------------------
 */
int vge_term()
{
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
	static const char* tn[4]={
		 "SANKAKU"
		,"NOKOGIR"
		,"KUKEI  "
		,"NOIZE  "
	};
	static int pos[6];
	static int mcur=-1;
	static double base=4;
	static int bmin=-1320;
	static int bExist=SONG_NUM;
	static int push=0;
	static int pflag=0;
	static int touch_off=0;
	static int px,py;
	static int paused=1;
	static int infy=0;
	static int shuf=0;
	static int focus=0;
	static int interval=0;
	static int playwait=0;
	static int whourai=120;
	static int playing=0;
	static int interval2=0;
	static int slide;
	static int touchSB=0;
	static struct InputInf pi;
	static int editmode=0;
	static int touching=0;
	struct InputInf ci;
	int i,j,k;
	int dp;
	int wav;

	/* Play after wait */
	if(playwait) {
		playwait--;
		if(0==playwait) {
			g_playing=1;
			vge_bplay(_list[mcur].no);
			focus=1;
			whourai=120;
			playing=1;
		}
	}

	/* タッチ状態を取得 */
	vge_touch(&ci.s,&ci.cx,&ci.cy,&ci.dx,&ci.dy);
	if(ci.s) {
		focus=0;
		vge_rand();
		pflag=1;
		if(0==touching) {
			if(HITCHK(ci.cx-4,ci.cy-4,8,8,224,130,16,190)) {
				touching=1;
			} else {
				touching=2;
			}
		}
	} else if(pflag) {
		pflag=0;
		push=1;
		ci.s=1;
		ci.cx=px;
		ci.cy=py;
		slide=0;
	} else {
		touching=0;
		pflag=0;
		push=0;
		slide=0;
	}

	/* リストの上下移動 */
	if(slide==0) {
		if(4<ci.dy || ci.dy<-4) {
			slide=1;
		}
	}
	if(slide) {
		base+=ci.cy-pi.cy;
		push=0;
		touch_off=1;
	}
	if(ci.s==0 && touch_off) {
		touch_off=0;
	}
	memcpy(&pi,&ci,sizeof(ci));

#ifdef _WIN32
	if(g_mouse_roll) {
		base+=g_mouse_roll/8;
		if(4<base) base=4;
		if(base<bmin) base=bmin;
		g_mouse_roll=0;
	}
#endif

	/* Fling */
	if(touchSB) {
		touchSB--;
		_flingY=0;
	}
	if(ci.s==0 && _flingY) {
		int mv=_flingY/6;
		if(_flingY<0 && -1<mv) mv=_flingY;
		if(0<_flingY && mv<1) mv=_flingY;
		base+=mv;
		_flingY-=mv;
	}

	/* Overscroll */
	if(ci.s==0) {
		if(4<base) {
			double mv=(base-4)/6.66666;
			if(mv<1) {
				base=4;
			} else {
				base-=mv;
			}
		}
		if(base<bmin) {
			double mv=(bmin-base)/6.66666;
			if(mv<1) {
				base=bmin;
			} else {
				base+=mv;
			}
		}
	}

	/* Auto focus */
	if(focus) {
		if(mcur*20+130+base<130) {
			i=130-(mcur*20+130+base);
			if(10<i) i=10;
			base+=i;
		} else if(320<mcur*20+146+base) {
			i=(mcur*20+146+base)-320;
			if(10<i) i=10;
			base-=i;
		} else {
			focus=0;
		}
	}

	/* Draw music list */
	for(i=0;i<SONG_NUM;i++) {
		if(_list[i].dis) {
			_list[i].played=1;
		}
		dp=i*20+130+base;
		if(i<bExist && 114<dp && dp<320) {
			if(!editmode && _list[i].dis) {
				vge_boxfSP(4,i*20+130+base,220,i*20+146+base,102);
				vge_boxSP(4,i*20+130+base,220,i*20+146+base,104);
			} else {
				if(mcur==i) {
					vge_boxfSP(4,i*20+130+base,220,i*20+146+base,75);
					vge_boxSP(4,i*20+130+base,220,i*20+146+base,111);
				} else {
					if(ci.s && touch_off==0 && 2==touching
					&& HITCHK(ci.cx-4,ci.cy-4,8,8,0,130,240,190)
					&& HITCHK(4,i*20+130+base,216,16,ci.cx-4,ci.cy-4,8,8)) {
						vge_boxfSP(4,i*20+130+base,220,i*20+146+base,60);
						vge_boxSP(4,i*20+130+base,220,i*20+146+base,111);
						if(push) {
							if(editmode) {
								push=0;
								vge_eff(2);
								_list[i].dis=1-_list[i].dis;
								_mylist.id[_mylist.no][i]=_list[i].dis;
								if(_list[i].dis) {
									_list[i].played=1;
								} else {
									_list[i].played=0;
								}
							} else {
								push=0;
								ci.s=0;
								mcur=i;
								paused=0;
								_list[i].played=1;
								vge_bstop();
								playwait=6;
								playing=0;
							}
						}
					} else {
						if(_list[i].dis) {
							vge_boxfSP(4,i*20+130+base,220,i*20+146+base,102);
							vge_boxSP(4,i*20+130+base,220,i*20+146+base,104);
						} else {
							vge_boxfSP(4,dp,220,i*20+146+base,_list[i].col+4*_list[i].played);
							vge_boxSP(4,dp,220,i*20+146+base,105);
						}
					}
				}
			}
			if(_list[i].dis) {
				putfontSD(8,i*20+135+base,"%3d.",(i+1));
				myprintD(24,i*20+135+base,"%s",_list[i].text);
			} else {
				putfontS(8,i*20+135+base,"%3d.",(i+1));
				myprint(24,i*20+135+base,"%s",_list[i].text);
			}
			if(_list[i].gxs) {
				if(_list[i].dis) {
					if(_list[i].kage) {
						vge_putSPM(_list[i].gno, _list[i].gx, _list[i].gy, _list[i].gxs, 12, 25, i*20+134+base, 103);
					}
					vge_putSPM(_list[i].gno, _list[i].gx, _list[i].gy, _list[i].gxs, 12, 24, i*20+133+base,103);
				} else {
					if(_list[i].kage) {
						vge_putSPM(_list[i].gno, _list[i].gx, _list[i].gy, _list[i].gxs, 12, 25, i*20+134+base, 1);
					}
					vge_putSP(_list[i].gno, _list[i].gx, _list[i].gy, _list[i].gxs, 12, 24, i*20+133+base);
				}
			}
		}
	}
	myprint(4,i*20+135+base,"Composed by ZUN.");
	putfontS(4,i*20+145+base,"THIS IS AN ALTERNATIVE FICTION OF THE TOUHOU PROJECT.");
	vge_putSP(0,0,112,136,48,4,i*20+155+base);

	/* Scroll bar */
	vge_boxfSP(224,130,240,320,103);
	if(1==touching) {
		touchSB=30;
		base=ci.cy-142;
		base*=(-bmin*100)/166;
		base/=100;
		base=4-base;
		i=(0-base+4)*100/(-bmin)*116/100;
		vge_boxfSP(225,142+i,238,192+i,56);
	} else {
		i=(0-base+4)*100/(-bmin)*116/100;
		vge_boxfSP(225,142+i,238,192+i,108);
	}

	/* Cursor(Top) */
	if(base>=4) {
		vge_putSP(0,208,32,16,12,224,130);
	} else {
		if(1==touching && HITCHK(224,130,16,12,ci.cx-8,ci.cy-8,16,16)) {
			touchSB=30;
			vge_putSP(0,176,32,16,12,224,130);
			if(push) {
				base=4;
				push=0;
			}
		} else {
			vge_putSP(0,144,32,16,12,224,130);
		}
	}

	/* Cursor(Bottom) */
	if(base<=bmin) {
		vge_putSP(0,224,32,16,12,224,308);
	} else {
		if(1==touching && HITCHK(224,308,16,12,ci.cx-8,ci.cy-8,16,16)) {
			touchSB=30;
			vge_putSP(0,192,32,16,12,224,308);
			if(push) {
				base=bmin;
				push=0;
			}
		} else {
			vge_putSP(0,160,32,16,12,224,308);
		}
	}

	/* Draw play pannel */
	vge_boxfSP(0,0,240,130,3);
	myprint(4,2,"Touhou BGM on VGS");

	/* Configuration */
	if(!editmode) {
		if(ci.s && touch_off==0 && HITCHK(220,0,20,16,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0, 72,176, 16,8, 222, 2);
			if(push) {
				push=0;
				editmode=1;
				paused=1;
				g_playing=0;
				vge_bstop();
				_forcePause=0;
				playing=0;
				mcur=-1;
				vge_eff(0);
			}
		} else {
			vge_putSP(0, 72,160, 16,8, 222, 2);
		}
	} else {
		if(ci.s && touch_off==0 && HITCHK(220,0,20,16,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0, 72,176, 16,8, 222, 2);
			if(push) {
				push=0;
				editmode=0;
				vge_eff(1);
			}
		} else {
			vge_putSP(0, 72,160, 16,8, 222, 2);
		}
	}

	if(editmode) {
		vge_boxfSP(0,14,240,105,51);
		vge_lineSP(0,13,240,13,111);
		vge_lineSP(0,106,240,106,111);
		vge_lineSP(0,108,240,108,106);
		vge_lineSP(0,129,240,129,111);
		vge_lineSP(0,127,240,127,106);

		myprint(8,20,"CHOOSE A LIST");
		for(i=0;i<3;i++) {
			if(i==_mylist.no) {
				vge_boxfSP(20+i*70,32,80+i*70,50,58);
				vge_boxSP(20+i*70,32,80+i*70,50,63);
			} else {
				if(ci.s && touch_off==0 && HITCHK(20+i*70,32,60,18,ci.cx-4,ci.cy-4,8,8)) {
					vge_boxfSP(20+i*70,32,80+i*70,50,58);
					vge_boxSP(20+i*70,32,80+i*70,50,63);
					if(push) {
						vge_eff(2);
						_mylist.no=i;
						for(j=0;j<SONG_NUM;j++) {
							_list[j].dis=_mylist.id[_mylist.no][j];
						}
					}
				} else {
					vge_boxfSP(20+i*70,32,80+i*70,50,4);
					vge_boxSP(20+i*70,32,80+i*70,50,8);
				}
			}
			myprint(26+i*70,38,"LIST#%d",i+1);
		}

		for(i=0,j=0,k=0;i<SONG_NUM;i++) {
			if(_list[i].dis) {
				j++;
				_list[i].played=1;
			} else {
				k++;
				_list[i].played=0;
			}
		}

		myprint(8,64,"CHANGE ALL");
		if(k==SONG_NUM) {
			vge_boxfSP(34,76,106,96, 102);
			vge_boxSP(34,76,106,96, 104);
			myprintD(42,82,"ENABLED");
		} else {
			if(ci.s && touch_off==0 && HITCHK(34,76,72,20,ci.cx-4,ci.cy-4,8,8)) {
				vge_boxfSP(34,76,106,96, 58);
				vge_boxSP(34,76,106,96, 63);
				if(push) {
					vge_eff(0);
					for(i=0;i<SONG_NUM;i++) {
						_list[i].dis=0;
						_mylist.id[_mylist.no][i]=0;
					}
				}
			} else {
				vge_boxfSP(34,76,106,96, 4);
				vge_boxSP(34,76,106,96, 8);
			}
			myprint(42,82,"ENABLED");
		}

		if(j==SONG_NUM) {
			vge_boxfSP(134,76,206,96, 102);
			vge_boxSP(134,76,206,96, 104);
			myprintD(138,82,"DISABLED");
		} else {
			if(ci.s && touch_off==0 && HITCHK(134,76,72,20,ci.cx-4,ci.cy-4,8,8)) {
				vge_boxfSP(134,76,206,96, 58);
				vge_boxSP(134,76,206,96, 63);
				if(push) {
					vge_eff(1);
					for(i=0;i<SONG_NUM;i++) {
						_list[i].dis=1;
						_mylist.id[_mylist.no][i]=1;
					}
				}
			} else {
				vge_boxfSP(134,76,206,96, 4);
				vge_boxSP(134,76,206,96, 8);
			}
			myprint(138,82,"DISABLED");
		}

		putfontS(8,114,"PLEASE TAP A SONG TO ENABLE OR DISABLE.");
		px=ci.cx;
		py=ci.cy;
		return 0;
	}

	/* RegBoard */
	vge_boxfSP(0,14,240,105,51);
	vge_lineSP(0,13,240,13,111);
	vge_lineSP(0,106,240,106,111);
	vge_lineSP(0,108,240,108,106);
	vge_lineSP(0,129,240,129,111);
	vge_lineSP(0,127,240,127,106);
	if(mcur<0) {
		putfontS(8,16,"INDEX     %05d",_psg.nidx);
	} else {
		if(_list[mcur].loop) {
			if(infy) {
				putfontS(8,16,"INDEX     %05d  PLAYING %d",_psg.nidx,_psg.loop+1);
			} else {
				if(_psg.loop<_list[mcur].loop) {
					putfontS(8,16,"INDEX     %05d  PLAYING %d OF %d",_psg.nidx,_psg.loop+1,_list[mcur].loop);
				} else {
					putfontS(8,16,"INDEX     %05d  FADEOUT",_psg.nidx);
				}
			}
		} else {
			putfontS(8,16,"INDEX     %05d  ACYCLIC SONG",_psg.nidx);
		}
	}
	putfontS(8,24,"WAIT TIME %05d",_psg.waitTime);
	putfontS(8,32,"CH0 COUNT %05d  CH1 COUNT %05d  CH2 COUNT %05d",_psg.ch[0].count,_psg.ch[1].count,_psg.ch[2].count);
	putfontS(8,40,"CH3 COUNT %05d  CH4 COUNT %05d  CH5 COUNT %05d",_psg.ch[3].count,_psg.ch[4].count,_psg.ch[5].count);

	/* Clac wav pow */
	for(i=0;i<6;i++) {
		wav=_psg.wav[i];
		if(wav<0)wav=-wav;
		wav*=_psg.ch[i].vol;
		wav/=10;
		for(k=0;k<3;k++) {
			if(pos[i]<wav) {
				pos[i]=wav;
			} else {
				pos[i]--;
			}
		}
		if(164<pos[i]) {
			pos[i]=164;
		}
		putfontS(8,56+i*8,"CH%d %s %02d ",i,tn[_psg.ch[i].toneT],_psg.ch[i].toneK);
		for(j=0;j<pos[i];j++) {
			if(j%2) {
				vge_lineSP(68+j,57+i*8,68+j,63+i*8,46);
			}
		}
	}

	/* Check all disabled */
	for(i=0,j=0;i<SONG_NUM;i++) {
		if(_list[i].dis) {
			j++;
		} else {
			break;
		}
	}
	if(j==SONG_NUM) {
		putfontS(8,114,"THE ALL OF SONGS ARE DISABLED.");
		px=ci.cx;
		py=ci.cy;
		return 0;
	}

	/* PLAY  button */
	if(paused || mcur==-1) {
		if(ci.s && touch_off==0 && HITCHK(2,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0,48,32,24,12,2,112);
			if(push) {
				if(mcur==-1) {
					mcur=0;
					while(_list[mcur].dis) {
						mcur++;
						if(bExist<=mcur) {
							mcur=0;
						}
					}
					paused=0;
					playwait=6;
					vge_bstop();
					for(i=0;i<SONG_NUM;i++) {
						if(!_list[i].dis) {
							break;
						}
					}
					_list[i].played=1;
					playing=0;
				} else {
					if(_list[mcur].dis) {
						do {
							mcur++;
							if(bExist<=mcur) {
								mcur=0;
							}
						} while(_list[mcur].dis);
						paused=0;
						vge_bstop();
						playing=0;
						playwait=6;
						_list[mcur].played=1;
						focus=1;
						interval=0;
					} else {
						paused=0;
						vge_bresume();
						playing=1;
					}
				}
			}
		} else {
			vge_putSP(0,0,32,24,12,2,112);
		}
	} else {
		if(ci.s && touch_off==0 && HITCHK(2,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0,48,32,24,12,2,112);
			if(push) {
				paused=0;
				playwait=6;
				_list[mcur].played=1;
				vge_bstop();
				playing=0;
			}
		} else {
			vge_putSP(0,0,32,24,12,2,112);
		}
	}

	/* PAUSE button */
	if(paused) {
		vge_putSP(0,120,32,24,12,28,112);
		if(_forcePause) {
			_forcePause=0;
		}
	} else {
		if(_forcePause) {
			paused=1;
			g_playing=0;
			vge_bstop();
			_forcePause=0;
			playing=0;
		} else if(ci.s && touch_off==0 && HITCHK(28,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0,72,32,24,12,28,112);
			if(push) {
				g_playing=0;
				paused=1;
				vge_bstop();
				playing=0;
			}
		} else {
			vge_putSP(0,24,32,24,12,28,112);
		}
	}

	/* INFINITE button */
	if(ci.s && touch_off==0 && HITCHK(54,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
		vge_putSP(0,168,80,24,12,54,112);
		if(push) {
			infy=1-infy;
		}
	} else {
		vge_putSP(0,144+(1-infy)*48,80,24,12,54,112);
	}

	if(!infy) {
		/* SHUFFLE button */
		if(ci.s && touch_off==0 && HITCHK(80,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
			vge_putSP(0,168,96,24,12,80,112);
			if(push) {
				shuf=1-shuf;
			}
		} else {
			vge_putSP(0,144+(1-shuf)*48,96,24,12,80,112);
		}
		/* LOOP COUNTER */
		if(-1==mcur || 0<=mcur && _list[mcur].loop) {
			if(ci.s && touch_off==0 && HITCHK(106,92,24,32,ci.cx-4,ci.cy-4,8,8)) {
				vge_putSP(0,(_list[0].loop-1)*24,176,24,12,106,112);
				if(push) {
					for(i=0;i<bExist;i++) {
						if(_list[i].loop) {
							_list[i].loop++;
							if(3<_list[i].loop) {
								_list[i].loop=1;
							}
						}
					}
				}
			} else {
				vge_putSP(0,(_list[0].loop-1)*24,160,24,12,106,112);
			}
		}
	}

	// acyclic song
	if(0==playwait && playing && 0==_psg.waitTime) {
		if(0==interval2) {
			interval2=1;
			if(shuf) {
				for(i=0;i<bExist;i++) if(_list[i].played==0) break;
				if(bExist==i) {
					for(j=0;j<SONG_NUM;j++) {
						if(_list[j].dis) {
							_list[j].played=1;
						} else {
							_list[j].played=0;
						}
					}
				}
			}
		} else {
			interval2++;
			if(60<=interval2) {
				if(infy==0) {
					if(shuf) {
						do {
							mcur=vge_rand()%bExist;
						} while(_list[mcur].played);
					} else {
						do {
							mcur++;
							if(bExist<=mcur) {
								mcur=0;
							}
						} while(_list[mcur].dis);
					}
				}
				paused=0;
				playing=0;
				playwait=6;
				_list[mcur].played=1;
				focus=1;
				interval=0;
				interval2=0;
			}
		}
	} else {
		interval2=0;
	}

	// cyclic songs
	if(-1!=mcur && 0==infy && _list[mcur].loop && _list[mcur].loop<=_psg.loop) {
		if(shuf) {
			for(i=0;i<bExist;i++) if(_list[i].played==0) break;
			if(bExist==i) {
				for(j=0;j<SONG_NUM;j++) {
					if(_list[j].dis) {
						_list[j].played=1;
					} else {
						_list[j].played=0;
					}
				}
			}
		}
		if(_psg.fade2==0) {
			_psg.fade2=1;
			interval=0;
		}
		if(100<=_psg.fade2) {
			if(interval<30) {
				interval++;
			} else {
				if(shuf) {
					do {
						mcur=vge_rand()%bExist;
					} while(_list[mcur].played);
				} else {
					do {
						mcur++;
						if(bExist<=mcur) {
							mcur=0;
						}
					} while(_list[mcur].dis);
				}
				paused=0;
				vge_bstop();
				playing=0;
				playwait=6;
				_list[mcur].played=1;
				focus=1;
				interval=0;
			}
		}
	}

	px=ci.cx;
	py=ci.cy;
	return 0;
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
static void myprint(int x,int y,const char* msg,...)
{
	char buf[256];
	int i;
	int c;
	int d;
	va_list args;

	va_start(args,msg);
	vsprintf(buf,msg,args);
	va_end(args);

	for(i=0;'\0'!=(c=(int)buf[i]);i++,x+=8) {
		c-=0x20;
		c&=0x7f;
		d=c>>5;
		vge_putSPM(0,(c-(d<<5))<<3,d<<3,8,8,x+1,y+1,1);
		vge_putSP(0,(c-(d<<5))<<3,d<<3,8,8,x,y);
	}
}

static void myprintD(int x,int y,const char* msg,...)
{
	char buf[256];
	int i;
	int c;
	int d;
	va_list args;

	va_start(args,msg);
	vsprintf(buf,msg,args);
	va_end(args);

	for(i=0;'\0'!=(c=(int)buf[i]);i++,x+=8) {
		c-=0x20;
		c&=0x7f;
		d=c>>5;
		vge_putSPM(0,(c-(d<<5))<<3,d<<3,8,8,x+1,y+1,103);
		vge_putSPM(0,(c-(d<<5))<<3,d<<3,8,8,x,y,103);
	}
}

static void myprint2(int x,int y,const char* msg,...)
{
	char buf[256];
	int i;
	int c;
	int d;
	va_list args;

	va_start(args,msg);
	vsprintf(buf,msg,args);
	va_end(args);

	for(i=0;'\0'!=(c=(int)buf[i]);i++,x+=8) {
		c-=0x20;
		c&=0x7f;
		d=c>>5;
		vge_putSPM(0,(c-(d<<5))<<3,d<<3,8,8,x+1,y+1,1);
		vge_putSPM(0,(c-(d<<5))<<3,d<<3,8,8,x,y,106);
	}
}

/*
 *----------------------------------------------------------------------------
 * print 4x8 font
 *----------------------------------------------------------------------------
 */
static void putfontS(int x,int y,const char* msg,...)
{
	char buf[64];
	int i;
	char c;
	va_list args;

	va_start(args,msg);
	vsprintf(buf,msg,args);
	va_end(args);

	for(i=0;'\0'!=(c=buf[i]);i++) {
		if('0'<=c && c<='9') {
			c-='0';
			vge_putSPM(0,c*4,24,4,8,x+i*4+1,y+1,1);
			vge_putSP(0,c*4,24,4,8,x+i*4,y);
		}
		else if('A'<=c && c<='Z') {
			c-='A';
			vge_putSPM(0,40+c*4,24,4,8,x+i*4+1,y+1,1);
			vge_putSP(0,40+c*4,24,4,8,x+i*4,y);
		}
		else if('.'==c) {
			vge_putSPM(0,144,24,4,8,x+i*4+1,y+1,1);
			vge_putSP(0,144,24,4,8,x+i*4,y);
		}
	}
}

static void putfontSD(int x,int y,const char* msg,...)
{
	char buf[64];
	int i;
	char c;
	va_list args;

	va_start(args,msg);
	vsprintf(buf,msg,args);
	va_end(args);

	for(i=0;'\0'!=(c=buf[i]);i++) {
		if('0'<=c && c<='9') {
			c-='0';
			vge_putSPM(0,c*4,24,4,8,x+i*4+1,y+1,103);
			vge_putSPM(0,c*4,24,4,8,x+i*4,y,103);
		}
		else if('A'<=c && c<='Z') {
			c-='A';
			vge_putSPM(0,40+c*4,24,4,8,x+i*4+1,y+1,103);
			vge_putSPM(0,40+c*4,24,4,8,x+i*4,y,103);
		}
		else if('.'==c) {
			vge_putSPM(0,144,24,4,8,x+i*4+1,y+1,103);
			vge_putSPM(0,144,24,4,8,x+i*4,y,103);
		}
	}
}
