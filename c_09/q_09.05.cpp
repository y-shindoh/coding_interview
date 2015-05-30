/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.5の回答
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
 * 文字列の全ての順列を生成
 * @note	対象はUS-ASCIIのみとする。
 */
class PermutationMaker
{
private:

	std::vector<char> flags_;			///< 使用状況フラグ
	std::vector<std::string>* storage_;	///< 順列の集合 (返却値)

	size_t length_;						///< 文字列長
	const char* input_;					///< 入力文字列
	char* output_;						///< 作業領域

	/**
	 * メソッド @a execute の再帰処理部分
	 * @param[in]	i	文字の追加位置
	 */
	void
	execute_routine(size_t i)
		{
			if (length_ <= i) {
				storage_->push_back(std::string(output_));
				return;
			}

			for (size_t j(0); j < length_; ++j) {
				if (flags_[j]) continue;
				flags_[j] = (char)1;
				output_[i] = input_[j];
				execute_routine(i + 1);
				flags_[j] = (char)0;
			}
		}

public:

	/**
	 * 文字列の全ての順列を生成
	 * @param[in]	input	文字列
	 * @param[in]	length	文字列 @a input の長さ
	 * @return	全ての順列
	 * @note	生成失敗時は @a 0 が返却される。
	 * @note	返却値は本メソッド利用者の責任で削除すること。
	 */
	std::vector<std::string>*
	execute(const char* input,
			size_t length)
		{
			assert(input);
			assert(length);

			input_ = input;
			length_ = length;
			storage_ = 0;
			output_ = 0;

			try {
				storage_ = new std::vector<std::string>();
				output_ = new char[length+1];
			}
			catch (...) {
				if (storage_) delete storage_;
				if (output_) delete output_;
				return 0;
			}

			flags_.clear();
			flags_.resize(length, (char)0);
			output_[length] = '\0';

			execute_routine(0);

			delete output_;

			return storage_;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	const char input[] = "Aa1";
	const size_t length = std::strlen(input);

	PermutationMaker maker;
	std::vector<std::string>* permutation = maker.execute(input, length);

	size_t m = permutation->size();
	size_t n;
	for (size_t i(0); i < m; ++i) {
		std::printf("[%lu] %s\n", i, permutation->at(i).c_str());
	}

	delete permutation;

	return 0;
}
