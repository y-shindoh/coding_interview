/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  イヌとネコしか入ることのできない動物保護施設があります。
  この施設は「先入れ先出し」の操作を厳格に行います。
  施設からは一番長い時間入っている動物を外に出すか、
  イヌとネコの好きなほう (で一番長い時間入っているもの) を外に出すことができます。
  どの動物でも好きなように連れ出せるわけではありません。
  このような仕組みを扱うデータ構造を作ってください。
  さらに enqueue, dequeueAny, dequeueDog, dequeueCat の操作を実装してください。
  あらかじめ用意された連結リストのデータ構造は用いてよいものとします。
  (C++ STLでは std::deque が連結リストの性質を持つ)
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <deque>

/**
 * @class	複数のqueueを1つのqueueとして見ことも個別のqueueとして見ることもできる拡張queue
 * @note	本当はIDを再調整する処理が必要だが、ここでは省略する。
 */
template<typename TYPE, size_t N>
class MultiQueue
{
private:

	/**
	 * queue群
	 * @note	各queueの要素はIDと値のペア。
	 */
	std::deque<std::pair<size_t, TYPE> > queues_[N];

	size_t count_;	///< queue内各要素のIDの基準
	size_t length_;	///< queue全体の要素数

	/**
	 * 最も古い要素を持つqueueを見つける
	 * @return	最も古い要素を持つqueueのID
	 * @note	見つからなかった場合は N 以上の整数を返却する。
	 * @note	計算量は O(1)。ただし N を定数と仮定する。
	 */
	size_t
	find_oldest_front() const
		{
			int k(N);
			size_t id, t;

			for (int i(0); i < (int)N; ++i) {
				if (queues_[i].empty()) continue;
				t = queues_[i].back().first;
				if (k < N && id <= t) continue;
				k = i;
				id = t;
			}

			return (size_t)k;
		}

public:

	/**
	 * コンストラクタ
	 */
	MultiQueue()
		: count_(0), length_(0)
		{
			;
		}

	/**
	 * 指定したキューが空か否かを確認
	 * @param[in]	index	キューのインデックス
	 * @return	true: 空, false: 空でない
	 * @note	計算量は O(1)。
	 */
	bool
	empty(size_t index) const
		{
			assert(index < N);

			return queues_[index].empty();
		}

	/**
	 * キュー全体が空か否かを確認
	 * @return true: 空, false: 空でない
	 * @note	計算量は O(1)。
	 */
	bool
	empty() const
		{
			return length_ == 0;
		}

	/**
	 * 指定したキューが持つ要素数を取得
	 * @param[in]	index	キューのインデックス
	 * @return	要素数
	 * @note	計算量は O(1)。
	 */
	size_t
	size(size_t index) const
		{
			assert(index < N);

			return queues_[index].size();
		}

	/**
	 * キュー全体が持つ要素数を取得
	 * @return	要素数
	 * @note	計算量は O(1)。
	 */
	size_t
	size() const
		{
			return length_;
		}

	/**
	 * 指定したキューに要素を追加
	 * @param[in]	index	キューのインデックス
	 * @param[in]	data	追加する要素
	 * @note	計算量は O(1)。
	 */
	void
	enqueue(size_t index,
			const TYPE& data)
		{
			assert(index < N);

			queues_[index].push_back(std::pair<size_t, TYPE>(count_, data));
			++count_;
			++length_;
		}

	/**
	 * 指定したキューの先頭要素を取得
	 * @param[in]	index	キューのインデックス
	 * @return	先頭要素
	 * @note	計算量は O(1)。
	 */
	TYPE
	front(size_t index) const
		{
			assert(index < N);
			assert(!queues_[index].empty());

			return queues_[index].front().second;
		}

	/**
	 * キュー全体の先頭要素を取得
	 * @return	先頭要素
	 * @note	計算量は O(1)。ただし N を定数と仮定する。
	 */
	TYPE
	front() const
		{
			assert(0 < length_);

			size_t i = find_oldest_front();
			assert(i < N);

			return queues_[i].front().second;
		}

	/**
	 * 指定したキューの先頭要素を削除
	 * @param[in]	index	キューのインデックス
	 * @note	キューが空の場合は何もしない。
	 * @note	計算量は O(1)。
	 */
	void
	dequeue(size_t index)
		{
			assert(index < N);

			if (queues_[index].empty()) return;
			queues_[index].pop_front();
			--length_;
		}

	/**
	 * キュー全体の先頭要素を削除
	 * @note	キューが空の場合は何もしない。
	 * @note	計算量は O(1)。ただし N は定数と仮定する。
	 */
	void
	dequeue()
		{
			if (0 == length_) return;

			size_t i = find_oldest_front();
			queues_[i].pop_front();
			--length_;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	char data[] = "ccccddcdcdccdd";
	MultiQueue<char, 2>* queue = new MultiQueue<char, 2>();

	for (size_t i(0); data[i]; ++i) {
		queue->enqueue(data[i] == 'c' ? 0 : 1, data[i]);
	}

	if (!queue->empty(1)) {
		std::printf("[%lu] %c\n", queue->size(1), queue->front(1));
		queue->dequeue(1);
	}

	while (!queue->empty(0)) {
		std::printf("[%lu] %c\n", queue->size(0), queue->front(0));
		queue->dequeue(0);
	}

	while (!queue->empty()) {
		std::printf("[%lu] %c\n", queue->size(), queue->front());
		queue->dequeue();
	}

	delete queue;

	return 0;
}
