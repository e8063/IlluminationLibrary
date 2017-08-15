/*
 * 国立舞鶴高専　電気情報工学科
 * イルミネーションライブラリ サンプルプログラム
 * ライブラリ・サンプルプログラム制作者:Kenta Yamamoto
 * Email:e8063@g.maizuru-ct.ac.jp
 * 
 * 制作者からのコメント:
 * このサンプルプログラムに従って記述を行えば、BOX等の仕様を考えずに
 * イルミネーションの点灯パターンを記述することが可能である。
*/

#include <Illumination.h>//IlluminationLibraryをインクルード
Illumination lib;//Illuminationクラスの実体化を行う

void setup() {
  lib.setup(true);//void setup内で必ず始めに呼び出すこと
  //引数をtrueにすると2番ピン(SSR_1)から9番ピン(SSR_8)を自動的にOUTPUTに初期化

  //関数名と関数に対応する制御コマンド(char型)を登録
  lib.setPattern(all_off,'0');
  //'0'を受信するとall_off関数の点灯パターンで点灯するように設定
  lib.setPattern(all_on,'1');
  //'1'を受信するとall_on関数の点灯パターンで点灯するように設定
  lib.setPattern(pattern,'P');
  //'P'を受信するとpattern関数の点灯パターンで点灯するように設定
  
  pinMode(13,OUTPUT);//確認用に13番ピンを使用
}

void loop() {
  lib.loopAction();//loop関数内で必ず実行すること
  //実行しないと正常にライブラリが動作しない
}

//以下、点灯パターンを記述
//※SSRの出力ピンはボックスのピン配置にあわせて予め定義(SSR_1 ~ SSR_8)されている

void all_off() {//全てのLEDを消灯するパターン(全消灯)
  digitalWrite(13, LOW);
  digitalWrite(SSR_1, LOW);
  digitalWrite(SSR_2, LOW);
  digitalWrite(SSR_3, LOW);
  digitalWrite(SSR_4, LOW);
  digitalWrite(SSR_5, LOW);
  digitalWrite(SSR_6, LOW);
  digitalWrite(SSR_7, LOW);
  digitalWrite(SSR_8, LOW);
  lib.wait();//次の制御コマンドを受信するまで待機
  //点灯パターンが変更されるまでここで処理が止まる
}

void all_on() {//全てのLEDを点灯するパターン(全点灯)
  digitalWrite(13, HIGH);
  digitalWrite(SSR_1, HIGH);
  digitalWrite(SSR_2, HIGH);
  digitalWrite(SSR_3, HIGH);
  digitalWrite(SSR_4, HIGH);
  digitalWrite(SSR_5, HIGH);
  digitalWrite(SSR_6, HIGH);
  digitalWrite(SSR_7, HIGH);
  digitalWrite(SSR_8, HIGH);
  lib.wait();//次の制御コマンドを受信するまで待機
  //点灯パターンが変更されるまでここで処理が止まる
}

void pattern() {//全てのLEDを点滅させるパターン
  digitalWrite(13, HIGH);
  digitalWrite(SSR_1, HIGH);
  digitalWrite(SSR_2, LOW);
  digitalWrite(SSR_3, HIGH);
  digitalWrite(SSR_4, LOW);
  digitalWrite(SSR_5, HIGH);
  digitalWrite(SSR_6, LOW);
  digitalWrite(SSR_7, HIGH);
  digitalWrite(SSR_8, LOW);
  lib.delay(700);//パターンの記述にdelay関数を利用する場合はライブラリ内のdelay関数を利用
  //ライブラリ内のdelay関数を利用しないとシリアル通信からのパターン変更が正常に行われない
  digitalWrite(13, LOW);
  digitalWrite(SSR_1, LOW);
  digitalWrite(SSR_2, HIGH);
  digitalWrite(SSR_3, LOW);
  digitalWrite(SSR_4, HIGH);
  digitalWrite(SSR_5, LOW);
  digitalWrite(SSR_6, HIGH);
  digitalWrite(SSR_7, LOW);
  digitalWrite(SSR_8, HIGH);
  lib.delay(700);//パターンの記述にdelay関数を利用する場合はライブラリ内のdelay関数を利用
  //lib.wait()を実行していないため、pattern()の終了後、パターン変更がなければ再度pattern()が実行される
}

