/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_07.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題7.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  素因数が3, 5, 7だけの整数値で、
  k番目に小さいものを見つけるアルゴリズムを設計してください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <queue>
#include <vector>

/**
 * 与えた因数から生成される合成数のうちk番目に小さいものを算出
 * @param[in]	factors	因数
 * @param[in]	lenght	引数 @a factors の要素数
 * @param[in]	k	昇順におけるインデックス (0始まり)
 * @return	k番目に小さい合成数
 */
template<typename TYPE>
TYPE
find_kth_composition(const TYPE* factors,
					 size_t lenght,
					 size_t k)
{
	std::priority_queue< TYPE, std::vector<TYPE>, std::greater<TYPE> > queue;
	TYPE value;

	queue.push((TYPE)1);

	for (size_t i(0); i <= k; ++i) {	// インデックスに注意
		value = queue.top();
		for (size_t j(0); j < lenght; ++j) {
			queue.push(value * factors[j]);
		}
		while (value >= queue.top()) queue.pop();	// 重複を除去
	}

	return queue.top();
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const unsigned int factors[] = {3, 5, 7};
	unsigned int n;

	for (unsigned int i(0); i < 9; ++i) {
		n = find_kth_composition<unsigned int>(factors, sizeof(factors) / sizeof(factors[0]), i);
		printf("[%u] %u\n", i, n);
	}

	return 0;
}
