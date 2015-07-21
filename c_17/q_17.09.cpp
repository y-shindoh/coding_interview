/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_17.09.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題17.9の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <iostream>
#include <string>
#include <map>	// 本当は unordered_map がより望ましい
#include <cstdio>

/**
 * 動作確認用コマンド
 * @note	単語は空白区切りで記述され、大文字小文字の違いを認める。
 */
int main()
{
	std::map<std::string, size_t> table;
	std::string word;

	while (std::cin >> word) {
		if (table.find(word) == table.end()) {
			table.insert(std::pair<std::string, size_t>(word, 0));
		}
		++table[word];
	}

	for (std::map<std::string, size_t>::iterator i = table.begin(); i != table.end(); ++i) {
		std::printf("%s: %lu\n", i->first.c_str(), i->second);
	}

	return 0;
}
