/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.05.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.5の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  MyQueueというクラス名で、2つのスタックを用いてキューを実装してください。
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
	std::vector<TYPE> output_;	///< 出力用スタック (FIFOを実現)

	/**
	 * 要素取り出しの準備
	 * @note	計算量は O(n)。ただし n は入力用スタックの持つ要素数。
	 */
	void
	prepare()
		{
			assert(output_.empty());

			TYPE data;

			while (!input_.empty()) {
				data = input_.back();
				input_.pop_back();
				output_.push_back(data);
			}
		}

public:

	/**
	 * 空か否かを確認
	 * @return	true: 要素がない, false: 要素がある
	 * @note	計算量は O(1)。
	 */
	bool
	empty() const
		{
			return input_.empty() && output_.empty();
		}

	/**
	 * 先頭要素を取得
	 * @return	先頭要素
	 * @note	最悪計算量は O(n)。ただし n は入力用スタックの持つ要素数。
	 */
	TYPE
	front()
		{
			assert(!input_.empty() || !output_.empty());

			if (output_.empty()) prepare();

			return output_.back();
		}

	/**
	 * 要素を末尾に追加
	 * @param[in]	data	追加する要素
	 * @note	最悪計算量は O(n)。ただし n は入力用スタックの持つ要素数。
	 */
	void
	enqueue(const TYPE& data)
		{
			input_.push_back(data);
		}

	/**
	 * 要素を先頭から削除
	 * @return	先頭要素
	 * @note	最悪計算量は O(n)。ただし n は入力用スタックの持つ要素数。
	 */
	TYPE
	dequeue()
		{
			assert(!input_.empty() || !output_.empty());

			if (output_.empty()) prepare();

			TYPE data = output_.back();
			output_.pop_back();

			return data;
		}

};

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9};
	MyDueue<int>* queue = new MyDueue<int>;

	for (size_t i(0); i < sizeof(data)/sizeof(data[0]); ++i) {
		queue->enqueue(data[i]);
	}

	std::printf("***FRONT***\n");
	std::printf("%d\n", queue->front());

	std::printf("***DEQUEUE***\n");
	int j;
	while (!queue->empty()) {
		j = queue->dequeue();
		std::printf("%d\n", j);
	}

	delete queue;

	return 0;
}
