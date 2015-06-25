/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

#define	K	((size_t)4)

/**
 * 動作確認用コマンド
 */
int main()
{
	size_t i(0);
	std::string line;
	std::vector<std::string> buffer;
	buffer.resize(K);

	while (std::getline(std::cin, line)) {
		buffer[i] = line;
		i = (i + 1) % K;
	}

	for (size_t j(0); j < K; ++j) {
		std::printf("%s\n", buffer[i].c_str());
		i = (i + 1) % K;
	}

	return 0;
}
