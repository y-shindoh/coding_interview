/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.12.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.12の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある配列において、
  2つの要素の合計値が指定した値と等しくなる組み合わせを全て見つけるアルゴリズムを設計してください。
 */

#include <cstddef>
#include <set>	// 本当は unordered_set がより望ましい
#include <cstdio>
#include <cassert>

/**
 * 配列から指定した合計値になる要素の組を探索
 * @param[in]	sum	合計値
 * @param[in]	data	配列
 * @param[in]	length	配列 @a data の要素数
 * @note	計算量は O(n log n) になる。ただし n は引数 @a length に等しい。
 */
void find_sum_1(int sum,
				const int* data,
				size_t length)
{
	assert(data);

	std::multiset<int> set;
	int v;

	for (size_t i = 0; i < length; ++i) {
		v = sum - data[i];
		for (size_t j(0); j < set.count(v); ++j) {
			std::printf("(%d, %d)\n", data[i], v);
		}
		set.insert(data[i]);
	}
}

/**
 * 配列から指定した合計値になる要素の組を探索
 * @param[in]	sum	合計値
 * @param[in]	data	重複なし昇順ソート済み配列
 * @param[in]	length	配列 @a data の要素数
 * @note	計算量は O(n) になる。ただし n は引数 @a length に等しい。
			ただし事前のソート処理が O(n log n) であることに注意。
 * @note	重複がある場合は、そのうち1つだけを処理する。
 */
void find_sum_2(int sum,
				const int* data,
				size_t length)
{
	assert(data);
	assert(0 < length);

	size_t i(0);
	size_t j(length-1);

	while (i < j) {
		if (sum == data[i] + data[j]) {
			std::printf("(%d, %d)\n", data[i], data[j]);
			while (i + 1 < length && data[i] == data[i+1]) ++i;	// 重複対策
			while (0 < j && data[j-1] == data[j]) --j;			// 重複対策
			++i;
			--j;
		}
		else {
			if (data[i] + data[j] < sum) ++i;
			else --j;
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {-2, -1, 0, 3, 5, 6, 7, 9, 13, 14};
	size_t length = sizeof(data) / sizeof(data[0]);

	find_sum_1(5, data, length);
	std::printf("----\n");
	find_sum_2(5, data, length);

	return 0;
}
