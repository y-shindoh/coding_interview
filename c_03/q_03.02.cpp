/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * @class	最小値を最悪計算量Θ(1)で出力できるスタック
 * @note	テンプレートの型 @a TYPE はスタックのキーの型。
 */
template<typename TYPE>
class MinimumStack
{
private:

	std::vector<TYPE> data_;	///< 本来のスタック
	std::vector<TYPE> minimum_;	///< 最小値のスタック

public:

	/**
	 * コンストラクタ
	 */
	MinimumStack()
		{
			;
		}

	/**
	 * デストラクタ
	 */
	virtual
	~MinimumStack()
		{
			;
		}

	/**
	 * スタックが空か確認
	 * @return	true: 空, false: 空でない
	 * @note	最悪計算量はO(1)。
	 */
	bool
	empty() const
		{
			return data_.empty();
		}

	/**
	 * スタックの要素数を取得
	 * @return	スタックの要素数
	 * @note	最悪計算量はO(1)。
	 */
	size_t
	size() const
		{
			return data_.size();
		}

	/**
	 * スタックの値を取得
	 * @return	最後にスタックに追加した値を取得
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	top() const
		{
			assert(!data_.empty());

			return data_.back();
		}

	/**
	 * スタックの最小値を取得
	 * @return	スタックの最小値
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	minimum() const
		{
			assert(!minimum_.empty());

			return minimum_.back();
		}

	/**
	 * スタックに要素を追加
	 * @param[in]	data	追加するデータ
	 * @note	ならし解析の計算量はO(1)となる。最悪計算量はO(n)で、nはスタックの長さ。
	 */
	void
	push(const TYPE& data)
		{
			data_.push_back(data);
			if (minimum_.empty() || data <= minimum_.back()) {
				minimum_.push_back(data);
			}
		}

	/**
	 * スタックから要素を削除
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	void
	pop()
		{
			assert(!data_.empty());
			assert(!minimum_.empty());

			if (data_.back() <= minimum_.back()) {
				minimum_.pop_back();
			}
			data_.pop_back();
		}

	/**
	 * スタックの状態を出力
	 * @param	file	出力先
	 */
	void
	print(FILE* file) const
		{
			size_t l = data_.size();
			std::fprintf(file, "[D] ");
			for (size_t i(0); i < l; ++i) {
				if (0 < i) std::fprintf(file, ", ");
				std::fprintf(file, "%G", (double)data_[i]);
			}
			std::fprintf(file, "\n");

			l = minimum_.size();
			std::fprintf(file, "[M] ");
			for (size_t i(0); i < l; ++i) {
				if (0 < i) std::fprintf(file, ", ");
				std::fprintf(file, "%G", (double)minimum_[i]);
			}
			std::fprintf(file, "\n");
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	MinimumStack<int>* stack = new MinimumStack<int>();

	stack->push(2);
	stack->push(3);
	stack->push(1);
	stack->push(4);
	stack->push(8);
	stack->push(-1);

	stack->print(stdout);

	stack->pop();
	stack->pop();

	stack->print(stdout);

	std::printf("last: %d\n", stack->top());
	std::printf("min:  %d\n", stack->minimum());

	delete stack;

	return 0;
}
