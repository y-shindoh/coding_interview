/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある文字列の、すべての順列を返すメソッドを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>

/**
 * 文字列の全ての順列を生成 (補助関数)
 */
void
make_permutational_strings(const std::string& input,
						   char* buffer,
						   bool* flags,
						   size_t i,
						   std::vector<std::string>& strings)
{
	assert(buffer);
	assert(flags);

	if (input.length() <= i) {
		strings.push_back(std::string(buffer));
		return;
	}

	for (size_t j(0); input[j]; ++j) {
		if (flags[j]) continue;
		buffer[i] = input[j];
		flags[j] = true;
		make_permutational_strings(input, buffer, flags, i+1, strings);
		flags[j] = false;
	}
}

/**
 * 文字列の全ての順列を生成
 * @param[in]	input	基礎となる文字列
 * @param[out]	strings	全ての順列 (生成失敗時は何も追加しない)
 * @note	US-ASCIIのみを処理対象とする。
 * @note	計算量は O(2^n)。ただし n は文字列 @a input の長さ。
 */
void
make_permutational_strings(const std::string& input,
						   std::vector<std::string>& strings)
{
	char* buffer(0);
	bool* flags(0);

	try {
		buffer = new char[input.size()+1];
		flags = new bool[input.size()];
	}
	catch (...) {
		;
	}

	if (buffer && flags) {
		buffer[input.size()] = '\0';
		std::memset((void*)flags, 0, sizeof(bool) * input.size());
		make_permutational_strings(input, buffer, flags, 0, strings);
	}

	if (buffer) delete [] buffer;
	if (flags) delete [] flags;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const std::string input("a0A");
	std::vector<std::string> strings;

	make_permutational_strings(input, strings);

	std::vector<std::string>::const_iterator it;

	for (it = strings.begin(); it != strings.end(); ++it) {
		std::printf("%s\n", it->c_str());
	}

	return 0;
}
