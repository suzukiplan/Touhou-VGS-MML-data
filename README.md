このリポジトリは、東方BGM on VGSのソースコード、各種情報（バグ、エンハンス、レビュー等）を管理する目的のものです。

# 再生方法
### 東方BGM on VGS（iPhone/Android）
- iPhone: https://itunes.apple.com/jp/app/dong-fangbgm-on-vgs/id680248037?mt=8
- Android: https://play.google.com/store/apps/details?id=com.suzukiplan.TOHOVGS
- 多分、これが一番簡単だと思います

### VGS BGM Player（iPhone）
- https://itunes.apple.com/us/app/vgs-bgm-player/id1056898557?mt=8
- [vgspackディレクトリ](https://github.com/suzukiplan/Touhou-VGS-MML-data/tree/master/vgspack) の内容をDropboxに保存してアプリからアクセスすれば、インポートすることができます
- 東方BGM on VGSより若干まどるっこしいですが、最新の曲や自作の曲が再生できたりします

### VGS mk-II SR（Mac or Linux）
- https://github.com/suzukiplan/vgs2
- ここで公開しているmmlファイルは、Mac（OS X 10.3以降推奨） か Linux（CentOS7推奨）を搭載したパソコンを持っていれば簡単に視聴できます。（Windowsでも多分使えますが obsoleted です）
- 詳しい手順は[こちら](https://gist.github.com/suzukiplan/ce6126d5344dd9a46e56)のシェルスクリプトを参照してください。
- 自作のプレイヤやプラグインを作って演奏したかったりする上級者向け。
- また、「このアレンジは気に食わん！」などと思った方は、VGS mk-II SRを使えば誰でも自由にカスタマイズできるので、自分でアレンジしてお楽しみください

### VGS BGM Decoder
- https://github.com/suzukiplan/vgs-bgm-decoder
- プログラマ専用（分かる人だけ使ってください）

# MMLの作成方法
### MMLとは？
- MML（Music Macro Language）とは、テキストで記述する音楽データのことです。
- midi等の祖先だと思っておけば概ね間違いありません。
- 標準的な規格は存在しないので、色々な方言が存在します。

### VGSのMMLの書き方＆鳴らし方
- VGSのMMLの仕様は [こちらのドキュメント](https://github.com/suzukiplan/vgs2/blob/master/MML.md) を参照してください。
- [SUZUKI PLAN - Video Game System MK-II SR](https://github.com/suzukiplan/vgs2) をインストールすればMMLをコンパイル＆演奏することができます。
- MMLのコンパイルには [vgs2mmlコマンド](https://github.com/suzukiplan/vgs2/blob/master/Command.md#vgs2mml) を用います。
- コンパイルしたMMLの演奏には [vgs2playコマンド](https://github.com/suzukiplan/vgs2/blob/master/Command.md#vgs2play) を用います。

### 作成した音楽データをVGS BGM Playerで演奏
- [vgs2mmlコマンド](https://github.com/suzukiplan/vgs2/blob/master/Command.md#vgs2mml) で作成した音楽データは、そのままの状態では VGS BGM Player で演奏することができません。
- 作成した音楽データを VGS BGM Player で演奏するには meta data を記述して、[vgs2packコマンド](https://github.com/suzukiplan/vgs2/blob/master/Command.md#vgs2pack)でBGMファイルとmetaファイルを結合する必要があります。
- meta dataの詳細については[こちらのドキュメント](https://github.com/suzukiplan/vgs2/blob/master/META.md)を参照してください。

# サポート情報
### 各種報告について
基本的にアプリのレビューは全て漏れなくチェックしているので、要望事項がある場合、レビューに書いて頂く方が手っ取り早いですが、機能の追加や不具合の報告の類の場合、Issuesを発行することを推奨します。レビューと違い、双方向でやり取りができるので、Issuesの方が正確に伝わる可能性が高いかもしれません。

### リクエストについて
- 曲のリクエストについては、Issuesではなくレビューの方でご連絡ください。
- やろうとしている曲の方針やリストは後述します。
- なお、リストに載っている曲でも、特にリクエストが多いものは優先的に着手する可能性が高いです。

### 対応予定曲の方針について
- やるのは Copyright が ZUN SOFT or 上海アリス幻樂団 の作品のみ
- 共同制作の類（西方や格ゲーや酒場など）は権利関係がよく分からないから原則やらない

>- 例外1: 音楽CDに録音されているものであればやる可能性がある（例：二色蓮花蝶）
>- 例外2: 東方幻想的音楽に掲載されているものについてはやる（例：☆秋霜玉）

- 二次創作作品は権利関係上NGのものもあるからやらない
- 二次創作作品については可能なものも幾つかあるが、ひとつやると全てできると誤解する人が必ず現れるため、できるものもやらない
- 東方Projectの二次創作ガイドラインについては、本リポジトリのWikiに簡単に記載しています

# 公開しているMMLの使用許諾
- 本MMLデータは、東方Projectの二次創作ガイドラインに準じて作成したものです。
- 本MMLデータは、東方Projectの二次創作ガイドラインに準拠した作品（以下、二次創作物）でご利用いただけます。
- 本MMLデータを改変したデータについても、二次創作物でご利用いただけます。

1-1 動画コンテンツ（YouTube、ニコニコ動画、ニコニコ大百科のピコカキコ等）での利用について
- 東方Projectの二次創作ガイドラインに準拠していれば、事前・事後の連絡無くご自由に利用いただけます。
- 利用により当方（SUZUKI PLAN）以外の第三者と何らかのトラブルが生じた場合、利用者が全ての責任を負うものとします。

1-2 自身で譜面データを作成できる音ゲー（BM98や太鼓さん二郎等）での利用について
- 1-1（動画コンテンツ）と同じルールでご利用いただけます。

1-3 プログラム製品・アプリへの組み込みについて
- 利用者は、GitHubアカウントを有し、本リポジトリを必ずforkするものとします。
- 利用により当方（SUZUKI PLAN）が不利益を被ると判断できる事由があった場合、利用を差し止めることがあります。
- 利用により当方（SUZUKI PLAN）以外の第三者と何らかのトラブルが生じた場合、利用者が全ての責任を負うものとします。

_※以前、別の形で公開していたMMLについては、ここの使用許諾を適用しません。各公開ドキュメントに付随している方の使用許諾を優先してください。_

# 対応予定リスト

### 東方靈異伝 (0/29)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|A Sacred Lot|タイトル画面テーマ|
|2|-|風の神社|未使用曲|
|3|-|永遠の巫女|１～４面、地獄１６～１９面テーマ|
|4|-|Highly Responsive to Prayers|魔界６～９面テーマ|
|5|-|東方怪奇談|地獄６～９面テーマ|
|6|-|Oriental Magician|魔界１１～１４面テーマ|
|7|-|破邪の小太刀|地獄１１～１４面テーマ|
|8|-|The Legend of KAGE|魔界１６～１９面テーマ|
|9|-|The Positive and Negative|５面テーマ|
|10|-|天使伝説|１０面テーマ|
|11|-|魔鏡|１５面テーマ|
|12|-|いざ、倒れ逝くその時まで|魔界最終面テーマ１|
|13|-|死なばもろとも|魔界最終面テーマ２|
|14|-|星幽剣士|地獄最終面テーマ|
|15|-|アイリス|エンディングテーマ|
|16|-|_A Sacred Lot_|タイトルテーマ PMDアレンジ版|
|17|-|_永遠の巫女_|１～４面、地獄１６～１９面テーマ（ちょっとアレンジ版）|
|18|-|_The Positive and Negative_|５面テーマ（快速アレンジ版）|
|19|-|_Highly Responsive to Prayers_|魔界６～９面テーマ（ほんのりアレンジ版）|
|20|-|_東方怪奇談_|地獄６～９面テーマ（さわやかアレンジ版）|
|21|-|_天使伝説_|１０面テーマ（こってりアレンジ版）|
|22|-|_Oriental Magician_|魔界１１～１４面テーマ（ノリノリアレンジ版）|
|23|-|_破邪の小太刀_|地獄１１～１４面テーマ（しあわせアレンジ版）|
|24|-|_魔鏡_|１５面テーマ（夢幻アレンジ版）|
|25|-|_the Legend of KAGE_|魔界１６～１９面テーマ（ダークアレンジ版）|
|26|-|_いざ、倒れ逝くその時まで_|魔界最終面テーマ１（まったりアレンジ版）|
|27|-|_Civilization of Magic_|魔界最終面テーマ２（ゆったりアレンジ版）|
|28|-|_星幽天使_|地獄最終面テーマ（のんびりアレンジ版）|
|29|-|_アイリス_|エンディングテーマ（6月アレンジ版）|

### 東方封魔録 (0/21)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|東方封魔録　～浄土曼荼羅||タイトル画面|
|2|-|博麗　～Eastern Wind|１面テーマ|
|3|-|She's in a temper!!|１面ボス・里香のテーマ１|
|4|-|End of Daylight|２面テーマ|
|5|-|やみのちから|２面ボス・明羅のテーマ|
|6|-|幻夢界|３面テーマ|
|7|-|死を賭して|３面ボス|
|8|-|ひもろぎ、むらさきにもえ|４面テーマ|
|9|-|恋色マジック|４面ボス・魔理沙のテーマ|
|10|-|東方封魔録　～幽幻乱舞|最終面テーマ|
|11|-|Complete Darkness|最終面ボス・魅魔のテーマ|
|12|-|エキストララブ|エキストラステージテーマ|
|13|-|戦車むすめのみるゆめ|エキストラボス・里香のテーマ２|
|14|-|遠野の森|エンディングテーマ|
|15|-|昔話わんだーらんど|スタッフロールテーマ|
|16|-|_ひもろぎ、むらさきにもえ_|Remix|
|17|-|_東方封魔録　～幽幻乱舞_|Remix|
|18|-|_Complete Darkness_|Remix|
|19|-|_博麗神社境内_|未使用曲（１面テーマ）|
|20|-|_陽落ちて_|未使用曲（２面テーマ）|
|21|-|封魔終演|未使用曲（スタッフロールテーマ）|

### 東方夢時空 (0/24)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|夢は時空を越えて|タイトル画面テーマ|
|2|-|Selection|使用キャラ選択テーマ|
|3|-|東方妖恋談|博麗 靈夢のテーマ|
|4|-|Reincarnation|魅魔のテーマ|
|5|-|Dim. Dream|霧雨 魔理沙のテーマ|
|6|-|Tabula rasa　～ 空白少女|エレンのテーマ|
|7|-|Maniacal Princess|小兎姫のテーマ|
|8|-|夢消失　～ Lost Dream|カナ・アナベラルのテーマ|
|9|-|夢幻遊戯　～ Dream War|朝倉 理香子のテーマ|
|10|-|魔法決戦！　～ Fight it out!|ＣＰＵ７人目のテーマ|
|11|-|Sailor of Time|北白河 ちゆりのテーマ|
|12|-|Strawberry Crisis!!|岡崎 夢美のテーマ|
|13|-|非統一魔法世界論|中ボスデモテーマ|
|14|-|魔法鐘愛|夢美デモテーマ|
|15|-|久遠の夢|共通エンディングテーマ|
|16|-|東方の青い空|昼のエンディングテーマ|
|17|-|永遠の満月|夜のエンディングテーマ|
|18|-|Maple Dream...|スタッフロールテーマ|
|19|-|霊人の休日|ネームレジストテーマ|
|20|-|勝利デモ|勝利デモテーマ|
|21|-|ゲームオーバー|ゲームオーバーテーマ|
|22|-|_時の風_|未使用曲|
|23|-|_スターボウドリーム_|未使用曲|
|24|-|_Phantasmagoria_|未使用曲|

### 東方幻想郷 (13/28)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT079.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT079.mml)|幻想郷　～ Lotus Land Story|タイトル画面テーマ|
|2|[BSLOT080.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT080.mml)|Witching Dream|靈夢１面のテーマ|
|3|[BSLOT081.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT081.mml)|Selene's Light|魔理沙１面のテーマ|
|4|[BSLOT082.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT082.mml)|装飾戦　～ Decoration Battle|１面ボス・オレンジのテーマ|
|5|[BSLOT086.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT086.mml)|Break the Sabbath|２面テーマ|
|6|[BSLOT087.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT087.mml)|紅響曲　～ Scarlet Phoneme|２面ボス・くるみのテーマ|
|7|[BSLOT061.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT061.mml)|Bad Apple!!|３面テーマ|
|8|[BSLOT078.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT078.mml)|霊戦　～ Perdition crisis|３面ボス・エリーのテーマ|
|9|[BSLOT075.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT075.mml)|アリスマエステラ|４面テーマ|
|10|[BSLOT074.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT074.mml)|少女綺想曲　～ Capriccio|４面ボス・靈夢のテーマ|
|11|[BSLOT073.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT073.mml)|星の器　～ Casket of Star|４面ボス・魔理沙のテーマ|
|12|[BSLOT105.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT105.mml)|Lotus Love|５面テーマ|
|13|[BSLOT106.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT106.mml)|眠れる恐怖　～ Sleeping Terror|５面ボス・幽香のテーマ１|
|14|-|Dream Land|最終面テーマ|
|15|-|幽夢　～ Inanimate Dream|最終面ボス・幽香のテーマ２|
|16|-|禁じざるをえない遊戯|エキストラステージテーマ|
|17|-|メイド幻想　～ Icemilk Magic|エキストラボス・夢月のテーマ|
|18|-|かわいい悪魔　～ Innocence|エキストラボス・幻月のテーマ|
|19|-|Days|バッドエンドのテーマ|
|20|-|Peaceful|グッドエンドのテーマ|
|21|-|Arcadian Dream|スタッフロールのテーマ|
|22|-|幻想の住人|ネームレジストのテーマ|
|23|-|_Lotus Road_|未使用曲（１面テーマ）|
|24|-|_Dreamy pilot_|未使用曲（４面テーマ）|
|25|-|_Incomplete Plot_|未使用曲（５面テーマ）|
|26|-|_Border Land_|未使用曲（６面テーマ）|
|27|-|_Magic Shop of Raspberry_|未使用曲（エキストラステージテーマ）|
|28|-|_Crescent Dream_|未使用曲（スタッフロールテーマ）|

### 東方怪綺談 (2/23)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|怪綺談　～ Mystic Square|タイトル画面テーマ|
|2|-|Dream Express|１面テーマ|
|3|-|魔法陣　～ Magic Square|１面ボス・サラのテーマ|
|4|-|夢想時空|２面テーマ|
|5|-|霊天　～ Spiritual Heaven|２面ボス・ルイズのテーマ|
|6|-|Romantic Children|３面テーマ|
|7|-|プラスチックマインド|３面ボス・アリスのテーマ１|
|8|-|メイプルワイズ|４面テーマ|
|9|-|禁断の魔法　～ Forbidden Magic|４面ボス・ユキ＆マイのテーマ|
|10|-|真紅の少女　～ Crimson Dead!!|４面ボス・ユキのテーマ|
|11|-|裏切りの少女　～ Judas Kiss|４面ボス・マイのテーマ|
|12|-|the Last Judgement|５面テーマ|
|13|-|悲しき人形　～ Doll of Misery|５面ボス・夢子のテーマ|
|14|-|世界の果て　～ World's End|６面テーマ|
|15|-|神話幻想　～ Infinite Being|６面ボス・神綺のテーマ|
|16|[BSLOT062.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT062.mml)|不思議の国のアリス|エキストラステージテーマ|
|17|[BSLOT063.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT063.mml)|the Grimoire of Alice|エキストラボス・アリスのテーマ２|
|18|-|神社|バッドエンドテーマ|
|19|-|Endless|グッドエンドテーマ１|
|20|-|久遠の楽園|グッドエンドテーマ２|
|21|-|Mystic Dream|スタッフロールテーマ|
|22|-|Peaceful Romancer|エキストラエンディングのテーマ|
|23|-|魂の休らむ所|ネームレジストテーマ|

### 東方幻想的音楽

#### （☆秋霜玉）(0/19)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|秋霜玉　～ Clockworks|タイトルテーマ|
|2|-|フォルスストロベリー|１面のテーマ|
|3|-|プリムローズシヴァ|１面ボス ミリアのテーマ|
|4|-|幻想帝都|２面のテーマ|
|5|-|ディザストラスジェミニ|２面ボス めい＆まいのテーマ|
|6|-|華の幻想 紅夢の宙|３面のテーマ|
|7|-|天空アーミー|３面ボス ゲイツのテーマ|
|8|-|スプートニク幻夜|４面のテーマ|
|9|-|機械サーカス　～ Reverie|４面ボス ミリアのテーマ|
|10|-|カナベラルの夢幻少女|５面のテーマ|
|11|-|魔法少女十字軍 |５面ボス エーリッヒのテーマ|
|12|-|アンティークテラー|最終面（６面）のテーマ|
|13|-|夢機械　～ Innocent Power|最終ボス エーリッヒの娘のテーマ(1)|
|14|-|幻想科学　～ Doll's Phantom|最終ボス エーリッヒの娘のテーマ(2)|
|15|-|少女神性　～ Pandora's Box|最終ボス エーリッヒの娘のテーマ(3)|
|16|-|シルクロードアリス|エキストラステージのテーマ|
|17|-|魔女達の舞踏会|エキストラボス１ 霧雨 魔理沙のテーマ|
|18|-|二色蓮花蝶　～ Ancients|エキストラボス２ 博麗 霊夢のテーマ|
|19|-|ハーセルヴズ|エンディングテーマ|

#### （☆トルテ ル マジック）(0/3)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|Witch of Love Potion|通常面テーマ|
|2|-|Magical and Hopeless|シューのテーマ|
|3|-|Sacred Battle|コアントローのテーマ|

#### （ZUN's Strange Works）(3/6)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT103.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT103.mml)|宵闇の魔術師|ふぁんたすていかに激しく|
|2|-|Magic of Life|残酷なアリス系|
|3|[BSLOT077.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT077.mml)|Plastic Space|秋霜玉'99（勝手に命名）１面テーマ|
|4|-|Inventive City|秋霜玉'99 ２面テーマ|
|5|-|夢幻回廊|スロウテンポにワアルド音楽|
|6|[BSLOT104.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT104.mml)|蓬莱幻想　～ far East|秋霜玉　エキストラステージのテーマ（未使用）|

### 蓬莱人形 (1/13)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT059.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT059.mml)|蓬莱伝説|オリジナル|
|2|-|二色蓮花蝶　～ Red and White|秋霜玉より|
|3|-|桜花之恋塚　～ Japanese Flower|稀翁玉より|
|4|-|明治十七年の上海アリス|オリジナル（こちらがオリジナルで紅魔郷の方がアレンジ）|
|5|-|東方怪奇談|東方霊異伝より|
|6|-|エニグマティクドール|稀翁玉より|
|7|-|サーカスレヴァリエ|秋霜玉より|
|8|-|人形の森|オリジナル|
|9|-|Witch of Love Potion|トルテルマジックより|
|10|-|リーインカーネイション|東方夢時空より|
|11|-|U.N.オーエンは彼女なのか？|東方紅魔郷より|
|12|-|永遠の巫女|東方霊異伝より|
|13|-|空飛ぶ巫女の不思議な毎日|オリジナル|

### 東方紅魔郷 (17/17)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT000.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT000.mml)|赤より紅い夢|タイトル画面テーマ|
|2|[BSLOT001.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT001.mml)|ほおずきみたいに紅い魂|１面テーマ|
|3|[BSLOT002.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT002.mml)|妖魔夜行|１面ボス・ルーミアのテーマ|
|4|[BSLOT003.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT003.mml)|ルーネイトエルフ|２面テーマ|
|5|[BSLOT004.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT004.mml)|おてんば恋娘|２面ボス・チルノのテーマ|
|6|[BSLOT005.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT005.mml)|上海紅茶館　～ Chinese Tea|３面テーマ|
|7|[BSLOT006.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT006.mml)|明治十七年の上海アリス|３面ボス・紅 美鈴のテーマ|
|8|[BSLOT007.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT007.mml)|ヴワル魔法図書館|４面テーマ|
|9|[BSLOT008.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT008.mml)|ラクトガール　～ 少女密室|４面ボス・パチュリー・ノーレッジのテーマ|
|10|[BSLOT009.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT009.mml)|メイドと血の懐中時計|５面テーマ|
|11|[BSLOT010.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT010.mml)|月時計　～ ルナ・ダイアル|５面ボス・十六夜 咲夜のテーマ|
|12|[BSLOT011.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT011.mml)|ツェペシュの幼き末裔|６面テーマ|
|13|[BSLOT012.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT012.mml)|亡き王女の為のセプテット|６面ボス・レミリア・スカーレットのテーマ|
|14|[BSLOT013.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT013.mml)|魔法少女達の百年祭|EXTRAテーマ|
|15|[BSLOT014.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT014.mml)|U.N.オーエンは彼女なのか？|EXTRAボス・フランドール・スカーレットのテーマ|
|16|[BSLOT015.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT015.mml)|紅より儚い永遠|エンディングテーマ|
|17|[BSLOT016.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT016.mml)|紅楼　～ Eastern Dream...|スタッフロールテーマ|

### 東方妖々夢 (21/21)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT017.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT017.mml)|妖々夢　～ Snow or Cherry Petal|タイトル画面テーマ|
|2|[BSLOT018.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT018.mml)|無何有の郷　～ Deep Mountain|１面テーマ|
|3|[BSLOT019.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT019.mml)|クリスタライズシルバー|１面ボス・レティ・ホワイトロックのテーマ|
|4|[BSLOT020.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT020.mml)|遠野幻想物語|２面テーマ|
|5|[BSLOT021.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT021.mml)|ティアオイエツォン(withered leaf)|２面ボス・橙のテーマ|
|6|[BSLOT022.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT022.mml)|ブクレシュティの人形師|３面テーマ|
|7|[BSLOT023.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT023.mml)|人形裁判　～ 人の形弄びし少女|３面ボス・アリス・マーガトロイドのテーマ|
|8|[BSLOT024.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT024.mml)|天空の花の都|４面テーマ|
|9|[BSLOT025.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT025.mml)|幽霊楽団　～ Phantom Ensemble|４面ボス・プリズムリバー三姉妹のテーマ|
|10|[BSLOT026.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT026.mml)|東方妖々夢　～ Ancient Temple|５面テーマ|
|11|[BSLOT027.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT027.mml)|広有射怪鳥事　～ Till When?|５面ボス・魂魄 妖夢のテーマ|
|12|[BSLOT028.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT028.mml)|アルティメットトゥルース|６面テーマ|
|13|[BSLOT029.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT029.mml)|幽雅に咲かせ、墨染の桜　～ Border of Life|６面ボス・西行寺 幽々子のテーマ|
|14|[BSLOT030.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT030.mml)|ボーダーオブライフ|６面ボス・西行寺 幽々子のテーマ２|
|15|[BSLOT031.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT031.mml)|妖々跋扈|EXTRAテーマ|
|16|[BSLOT032.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT032.mml)|少女幻葬　～ Necro-Fantasy|EXTRAボス・八雲 藍のテーマ|
|17|[BSLOT033.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT033.mml)|妖々跋扈　～ Who done it!|PHANTASMテーマ|
|18|[BSLOT034.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT034.mml)|ネクロファンタジア|PHANTASMボス・八雲 紫のテーマ|
|19|[BSLOT035.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT035.mml)|春風の夢|エンディングテーマ|
|20|[BSLOT036.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT036.mml)|さくらさくら　～ Japanize Dream...|スタッフロールテーマ|
|21|[BSLOT037.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT037.mml)|過去の花　～ Fairy of Flower|未使用曲|

### 東方萃夢想 (0/3)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|Demystify Feast|宴会直前ステージのテーマ|
|2|-|夜が降りてくる　～ Evening Star|セミファイナルステージ・八雲 紫のテーマ|
|3|-|御伽の国の鬼が島　～ Missing Power|ファイナルステージ・伊吹 萃香のテーマ|

### 東方永夜抄 (21/21)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT038.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT038.mml)|永夜抄　～ Eastern Night.|タイトル画面テーマ|
|2|[BSLOT039.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT039.mml)|幻視の夜　～ Ghostly Eyes|１面テーマ|
|3|[BSLOT040.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT040.mml)|蠢々秋月　～ Mooned Insect|１面ボス・リグル・ナイトバグのテーマ|
|4|[BSLOT041.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT041.mml)|夜雀の歌声　～ Night Bird|２面テーマ|
|5|[BSLOT042.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT042.mml)|もう歌しか聞こえない|２面ボス・ミスティア・ローレライのテーマ|
|6|[BSLOT043.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT043.mml)|懐かしき東方の血　～ Old World|３面のテーマ|
|7|[BSLOT044.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT044.mml)|プレインエイジア|３面ボス・上白沢 慧音のテーマ|
|8|[BSLOT045.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT045.mml)|永夜の報い　～ Imperishable Night. |４面テーマ|
|9|[BSLOT046.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT046.mml)|少女綺想曲　～ Dream Battle|４面ボス・博麗 霊夢のテーマ|
|10|[BSLOT047.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT047.mml)|恋色マスタースパーク|４面ボス・霧雨 魔理沙のテーマ|
|11|[BSLOT048.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT048.mml)|シンデレラケージ　～ Kagome-Kagome|５面テーマ|
|12|[BSLOT049.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT049.mml)|狂気の瞳　～ Invisible Full Moon|５面ボス・鈴仙・U・イナバのテーマ|
|13|[BSLOT050.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT050.mml)|ヴォヤージュ1969|６面テーマ|
|14|[BSLOT051.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT051.mml)|千年幻想郷　～ History of the Moon|６面Aボス・八意 永琳のテーマ|
|15|[BSLOT052.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT052.mml)|竹取飛翔　～ Lunatic Princess|６面Bボス・蓬莱山 輝夜のテーマ|
|16|[BSLOT053.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT053.mml)|ヴォヤージュ1970|永琳・輝夜ファイナルスペルのテーマ|
|17|[BSLOT054.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT054.mml)|エクステンドアッシュ　～ 蓬莱人|EXTRAテーマ|
|18|[BSLOT055.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT055.mml)|月まで届け、不死の煙|EXTRAボス・藤原 妹紅のテーマ|
|19|[BSLOT056.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT056.mml)|月見草|エンディングテーマ|
|20|[BSLOT057.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT057.mml)|Eternal Dream　～ 幽玄の槭樹|スタッフロールテーマ|
|21|[BSLOT058.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT058.mml)|東方妖怪小町|ラストワードのテーマ|

### 東方花映塚 (8/19)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT070.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT070.mml)|花映塚　～ Higan Retour|タイトル画面テーマ|
|2|[BSLOT071.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT071.mml)|春色小径　～ Colorful Path|博麗 霊夢のテーマ|
|3|[BSLOT076.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT076.mml)|オリエンタルダークフライト|霧雨 魔理沙のテーマ|
|4|[BSLOT066.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT066.mml)|フラワリングナイト|十六夜 咲夜のテーマ|
|5|-|東方妖々夢　～ Ancient Temple|魂魄 妖夢のテーマ|
|6|-|狂気の瞳　～ Invisible Full Moon|鈴仙・U・イナバのテーマ|
|7|[BSLOT083.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT083.mml)|おてんば恋娘の冒険|チルノのテーマ|
|8|-|幽霊楽団　～ Phantom Ensemble|プリズムリバー三姉妹のテーマ|
|9|-|もう歌しか聞こえない　～ Flower Mix|ミスティア・ローレライのテーマ|
|10|[BSLOT084.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT084.mml)|お宇佐さまの素い幡|因幡 てゐのテーマ|
|11|[BSLOT060.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT060.mml)|風神少女　 (Short Version)|射命丸 文のテーマ|
|12|-|ポイズンボディ　～ Forsaken Doll|メディスン・メランコリーのテーマ|
|13|-|今昔幻想郷　～ Flower Land|風見 幽香のテーマ|
|14|-|彼岸帰航　～ Riverside View|小野塚 小町のテーマ|
|15|[BSLOT085.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT085.mml)|六十年目の東方裁判　～ Fate of Sixty Years|四季映姫・ヤマザナドゥのテーマ|
|16|-|花の映る塚|会話場面のテーマ１|
|17|-|此岸の塚|会話場面のテーマ２|
|18|-|花は幻想のままに|エンディングテーマ|
|19|-|魂の花　～ Another Dream...|スタッフロールテーマ|

### 東方文花帖 (0/6)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|天狗の手帖　～ Mysterious Note|タイトル画面テーマ|
|2|-|風の循環　～ Wind Tour|撮影曲１|
|3|-|天狗が見ている　～ Black Eyes|撮影曲２|
|4|-|東の国の眠らない夜|撮影曲３|
|5|-|レトロスペクティブ京都|撮影曲４|
|6|-|風神少女|撮影曲５|

### 東方風神録 (18/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|[BSLOT098.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT098.mml)|封印されし神々|タイトル画面テーマ|
|2|[BSLOT088.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT088.mml)|人恋し神様　～ Romantic Fall|１面テーマ|
|3|[BSLOT069.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT069.mml)|稲田姫様に叱られるから|１面ボス・秋 穣子のテーマ|
|4|[BSLOT089.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT089.mml)|厄神様の通り道　～ Dark Road|２面テーマ|
|5|[BSLOT090.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT090.mml)|運命のダークサイド|２面ボス・鍵山 雛のテーマ|
|6|[BSLOT064.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT064.mml)|神々が恋した幻想郷|３面テーマ|
|7|[BSLOT065.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT065.mml)|芥川龍之介の河童　～ Candid Friend|３面ボス・河城 にとりのテーマ|
|8|[BSLOT091.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT091.mml)|フォールオブフォール　～ 秋めく滝|４面テーマ|
|9|[BSLOT092.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT092.mml)|妖怪の山　～ Mysterious Mountain|４面ボス・射命丸 文のテーマ|
|10|[BSLOT093.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT093.mml)|少女が見た日本の原風景|５面テーマ|
|11|[BSLOT094.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT094.mml)|信仰は儚き人間の為に|５面ボス・東風谷 早苗のテーマ|
|12|[BSLOT095.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT095.mml)|御柱の墓場　～ Grave of Being|６面テーマ|
|13|[BSLOT096.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT096.mml)|神さびた古戦場　～ Suwa Foughten Field|６面ボス・八坂 神奈子のテーマ|
|14|[BSLOT067.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT067.mml)|明日ハレの日、ケの昨日|EXTRAテーマ|
|15|[BSLOT068.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT068.mml)|ネイティブフェイス|EXTRAボス・洩矢 諏訪子のテーマ|
|16|[BSLOT097.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT097.mml)|麓の神社|エンディングテーマ|
|17|[BSLOT099.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT099.mml)|神は恵みの雨を降らす　～ Sylphid Dream|スタッフロールテーマ|
|18|[BSLOT100.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT100.mml)|プレイヤーズスコア|ゲームオーバーテーマ|

### 東方緋想天 (0/3)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|黒い海に紅く　～ Legendary Fish|永江 衣玖のテーマ|
|2|-|有頂天変　～ Wonderful Heaven|比那名居 天子のテーマ|
|3|-|幼心地の有頂天|ラストスペルのテーマ|

### 東方地霊殿 (3/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|地霊達の起床|タイトル画面テーマ|
|2|-|暗闇の風穴|１面テーマ|
|3|-|封じられた妖怪　～ Lost Place|１面ボス・黒谷 ヤマメのテーマ|
|4|-|渡る者の途絶えた橋|２面テーマ|
|5|[BSLOT101.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT101.mml)|緑眼のジェラシー|２面ボス・水橋 パルスィのテーマ|
|6|-|旧地獄街道を行く|３面テーマ|
|7|-|華のさかづき大江山|３面ボス・星熊 勇儀のテーマ|
|8|-|ハートフェルトファンシー|４面テーマ|
|9|[BSLOT072.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT072.mml)|少女さとり　～ 3rd eye|４面ボス・古明地 さとりのテーマ|
|10|-|廃獄ララバイ|５面のテーマ|
|11|[BSLOT102.mml](https://github.com/suzukiplan/Touhou-VGS-MML-data/blob/master/data/BSLOT102.mml)|死体旅行　～ Be of good cheer!|５面ボス・火焔猫 燐のテーマ|
|12|-|業火マントル|６面のテーマ|
|13|-|霊知の太陽信仰　～ Nuclear Fusion|６面ボス・霊烏路 空のテーマ|
|14|-|ラストリモート|EXTRAのテーマ|
|15|-|ハルトマンの妖怪少女|EXTRAボス・古明地 こいしのテーマ|
|16|-|地霊達の帰宅|エンディングテーマ|
|17|-|エネルギー黎明 ～ Future Dream...|スタッフロールのテーマ|
|18|-|プレイヤーズスコア|ゲームオーバーテーマ　（※風神録と同じ）|

### 東方星蓮船 (0/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|青空の影|タイトル画面テーマ|
|2|-|春の湊に|１面テーマ|
|3|-|小さな小さな賢将|１面ボス・ナズーリンのテーマ|
|4|-|閉ざせし雲の通い路|２面テーマ|
|5|-|万年置き傘にご注意を|２面ボス・多々良 小傘のテーマ|
|6|-|スカイルーイン|３面テーマ|
|7|-|時代親父とハイカラ少女|３面ボス・雲居 一輪＆雲山のテーマ|
|8|-|幽霊客船の時空を越えた旅|４面テーマ|
|9|-|キャプテン・ムラサ|４面ボス・村紗 水蜜のテーマ|
|10|-|魔界地方都市エソテリア|５面テーマ|
|11|-|虎柄の毘沙門天|５面ボス・寅丸 星のテーマ|
|12|-|法界の火|６面テーマ|
|13|-|感情の摩天楼　～ Cosmic Mind|６面ボス・聖 白蓮のテーマ|
|14|-|夜空のユーフォーロマンス|EXTRAのテーマ|
|15|-|平安のエイリアン|EXTRAボス・封獣 ぬえのテーマ|
|16|-|妖怪寺|エンディングテーマ|
|17|-|空の帰り道　～ Sky Dream|スタッフロールのテーマ|
|18|-|プレイヤーズスコア|ゲームオーバーテーマ　（※風神録と同じ）|

### 東方非想天則 (0/2)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|アンノウンX　～ Unfound Adventure|ファイナルステージ共通テーマ|
|2|-|空に浮かぶ物体X|早苗ストーリー・ラストスペルのテーマ|

### ダブルスポイラー (0/7)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|ニュースハウンド|タイトル画面テーマ|
|2|-|あなたの町の怪事件|取材のテーマ１|
|3|-|妖怪モダンコロニー|取材のテーマ２|
|4|-|ネメシスの要塞|取材のテーマ３|
|5|-|無間の鐘　～ Infinite Nightmare|取材のテーマ４|
|6|-|妖怪の山　～ Mysterious Mountain|取材のテーマ５|
|7|-|_（曲名不明）_|はたてモード開放画面・コンプリート画面のテーマ|
|8|-|_（未使用？）_|音楽室には登録なし（データではth125_07.wav）|

### 妖精大戦争 (0/10)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|春の氷精|タイトル画面テーマ|
|2|-|可愛い大戦争のリフレーン|１面のテーマ|
|3|-|いたずらに命をかけて|１、２面ボスのテーマ|
|4|-|年中夢中の好奇心|２面のテーマ|
|5|-|真夜中のフェアリーダンス|３面のテーマ|
|6|-|妖精大戦争　～ __Fairy__ Wars|３面ボスのテーマ|
|7|-|ルーズレイン|EXTRAのテーマ|
|8|-|メイガスナイト|EXTRAボス・霧雨 魔理沙のテーマ|
|9|-|春の氷精　- 静 -|エンディングテーマ|
|10|-|プレイヤーズスコア|ネームレジストのテーマ（※新アレンジ）|

_※妖精大戦争　～ Fairy WarsのFairyの表記は、ゲーム中及び音楽室選択画面だとFailyと表記されている（1.00a）_

### 東方神霊廟 (0/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|欲深き霊魂|タイトル画面テーマ|
|2|-|死霊の夜桜|１面テーマ|
|3|-|ゴーストリード|１面ボス・西行寺 幽々子のテーマ|
|4|-|妖怪寺へようこそ|２面テーマ|
|5|-|門前の妖怪小娘|２面ボス・幽谷 響子のテーマ|
|6|-|素敵な墓場で暮しましょ|３面テーマ|
|7|-|リジッドパラダイス|３面ボス・宮古 芳香のテーマ|
|8|-|デザイアドライブ|４面テーマ|
|9|-|古きユアンシェン|４面ボス・霍 青娥のテーマ|
|10|-|夢殿大祀廟|５面テーマ|
|11|-|大神神話伝|５面ボス・物部 布都のテーマ|
|12|-|小さな欲望の星空|６面テーマ|
|13|-|聖徳伝説　～ True Administrator|６面ボス・豊聡耳 神子のテーマ|
|14|-|妖怪裏参道|EXTRAのテーマ|
|15|-|佐渡の二ッ岩|EXTRAボス・二ッ岩 マミゾウのテーマ|
|16|-|神社の新しい風|エンディングテーマ|
|17|-|デザイアドリーム|スタッフロールテーマ|
|18|-|プレイヤーズスコア|ゲームオーバーテーマ　（※妖精大戦争と同じ）|

### 東方心綺楼 (0/2)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|幻想郷の二ッ岩|二ッ岩 マミゾウのテーマ|
|2|-|亡失のエモーション|秦 こころのテーマ|

### 東方輝針城 (0/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|不思議なお祓い棒|タイトル画面テーマ|
|2|-|ミストレイク|１面テーマ|
|3|-|秘境のマーメイド|１面ボス・わかさぎ姫のテーマ|
|4|-|運河を行き交う人妖|２面テーマ|
|5|-|柳の下のデュラハン|２面ボス・赤蛮奇のテーマ|
|6|-|満月の竹林|３面テーマ|
|7|-|孤独なウェアウルフ|３面ボス・今泉 影狼のテーマ|
|8|-|マジカルストーム|４面テーマ|
|9|-|幻想浄瑠璃|４面ボス・九十九 弁々＆九十九 八橋のテーマ|
|10|-|空中に沈む輝針城|５面テーマ|
|11|-|リバースイデオロギー|５面ボス・鬼人 正邪のテーマ|
|12|-|針小棒大の天守閣|６面テーマ|
|13|-|輝く針の小人族　～ Little Princess|６面ボス・少名 針妙丸のテーマ|
|14|-|魔力の雷雲|EXTRAのテーマ|
|15|-|始原のビート　～ Pristine Beat|EXTRAボス・堀川 雷鼓のテーマ|
|16|-|小槌の魔力|エンディングテーマ|
|17|-|不思議な不思議な道具達|スタッフロールテーマ|
|18|-|プレイヤーズスコア|ゲームオーバーテーマ　（※妖精大戦争と同じ）|

### 弾幕アマノジャク (0/9)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|反則の狼煙を上げろ|タイトル画面テーマ|
|2|-|不可能弾幕には反則を|最序盤のテーマ|
|3|-|ミッドナイトスペルカード|序盤のテーマ|
|4|-|ロマンチック逃飛行|中盤のテーマ|
|5|-|永遠の三日天下|終盤のテーマ|
|6|-|秘境のマーメイド|（※輝針城から再録）|
|7|-|リバースイデオロギー|（※輝針城から再録）|
|8|-|幻想浄瑠璃|（※輝針城から再録）|
|9|-|妖怪の山　～ Mysterious Mountain|（※風神録から再録）|

### 東方深秘録 (0/2)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|華狭間のバトルフィールド -- 茨木 華扇のテーマ
|2|-|ラストオカルティズム　～ 現し世の秘術師 -- 宇佐見 菫子のテーマ

### 東方紺珠伝 (0/18)

|No|MML file|Title|Description|
|---:|---|---|---|
|1|-|宇宙巫女現る|タイトル画面テーマ|
|2|-|忘れがたき、よすがの緑|１面テーマ|
|3|-|兎は舞い降りた|１面ボス・清蘭のテーマ|
|4|-|湖は浄めの月光を映して|２面テーマ|
|5|-|九月のパンプキン|２面ボス・鈴瑚のテーマ|
|6|-|宇宙を飛ぶ不思議な巫女|３面テーマ|
|7|-|永遠の春夢|３面ボス・ドレミー・スイートのテーマ|
|8|-|凍り付いた永遠の都|４面テーマ|
|9|-|逆転するホイールオブフォーチュン|４面ボス・稀神 サグメのテーマ|
|10|-|遥か３８万キロのボヤージュ|５面テーマ|
|11|-|星条旗のピエロ|５面ボス・クラウンピースのテーマ|
|12|-|故郷の星が映る海|６面テーマ|
|13|-|ピュアヒューリーズ　～ 心の在処|６面ボス・純狐のテーマ|
|14|-|見た事も無い悪夢の世界|EXTRAのテーマ|
|15|-|パンデモニックプラネット|EXTRAボス・ヘカーティア・ラピスラズリのテーマ|
|16|-|神社から見える月|エンディングテーマ|
|17|-|宇宙巫女帰還する|スタッフロールテーマ|
|18|-|プレイヤーズスコア|ゲームオーバーテーマ　（※輝針城・神霊廟・妖精大戦争と同じ）|

# 連絡先
- Twitter https://twitter.com/suzukiplan
- Google+ https://plus.google.com/u/0/+YojiSuzuki/about
