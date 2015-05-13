/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <vector>

/**
 * @class	文字をカウントするクラス
 * @note	テンプレートの型 @a TYPE には符号なし整数を指定すること。
 * @note	US-ASCIIのみに対応。より広い空間を扱う場合はHashテーブルが欲しい。
 * @note	実質的にはUS-ASCIIの文字種数を長さに持つただの配列。
 * @note	基本的なアイディアはバケット・ソート。
 */
template<typename TYPE>
class LetterChecker
{
private:

	std::vector<TYPE> buffer_;	///< 各文字のカウント

public:

	/**
	 * コンストラクタ
	 */
	LetterChecker()
		{
			buffer_.resize((size_t)0x100, (TYPE)0);
		}

	/**
	 * 文字を追加
	 * @param[in]	letter	文字
	 * @return	文字 @a letter の出現回数。
	 */
	TYPE
	count(char letter)
		{
			size_t i = 0xFF & (size_t)letter;	// 冗長?
			buffer_[i]++;
			return buffer_[i];
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	////////////////////////////////////////////////////////////
	// US-ASCIIの場合、文字列長が256以上なら、チェック不要。
	// US-ASCIIは '\0' を除くと文字種が255であり、
	// 文字列長が256以上なら必ず重複があるため。

	char sample[] = "AbCdBC.";

	LetterChecker<unsigned char>* checker = new LetterChecker<unsigned char>();
	size_t c;

	for (size_t i(0); sample[i]; ++i) {
		c = (size_t)checker->count(sample[i]);
		std::printf("%c: %lu\n", sample[i], c);
		if (c == 2) std::printf(">>>> '%c' appeared twice.\n", sample[i]);
	}

	delete checker;

	return 0;
}
