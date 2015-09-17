/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  文字列の配列を、
  アナグラムになっている文字列がお互いに隣り合うように並び替えるメソッドを書いてください。
 */

#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <string>

/*
  MEMO:
  C++11を使う場合、以下の要領でより効率的な方法が実現できる。
  1) 各文字列をソートしてキーとなる文字列を作る。 (後述の sort_char と同等)
  2) unordered_map にキーの文字列と元の文字列を保持する。このとき、後者は複数保持できるようにする。
  3) unordered_map をイテレートして、各キー毎の元の文字列を書き出す。
  ※ 古い map ではこの方法は効率が少し悪い。
 */

/**
 * 2つの値を入れ替え
 * @param[in,out]	left	処理対象のオブジェクト
 * @param[in,out]	right	処理対象のオブジェクト
 */
template<typename TYPE>
void
swap(TYPE& left,
	 TYPE& right)
{
	TYPE tmp(left);
	left = right;
	right = tmp;
}

/**
 * 文字列を文字レベルでソート
 * @param[in]	string	入力文字列
 * @param[out]	buffer	出力文字列
 * @note	今回は手抜きしてバブル・ソートで実装。
 * @note	US-ASCIIにのみ対応。
 */
void
sort_char(const char* string,
		  char* buffer)
{
	assert(string);
	assert(buffer);

	std::strcpy(buffer, string);

	size_t n = std::strlen(string);
	size_t k;
	bool flag;

	for (size_t i(0); i < n; ++i) {
		k = n - i;
		flag = true;
		for (size_t j(1); j < k; ++j) {
			if (buffer[j-1] <= buffer[j]) continue;
			swap<char>(buffer[j-1], buffer[j]);
			flag = false;
		}
		if (flag) break;
	}
}

/**
 * キー文字列により配列をソート
 * @param[in]	data	キー文字列と外部インデックスの組の配列
 * @param[in]	length	配列 @a data の要素数
 * @note	今回は手抜きしてバブル・ソートで実装。
 */
void
sort_pairs_array(std::pair<std::string, const char*>* data,
				 size_t length)
{
	assert(data);
	assert(length);

	bool flag;
	size_t k;

	for (size_t i(0); i < length; ++i) {
		k = length - i;
		flag = true;
		for (size_t j(1); j < k; ++j) {
			if (data[j-1].first <= data[j].first) continue;
			data[j-1].first.swap(data[j].first);
			swap<const char*>(data[j-1].second, data[j].second);
			flag = false;
		}
		if (flag) break;
	}
}

/**
 * 動作確認用コマンド
 * @note	本来はメソッドを作る問題だが、
			ここでは説明を簡単にするため、問題に従っていない。
 */
int main()
{
	const char data_1[][10] = {"ABCabc",
							   "EFGHefgh",
							   "KLMklm",
							   "iIjJ",
							   "AaBbCc",
							   "IJij"};
	const size_t l = sizeof(data_1) / sizeof(data_1[0]);
	std::pair<std::string, const char*> data_2[10];
	char buffer[1024];

	for (size_t i(0); i < l; ++i) {
		sort_char(data_1[i], buffer);
		data_2[i].first = buffer;
		data_2[i].second = data_1[i];
	}

	sort_pairs_array(data_2, l);

	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu] '%s' => '%s'\n", i, data_2[i].second, data_2[i].first.c_str());
	}

	return 0;
}
