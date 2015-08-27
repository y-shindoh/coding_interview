/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  1つの配列を使って3つのスタックを実装するにはどのようにすればよいのか
  述べてください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * 1つの配列で複数のスタックを実現したスタック
 * @note	実装方法は複数あるが、
			今回は全てのスタックが同等の要素数を扱う前提の実装を考えた。
 * @note	実装を簡単にするため std::vector を用いた。このため冗長さがある。
 */
template<typename TYPE, size_t N>
class MultiStack
{
private:

	std::vector<TYPE> stack_;	///< データ (問題の「1つの配列」に該当)
	size_t length_[N];			///< 各スタックの要素数

public:

	/**
	 * コンストラクタ
	 * @param[in]	capability	配列の長さの初期値
	 */
	MultiStack(size_t capability = 32 * N)
		{
			assert(0 < capability);

			stack_.resize(capability);
			std::memset((void*)length_, 0, sizeof(size_t) * N);
		}

	/**
	 * 指定したスタックの要素数を取得
	 * @param[in]	index	スタックのインデックス
	 * @return	スタックの要素数
	 * @note	計算量は O(1)。
	 */
	size_t
	size(size_t index) const
		{
			assert(index < N);

			return length_[index];
		}

	/**
	 * 指定したスタックの先頭要素を参照
	 * @param[in]	index	スタックのインデックス
	 * @return	スタックの先頭要素
	 * @note	計算量は O(1)。
	 */
	TYPE
	top(size_t index) const
		{
			assert(index < N);

			size_t i = (length_[index] - 1) * N + index;
			return stack_[i];
		}

	/**
	 * 指定したスタックに要素を追加
	 * @param[in]	index	スタックのインデックス
	 * @param[in]	data	追加する要素
	 * @note	ならし計算量は O(1)。
	 */
	void
	push(size_t index,
		 const TYPE& data)
		{
			assert(index < N);

			size_t l = (length_[index] + 1) * N;
			if (stack_.size() < l) stack_.resize(l * 2);

			size_t i = length_[index] * N + index;
			stack_[i] = data;
			length_[index]++;
		}

	/**
	 * 指定したスタックから要素を削除
	 * @param[in]	index	指定したスタック
	 * @return	削除した要素
	 * @note	計算量は O(1)。
	 */
	TYPE
	pop(size_t index)
		{
			assert(index < N);
			assert(0 < length_[index]);

			length_[index]--;
			size_t i = length_[index] * N + index;

			return stack_[i];
		}

	/**
	 * 全てのスタックの状態を出力
	 * @param[in,out]	file	出力先
	 */
	void
	print(FILE* file) const
		{
			assert(file);

			size_t k;

			for (size_t i(0); i < N; ++i) {
				std::fprintf(file, "[%lu] ", i);
				for (size_t j(0); j < length_[i]; ++j) {
					if (0 < j) std::fprintf(file, ", ");
					k = j * N + i;
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
	MultiStack<int, 3>* stack = new MultiStack<int, 3>;

	stack->push(1, 5);
	stack->push(1, 6);
	stack->push(0, 2);
	stack->push(1, 8);
	stack->push(2, 1);
	stack->push(2, 1);
	stack->push(1, 10);
	stack->push(1, 12);
	stack->print(stdout);
	if (0 < stack->size(1)) {
		std::printf(">>>> %d\n", stack->top(1));
		std::printf(">>>> %d\n", stack->pop(1));
	}
	stack->print(stdout);

	delete stack;

	return 0;
}
