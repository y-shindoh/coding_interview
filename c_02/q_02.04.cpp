/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  ある数xが与えられたとき、連結リストの要素を並び替え、
  xより小さいものが前にくるようにするコードを書いてください。
 */

#include <cstddef>
#include <cstdio>
#include "list.hpp"

/**
 * 単方向リストで指定値未満のノードを前方に移動
 * @param[in,out]	node	単方向リストの先頭ノード
 * @param[in]	data	指定値
 * @return	処理後の単方向リストの先頭ノード
 * @	計算量は O(n)。ただし n は引数 @a node のノード数。
 */
template<typename TYPE>
Node<TYPE>*
Relocate(Node<TYPE>* node,
		 const TYPE& data)
{
	Node<TYPE>* result(0);
	Node<TYPE>* tail(0);
	Node<TYPE>* remain(0);
	Node<TYPE>* previous(0);
	Node<TYPE>* next;

	while (node) {
		next = node->get_next();
		if (data <= node->get_data()) {
			previous = node;
			if (!remain) remain = node;
		}
		else {
			if (previous) {
				previous->set_next(next);
			}
			node->set_next(0);
			if (!result) result = node;
			if (tail) tail->set_next(node);
			tail = node;
		}
		node = next;
	}

	if (result) {
		tail->set_next(remain);
		return result;
	}
	else {
		return remain;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 5, 0, 2, 4, 4, 6, 8, 1};
	int k(5);

	Node<int>* list = Node<int>::MakeLinkedList(data, sizeof(data)/sizeof(data[0]));
	Node<int>::PrintLinkedList(list);

	list = Relocate<int>(list, k);
	std::printf("%d => ", k);
	Node<int>::PrintLinkedList(list);

	Node<int>::DeleteLinkedList(list);

	return 0;
}
