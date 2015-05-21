/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <set>
#include <cassert>
#include "list.hpp"

/**
 * リストからループの最初のノードを抽出
 * @param[in]	node	処理対象のリスト
 * @return	ループの最初のノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 * @note	確実に正解を出す回答。本来の回答とは違う。
 */
template<typename TYPE>
const Node<TYPE>*
FindLoop1(const Node<TYPE>* node)
{
	assert(node);

	std::set<const Node<TYPE>*> nodes;

	while (node) {
		if (nodes.find(node) != nodes.end()) return node;
		nodes.insert(node);
		node = node->get_next();
	}

	return 0;
}

/**
 * リストからループの最初のノードを抽出
 * @param[in]	node	処理対象のリスト
 * @return	ループの最初のノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 * @note	ループが見つからない場合は @a 0 が返却される。
 * @note	計算量はO(n)となる。
 * @note	本来の回答はこちら。
 */
template<typename TYPE>
const Node<TYPE>*
FindLoop2(const Node<TYPE>* node)
{
	assert(node);

	const Node<TYPE>* fast(node);
	const Node<TYPE>* slow(node);

	while ('-') {
		fast = fast->get_next();
		if (!fast) return 0;
		fast = fast->get_next();
		if (!fast) return 0;
		slow = slow->get_next();
		if (fast == slow) break;
	}

	slow = node;

	while ('-') {
		if (fast == slow) return fast;
		fast = fast->get_next();
		slow = slow->get_next();
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
	Node<int>* const list = Node<int>::MakeList(data, sizeof(data)/sizeof(data[0]));
	Node<int>* const tail = Node<int>::GetEndNode(list);
	Node<int>* node(list);
	const Node<int>* loop;

	Node<int>::Print(stdout, list);

	for (size_t i(0); i < 4; ++i) {
		node = node->get_next();
	}
	std::printf("CONNECT: %d\n", node->get_key());

	// ループを作る
	tail->set_next(node);

	loop = FindLoop1<int>(list);
	if (loop) {
		std::printf("FOUND: %d\n", loop->get_key());
	}

	loop = FindLoop2<int>(list);
	if (loop) {
		std::printf("FOUND: %d\n", loop->get_key());
	}

	// ループを切る
	tail->set_next(0);

	Node<int>::DeleteList(list);

	return 0;
}
