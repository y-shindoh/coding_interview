/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  二分探索木において、
  与えられたノードのin-orderで「次」のノードを探すアルゴリズムを書いてください。
  各ノードは、その親ノードへのリンクを持っていると仮定してかまいません。
 */

#include <cstddef>
#include <cstdio>
#define	_USE_TRACE_BACK_TREE_	1
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	const Node<int>* head;
	const Node<int>* node;

	head = Node<int>::Build(data, sizeof(data) / sizeof(data[0]));
	std::printf("**tree**\n");
	head->print(stdout);

	node = head->get_min();

	std::printf("**in-order tracing**\n");
	while (node) {
		std::printf("%d\n", node->get_data());
		node = node->get_next();	// 問題の回答
	}

	delete head;

	return 0;
}
