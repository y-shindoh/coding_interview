/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "utility.hpp"

/**
 * 回転させたソート済み配列の本来の先頭を探索
 * @param[in]	data	回転させたソート済み配列
 * @param[in]	length	配列 @a data の要素数
 * @return	本来の先頭
 * @note	テンプレートの型 @a TYPE は各配列の要素の型。
 * @note	配列に重複がなければ最悪計算量は O(log n)。そうでなければ O(n)。
 */
template<typename TYPE>
size_t
FindHead(const TYPE* data,
		 size_t length)
{
	assert(data);
	assert(length);

	size_t s(0);
	size_t e(length - 1);
	size_t i(0);
	bool flag;

	while (s + 1 < e) {
		i = (s + e) / 2;
//		std::printf("[%lu:%lu] => %lu\n", s, e, i);
		flag = true;
		if (data[s] < data[i]) {
			s = i;
			flag = false;
		}
		if (data[i] < data[e]) {
			e = i;
			flag = false;
		}
		if (flag) {
			// 重複あり対策
			while (s < i && data[s] == data[s+1]) ++s;
			while (i < e && data[e-1] == data[e]) --e;
		}
	}

//	std::printf("[%lu:%lu] => %lu\n", s, e, i);

	if (s + 1 != e) return 0;

	return e;
}

/**
 * 回転させたソート済み配列を探索
 * @param[in]	data	回転させたソート済み配列
 * @param[in]	length	配列 @a data の要素数
 * @param[in]	key	探索する値
 * @return	値 @a key の位置。探索失敗時は @a INVALID_INDEX が返却される。
 * @note	テンプレートの型 @a TYPE は各配列の要素の型。
 * @note	配列に重複がなければ最悪計算量は O(log n)。そうでなければ O(n)。
 */
template<typename TYPE>
size_t
FindRotatedArray(const TYPE* data,
				 size_t length,
				 const TYPE& key)
{
	assert(data);
	assert(length);

	size_t h(INVALID_INDEX);
	size_t k = FindHead<TYPE>(data, length);

	if (data[0] <= key) {
		h = BinarySearch(data, k, key);
	}
	else {
		if (k < length) {
			h = BinarySearch(data + k, length - k, key);
			if (h < INVALID_INDEX) h += k;
		}
	}

	return h;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
//	int data[] = {3, 3, 1, 3,3,3,3,3,3};
//	int data[] = {3,3, 1,1, 3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {3,3, 4,4, 3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {3,3,3,3,3,3,3,3,3,3,3,3,3};
//	int data[] = {4,4, 1,1, 2,2, 3,3,3, 4,4};
	int key(5);
	size_t l = sizeof(data) / sizeof(data[0]);
	size_t i = FindHead<int>(data, l);
	size_t k = FindRotatedArray<int>(data, l, key);

	print_array<int>(data, l, "DATA");
	std::printf("head => %lu\n", i);
	if (k < INVALID_INDEX) {
		std::printf("data[%lu] = %d\n", k, key);
	}
	else {
		std::printf("data[-] = %d\n", key);
	}

	return 0;
}
