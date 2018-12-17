//======================================
// randYusha3.c
// 概要:   勇者と魔物が戦うゲーム
// 作者:   平野 政輝
// 作成日:  2018/12/12
// 修正日:
// 目的:   構造体について学ぶ
// 使い方: gcc randYusha.c -o randYusha でコンパイルした後、
//         ./randYusha で実行すると、勇者と魔物の戦闘が表示される。
//======================================
#include <stdio.h>  // 標準入出力ヘッダファイル
#include <stdlib.h> // rand()などを使うためのヘッダファイル
#include <time.h>   // UNIX時間取得用ヘッダファイル

// キャラクターの構造体charaの宣言
struct chara {
	int  hp;    // 体力のメンバ変数（整数の変数）
	int  atk;   // 攻撃力のメンバ変数（整数の変数）
	char  *name; // 名前のメンバ変数（ポインタ変数）
	int agi;
	int crt;
	int hit;
};

// 関数のプロトタイプ宣言
struct chara randChara(void);
    // キャラクターの強さを乱数で決める関数
void printChara(struct chara chr);
    // キャラクターの強さを表示する関数
void attackChara(struct chara * chr, struct chara atk_chr);
    // キャラクターatk_chrがchrに攻撃する関数

// メイン関数
int main(void)
{
	char *yushaName[3] = {"アルゴル", "パール", "リスプ"};
	    // 勇者の名前の候補
	char *enemyName[3] = {"コウモリ", "ゾンビ", "大魔王"};
	    // 敵の名前の候補
	struct chara  yusha, enemy; // 勇者と敵の構造体変数を定義

	srand((unsigned int)time(NULL)); // 乱数の種の設定

	// 勇者と敵の強さと名前を乱数で決定する
	yusha = randChara();
	yusha.name = yushaName[rand()%3];
	enemy = randChara();
	enemy.name = enemyName[rand()%3];

	// 戦闘開始メッセージと強さを表示
	printf("勇者%sの前に%sが現れた！\n",
		   yusha.name, enemy.name); // 戦闘開始メッセージを表示
	printChara(yusha); // 関数で勇者のステータスを表示する
	printChara(enemy); // 関数で敵のステータスを表示する

	// どちらかのHPが0以下になるまで勇者と敵が戦う
	while ( 1 ) {  // 無限ループ

		if(yusha.agi >= enemy.agi){
			// 勇者のターン
			attackChara(&enemy, yusha);  // 敵に対する勇者の攻撃
			if (enemy.hp < 0) {  // 敵を倒したならば
				printf("勇者の勝利！\n");  // 勝利メッセージを表示
				break;      // while文を抜ける
			}

			// 敵のターン
			attackChara(&yusha, enemy);  // 勇者に対する敵の攻撃
			if (yusha.hp < 0) {  // 勇者が倒されたならば
				printf("敗北。勇者の。\n");  // 敗北メッセージを表示
				break;      // while文を抜ける
			}

		}else{

			// 敵のターン
			attackChara(&yusha, enemy);  // 勇者に対する敵の攻撃
			if (yusha.hp < 0) {  // 勇者が倒されたならば
				printf("敗北。勇者の。\n");  // 敗北メッセージを表示
				break;      // while文を抜ける
			}

			// 勇者のターン
			attackChara(&enemy, yusha);  // 敵に対する勇者の攻撃
			if (enemy.hp < 0) {  // 敵を倒したならば
				printf("勇者の勝利！\n");  // 勝利メッセージを表示
				break;      // while文を抜ける
			}

		}
	}

	return 0;  // 正常終了
	}

// キャラクターの強さを乱数で決める関数
struct chara randChara(void) {
	struct chara chr;
	chr.name = "???";
	chr.hp = rand()%200 + 1;
	chr.atk = rand()%80 + 10;
	chr.agi = rand()%100 + 1;
	chr.crt = rand()%100 + 1;
	chr.hit = rand()%60 + 31;
	return chr;
}

// キャラクターの強さを表示する関数
void printChara(struct chara chr) {
	printf("%s HP:%3d atk:%2d agi:%3d crt:%3d hit:%3d\n",chr.name,chr.hp,chr.atk,chr.agi,chr.crt,chr.hit);
}

// キャラクターatk_chrがchrに攻撃する関数
void attackChara(struct chara * chr ,struct chara atk_chr ) {
  
	printf("%sの攻撃！\n",atk_chr.name);

	
	  if(rand()%100 < atk_chr.hit){
	    if(rand()%100 < atk_chr.crt){
	      printf("会心の一撃！\n");
	      chr -> hp -= 2*atk_chr.atk;
	      printf("%sに%dのダメージ！(残りHP %d)\n",chr->name,2*atk_chr.atk,chr->hp);
	      
	    }else{
	      chr -> hp -= atk_chr.atk;
	      
	      printf("%s に%dのダメージ！(残りHP %d)\n",chr->name,atk_chr.atk,chr->hp);
	    }
	  }else{
	    printf("攻撃は外れた！\n");
	  }
}
