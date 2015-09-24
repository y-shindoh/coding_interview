/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  C++を用いて、入力ファイルの後ろからK行を表示するメソッドを書いてください。
 */

#include <cstddef>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

/**
 * ファイルの末尾の指定行を取得
 * @param[in,out]	stream	ファイル
 * @param[out]	lines	取得した行
 * @param[in]	number	取得する行
 * @note	引数 @a lines には行の先頭に近い順に行が格納される。
 */
void
get_last_lines(std::istream& stream,
			   std::vector<std::string>& lines,
			   size_t number)
{
	lines.clear();
	lines.resize(number);

	size_t i(0);
	size_t j;
	std::string line;

	while (std::getline(stream, line)) {
		j = i++ % number;
		lines[j] = line;
	}

	if (i <= number) {
		lines.resize(i);
	}
	else {
		for (i %= number; 0 < i && i < number; ++i) {
			line = lines[number-1];
			for (size_t k(1); k < number; ++k) {
				j = number - k;
				lines[j] = lines[j-1];
			}
			lines[0] = line;
		}
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::vector<std::string> lines;

	get_last_lines(std::cin, lines, 4);

	for (size_t i(0); i < lines.size(); ++i) {
		std::printf("[%lu]\t'%s'\n", i, lines[i].c_str());
	}

	return 0;
}
