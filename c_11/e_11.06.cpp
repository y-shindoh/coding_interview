/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <deque>

/**
 * 基数ソートの実装 (直接基数法)
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は平均 O(kn)。ただし k = log_N M (Mは @a data の最大値)。
 * @note	テンプレートの型 @a TYPE は符号なし整数を指定すること。
 * @note	テンプレートの整数 @a N はバケットの大きさ。
 */
template<typename TYPE, size_t N>
void
RadixSort(TYPE* data,
		  size_t length)
{
	assert(data);
	assert(length);

	std::deque<TYPE> buckets[N];

	for (size_t i(0); i < length; ++i) {
		buckets[0].push_back(data[i]);
	}

	size_t l[N];
	bool flag;
	size_t d(1);
	size_t k, t;

	do {
		for (size_t i(0); i < N; ++i) {
			l[i] = buckets[i].size();
		}

		flag = false;
		for (size_t i(0); i < N; ++i) {
			for (size_t j(0); j < l[i]; ++j) {
				t = (size_t)buckets[i].front();
				buckets[i].pop_front();
				if (t >= d) flag = true;
				k = t / d % N;
				buckets[k].push_back(t);
			}
		}
		d *= N;
	} while (flag);

	for (size_t i(0); i < length; ++i) {
		t = buckets[0].front();
		buckets[0].pop_front();
		data[i] = t;
	}
}

/**
 * 配列の表示
 */
template<typename TYPE>
void
print_array(const TYPE* data,
			size_t length,
			const char* prefix = 0)
{
	if (prefix) std::printf("%s:\t", prefix);
	for (size_t i(0); i < length; ++i) {
		if (0 < i) std::printf(", ");
		std::printf("%G", (double)data[i]);
	}
	std::printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {10, 1, 9, 2, 8, 3, 7, 4, 6, 5};
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	RadixSort<int, 10>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
