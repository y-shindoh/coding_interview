/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.04.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.4の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  二分探索木が与えられたとき、
  同じ深さのノード同士の連結リストを作るアルゴリズムを設計してください
  (たとえば、深さDの木があるとき、D個の連結リストを作ることになります)。
 */

#include <cstddef>
#include <cstdio>
#include <vector>
#include <list>
#include "binary_search_tree.hpp"

/**
 * 動作確認用コマンド
 */
int main()
{
	const int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
	Node<int>* node(0);
	std::vector< std::list<const Node<int>*> > nodes[2];

	// 下記 Node<TYPE>::get_nodes_*<f> が回答

	node = Node<int>::Build(data, sizeof(data)/sizeof(data[0]));
	node->print(stdout);
	node->get_nodes_dfs(nodes[0]);	// 深さ優先探索
	node->get_nodes_bfs(nodes[1]);	// 幅優先探索

	size_t l;
	std::list<const Node<int>*>::const_iterator it;

	for (size_t i(0); i < 2; ++i) {
		l = nodes[i].size();
		for (size_t j(0); j < l; ++j) {
			std::printf("[%lu:%lu] ", i, j);
			for (it = nodes[i][j].begin(); it != nodes[i][j].end(); ++it) {
				if (it != nodes[i][j].begin()) std::printf(", ");
				std::printf("%d", (*it)->get_data());
			}
			std::printf("\n");
		}
	}

	delete node;

	return 0;
}
