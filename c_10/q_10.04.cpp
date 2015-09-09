/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_10.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題10.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  1からNまでのすべての数が含まれる配列があります。
  Nの値は最大で32,000です。
  配列の数には重複しているものが含まれており、Nの値は分かりません。
  4KBしかメモリが使えないとき、
  重複する値を表示するにはどのようにすればよいでしょうか?
 */

#include <cstddef>
#include <bitset>
#include <cstdio>

/**
 * 動作確認用コマンド
 */
int main()
{
	// 4KBは、4 * 1024 * 8 = 32768ビットで、
	// 1〜32000の整数を表現には十分な大きさがある。
	std::bitset<4 * 1024 * 8> set;
	unsigned int data[] = {1, 2, 32000, 2};

	for (size_t i(0); i < sizeof(data) / sizeof(data[0]); ++i) {
		unsigned int k = data[i];
		if (set[k]) {
			std::printf("%u is a duplicated value.\n", k);
		}
		set.set(k);
	}

	return 0;
}
