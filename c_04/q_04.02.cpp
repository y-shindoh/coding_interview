/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <set>
#include <vector>
#include "binary_search_tree.hpp"

/**
 * 比較関数
 */
bool
search(std::vector< std::set<size_t> >& table,
	   size_t start,
	   size_t goal,
	   std::set<size_t>& used)
{
	if (start == goal) return true;

	bool flag;
	std::set<size_t>::const_iterator it;

	for (it = table[start].begin(); it != table[start].end(); ++it) {
		if (used.find(*it) != used.end()) continue;
		used.insert(*it);
		flag = search(table, *it, goal, used);
		used.erase(*it);
		if (flag) return true;
	}

	return false;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::vector< std::set<size_t> > table;
	std::set<size_t> used;

	table.resize(5);
	table[0].insert(2);
	table[2].insert(1);
	table[1].insert(4);

	if (search(table, 0, 5, used)) {
		std::printf("OK\n");
	}
	else {
		std::printf("NG\n");
	}

	table[4].insert(5);

	if (search(table, 0, 5, used)) {
		std::printf("OK\n");
	}
	else {
		std::printf("NG\n");
	}

	return 0;
}
