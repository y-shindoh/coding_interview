/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  n個の整数からなる、ソート済みの配列を何回か回転させたものがあります。
  この配列の中から、ある要素を見つけるコードを書いてください。
  配列は、初め昇順でソートされていたと仮定してもかまいません。

  例:
  入力: find 5 in (15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14)
  出力: 8 (配列中の5のインデックス)
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "utility.hpp"

/**
 * 回転させたソート済み配列の本来の先頭を探索
 * @param[in]	data	回転させた昇順ソート済み配列
 * @param[in]	length	配列 @a data の要素数
 * @return	本来の先頭 (回転が見つからない場合は @a INVALID_INDEX を返す)
 * @note	テンプレートの型 @a TYPE は各配列の要素の型。
 * @note	配列に重複がなければ最悪計算量は O(log n)。そうでなければ O(n)。
			ただし n は配列 @a data の要素数。
 */
template<typename TYPE>
size_t
FindHead(const TYPE* data,
		 size_t length)
{
	assert(data);
	assert(0 < length);
	assert(length < INVALID_INDEX);

	size_t s(0);				// 末尾およびその左側を指す
	size_t e(length - 1);		// 先頭およびその右側を指す
	size_t i;					// 先頭候補
	size_t j(INVALID_INDEX);	// 前回の二部探索失敗時のi

	while (s < e) {
		i = (s + e + 1) / 2;

		if (data[i-1] > data[i]) return i;	// 回転の箇所を発見

		if (data[s] < data[i]) {
			s = i;
			continue;
		}

		if (data[i] < data[e]) {
			e = i;
			continue;
		}

		if (i == j) return INVALID_INDEX;	// 探索失敗 (入力データの不備)
		j = i;

		// 変化のあるところまで探索位置を制限 (重複対策)
		while (s + 1 < length && data[s] == data[s+1]) ++s;
		while (0 < e && data[e-1] == data[e]) --e;
	}

	return 0;	// 回転なし
}

/**
 * 回転させたソート済み配列を探索
 * @param[in]	data	回転させた昇順ソート済み配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	key	探索する値
 * @return	値 @a key の位置。探索失敗時は @a INVALID_INDEX が返却される。
 * @note	テンプレートの型 @a TYPE は各配列の要素の型。
 * @note	配列に重複がなければ最悪計算量は O(log n)。そうでなければ O(n)。
			ただし n は配列 @a data の要素数。
 */
template<typename TYPE>
size_t
FindRotatedArray(const TYPE* data,
				 size_t length,
				 const TYPE& key)
{
	assert(data);
	assert(0 < length);

	size_t h(INVALID_INDEX);
	size_t k = FindHead<TYPE>(data, length);

	if (0 < k && data[0] <= key) {
		h = BinarySearch(data, k, key);
	}
	else if (k < length) {
		h = BinarySearch(data + k, length - k, key);
		if (h < INVALID_INDEX) h += k;
	}

	return h;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
//	int data[] = {15, 16, 19, 5, 7, 10, 14, 20, 25, 1, 3, 4};
//	int data[] = {3, 3, 1, 3,3,3,3,3,3};
//	int data[] = {3,3, 1,1, 3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {3,3, 4,4, 3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {3,3,3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {4,4, 1,1, 2,2, 3,3,3, 4,4};
	int key(5);
//	int key(3);
	size_t l = sizeof(data) / sizeof(data[0]);
	size_t i = FindHead<int>(data, l);
	size_t k = FindRotatedArray<int>(data, l, key);

	print_array<int>(data, l, "DATA");
	if (i < INVALID_INDEX) {
		std::printf("head => %lu\n", i);
	}
	else {
		std::printf("head => -\n");
	}
	if (k < INVALID_INDEX) {
		std::printf("data[%lu] = %d\n", k, key);
	}
	else {
		std::printf("data[-] = %d\n", key);
	}

	return 0;
}
