/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_13.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題13.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  パラメータとしてノード構造体へのポインタを受け取り、
  そのデータ構造体の完全なコピーを返すメソッドを書いてください。
  ただし、そのノード構造体は他のノードへのポインタを2つ持っています。
 */

#include <cstddef>
#include <cstdio>

/**
 * 二分探索木のノード
 * @note	問題のノード構造体に該当。
 */
template<typename TYPE>
class Node
{
private:

	TYPE data_;					///< 格納データ
	Node<TYPE>* children_[2];	///< 子ノード

public:

	/**
	 * コンストラクタ
	 * @param[in]	data	格納するデータ
	 */
	Node(const TYPE& data)
		: data_(data)
		{
			children_[0] = children_[1] = 0;
		}

	/**
	 * デストラクタ
	 * @note	計算量は O(n)。ただし n はノード数。
	 */
	~Node()
		{
			for (size_t i(0); i < 2; ++i) {
				if (!children_[i]) continue;
				delete children_[i];
			}
		}

	/**
	 * 二分探索木にノードを追加
	 * @param[in]	data	追加ノードに格納する値
	 * @note	計算量は O(log n)。ただし n はノード数。
	 */
	void
	add(const TYPE& data)
		{
			Node<TYPE>* node(this);
			size_t i;

			while (node) {
				if (node->data_ >= data) {
					i = 0;
				}
				else {
					i = 1;
				}
				if (!node->children_[i]) break;
				node = node->children_[i];
			}

			node->children_[i] = new Node<TYPE>(data);
		}

	/**
	 * 二分探索木を複製
	 * @return	複製した二分探索木の根ノード
	 * @note	計算量は O(n)。ただし n はノード数。
	 * @note	ループのあるデータ構造の場合、std:set で検出する機構を追加する。
	 */
	Node<TYPE>*
	copy() const
		{
			Node<TYPE>* node = new Node<TYPE>(data_);

			for (size_t i(0); i < 2; ++i) {
				if (!children_[i]) continue;
				node->children_[i] = children_[i]->copy();
			}

			return node;
		}

	/**
	 * 二分探索木を出力
	 * @param[in,out]	file	出力先
	 * @param[in]	prefix	ノード書き出しのプレフィックス
	 * @param[in]	depth	ノード書き出しのインデントの深さ
	 */
	void
	print(FILE* file = stdout,
		  char prefix ='C',
		  size_t depth = 0) const
		{
			if (children_[0]) {
				children_[0]->print(file, 'L', depth + 1);
			}
			for (size_t i(0); i < depth; ++i) std::fprintf(file, "  ");
			std::fprintf(file, "%c:%G\n", prefix, (double)data_);
			if (children_[1]) {
				children_[1]->print(file, 'R', depth + 1);
			}
		}
};

/**
 * 動作確認コマンド
 */
int
main()
{
	Node<int>* tree_o = new Node<int>(5);
	tree_o->add(6);
	tree_o->add(3);
	tree_o->add(4);

	Node<int>* tree_c = tree_o->copy();

	tree_o->add(2);
	tree_c->add(10);

	tree_o->print();
	tree_c->print();

	delete tree_o;
	delete tree_c;

	return 0;
}
