/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.09.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.9の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  確保されたメモリのアドレスが指定された2の累乗で割り切れる数になっているように
  調整された malloc と free を書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cassert>

/**
 * 先頭のアドレス値が指定値で割り切れる値となるメモリ領域を確保
 * @param[in]	length	欲しいメモリ超
 * @param[in]	segment	割り切る値
 * @return	確保したメモリ領域
 */
void*
my_malloc(size_t length,
		  size_t segment = 4)
{
	assert(0 < length);
	assert(2 <= segment);

	char* p = (char*)malloc(length + segment);
	std::printf("original: %lu\n", (size_t)p);

	*p++ = 0;
	while ((size_t)p % segment) {
		*p++ = ~(char)0;
	}
	std::printf("modified: %lu\n", (size_t)p);

	return (void*)p;
}

/**
 * 関数 my_malloc で確保したメモリ領域を解放
 * @param[in,out]	pointer	開放するメモリ領域
 * @note	引数 @a pointer に 0 を代入した場合は何もしない。
 */
void
my_free(void* pointer)
{
	if (!pointer) return;

	char* p = (char*)pointer;
	while (*--p) ;
	std::printf("original: %lu\n", (size_t)p);
	std::free((void*)p);
}


/**
 * 動作確認コマンド
 */
int
main()
{
	void* buffer = my_malloc(1000, 128);

	my_free(buffer);

	return 0;
}
