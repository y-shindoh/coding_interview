/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  循環する連結リストが与えられたとき、
  循環する部分の最初のノードを返すアルゴリズムを実装してください。

  循環を含む連結リストの定義:
  連結リストAではループを作るために、
  リスト内のノードの次へのポインタが以前に出現したノードを指している。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * 循環する連結リストの連結箇所であるノードを探索
 * @param[in]	node	連結リストの先頭のノード
 * @return	連結箇所であるノード
 * @note	計算量は O(n)。ただし n は引数 @a node のノード数。
 */
template<typename TYPE>
const Node<TYPE>*
FindConnect(const Node<TYPE>* node)
{
	assert(node);

	const Node<TYPE>* fast(node);
	const Node<TYPE>* slow(node);

	do {
		fast = fast->get_next();
		assert(fast);	// ERROR: found the tail
		fast = fast->get_next();
		assert(fast);	// ERROR: found the tail
		slow = slow->get_next();
	} while (fast != slow);

	fast = node;

	while (fast != slow) {
		fast = fast->get_next();
		slow = slow->get_next();
	}

	return fast;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};

	Node<int>* list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);

	Node<int>* connect(list);
	for (size_t i(0); i < 7; ++i) {
		connect = connect->get_next();
	}
	Node<int>* end(connect);
	while (end->get_next()) {
		end = end->get_next();
	}
	end->set_next(connect);
	const Node<int>* node = FindConnect<int>(list);

	if (node == connect) {
		std::printf("SUCCEED: %d\n", node->get_data());
	}
	else {
		std::printf("FAILED: %d, %d\n", connect->get_data(), node->get_data());
	}

	end->set_next(0);
	Node<int>::DeleteLinkedList(list);

	return 0;
}
