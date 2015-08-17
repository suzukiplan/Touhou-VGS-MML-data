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
};

static void trimstring(char* src)
{
	int i,j;
	int len;
	for(i=0;' '==src[i];i++);
	if(i) {
		for(j=0;src[i]!='\0';j++,i++) {
			src[j]=src[i];
		}
		src[j]='\0';
	}
	for(len=(int)strlen(src)-1;0<=len && ' '==src[len];len--) {
		src[len]='\0';
	}
}

int main(int argc,char* argv[])
{
	FILE* fpR;
	FILE* fpW;
	char* token[6];
	char buf[1024];
	int tn,i;
	struct SongData dat;
	int w=0;

	if(argc<3) {
		puts("usage: mklist input output");
		return 1;
	}

	fpR=fopen(argv[1],"rt");
	if(NULL==fpR) {
		puts("Could not open the input file.");
		return 2;
	}

	fpW=fopen(argv[2],"wb");
	if(NULL==fpW) {
		puts("Could not open the output file.");
		fclose(fpR);
		return 2;
	}

	while(fgets(buf,sizeof(buf),fpR)) {
		memset(token,0,sizeof(token));
		token[0]=&buf[0];
		for(tn=1,i=0;buf[i]!='\0';i++) {
			if(buf[i]=='\n' || buf[i]=='\r') {
				buf[i]='\0';
				break;
			}
			if('#'==buf[i]) {
				buf[i]='\0';
				break;
			}
			if(tn<6 && ','==buf[i]) {
				buf[i]='\0';
				token[tn++]=&buf[i+1];
			}
		}
		if(tn<5) continue;
		for(i=0;i<5;i++) {
			trimstring(token[i]);
		}
		memset(&dat,0,sizeof(dat));
		dat.id=(int)strtol(token[0],NULL,16);
		dat.no=atoi(token[1]);
		dat.loop=atoi(token[2]);
		dat.col=atoi(token[3]);
		strcpy(dat.text,token[4]);
		dat.played=0;
		dat.dis=0;
		fwrite(&dat,sizeof(dat),1,fpW);
		w++;
	}
	printf("%d songs wrote.\n",w);

	fclose(fpR);
	fclose(fpW);
	return 0;
}
