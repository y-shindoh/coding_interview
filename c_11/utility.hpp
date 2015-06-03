/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	utility.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の11章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#ifndef	__UTILITY_HPP__
#define	__UTILITY_HPP__ "utility.hpp"

#include <cstddef>
#include <cstdio>
#include <cassert>

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

#define	INVALID_INDEX	(~(size_t)0)	///< 型 @a size_t の不正値

/**
 * ソート済み配列に対し要素を探索
 * @param[in]	data	探索対象のソート済み配列
 * @param[in]	length	配列 @a data の長さ
 * @param[in]	key	探索対象の要素
 * @return	配列 @a data の @a key のあるインデックス
 * @note	探索失敗時には @a INVALID_INDEX が返却される。
 * @note	単純なバイナリ・サーチで処理している。最悪計算量は O(log n)。
 * @note	空の配列や @a size_t の限界を超える配列に対しては動作を保証しない。
 */
template <typename TYPE>
size_t
BinarySearch(const TYPE* data,
			 size_t length,
			 const TYPE& key)
{
	assert(data);
	assert(length);
	assert(length != INVALID_INDEX);

	size_t s(0);
	size_t e = length - 1;
	size_t i;

	while (s <= e) {
		i = (s + e) / 2;
		if (data[i] < key) {
			s = i + 1;
			continue;
		}
		if (data[i] > key) {
			if (0 == i) break;
			e = i - 1;
			continue;
		}
		return i;
	}

	return INVALID_INDEX;
}

#endif	// __UTILITY_HPP__
