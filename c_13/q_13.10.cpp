/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.10.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.10の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  Cで、2次元配列を割り当てる my2DAlloc という関数を書いてください。
  ただし、malloc の呼び出しを最小限にして、
  メモリには arr[i][j] という記述でアクセスできるようにしてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

/**
 * 2次元配列のメモリ領域を確保
 * @param[in]	height	行列の高さ
 * @param[in]	width	行列の幅
 * @return	行列のメモリ領域
 */
template<typename TYPE>
TYPE**
my_malloc(size_t height,
		  size_t width)
{
	assert(0 < height);
	assert(0 < width);

	TYPE** p = (TYPE**)std::malloc(height * sizeof(TYPE*) + height * width * sizeof(TYPE));

	if (p) {
		TYPE* v = (TYPE*)(p + height);

		for (size_t i(0); i < height; ++i) {
			p[i] = v + i * width;
		}
	}

	return p;
}

/**
 * 動作確認コマンド
 */
int
main()
{
	char** buffer = my_malloc<char>(32, 6);

	buffer[0][5] = 'a';
	buffer[2][3] = 'b';

	std::free((void*)buffer);

	return 0;
}
