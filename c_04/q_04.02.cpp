/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_04.02.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題4.2の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  有向グラフが与えられたとき、
  2つのノード間に経路があるかどうかを見つけるアルゴリズムを設計してください。
 */

#include <cstddef>
#include <cstdio>
#include <vector>
#include <set>
#include <deque>

/**
 * 有向グラフ上の経路を探索 (補助関数)
 * @param[in,out]	table	有向グラフ
 * @param[in]	from	スタート
 * @param[in]	to	ゴール
 * @param[in,out]	buffer	通過済みノード (最初の呼び出しでは空にすること)
 * @return	true: 経路あり, false: 経路なし
 * @note	単純な深さ優先探索で実装している。
 */
bool
search_dfs(const std::vector< std::set<size_t> >& table,
		   size_t from,
		   size_t to,
		   std::set<size_t> buffer)
{
	if (table[from].find(to) != table[from].end()) return true;

	std::set<size_t>::const_iterator i;
	bool flag;

	for (i = table[from].begin(); i != table[from].end(); ++i) {
		if (buffer.find(*i) != buffer.end()) continue;
		buffer.insert(*i);
		flag = search_dfs(table, *i, to, buffer);
		buffer.erase(*i);
		if (flag) return true;
	}

	return false;
}

/**
 * 有向グラフ上の経路を探索
 * @param[in,out]	table	有向グラフ
 * @param[in]	from	スタート
 * @param[in]	to	ゴール
 * @return	true: 経路あり, false: 経路なし
 * @note	単純な深さ優先探索で実装している。
 */
bool
search_dfs(const std::vector< std::set<size_t> >& table,
		   size_t from,
		   size_t to)
{
	std::set<size_t> buffer;
	buffer.insert(from);

	return search_dfs(table, from, to, buffer);
}


/**
 * 有向グラフ上の経路を探索
 * @param[in,out]	table	有向グラフ
 * @param[in]	from	スタート
 * @param[in]	to	ゴール
 * @return	true: 経路あり, false: 経路なし
 * @note	単純な幅優先探索で実装している。
 */
bool
search_bfs(const std::vector< std::set<size_t> >& table,
		   size_t from,
		   size_t to)
{
	std::deque<size_t> buffer;
	std::set<size_t> done;
	std::set<size_t>::const_iterator it;
	size_t i;

	buffer.push_back(from);
	done.insert(from);

	while (!buffer.empty()) {
		i = buffer.front();
		buffer.pop_front();
		if (i == to) return true;
		for (it = table[i].begin(); it != table[i].end(); ++it) {
			if (done.find(*it) != done.end()) continue;
			buffer.push_back(*it);
			done.insert(*it);
		}
	}

	return false;
}

/**
 * 動作確認用コマンド
 */
int main()
{
	std::vector< std::set<size_t> > table;	// 有向グラフのテーブル

	table.resize(6);	// ノード数6 (0〜5)
	table[0].insert(2);	// 0 => 2
	table[2].insert(1);	// 2 => 1
	table[1].insert(4);	// 1 => 4

	if (!search_dfs(table, 0, 5)) {
		std::printf("NG (DFS)\n");	// 到達不可
	}

	if (!search_bfs(table, 0, 5)) {
		std::printf("NG (BFS)\n");	// 到達不可
	}

	table[4].insert(5);	// 4 => 5

	if (search_dfs(table, 0, 5)) {
		std::printf("OK (DFS)\n");	// 到達可
	}

	if (search_bfs(table, 0, 5)) {
		std::printf("OK (BFS)\n");	// 到達可
	}

	return 0;
}
