/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_07.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題7.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <queue>
#include <vector>

/**
 * 3^h * 5^i * 7^j で表現できる数のうちk番目に小さいものを算出 (h, i, j, kは自然数)
 * @param[in]	k	位置 (自然数)
 * @return	該当する自然数
 * @note	テンプレートの型 @a TYPE は符号なし整数を指定すること。
 * @note	計算量は O(k log k) となる。
 */
template<typename TYPE>
TYPE
find_kth_number(TYPE k)
{
	std::priority_queue<TYPE, std::vector<TYPE>, std::greater<TYPE> > queue;
	TYPE value;
	TYPE previous(0);

	queue.push((TYPE)1);

	for (TYPE i(0); ; ++i) {
		assert(!queue.empty());
		value = queue.top();
		queue.pop();
		if (value == previous) {
			--i;
			continue;	// 重複は除去 (重複は2k以下しか出現しない)
		}
		if (k <= i) break;
		previous = value;
		queue.push((TYPE)3 * value);
		queue.push((TYPE)5 * value);
		queue.push((TYPE)7 * value);
	}

	return value;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	for (unsigned int i(7); i <= 9; ++i) {
		unsigned int n = find_kth_number<unsigned int>(i);
		printf("[%u] %u\n", i, n);
	}

	return 0;
}
