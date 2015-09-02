/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.01.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.1の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  二分木が平衡かどうかを調べる関数を実装してください。
  平衡木とは、どのノードの2つの部分木も、
  その高さの差が1以下であるような木と定義します。
 */

#include <cstddef>
#include <cstdio>
#include "binary_search_tree.hpp"

/**
 * 比較関数
 */
int
compare(const int& left,
		const int& right)
{
	if (left < right) {
		return -1;
	}
	else if (left > right) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	Node<int>* node(0);

	// 下記 Node<TYPE>::is_balanced<f> が回答

	node = Node<int>::Build(data, sizeof(data)/sizeof(data[0]));
	node->print(stdout);
	std::printf("=> %s\n", node->is_balanced() ? "balanced" : "unbalanced");
	node->add(7);
	node->print(stdout);
	std::printf("=> %s\n", node->is_balanced() ? "balanced" : "unbalanced");
	node->add(-1);
	node->print(stdout);
	std::printf("=> %s\n", node->is_balanced() ? "balanced" : "unbalanced");

	delete node;

	return 0;
}
