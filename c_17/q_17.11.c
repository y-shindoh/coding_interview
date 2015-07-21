/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.11.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.11の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

int flag = 0;

/**
 * 等確率で0〜4の整数を生成
 * @reutrn	0〜4の整数
 */
int rand5()
{
	if (!flag) {
		flag = 1;
		srand((unsigned int)time(NULL));
	}
	return rand() % 5;
}

/**
 * 等確率で0〜6の整数を生成
 * @reutrn	0〜6の整数
 * @note	関数 @a rand5 を利用する。
 */
int rand7()
{
	int n;

	while ('-') {
		n = rand5() * 5 + rand5();	// 5進数と考えて処理すると良い
		if (7 * 3 <= n) continue;	// 21以上は0〜3と余計に重複するので再トライ
		return n % 7;	// 0〜20の重複具合が等しいので、等確率で0〜7が発生
	}

	/* 再トライの確率は最終的に他の整数へ等しく再分配される */
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int v;

	for (size_t i = 0; i < 10; ++i) {
		v = rand7();
		if (0 < i) printf(", ");
		printf("%d", v);
	}
	printf("\n");

	return 0;
}
