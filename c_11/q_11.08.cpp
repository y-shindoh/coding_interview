/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_11.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題11.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  整数の列を読み取っているのを想像してみてください。
  定期的にある値xの順位 (x以下の値の数) を調べられるようにしておきたいです。
  この作業を扱うデータ構造とアルゴリズムを実装してください。
  つまり、値が生成されたときに呼ばれる track(int x) というメソッドと、
  x 以下の値の個数 (x 自身は個数に含まない) を返す
  getRankOfNumber(int x) というメソッドを実装してください。
 */

#include <cstddef>
#include <cstdio>
#include "utility.hpp"

/**
 * 二分探索木のノード
 */
template<typename TYPE>
class Node
{
private:

	TYPE data_;		///< 格納する値
	size_t count_;	///< 格納した値より小さな値の総数
	Node<TYPE>* children_[2];	///< 子ノード

public:

	/**
	 * コンストラクタ
	 * @param[in]	data	格納する値
	 */
	Node(const TYPE& data)
		: data_(data), count_(0)
		{
			children_[0] = children_[1] = 0;
		}

	/**
	 * デストラクタ
	 */
	~Node()
		{
			for (size_t i(0); i < 2; ++i) {
				if (children_[i]) delete children_[i];
			}
		}

	/**
	 * 二分探索木に値を追加
	 * @param[in]	data	追加する値
	 * @note	平均計算量は O(log n)。ただし n はノード数。
	 * @note	本メソッドは問題の track(int x) に該当する。
	 */
	void
	add(const TYPE& data)
		{
			Node<TYPE>* node(this);
			size_t i;

			while ('-') {
				i = data <= node->data_ ? 0 : 1;
				if (0 == i) node->count_++;
				if (!node->children_[i]) break;
				node = node->children_[i];
			}

			node->children_[i] = new Node<TYPE>(data);
		}

	/**
	 * 指定値以下の値を格納している個数の算出
	 * @param[in]	data	指定値
	 * @return	該当個数 (ただし指定値そのものは除く)
	 * @note	平均計算量は O(log n)。ただし n はノード数。
	 * @note	本メソッドは問題の getRankOfNumber(int x) に該当する。
	 */
	size_t
	count(const TYPE& data) const
		{
			const Node<TYPE>* node(this);
			size_t i;
			size_t c(0);

			while ('-') {
				i = data <= node->data_ ? 0 : 1;
				if (i == 1) {
					c += node->count_ + 1;
				}
				else if (data == node->data_) {
					c += node->count_;
					break;
				}
				if (!node->children_[i]) break;
				node = node->children_[i];
			}

			return c;
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {5, 1, 4, 4, 5, 9, 7, 13, 3};
	Node<int>* btree(0);

	for (size_t i(0); i < sizeof(data) / sizeof(data[0]); ++i) {
		if (!btree) {
			btree = new Node<int>(data[i]);
		}
		else {
			btree->add(data[i]);
		}
	}

	int k;
	size_t c;

	k = 1;
	c = btree->count(k);
	std::printf("%d => %lu\n", k, c);

	k = 3;
	c = btree->count(k);
	std::printf("%d => %lu\n", k, c);

	k = 4;
	c = btree->count(k);
	std::printf("%d => %lu\n", k, c);

	if (btree) delete btree;

	return 0;
}
