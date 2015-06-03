/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstring>
#include <cassert>
#include "utility.hpp"

/**
 * ソート済み配列にソート済み配列をマージ
 * @param[in,out]	main_array	マージ先の配列
 * @param[in]	main_length	配列 @a main_array の要素数
 * @param[in]	sub_array	マージ相手の配列
 * @param[in]	sub_length	配列 @a sub_length の要素数
 * @return	マージ結果の配列の要素数
 * @note	配列 @a main_array は2つの配列の要素数の和より長いこと。
 * @note	最悪計算量は O(m+n)となる。m, nはそれぞれの配列の長さ。
 * @note	テンプレートの型 @a TYPE は各配列の要素の型。
 */
template<typename TYPE>
size_t
MergeSortedArray(TYPE* main_array,
				 size_t main_length,
				 const TYPE* sub_array,
				 size_t sub_length)
{
	assert(main_array);
	assert(main_length);
	assert(sub_array);
	assert(sub_length);

	std::memmove((void*)(main_array + sub_length),
				 (const void*)main_array, main_length * sizeof(TYPE));

	size_t h(sub_length), k(0);
	size_t max_length = main_length + sub_length;
	for (size_t i(0); i < max_length; ++i) {
		if (sub_length <= k) break;
		if (max_length <= h) main_array[i] = sub_array[k++];
		else if (main_array[h] < sub_array[k]) main_array[i] = main_array[h++];
		else main_array[i] = sub_array[k++];
	}

	return max_length;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int A[10] = {1, 2, 4, 5, 7};
	int B[] = {3, 6, 8};

	size_t l = MergeSortedArray<int>(A, 5, B, 3);

	print_array<int>(A, l, "DATA");

	return 0;
}
