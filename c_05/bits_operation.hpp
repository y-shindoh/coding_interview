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

typedef unsigned long long int bo_uint;

#include <cstddef>
#include <cstdio>

/**
 * 符号なし整数のビット1の数を算出
 * @param[in]	value	算出対象の符号なし整数
 * @return	ビット1の数
 */
template<typename TYPE>
size_t
count_bit(TYPE value)
{
	value = ((0xAAAAAAAAAAAAAAAA & (bo_uint)value) >> 1) + ((0x5555555555555555) & (bo_uint)value);
	value = ((0xCCCCCCCCCCCCCCCC & (bo_uint)value) >> 2) + ((0x3333333333333333) & (bo_uint)value);
	value = ((0xF0F0F0F0F0F0F0F0 & (bo_uint)value) >> 4) + ((0x0F0F0F0F0F0F0F0F) & (bo_uint)value);
	value = ((0xFF00FF00FF00FF00 & (bo_uint)value) >> 8) + ((0x00FF00FF00FF00FF) & (bo_uint)value);
	value = ((0xFFFF0000FFFF0000 & (bo_uint)value) >> 16) + ((0x0000FFFF0000FFFF) & (bo_uint)value);
	return ((0xFFFFFFFF00000000 & (bo_uint)value) >> 32) + ((0x00000000FFFFFFFF) & (bo_uint)value);
}

/**
 * 符号なし整数のビットの状態を出力
 * @param[out]	file	出力先
 * @param[in]	vaue	符号なし整数
 * @param[in]	prefix	行頭に付与する文字列 (0なら何も出力しない)
 * @note	little endian用の実装であることに注意。
 */
template<typename TYPE>
void
print_bits(FILE* file,
		   const TYPE value,
		   const char* prefx = 0)
{
	assert(file);

	if (prefx) std::fprintf(file, "%s ", prefx);

	for (size_t i(0); i < sizeof(TYPE); ++i) {
		size_t h = sizeof(TYPE) - i - 1;	// for little endian
		for (size_t j(0); j < 8; ++j) {
			size_t k = 8 - j - 1;
			if (value & ((bo_uint)1 << ((8 * h) + k))) std::printf("1");
			else std::printf("0");
		}
		std::fprintf(file, " ");
	}

	std::fprintf(file, "[0x%llX]\n", (bo_uint)value);
}

#endif	// __BITS_OPERATION_HPP__
