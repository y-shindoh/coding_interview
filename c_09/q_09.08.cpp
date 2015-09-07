/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  25セント貨、10セント貨、5セント貨、1セント貨が無数にあるとして、
  これらを使って
  nセントを表現するすべての場合の数を計算するコードを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 指定金額のコインの組み合わせを全て出力
 * @param[in]	coins	コインの種類
 * @param[in]	length	コインの種類の総数
 * @param[in]	value	指定金額
 * @param[in,out]	numbers	作業領域
 * @param[in]	i	使用済みコインの種類の総数
 */
template<typename TYPE>
void
calculate(const TYPE* coins,
		  size_t length,
		  TYPE value,
		  std::vector<TYPE>& numbers,
		  size_t i = 0)
{
	assert(coins);

	if (length <= i) {
		if (value == 0) {
			bool flag(false);
			std::printf("[");
			for (size_t j(0); j < length; ++j) {
				if (numbers[j] == 0) continue;
				if (flag) std::printf(", ");
				std::printf("%G*%G", (double)coins[j], (double)numbers[j]);
				flag = true;
			}
			std::printf("]\n");
		}
		return;
	}

	for (TYPE j(0); coins[i] * j <= value; ++j) {
		numbers.push_back(j);
		calculate<TYPE>(coins, length, value - coins[i] * j, numbers, i + 1);
		numbers.pop_back();
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const unsigned int coins[] = {25, 10, 5, 1};
	const size_t length = sizeof(coins) / sizeof(coins[0]);
	unsigned int value(30);
	std::vector<unsigned int> numbers;

	calculate<unsigned int>(coins, length, value, numbers);

	return 0;
}
