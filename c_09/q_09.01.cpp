/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <vector>

/**
 * n段の階段を一歩で1〜N段ずつ登る場合の登り方の数
 * @param[in]	n	階段の段数
 * @param[out]	c	登り方の数 (事前に0で初期化すること)
 * @note	テンプレートの型 @a TYPE は符号なし整数を指定すること。
 * @note	テンプレートの整数 @a N は一歩で登れる段数を指定すること。
 * @note	分割統治法を併用すれば高速に処理できるが、ここではしない。
 */
template<typename TYPE, size_t N>
void
find_step_sequence(TYPE n, TYPE& c)
{
	for (size_t i(1); i <= N; ++i) {
		if (n <= i) {
			if (n == i) ++c;
			break;
		}
		find_step_sequence<TYPE, N>(n - i, c);
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t n(20);
	size_t c(0);

	find_step_sequence<size_t, 3>(n, c);
	std::printf("%lu / 1-%lu => %lu\n", n , (size_t)3, c);

	return 0;
}
