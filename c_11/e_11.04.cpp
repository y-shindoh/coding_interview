/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	e_11.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の第11章の例題
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <utility>

/**
 * マージ・ソートの実装
 * @param[in,out]	data	ソート対象の配列
 * @param	buffer	作業領域
 * @param[in]	length	配列 @a data の長さ
 * @note	計算量は O(n log n)。
 */
template<typename TYPE>
void
MergeSort(TYPE* data,
		  TYPE* buffer,
		  size_t length)
{
	assert(data);
	assert(buffer);
	assert(length);

	if (length <= 1) return;
	if (length == 2) {
		if (data[0] > data[1]) std::swap<TYPE>(data[0], data[1]);
		return;
	}

	const size_t center = length / 2;
	if (1 < center) MergeSort(data, buffer, center);
	if (1 < length - center) MergeSort(data + center, buffer, length - center);

	size_t i(0), j(center);
	for (size_t k(0); k < length; ++k) {
		if (center <= i) break;
		if (length <= j) buffer[k] = data[i++];
		else if (data[i] <= data[j]) buffer[k] = data[i++];
		else buffer[k] = data[j++];
	}

	std::memcpy((void*)data, (const void*)buffer, sizeof(TYPE) * j);
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
	int buffer[10];
	const size_t l = sizeof(data) / sizeof(data[0]);

	print_array<int>(data, l, "BEFORE");

	MergeSort<int>(data, buffer, l);

	print_array<int>(data, l, "AFTER");

	return 0;
}
