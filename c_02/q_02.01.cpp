/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ソートされていない連結リストから、重複する要素を削除するコードを書いてください。

  発展問題:
  もし、一時的なバッファが使用できないとすれば、どうやってこの問題を解きますか?
 */

#include <cstddef>
#include <cstdio>
#include <set>
#include "list.hpp"

/**
 * 単方向リストから重複する要素を削除 (作業領域を使用)
 * @param[in,out]	node	単方向リストの先頭ノード
 * @param[out]	buffer	作業領域
 * @note	最悪計算量は O(n log n)。ただし n は引数 @a node のノード数。
 */
template<typename TYPE>
void
DeleteDuplicatedNode(Node<TYPE>* node,
					 std::set<TYPE>& buffer)
{
	Node<TYPE>* previous(0);
	Node<TYPE>* next;
	TYPE data;

	buffer.clear();

	while (node) {
		next = node->get_next();
		data = node->get_data();
		if (buffer.find(data) == buffer.end()) {
			buffer.insert(data);
			previous = node;
		}
		else {
			if (previous) previous->set_next(next);
			delete node;
		}
		node = next;
	}
}

/**
 * 単方向リストから重複する要素を削除 (作業領域を使わない)
 * @param[in,out]	node	単方向リストの先頭ノード
 * @note	最悪計算量は O(n^2)。ただし n は引数 @a node の要素数。
 */
template<typename TYPE>
void
DeleteDuplicatedNode(Node<TYPE>* node)
{
	TYPE data;
	Node<TYPE>* p;	// 処理対象直前に残っているノード
	Node<TYPE>* c;	// 処理対象のノード
	Node<TYPE>* n;	// 次の処理対象のノード

	while (node) {
		data = node->get_data();
		p = node;
		c = node->get_next();
		while (c) {
			n = c->get_next();
			if (data == c->get_data()) {
				p->set_next(n);
				delete c;
			}
			else {
				p = c;
			}
			c = n;
		}
		node = node->get_next();
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	std::set<int> buffer;

	Node<int>* list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);
	DeleteDuplicatedNode<int>(list, buffer);
	std::printf("=> ");
	Node<int>::PrintLinkedList(list);
	Node<int>::DeleteLinkedList(list);

	list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);
	DeleteDuplicatedNode<int>(list);
	std::printf("=> ");
	Node<int>::PrintLinkedList(list);
	Node<int>::DeleteLinkedList(list);

	return 0;
}
