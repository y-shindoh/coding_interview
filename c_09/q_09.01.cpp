/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  子供がn段の階段を駆け上がりますが、一歩で1段、2段、もしくは3段を登ることができます。
  このとき、考え得る階段の上がり方が何通りあるかを求めるメソッドを実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 階段の登り方が何種類あるかを算出
 * @param[in]	length	階段の合計段数
 * @param[in]	step	一歩で登ることのできる最大段数
 * @return	階段の登り方の種類
 * @note	動的計画法を用いて O(length * step) の計算量に抑制。
 * @note	メモリ占有量は O(step)。
 */
template<typename TYPE>
TYPE
find_step_sequence(size_t length,
				   size_t step)
{
	std::vector<TYPE> buffer;
	buffer.push_back((TYPE)1);
	for (size_t i(0); i < step; ++i) {
		buffer.push_back((TYPE)0);
	}

	size_t h, k;

	for (size_t i(0); i < length; ++i) {
		h = i % (step + 1);
		for (size_t j(1); j <= step; ++j) {
			k = (h + j) % (step + 1);
			buffer[k] += buffer[h];
		}
		buffer[h] = 0;
	}

	h = length % (step + 1);

	return buffer[h];
}

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t n;
	size_t s(3);

	for (size_t i(1); i <= 10; ++i) {
		n = find_step_sequence<size_t>(i, s);
		std::printf("%lu / 1-%lu => %lu\n", i, s, n);
	}

	return 0;
}
