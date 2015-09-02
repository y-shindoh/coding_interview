/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  二分木において、
  2つのノードの上位ノードで最初に共通するものを探すアルゴリズムを設計し、
  コードを書いてください。
  ただし、データ構造の中に新たにノードを追加してはいけません
  (二分木は二分探索木とは限りません)。
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
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	Node<int>* head(0);

	head = Node<int>::Build(data, sizeof(data) / sizeof(data[0]));
	std::printf("**tree**\n");
	head->print(stdout);

	// 下記の Node<int>::FindMinimumSubtree が問題の回答

	const Node<int>* node_1 = head->search(4);
	const Node<int>* node_2 = head->search(0);
	if (node_1 && node_2) {
		const Node<int>* node = Node<int>::FindMinimumSubtree(node_1, node_2);
		if (node) {
			std::printf(">>>> %d, %d => %d\n",
						node_1->get_data(), node_2->get_data(), node->get_data());
		}
	}

	delete head;

	return 0;
}
