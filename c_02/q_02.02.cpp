/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * リストの末尾からn番目の要素を取得
 * @param[in]	head	リストの先頭ノード
 * @param[in]	n	指定する位置 (1以上)
 * @return	リストの末尾からn番目の要素
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	取得失敗時は @a 0 が返却される。
 * @note	計算量はO(n)となる。ただしこのnはリストの長さとする。
 */
template<typename TYPE>
const Node<TYPE>*
GetTailNode(const Node<TYPE>* node,
			size_t n = 1)
{
	const Node<TYPE>* follow(node);

	for (size_t i(0); i < n; ++i) {
		if (!node) return 0;
		node = node->get_next();
	}

	while (node) {
		node = node->get_next();
		follow = follow->get_next();
	}

	return follow;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	Node<int>* list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	const Node<int>* node;

	Node<int>::Print(stdout, list);
	for (size_t i(1); i < sizeof(data)/sizeof(data[0]); i += 3) {
		node = GetTailNode<int>(list, i);
		if (node) {
			std::printf("[%lu]\t%d\n", i, node->get_key());
		}
	}

	Node<int>::DeleteList(list);

	return 0;
}
