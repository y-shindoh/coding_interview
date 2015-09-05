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
#include <set>

/**
 * 与えた因数から生成される合成数のうちk番目に小さいものを算出
 * @param[in]	factors	因数
 * @param[in]	lenght	引数 @a factors の要素数
 * @param[in]	k	昇順におけるインデックス (0始まり)
 * @return	k番目に小さい合成数
 */
template<typename TYPE>
TYPE
find_kth_composition_1(const TYPE* factors,
					   size_t lenght,
					   size_t k)
{
	assert(factors);

	std::priority_queue< TYPE, std::vector<TYPE>, std::greater<TYPE> > queue;
	std::set<TYPE> post;
	TYPE x, y;

	queue.push((TYPE)1);

	for (size_t i(0); i < k; ++i) {
		x = queue.top();
		for (size_t j(0); j < lenght; ++j) {
			y = x * factors[j];
			if (post.find(y) != post.end()) continue;
			queue.push(y);
			post.insert(y);
		}
		queue.pop();
	}

	return queue.top();
}

/**
 * 与えた因数から生成される合成数のうちk番目に小さいものを算出
 * @param[in]	factors	因数
 * @param[in]	lenght	引数 @a factors の要素数
 * @param[in]	k	昇順におけるインデックス (0始まり)
 * @return	k番目に小さい合成数
 * @note	型 @a TYPE には符号なし整数を指定すること。
 */
template<typename TYPE>
TYPE
find_kth_composition_2(const TYPE* factors,
					   size_t lenght,
					   size_t k)
{
	assert(factors);
	assert(0 < lenght);

	std::vector< std::queue<TYPE> > queue;
	std::set<TYPE> post;

	queue.resize(lenght);
	queue[0].push((TYPE)1);

	TYPE x, y;
	size_t h;

	for (size_t i(0); ; ++i) {
		// 最小値の探索
		x = ~(TYPE)0;
		for (size_t j(0); j < lenght; ++j) {
			if (queue[j].empty() || x <= queue[j].front()) continue;
			x = queue[j].front();
			h = j;
		}
		if (k <= i) break;
		queue[h].pop();
		// 次の値の格納
		for (size_t j(0); j < lenght; ++j) {
			y = x * factors[j];
			if (post.find(y) != post.end()) continue;
			queue[j].push(y);
			post.insert(y);
		}
	}

	return x;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const size_t factors[] = {3, 5, 7};
	size_t n;

	for (size_t i(0); i < 10; ++i) {
		n = find_kth_composition_1<size_t>(factors, sizeof(factors) / sizeof(factors[0]), i);
		printf("[%lu] %lu\n", i, n);
	}

	for (size_t i(0); i < 10; ++i) {
		n = find_kth_composition_2<size_t>(factors, sizeof(factors) / sizeof(factors[0]), i);
		printf("[%lu] %lu\n", i, n);
	}

	return 0;
}
