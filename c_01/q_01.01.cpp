/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>

/**
 * @class	1つの文字を複数含んでいるかチェック
 * @note	US-ASCIIのみに対応。US-ASCII内の全ての文字を扱う。
 * @note	実質的にはUS-ASCIIの文字種数を長さに持つただの配列。
 * @note	基本的なアイディアはバケット・ソート。
 */
class LetterChecker
{
private:

	bool buffer_[0x100];	///< 出現文字のフラグ

public:

	/**
	 * 文字列の重複文字の有無をチェック
	 * @param[in]	string	チェック対象の文字列
	 * @return	true: 重複文字あり, false: 重複文字なし
	 */
	bool
	execute(const char* string)
		{
			size_t l = std::strlen(string);
			if (0x100 <= l) return true;

			std::memset((void*)buffer_, 0, sizeof(buffer_));
			int k;
			for (size_t i(0); i < l; ++i) {
				k = 0xFF & (int)string[i];
				if (buffer_[k]) return true;
				buffer_[k] = true;
			}

			return false;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	char sample[][1024] = {"AbCdBC.", "AbCdBc."};

	LetterChecker* checker = new LetterChecker();

	for (size_t i(0); i < sizeof(sample)/sizeof(sample[0]); ++i) {
		if (checker->execute(sample[i])) {
			std::printf("FOUND     ");
		}
		else {
			std::printf("NOT FOUND ");
		}
		std::printf("'%s'\n", sample[i]);
	}

	delete checker;

	return 0;
}
