/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_18.06.c
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題18.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

_Bool flag = false;	///< ランダム処理の初期化状態

/**
 * 0以上指定値未満の整数をランダムに生成
 * @param[in]	l	指定値
 * @return	ランダムに生成された整数
 * @note	完全な等確率で各数値が出力されると仮定する。
 */
size_t MyRand(size_t l)
{
	if (!flag) {
		flag = true;
		srand((unsigned)time(NULL));
		rand();	// 初算出の偏りの対処 (おまじないレベル)
	}

	return (size_t)((double)l * (double)rand() / ((double)RAND_MAX + 1.0));
}

/**
 * 指定番目の小ささのデータを取得
 * @param[in,out]	data	データの配列
 * @param[in]	index	指定番目 (0始まり)
 * @param[in]	start	探索対象の開始インデックス
 * @param[in]	end	探索対象の終了インデックス
 * @return	指定番目の小ささのデータ
 * @note	乱択+選択アルゴリズム。
			配列に重複データがなければ、平均計算量は O(n) になる。
 */
size_t select(size_t* data,
			  size_t index,
			  size_t start,
			  size_t end)
{
	if (start == end && start == index) return data[index];

	size_t k = MyRand(end + 1 - start) + start;
	size_t j = start;
	size_t d = data[k];
	size_t t;

	for (size_t i = start; i <= end; ++i) {
		if (data[i] > d) continue;
		t = data[i];
		data[i] = data[j];
		data[j] = t;
		++j;
	}
	--j;	// 注意: 絶対に「start」以上。

	if (index <= j) {
		return select(data, index, start, j);
	}
	else {
		return select(data, index, j + 1, end);
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t data[] = {29, 30, 0, 1, 2, 3, 10, 23, 100, 200, 300, 1100, 12, 20, 21, 22};
	const size_t length = sizeof(data) / sizeof(data[0]);

	for (size_t i = 0; i < length; ++i) {
		if (0 < i) printf(", ");
		printf("%lu", data[i]);
	}
	printf("\n");

	size_t i = 5;
	size_t v = select(data, i, 0, length - 1);

	printf("%lu => %lu\n", i, v);

	return 0;
}
