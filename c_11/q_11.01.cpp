/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cassert>
#include "utility.hpp"

/**
 * 昇順ソート済み配列に昇順ソート済み配列をマージ
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

	int i = (int)main_length - 1;
	int j = (int)sub_length - 1;
	int k = (int)main_length + sub_length - 1;

	while (0 <= k) {
		if (j < 0) break;
		if (i < 0) main_array[k] = sub_array[j--];
		else if (main_array[i] <= sub_array[j]) main_array[k] = sub_array[j--];
		else main_array[k] = main_array[i--];
		--k;
	}

	return main_length + sub_length;
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
