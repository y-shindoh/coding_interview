/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_01.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題1.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * @class	文字をカウントするクラス
 * @note	テンプレートの型 @a TYPE には符号なし整数を指定すること。
 * @note	US-ASCIIのみに対応。より広い空間を扱う場合はHashテーブルなどが必要。
 * @note	実質的にはUS-ASCIIの文字種数を長さに持つただの配列。
 * @note	基本的なアイディアはバケット・ソート。
 */
template<typename TYPE>
class LetterChecker
{
private:

	std::vector<TYPE> buffer_;	///< 各文字のカウント
	size_t number_of_types_;	///< 文字種のカウント

public:

	/**
	 * コンストラクタ
	 */
	LetterChecker()
		: number_of_types_(0)
		{
			buffer_.resize((size_t)0x100, (TYPE)0);
		}

	/**
	 * 文字を追加
	 * @param[in]	string	文字列
	 */
	void
	count(const char* string)
		{
			size_t j;
			for (size_t i(0); string[i]; ++i) {
				j = 0xFF & (size_t)string[i];	// 冗長?
				if (!buffer_[j]) ++number_of_types_;
				buffer_[j]++;
				assert(buffer_[j] < (TYPE)~(TYPE)0);
			}
		}

	/**
	 * 文字の出現数を比較
	 * @param[in]	other	比較対象の @a LetterChecker オブジェクト
	 * @return	true: 全文字種で出現数が等しい, false: 等しくない出現数の文字があった
	 * @note	trueが返却された場合、
				2つの @a LetterChecker オブジェクトが読み込んだそれぞれの文字列は、
				一方の順番を入れ替えればもう一方と等しい文字列になる。
	 */
	bool
	equal(const LetterChecker<TYPE>* other) const
		{
			if (number_of_types_ != other->number_of_types_) return false;

			for (size_t i(0); i < (size_t)0x100; ++i) {
				if (buffer_[i] != other->buffer_[i]) return false;
			}

			return true;
		}

	/**
	 * 文字の出現数を比較
	 * @param[in]	left	比較対象の @a LetterChecker オブジェクト
	 * @param[in]	right	比較対象の @a LetterChecker オブジェクト
	 * @return	true: 全文字種で出現数が等しい, false: 等しくない出現数の文字があった
	 * @note	trueが返却された場合、
				2つの @a LetterChecker オブジェクトが読み込んだそれぞれの文字列は、
				一方の順番を入れ替えればもう一方と等しい文字列になる。
	 */
	static bool
	Equal(const LetterChecker<TYPE>* left,
		  const LetterChecker<TYPE>* right)
		{
			return left->equal(right);
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	////////////////////////////////////////////////////////////
	// - 大文字と小文字は区別する。
	// - US-ASCIIの全ての文字を処理対象とする。
	// - 文字列長が異なれば、入れ替えでは同一の文字列に変換できない。
	char sample[][16] = {"AbCdBC.", "AbcdBC.", "CdB.bCA"};

	LetterChecker<unsigned char>* checker[] = {0, 0, 0};
	const size_t l = sizeof(checker)/sizeof(checker[0]);

	for (size_t i(0); i < l; ++i) {
		std::printf("[%lu]\t'%s'\n", i, sample[i]);
	}

	for (size_t i(0); i < l; ++i) {
		checker[i] = new LetterChecker<unsigned char>();
		checker[i]->count(sample[i]);
	}

	bool flag;
	for (size_t i(0); i < l; ++i) {
		for (size_t j(i+1); j < l; ++j) {
			flag = LetterChecker<unsigned char>::Equal(checker[i], checker[j]);
			if (flag) {
				std::printf("%lu == %lu\n", i, j);
			}
			else {
				std::printf("%lu != %lu\n", i, j);
			}
		}
	}

	for (size_t i(0); i < l; ++i) {
		delete checker[i];
	}

	return 0;
}
