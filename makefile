ASSETS=\
	data/DSLOT000.DAT\
	data/DSLOT001.DAT\
	data/DSLOT002.DAT\
	data/GSLOT000.CHR\
	data/GSLOT255.CHR\
	data/ESLOT000.PCM\
	data/ESLOT001.PCM\
	data/ESLOT002.PCM\
	data/BSLOT000.BGM\
	data/BSLOT001.BGM\
	data/BSLOT002.BGM\
	data/BSLOT003.BGM\
	data/BSLOT004.BGM\
	data/BSLOT005.BGM\
	data/BSLOT006.BGM\
	data/BSLOT007.BGM\
	data/BSLOT008.BGM\
	data/BSLOT009.BGM\
	data/BSLOT010.BGM\
	data/BSLOT011.BGM\
	data/BSLOT012.BGM\
	data/BSLOT013.BGM\
	data/BSLOT014.BGM\
	data/BSLOT015.BGM\
	data/BSLOT016.BGM\
	data/BSLOT017.BGM\
	data/BSLOT018.BGM\
	data/BSLOT019.BGM\
	data/BSLOT020.BGM\
	data/BSLOT021.BGM\
	data/BSLOT022.BGM\
	data/BSLOT023.BGM\
	data/BSLOT024.BGM\
	data/BSLOT025.BGM\
	data/BSLOT026.BGM\
	data/BSLOT027.BGM\
	data/BSLOT028.BGM\
	data/BSLOT029.BGM\
	data/BSLOT030.BGM\
	data/BSLOT031.BGM\
	data/BSLOT032.BGM\
	data/BSLOT033.BGM\
	data/BSLOT034.BGM\
	data/BSLOT035.BGM\
	data/BSLOT036.BGM\
	data/BSLOT037.BGM\
	data/BSLOT038.BGM\
	data/BSLOT039.BGM\
	data/BSLOT040.BGM\
	data/BSLOT041.BGM\
	data/BSLOT042.BGM\
	data/BSLOT043.BGM\
	data/BSLOT044.BGM\
	data/BSLOT045.BGM\
	data/BSLOT046.BGM\
	data/BSLOT047.BGM\
	data/BSLOT048.BGM\
	data/BSLOT049.BGM\
	data/BSLOT050.BGM\
	data/BSLOT051.BGM\
	data/BSLOT052.BGM\
	data/BSLOT053.BGM\
	data/BSLOT054.BGM\
	data/BSLOT055.BGM\
	data/BSLOT056.BGM\
	data/BSLOT057.BGM\
	data/BSLOT058.BGM\
	data/BSLOT059.BGM\
	data/BSLOT060.BGM\
	data/BSLOT061.BGM\
	data/BSLOT062.BGM\
	data/BSLOT063.BGM\
	data/BSLOT064.BGM\
	data/BSLOT065.BGM\
	data/BSLOT066.BGM\
	data/BSLOT067.BGM\
	data/BSLOT068.BGM\
	data/BSLOT069.BGM\
	data/BSLOT070.BGM\
	data/BSLOT071.BGM\
	data/BSLOT072.BGM\
	data/BSLOT073.BGM\
	data/BSLOT074.BGM\
	data/BSLOT075.BGM\
	data/BSLOT076.BGM\
	data/BSLOT077.BGM\
	data/BSLOT078.BGM\
	data/BSLOT079.BGM\
	data/BSLOT080.BGM\
	data/BSLOT081.BGM\
	data/BSLOT082.BGM\
	data/BSLOT083.BGM\
	data/BSLOT084.BGM\
	data/BSLOT085.BGM\
	data/BSLOT086.BGM\
	data/BSLOT087.BGM\
	data/BSLOT088.BGM\
	data/BSLOT089.BGM\
	data/BSLOT090.BGM\
	data/BSLOT091.BGM\
	data/BSLOT092.BGM\
	data/BSLOT093.BGM\
	data/BSLOT094.BGM\
	data/BSLOT095.BGM\
	data/BSLOT096.BGM\
	data/BSLOT097.BGM\
	data/BSLOT098.BGM\
	data/BSLOT099.BGM\
	data/BSLOT100.BGM\
	data/BSLOT101.BGM\
	data/BSLOT102.BGM\
	data/BSLOT103.BGM\
	data/BSLOT104.BGM\
	data/BSLOT105.BGM

all: mklist mklist2 mkmeta mkpack romdata.bin 

build: $(ASSETS)

clean:
	rm -f mklist mklist2 mkmeta
	rm -f $(ASSETS)
	rm -f data/*.vgs
	rm -f *.sjis
	rm -f tohovgs.pkg
	rm -rf vgspack

mklist: src/mklist.c
	gcc -o mklist src/mklist.c

mklist2: src/mklist2.c
	gcc -o mklist2 src/mklist2.c

mkmeta: src/mkmeta.c
	gcc -o mkmeta src/mkmeta.c

mkpack: src/mkpack.c src/vgs2tar.c src/vgs2tar.h src/vgs2pack.h
	gcc -o mkpack src/mkpack.c src/vgs2tar.c

.SUFFIXES: .bmp .CHR
.bmp.CHR:
	vgsbmp $< $@

.SUFFIXES: .wav .PCM
.wav.PCM:
	vgs2wav $< $@

.SUFFIXES: .mml .BGM
.mml.BGM:
	vgs2mml $< $@
	./mkmeta $<
	vgs2pack $<

romdata.bin: $(ASSETS)
	vgs2rom ./data romdata.bin 
	vgs2tar tohovgs.pkg data/*.vgs
	./mkpack

data/DSLOT000.DAT: songlist.txt
	iconv -f UTF-8 -t SJIS < songlist.txt > songlist.txt.sjis
	./mklist songlist.txt.sjis data/DSLOT000.DAT

data/DSLOT001.DAT: songlist_en.txt
	iconv -f UTF-8 -t SJIS < songlist_en.txt > songlist_en.txt.sjis
	./mklist songlist_en.txt.sjis data/DSLOT001.DAT

data/DSLOT002.DAT: titlelist.txt
	iconv -f UTF-8 -t SJIS < titlelist.txt > titlelist.txt.sjis
	./mklist2 titlelist.txt.sjis data/DSLOT002.DAT

