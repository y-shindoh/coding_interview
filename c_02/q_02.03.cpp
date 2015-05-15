/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * リストの要素を削除
 * @param[in]	node	削除対象の要素 (リストの先頭と末尾を除く)
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	計算量はO(1)となる。
 */
template<typename TYPE>
void
DeleteCenterNode(Node<TYPE>* node)
{
	assert(node);

	Node<TYPE>* next = node->get_next();

	assert(next);

	node->set_key(next->get_key());
	node->set_next(next->get_next());

	delete next;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	Node<int>* list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));

	Node<int>::Print(stdout, list);
	DeleteCenterNode<int>(list->get_next()->get_next());
	Node<int>::Print(stdout, list);

	Node<int>::DeleteList(list);

	return 0;
}
