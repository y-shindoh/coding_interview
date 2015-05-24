/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	bits_operation.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の5章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#ifndef	__BITS_OPERATION_HPP__
#define	__BITS_OPERATION_HPP__	"bits_operation.hpp"

#include <cstddef>
#include <cstdio>
#include <cassert>

/**
 * ビットの状況を出力
 * @param[out]	file	出力先ファイル
 * @param[in]	bits	処理対象の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
void
print_bits(FILE* file,
		   TYPE bits)
{
	TYPE h, k;
	int c;

	for (size_t i(0); i < sizeof(TYPE); ++i) {
		if (0 < i) std::fputc((int)' ', file);
		h = sizeof(TYPE) - i - 1;	// for little endian
		for (size_t j(0); j < 8; ++j) {
			k = 8 - j - 1;
			c = '0';
			if (bits & ((TYPE)1 << (h * 8 + k))) c = '1';
			std::fputc(c, file);
		}
	}

	std::fprintf(file, " [0x%lX]\n", (size_t)bits);
}

/**
 * 指定位置のビットを取得
 * @param[in]	bits	処理対象の整数
 * @param[in]	i	位置
 * @return	処理後の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
TYPE
get_bit(TYPE bits,
		size_t i)
{
	assert(i < sizeof(TYPE) * 8);

	return bits & ((TYPE)1 << i);
}

/**
 * 指定位置のビットを @a 1 にする
 * @param[in]	bits	処理対象の整数
 * @param[in]	i	位置
 * @return	処理後の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
TYPE
set_bit(TYPE bits,
		size_t i)
{
	assert(i < sizeof(TYPE) * 8);

	return bits | ((TYPE)1 << i);
}

/**
 * 指定位置のビットを @a 0 にする
 * @param[in]	bits	処理対象の整数
 * @param[in]	i	位置
 * @return	処理後の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
TYPE
clear_bit(TYPE bits,
		  size_t i)
{
	assert(i < sizeof(TYPE) * 8);

	return bits & ~((TYPE)1 << i);
}

/**
 * 指定位置以上の全ビットを @a 0 にする
 * @param[in]	bits	処理対象の整数
 * @param[in]	i	位置
 * @return	処理後の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
TYPE
clear_high_bits(TYPE bits,
				size_t i)
{
	assert(i < sizeof(TYPE) * 8);

	return bits & (((TYPE)1 << i) - 1);
}

/**
 * 指定位置以下の全ビットを @a 0 にする
 * @param[in]	bits	処理対象の整数
 * @param[in]	i	位置
 * @return	処理後の整数
 * @note	テンプレートの型 @a TYPE は @a int 以上の幅の符号なし整数。
 */
template<typename TYPE>
TYPE
clear_low_bits(TYPE bits,
			   size_t i)
{
	assert(i < sizeof(TYPE) * 8);

	if (i + 1 == sizeof(TYPE) * 8) return 0;
	return bits & ~(((TYPE)1 << (i+1)) - 1);
}

#endif	// __BITS_OPERATION_HPP__
