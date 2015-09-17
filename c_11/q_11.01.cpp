/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
   問題:
   2つのソートされた配列A, Bがあります。
   Aの配列には十分に空きがあり、後ろにBを追加することができます。
   このとき、BをAにソートされた状態でマージするメソッドを書いてください。
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
	assert(0 < main_length);
	assert(sub_array);
	assert(0 < sub_length);

	for (size_t i(main_length); 0 < i; --i) {
		main_array[i+sub_length-1] = main_array[i-1];
	}

	size_t h(sub_length);
	size_t k(0);

	for (size_t i(0); i < main_length + sub_length; ++i) {
		if (h < main_length + sub_length && main_array[h] < sub_array[k]) {
			main_array[i] = main_array[h];
			++h;
		}
		else {
			main_array[i] = sub_array[k];
			if (++k >= sub_length) break;
		}
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
