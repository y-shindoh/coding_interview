/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  単方向連結リストにおいて、中央の要素のみアクセス可能であるとします。
  その要素を削除するアルゴリズムを実装してください。
 */

#include <cstddef>
#include <cassert>
#include "list.hpp"

/**
 * 末尾以外のノードをリストから削除
 * @param[in,out]	node	削除対象のノード
 * @note	実際に削除されるのは、引数 @a node の次のノード。
 * @note	計算量は O(1)。
 */
template<typename TYPE>
void
DeleteNotTailNode(Node<TYPE>* node)
{
	assert(node);
	assert(node->get_next());

	Node<TYPE>* next = node->get_next();

	node->set_next(next->get_next());
	node->set_data(next->get_data());

	delete next;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};

	Node<int>* list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);

	Node<int>* node(list);
	for (size_t i(0); i < 5; ++i) {
		node = node->get_next();
	}
	DeleteNotTailNode<int>(node);
	Node<int>::PrintLinkedList(list);

	Node<int>::DeleteLinkedList(list);

	return 0;
}
