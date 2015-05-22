/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * @class	2つのスタック (LIFO) でキュー (FIFO) を実現
 * @note	テンプレートの型 @a TYPE はスタックのキーの型。
 */
template<typename TYPE>
class MyDueue
{
private:

	std::vector<TYPE> input_;	///< 入力用スタック
	std::vector<TYPE> output_;	///< 出力用スタック (LIFOを実現)

	/**
	 * スタック間で要素移動
	 * @note	計算量をおさえるため、出力用スタックが空の時にのみ動作。
	 */
	void
	adjust_stacks()
		{
			if (output_.empty()) {
				TYPE data;
				while (!input_.empty()) {
					data = input_.back();
					input_.pop_back();
					output_.push_back(data);
				}
			}
		}

public:

	/**
	 * デストラクタ
	 */
	virtual
	~MyDueue()
		{
			;
		}

	/**
	 * 空かどうか確認
	 * @return	true: 空, false: 空でない
	 * @note	最悪計算量はO(1)。
	 */
	bool
	empty() const
		{
			return input_.empty() && output_.empty();
		}

	/**
	 * 先頭要素を取得
	 * @return	先頭要素
	 * @note	事前にキューが空でないことを確認すること。
	 * @note	最悪計算量はO(n)。ただしnは @a stack_ の長さ。
	 */
	TYPE
	front()
		{
			assert(!input_.empty() || !output_.empty());

			adjust_stacks();

			assert(!output_.empty());

			return output_.back();
		}

	/**
	 * 要素を追加
	 * @param[in]	data	追加するデータ
	 * @note	ならし解析の計算量はO(1)となる。最悪計算量はO(n)で、nは @a stack_ の長さ。
	 */
	void
	enqueue(const TYPE& data)
		{
			input_.push_back(data);
		}

	/**
	 * 要素を削除
	 * @param[out]	data	削除した要素
	 * @note	事前にキューが空でないことを確認すること。
	 * @note	最悪計算量はO(n)。ただしnは @a stack_ の長さ。
	 */
	void
	dequeue(TYPE* data = 0)
		{
			assert(!input_.empty() || !output_.empty());

			adjust_stacks();

			assert(!output_.empty());

			if (data) *data = output_.back();
			output_.pop_back();
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9};
	MyDueue<int>* queue = new MyDueue<int>();

	for (size_t i(0); i < sizeof(data)/sizeof(data[0]); ++i) {
		queue->enqueue(data[i]);
	}

	std::printf("***FRONT***\n");
	std::printf("%d\n", queue->front());

	std::printf("***DEQUEUE***\n");
	int j;
	while (!queue->empty()) {
		queue->dequeue(&j);
		std::printf("%d\n", j);
	}

	delete queue;

	return 0;
}
