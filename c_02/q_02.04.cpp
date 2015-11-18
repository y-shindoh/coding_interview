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
	Node<TYPE>* sh(0);		// 指定値より小さな値のノードの先頭
	Node<TYPE>* st(0);		// 指定値より小さな値のノードの末尾
	Node<TYPE>* bh(0);		// 指定値以上の値のノードの先頭
	Node<TYPE>* n;

	while (node) {
		n = node->get_next();
		if (node->get_data() < data) {
			node->set_next(sh);
			sh = node;
			if (!st) st = node;
		}
		else {
			node->set_next(bh);
			bh = node;
		}
		node = n;
	}

	if (!st) return bh;

	st->set_next(bh);
	return sh;
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
