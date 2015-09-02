/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.09.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.9の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  各ノードにある値を持った二分木が与えられたとき、
  合計値が与えられた値になるすべての経路を出力するアルゴリズムを設計してください。
  経路の始まりと終わりは、二分木のどのノードであってもかまいませんが、
  片方のノードがもう片方のノードの祖先になっているもののみを考えることとします。
 */

#include <cstddef>
#include <cstdio>
#include <vector>
#include <utility>
#define	_USE_TRACE_BACK_TREE_	1
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7};
	const Node<int>* head;

	head = Node<int>::Build(data, sizeof(data) / sizeof(data[0]));
	head->print(stdout);

	// 下記 Node<TYPE>::get_sequence<f> が回答

	std::vector< std::pair<const Node<int>*, const Node<int>*> > results;
	const Node<int>* node;
	size_t l;
	const int value(14);

	head->get_sequence(results, value);
	l = results.size();

	for (size_t i(0); i < l; ++i) {
		node = 0;
		std::printf("%d = ", value);
		do {
			if (!node) {
				node = results[i].second;
			}
			else {
				std::printf(" -> ");
				node = node->get_parent();
			}
			std::printf("%d", node->get_data());
		} while (node != results[i].first);
		std::printf("\n");
	}

	delete head;

	return 0;
}
