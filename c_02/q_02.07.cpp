/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_02.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題2.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  連結リストが回文
  (先頭から巡回しても末尾から巡回しても、各ノードの要素がまったく同じになっている)
  かどうかを調べる関数を実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include "list.hpp"

/**
 * 単方向リストが回文か否かを確認
 * @param[in]	node	単方向リスト
 * @return	true: 回文, false: 回文ではない
 * @note	計算量は O(n)。ただし n は引数 @a node のノード数。
 * @note	双方向リストなら、先頭から正順に・末尾から逆順にたどりつつ値を比較すれば良い。
 * @note	他のデータ構造を使った方が効率が良いが、ここでは単方向リストのみ用いた。
 */
template<typename TYPE>
bool
IsPalindrome(const Node<TYPE>* node)
{
	assert(node);

	Node<TYPE>* competitor(0);
	const Node<TYPE>* n(node);
	size_t l(0);

	while (n) {
		competitor = new Node<TYPE>(n->get_data(), competitor);
		n = n->get_next();
		++l;
	}

	bool flag(true);
	n = competitor;
	l /= 2;
	for (size_t i(0); i < l; ++i) {
		if (node->get_data() != n->get_data()) {
			flag = false;
			break;
		}
		else {
			node = node->get_next();
			n = n->get_next();
		}
	}

	Node<TYPE>::DeleteLinkedList(competitor);

	return flag;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[][12] = {{1, 3, 5, 7, 9, 0, 0, 2, 4, 4, 6, 8},
					  {1, 3, 5, 2, 4, 6, 6, 4, 2, 5, 3, 1}};
	Node<int>* list;

	for (size_t i(0); i < sizeof(data) / sizeof(data[0]); ++i) {
		list = Node<int>::MakeLinkedList(data[i], sizeof(data[0]) / sizeof(data[0][0]));
		if (IsPalindrome<int>(list)) {
			std::printf("PALINDROME: ");
		}
		else {
			std::printf("NOT PALINDROME: ");
		}
		Node<int>::PrintLinkedList(list);
		Node<int>::DeleteLinkedList(list);
	}

	return 0;
}
