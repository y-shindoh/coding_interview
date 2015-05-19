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

/**
 * 探索処理
 * @param	table	有向グラフのテーブル
 * @param	start	始点
 * @param	goal	終点
 * @param	buffer	探索用作業領域
 * @note	深さ優先探索で実装している。無向グラフならunion-find treeが有利。
 */
bool
search(std::vector< std::set<size_t> >& table,
	   size_t start,
	   size_t goal,
	   std::set<size_t>& buffer)
{
	if (start == goal) return true;

	bool flag;
	std::set<size_t>::const_iterator it;

	for (it = table[start].begin(); it != table[start].end(); ++it) {
		if (buffer.find(*it) != buffer.end()) continue;
		buffer.insert(*it);
		flag = search(table, *it, goal, buffer);
		buffer.erase(*it);
		if (flag) return true;
	}

	return false;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::vector< std::set<size_t> > table;	// 有向グラフのテーブル
	std::set<size_t> buffer;	// 探索用作業領域

	table.resize(6);	// ノード数6 (0〜5)
	table[0].insert(2);	// 0 => 2
	table[2].insert(1);	// 2 => 1
	table[1].insert(4);	// 1 => 4

	if (!search(table, 0, 5, buffer)) {
		std::printf("NG\n");	// 到達不可
	}

	table[4].insert(5);	// 4 => 5

	if (search(table, 0, 5, buffer)) {
		std::printf("OK\n");	// 到達可
	}

	return 0;
}
