/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>

/**
 * コインの全ての組み合わせを生成
 */
template<typename TYPE>
class CoinsCalculator
{
private:

	size_t length_;								///< コインの種類の総数
	const TYPE* coin_types_;					///< 各コインの価値
	std::vector<TYPE> buffer_;					///< 作業領域 (枚数)
	std::vector<std::vector<TYPE> >* storage_;	///< 返却値

	/**
	 * メソッド @a execute の再帰処理部分
	 * @param[in]	value	残りの価値
	 * @param[in]	i	処理対象のコイン
	 */
	void
	execute_routine(TYPE value,
					size_t i)
		{
			if (length_ <= i) {
				if (value == (TYPE)0) storage_->push_back(buffer_);
				return;
			}

			if (coin_types_[i]) {
				for (size_t j(0); ; ++j) {
					if (value < coin_types_[i] * (TYPE)j) break;
					buffer_[i] = (TYPE)j;
					execute_routine(value - coin_types_[i] * (TYPE)j, i + 1);
				}
				buffer_[i] = (TYPE)0;
			}
			else {
				execute_routine(value, i + 1);
			}
		}

public:

	/**
	 * コインの全ての組み合わせを生成
	 * @param[in]	value	求めたい合計の価値
	 * @param[in]	coins	各コインの価値
	 * @param[in]	length	引数 @a coins の長さ
	 * @return	全ての組み合わせ
	 * @note	生成失敗時は @a 0 が返却される。
	 * @note	返却値は本メソッド利用者の責任で削除すること。
	 */
	std::vector<std::vector<TYPE> >*
	execute(TYPE value,
			const TYPE* coins,
			size_t length)
		{
			assert(coins);
			assert(length);

			length_ = length;
			coin_types_ = coins;
			buffer_.clear();
			buffer_.resize(length, (TYPE)0);

			try {
				storage_ = new std::vector<std::vector<TYPE> >();
			}
			catch (...) {
				return 0;
			}

			execute_routine(value, 0);

			return storage_;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	const unsigned int coins[] = {1, 5, 10, 25};
	const size_t length = sizeof(coins) / sizeof(coins[0]);
	unsigned int value(30);

	CoinsCalculator<unsigned int> calculator;
	std::vector<std::vector<unsigned int> >* answers = calculator.execute(value, coins, length);

	size_t m = answers->size();
	size_t n;
	for (size_t i(0); i < m; ++i) {
		std::printf("[%lu] ", i);
		n = answers->at(i).size();
		for (size_t j(0); j < n; ++j) {
			if (0 < j) std::printf(", ");
			std::printf("%u", answers->at(i)[j]);
		}
		std::printf("\n");
	}

	delete answers;

	return 0;
}
