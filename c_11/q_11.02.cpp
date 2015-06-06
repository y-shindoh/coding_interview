/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>
#include <utility>

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
			assert(string);

			size_t j;
			for (size_t i(0); string[i]; ++i) {
				j = 0xFF & (size_t)string[i];	// 冗長?
				if (!buffer_[j]) ++number_of_types_;
				buffer_[j]++;
				assert(buffer_[j] < (TYPE)~(TYPE)0);
			}
		}

	/**
	 * オブジェクトの比較
	 * @param[in]	left	第1オブジェクト
	 * @param[in]	right	第2オブジェクト
	 * @retval	0: 2つのオブジェクトは等しい文字種とその出現数を持つ
	 * @retval	負: 引数 @a left は引数 @a right より文字種が少ないか小さい数値の文字が多い
	 * @retval	正: 引数 @a right は引数 @a left より文字種が少ないか小さい数値の文字が多い
	 */
	static int
	Compare(const LetterChecker<TYPE>& left,
			const LetterChecker<TYPE>& right)
		{
			if (left.number_of_types_ < right.number_of_types_) {
				return -1;
			}
			else if (left.number_of_types_ > right.number_of_types_) {
				return 1;
			}
			else {
				for (size_t i(0); i < 0x100; ++i) {
					if (left.buffer_[i] > right.buffer_[i]) return -1;
					if (left.buffer_[i] < right.buffer_[i]) return 1;
				}
			}
			return 0;
		}
};

/**
 * 文字種情報により配列をソート
 * @param[in]	data	文字種情報と外部インデックスの組の配列
 * @param[in]	length	配列 @a data の要素数
 */
template<typename TYPE>
void
sort_pairs_array(std::pair<LetterChecker<TYPE>, size_t>* data,
				 size_t length)
{
	assert(data);
	assert(length);

	bool flag;
	size_t k;
	std::pair<LetterChecker<TYPE>, size_t> tmp;

	for (size_t i(0); i < length; ++i) {
		k = length - i;
		flag = false;
		for (size_t j(1); j < k; ++j) {
			if (LetterChecker<TYPE>::Compare(data[j-1].first, data[j].first) <= 0) continue;
			tmp = data[j-1];
			data[j-1] = data[j];
			data[j] = tmp;
			flag = true;
		}
		if (!flag) break;
	}
}

/**
 * 動作確認用コマンド
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
	std::pair<LetterChecker<size_t>, size_t> data_2[10];

	for (size_t i(0); i < l; ++i) {
		data_2[i].first.count(data_1[i]);
		data_2[i].second = i;
	}

	sort_pairs_array<size_t>(data_2, l);

	size_t j;
	for (size_t i(0); i < l; ++i) {
		j = data_2[i].second;
		std::printf("[%lu] '%s'\n", i, data_1[j]);
	}

	return 0;
}
