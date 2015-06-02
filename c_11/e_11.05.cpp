/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <utility>

/**
 * クイック・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は O(n log n)。
 */
template<typename TYPE>
void
QuickSort(TYPE* data,
		  size_t length,
		  bool flag = true)
{
	assert(data);
	assert(length);

	if (length <= 1) return;
	if (length == 2) {
		if (data[0] > data[1]) std::swap<TYPE>(data[0], data[1]);
		return;
	}

	if (flag) std::srand((unsigned)std::time(0));	// 乱択

	size_t h = (size_t)std::rand() % length;
	if (0 != h) std::swap(data[h], data[0]);
	size_t j(1);

	for (size_t i(1); i < length; ++i) {
		if (data[i] >= data[0]) continue;
		if (i != j) std::swap(data[i], data[j]);
		++j;
	}
	if (1 < j) std::swap(data[0], data[j-1]);	// 適切な場所に移動

	if (2 < j) QuickSort<TYPE>(data, j - 1, false);
	if (1 < length - j) QuickSort<TYPE>(data + j, length - j, false);
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

	QuickSort<int>(data, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
