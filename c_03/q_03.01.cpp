/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * @class	1つの配列で複数のスタックを実現
 * @note	テンプレートの整数 @a N はスタックの数
 */
template<typename TYPE, size_t N>
class MultiStack
{
private:

	std::vector<TYPE> stack_;	///< スタック本体
	size_t length_[N];			///< 各スタックが保持するデータ数

public:

	/**
	 * コンストラクタ
	 * @param[in]	l	各スタックのメモリの広さの初期値 (自然数)
	 */
	MultiStack(size_t l = 16)
		{
			assert(0 < l);

			stack_.resize(l * N);
			std::memset((void*)length_, 0, sizeof(size_t) * N);
		}

	/**
	 * 指定のスタックが空かどうか確認
	 * @param[in]	i	スタックのインデックス
	 * @return	true: 空, false: 空でない
	 * @note	最悪計算量はO(1)。
	 */
	bool
	empty(size_t i) const
		{
			assert(i < N);

			return !length_[i];
		}

	/**
	 * 指定のスタックからデータを取得 (削除はしない)
	 * @param[in]	i	スタックのインデックス
	 * @return	取得した要素
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	seek(size_t i) const
		{
			assert(i < N);
			assert(0 < length_[i]);

			const size_t j = length_[i] * N + i - 1;

			return stack_[j];
		}

	/**
	 * 指定のスタックに要素を追加
	 * @param[in]	i	スタックのインデックス
	 * @param[in]	data	追加するデータ
	 * @note	ならし解析の計算量はO(1)となる。最悪計算量はO(n)で、nは @a stack_ の長さ。
	 */
	void
	push(size_t i,
		 const TYPE& data)
		{
			assert(i < N);

			const size_t l = stack_.size();
			size_t j = length_[i];

			if (l < (j + 1) * N) {
				stack_.resize(l * 2);
			}

			j *= N;
			j += i;
			stack_[j] = data;
			length_[i]++;
		}

	/**
	 * 指定のスタックから要素を取得・削除
	 * @param[in]	i	スタックのインデックス
	 * @return	取得した要素
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	pop(size_t i)
		{
			assert(i < N);
			assert(0 < length_[i]);

			size_t j = --length_[i];
			j *= N;
			j += i;

			return stack_[j];
		}

	/**
	 * スタックの状態を出力
	 * @param	file	出力先
	 */
	void
	print(FILE* file) const
		{
			for (size_t i(0); i < N; ++i) {
				std::fprintf(file, "[%lu] ", i);
				for (size_t j(0); j < length_[i]; ++j) {
					size_t k = j * N + i;
					if (0 < j) std::printf(", ");
					std::fprintf(file, "%G", (double)stack_[k]);
				}
				std::fprintf(file, "\n");
			}
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	MultiStack<int, 3>* stack = new MultiStack<int, 3>(1);

	stack->push(1, 5);
	stack->push(1, 6);
	stack->push(0, 2);
	stack->push(1, 8);
	stack->push(2, 1);
	stack->push(2, 1);
	stack->push(1, 10);
	stack->push(1, 12);
	stack->print(stdout);
	std::printf(">>>> %d\n", stack->pop(0));
	stack->print(stdout);

	delete stack;

	return 0;
}
