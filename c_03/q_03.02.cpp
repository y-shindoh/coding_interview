/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  push と pop に加えて、最小の要素を返す関数 min を持つスタックを
  どのようにデザインしますか?
  ただし push, pop, min 関数はすべて O(1) の実行時間になるようにしてください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * @class	最小値を最悪計算量Θ(1)で出力できるスタック
 * @note	テンプレートの型 @a TYPE はスタックのキーの型。
 * @note	各メソッドの計算量は、実際には std::vector に依存している。
 */
template<typename TYPE>
class MinimumStack
{
private:

	std::vector<TYPE> data_;	///< データのスタック
	std::vector<size_t> index_;	///< 最小値を指すインデックス

public:

	/**
	 * スタックが空かどうかを確認
	 * @return	true: 空, false: 空ではない
	 * @note	計算量は O(1)。
	 */
	bool
	empty() const
		{
			return data_.empty();
		}

	/**
	 * スタックの先頭要素を参照
	 * @return	先頭要素
	 * @note	計算量は O(1)。
	 */
	TYPE
	top() const
		{
			assert(!data_.empty());

			return data_.back();
		}

	/**
	 * スタック中の最小値を参照
	 * @return	最小値
	 * @note	計算量は O(1)。
	 */
	TYPE
	min() const
		{
			assert(!index_.empty());

			size_t i = index_.back();
			return data_[i];
		}

	/**
	 * スタックに要素を追加
	 * @param[in]	data	追加対象の要素
	 * @note	ならし計算量は O(1)。
	 */
	void
	push(const TYPE& data)
		{
			if (index_.empty()) {
				index_.push_back(0);
			}
			else {
				size_t i = index_.back();
				if (data < data_[i]) {
					i = data_.size();
					index_.push_back(i);
				}
			}

			data_.push_back(data);
		}

	/**
	 * スタックから先頭要素を除去
	 * @note	計算量は O(1)。
	 */
	TYPE
	pop()
		{
			assert(!data_.empty());
			assert(!index_.empty());

			TYPE data = data_.back();

			data_.pop_back();
			if (data_.size() <= index_.back()) index_.pop_back();

			return data;
		}

	/**
	 * スタックの内容を出力
	 * @param[in,out]	file	出力先
	 */
	void
	print(FILE* file) const
		{
			assert(file);

			if (data_.empty()) return;

			std::fprintf(file, "[D] ");
			for (size_t i(0); i < data_.size(); ++i) {
				if (0 < i) std::fprintf(file, ", ");
				std::fprintf(file, "%G", (double)data_[i]);
			}
			std::fprintf(file, "\n");

			std::fprintf(file, "[I] ");
			for (size_t i(0); i < index_.size(); ++i) {
				if (0 < i) std::fprintf(file, ", ");
				std::fprintf(file, "%lu", index_[i]);
			}
			std::fprintf(file, "\n");
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	MinimumStack<int>* stack = new MinimumStack<int>;

	stack->push(2);
	stack->push(3);
	stack->push(1);
	stack->push(4);
	stack->push(8);
	stack->push(-1);

	stack->print(stdout);

	if (!stack->empty()) stack->pop();
	if (!stack->empty()) stack->pop();

	stack->print(stdout);

	if (!stack->empty())  {
		std::printf("last: %d\n", stack->top());
		std::printf("min:  %d\n", stack->min());
	}

	delete stack;

	return 0;
}
