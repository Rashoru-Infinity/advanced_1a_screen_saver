# advanced_1a_screen_saver
![messageImage_1620578672668](https://user-images.githubusercontent.com/49583698/117580244-142e6c80-b132-11eb-8fed-3fcfe71eed3c.jpg)
高度情報演習1Aのスクリーンセーバー制作の授業の一環で制作しました.  
behavior.confに記述したマップのファイルを元にマップを形成し, behavior.confに記述されたパターンを元に視点が移動します.  
こちらのブランチは魚眼効果のあるバージョンになります.  

# Usage
```
#コンパイル
make
または
make all

#オブジェクトファイルの削除
make clean

#ビルドで生成されたすべてのバイナリを削除
make fclean

#ビルドで生成されたすべてのバイナリの削除とビルド
make re

#実行
al19136 s
```

# behavior.conf
マップを読み込むファイルの指定と、プレイヤーの行動パターンを記述します.  
以下が有効な記述例です.  
```
map: sample2.map

pattern: turnRight24
	turnR
	turnR
	turnR
	turnR
	turnR
	turnR
	turnR
	turnR
	exit

pattern: turnRight72
	turnRight24
	turnRight24
	turnRight24
	exit

pattern: ahead1.5
	ahead
	ahead
	ahead
	ahead
	ahead
	exit

entryPoint:
	ahead1.5
	turnRight72
	exit
```

## map
マップファイルを指定します
  - プレイヤーはN(上向き), S(下向き), W(左向き), E(右向き)のいずれかで表現されます
  - プレイヤーは必ずX(障害物)で囲まれています
  - 高さ・幅はそれぞれ10マス以下です(マップが広すぎると描画のための負荷が大きくなるため)  
以下が有効なマップの例です.
```
XXXXXXXXX
XOXOXOOOX
XOOOOOXOX
XOOEOOOOX
XOOOOOOOOX
 XOOOOOOX
XOOOOOXOX
XXXXXXXXX
```
## action  
プレイヤーの動作の基本単位です.  
actionを組み合わせてpatternやentryPointを記述します.  
- ahead 0.3マス前進
- back 0.3マス後退
- turnR 3度右に回る
- turnL 3度左に回る

## pattern  
特定の行動の組み合わせをパターンという単位にして記述できます.  
パターンの終端にexitが必要です.  

## entryPoint
C言語のmain関数や[start](https://www.atmarkit.co.jp/ait/articles/1703/01/news173_2.html)に相当します.  
actionやpatternを組み合わせて記述します.  
一連の動作の最後にexitが必要です. 

# Note
- patternの記述を呼び出し元のpatternまたはentryPointより後に記述することはできません
- WindowsのAPIを使っているため,　LinuxやMacOSなどの環境ではビルドできません
