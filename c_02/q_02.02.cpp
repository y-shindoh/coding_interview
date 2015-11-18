/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  単方向連結リストにおいて、
  末尾から数えてk番目の要素を見つけるアルゴリズムを実装してください。
 */

#include <cstddef>
#include <cstdio>
#include "list.hpp"

/**
 * 連結リストの末尾からk番目のノードを取得
 * @param[in]	node	連結リストの先頭ノード
 * @param[in]	k	位置
 * @return	末尾からk番目のノード (存在しない場合は @a 0 が返却される)
 * @note	末尾のノードを1番目として数える。
 * @note	計算量は O(n)。ただし n は引数 @a node のノード数。
 */
template<typename TYPE>
const Node<TYPE>*
FindLastNthNode(const Node<TYPE>* node,
				size_t n)
{
	const Node<TYPE>* right(node);
	const Node<TYPE>* left(node);

	for (size_t i(0); i < n; ++i) {
		if (!right) return 0;
		right = right->get_next();
	}

	while (right) {
		right = right->get_next();
		left = left->get_next();
	}

	return left;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	size_t k(5);
//	size_t k(32);

	Node<int>* list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);

	const Node<int>* node = FindLastNthNode<int>(list, k);
	if (node) {
		std::printf("=> %d (%lu)\n", node->get_data(), k);
	}
	else {
		std::printf("=> not found (%lu)\n", k);
	}

	Node<int>::DeleteLinkedList(list);

	return 0;
}
