/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	binary_search_tree.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の4章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#ifndef	_BINARY_SEARCH_TREE_HPP_
#define	_BINARY_SEARCH_TREE_HPP_	"binary_search_tree.hpp"

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>
#include <list>
#include <deque>

//#define	_USE_TRACE_BACK_TREE_	"use trace back tree."

/**
 * 二分探索木のノード
 */
template<typename TYPE>
class Node
{
private:

	Node<TYPE>* children_[2];	///< 子ノード
#ifdef	_USE_TRACE_BACK_TREE_
	Node<TYPE>* parent_;		///< 親ノード
#endif	// _USE_TRACE_BACK_TREE_
	TYPE data_;					///< 保持するデータ

	/**
	 * 木の深さの高低差が1以下か確認 (補助メソッド)
	 * @param[in]	depth	ノードの深さ
	 * @param[in,out]	shortest	最も浅い葉の深さ
	 * @param[in,out]	longest	最も深い葉の深さ
	 * @return	true: 1以下, false: 2以上
	 * @note	最悪計算量は O(n)。ただし n は部分木のノードの総数。
	 * @note	深さ優先探索で実装している。
	 */
	bool
	is_balanced(size_t depth,
				size_t& shortest,
				size_t& longest) const
		{
			bool flag;

			for (size_t i(0); i < 2; ++i) {
				if (children_[i]) {
					flag = children_[i]->is_balanced(depth+1, shortest, longest);
					if (!flag) return false;
				}
				else {
					if (depth < shortest) shortest = depth;
					if (longest < depth) longest = depth;
					if (shortest + 1 < longest) return false;
				}
			}

			return true;
		}

	/**
	 * 全ての子孫ノードの値が同一か確認
	 * @param[in]	node	比較対象のノード
	 * @return	true: 同一, false: 同一でない
	 * @note	最悪計算量は O(n)。
				ただし n は、部分木のノードの総数と引数 @a node のノードの総数のうち、小さい方。
	 * @note	平均メモリ使用量は O(log n)。
				ただし n は、部分木のノードの総数と引数 @a node のノードの総数のうち、小さい方。
	 */
	bool
	have_subtree_routine(const Node<TYPE>* node) const
		{
			assert(node);

			if (this->data_ != node->data_) return false;

			bool flag;

			for (size_t i(0); i < 2; ++i) {
				if (!this->children_[i] != !node->children_[i]) return false;
				if (!this->children_[i]) continue;
				flag = this->children_[i]->have_subtree_routine(node->children_[i]);
				if (!flag) return false;
			}

			return true;
		}

public:

#ifdef	_USE_TRACE_BACK_TREE_

	/**
	 * コンストラクタ
	 * @param[in]	data	保持させるデータ
	 */
	Node(const TYPE& data)
		: parent_(0), data_(data)
		{
			children_[0] = children_[1] = 0;
		}

#else	// _USE_TRACE_BACK_TREE_

	/**
	 * コンストラクタ
	 * @param[in]	data	保持させるデータ
	 */
	Node(const TYPE& data)
		: data_(data)
		{
			children_[0] = children_[1] = 0;
		}

#endif	// _USE_TRACE_BACK_TREE_

	/**
	 * デストラクタ
	 * @note	計算量は O(n)。ただし n は部分木のノードの総数。
	 */
	virtual
	~Node()
		{
			for (size_t i (0); i < 2; ++i) {
				if (!children_[i]) continue;
				delete children_[i];
			}
		}

	/**
	 * データを取得
	 * @return	データ
	 * @note	計算量は O(1)。
	 */
	TYPE
	get_data() const
		{
			return data_;
		}

	/**
	 * データを設定
	 * @param[in]	data	データ
	 * @note	計算量は O(1)。
	 */
	void
	set_data(const TYPE& data)
		{
			data_ = data;
		}

#ifdef	_USE_TRACE_BACK_TREE_

	/**
	 * 親ノードを取得
	 * @return	親ノード
	 */
	const Node<TYPE>*
	get_parent() const
		{
			return parent_;
		}

#endif	// _USE_TRACE_BACK_TREE_

	/**
	 * データを追加
	 * @param[in]	data	追加するデータ
	 * @note	平均計算量は O(log n)。ただし n は部分木のノードの総数。
	 */
	void
	add(const TYPE& data)
		{
			Node<TYPE>* node(this);
			size_t i;

			while ('-') {
				i = (data <= node->data_) ? 0 : 1;

				if (node->children_[i]) {
					node = node->children_[i];
					continue;
				}

				node->children_[i] = new Node<TYPE>(data);
#ifdef	_USE_TRACE_BACK_TREE_
				node->children_[i]->parent_ = node;
#endif	// _USE_TRACE_BACK_TREE_
				return;
			}
		}

	/**
	 * 木の中のデータを探索
	 * @param[in]	data	探索対象のデータ
	 * @return	データを保持するノード (探索失敗時は 0 が返る)
	 * @note	平均計算量は O(log n)。ただし n は木のノード数。
	 */
	Node<TYPE>*
	search(const TYPE& data)
		{
			Node<TYPE>* node(this);
			size_t i;

			while (node) {
				if (node->data_ == data) break;
				i = (data <= node->data_) ? 0 : 1;
				node = node->children_[i];
			}

			return node;
		}

	/**
	 * 木の中のデータを探索
	 * @param[in]	data	探索対象のデータ
	 * @return	データを保持するノード (探索失敗時は 0 が返る)
	 * @note	平均計算量は O(log n)。ただし n は木のノード数。
	 */
	const Node<TYPE>*
	search(const TYPE& data) const
		{
			const Node<TYPE>* node(this);
			size_t i;

			while (node) {
				if (node->data_ == data) break;
				i = (data <= node->data_) ? 0 : 1;
				node = node->children_[i];
			}

			return node;
		}

	/**
	 * 最小の値を持つノードを探索
	 * @return	最小の値を持つノード
	 * @note	平均計算量は O(log n)。ただし n は木のノードの総数。
	 */
	const Node<TYPE>*
	get_min() const
		{
			const Node<TYPE>* node(this);

			while (node->children_[0]) node = node->children_[0];

			return node;
		}

#ifdef	_USE_TRACE_BACK_TREE_

	/**
	 * 次のノードを探索 (問題4.6の解答)
	 * @return	次のノード (探索失敗時は 0 が返る)
	 * @note	平均計算量は O(log n)。ただし n は木のノードの総数。
	 */
	const Node<TYPE>*
	get_next() const
		{
			if (children_[1]) {
				return children_[1]->get_min();
			}
			else {
				const Node<TYPE>* node(this);
				while (node->parent_) {
					if (node == node->parent_->children_[0]) return node->parent_;
					node = node->parent_;
				}
			}

			return 0;
		}

#endif	// _USE_TRACE_BACK_TREE_

	/**
	 * 木の深さの高低差が1以下か確認 (問題4.1の解答)
	 * @return	true: 1以下, false: 2以上
	 * @note	最悪計算量は O(n)。ただし n は木のノードの総数。
	 */
	bool
	is_balanced() const
		{
			size_t s = ~((size_t)0);
			size_t l(0);
			return is_balanced(0, s, l);
		}

	/**
	 * 連結リストに同じ深さのノードを格納 (問題4.4の解答)
	 * @param[out]	nodes	格納先
	 * @param[in]	depth	処理中の深さ
	 * @note	計算量は O(n)。ただし n は木のノードの総数。
	 * @note	深さ優先探索で実装している。
				実装はシンプルだが、スタックの分だけメモリを食う。
	 */
	void
	get_nodes_dfs(std::vector< std::list<const Node<TYPE>*> >& nodes,
				  size_t depth = 0) const
		{
			if (!children_[0] || !children_[1]) {
				if (nodes.size() <= depth) nodes.resize(depth+1);
			}

			for (size_t i(0); i < 2; ++i) {
				if (!children_[i]) continue;
				children_[i]->get_nodes_dfs(nodes, depth + 1);
			}

			nodes[depth].push_back(this);	// post-order
		}


	/**
	 * 連結リストに同じ深さのノードを格納 (問題4.4の解答)
	 * @param[out]	nodes	格納先
	 * @note	計算量は O(n)。ただし n は木のノードの総数。
	 * @note	幅優先探索で実装している。
				実装は少し複雑だが、メモリ利用効率が良い。
	 */
	void
	get_nodes_bfs(std::vector< std::list<const Node<TYPE>*> >& nodes) const
		{
			std::list<const Node<TYPE>*> queue;
			typename std::list<const Node<TYPE>*>::const_iterator it;

			queue.push_back(this);

			while (!queue.empty()) {
				nodes.push_back(queue);
				queue.clear();
				for (it = nodes.back().begin(); it != nodes.back().end(); ++it) {
					for (size_t i(0); i < 2; ++i) {
						if (!(*it)->children_[i]) continue;
						queue.push_back((*it)->children_[i]);
					}
				}
			}
		}

	/**
	 * 二部探索木の条件を満たしているか確認 (問題4.5の解答)
	 * @param[in]	min	木のデータの下限
	 * @param[in]	max	木のデータの上限
	 * @return	true: 満たしている, false: 満たしていない
	 * @note	各ノードが min < data_ <= max を満たしているとき、true が返る。
	 * @note	最初の呼び出し時には型の最小値・最大値を引数に設定すること。
	 * @note	本メソッドを利用する場合、格納データに型の最小値は使えない。
	 * @note	最悪計算量は O(n)。ただし n は木のノードの総数。
	 * @note	平均メモリ使用量は O(log n)。ただし n は木のノードの総数。
	 */
	bool
	check_condition(TYPE min,
					TYPE max) const
		{
			if (data_ <= min) return false;
			if (max < data_) return false;

			if (children_[0]) {
				if (!children_[0]->check_condition(min, data_)) return false;
			}

			if (children_[1]) {
				if (!children_[1]->check_condition(data_, max)) return false;
			}

			return true;
		}

	/**
	 * 木を部分木として持っているか否かを確認 (問題4.8の解答)
	 * @param[in]	node	木の根ノード
	 * @return	部分木の根ノード (持っていない場合は 0 が返る)
	 * @note	最悪計算量は O(mn)。ただし m は木のノードの総数、n は引数 @a node のノードの総数。
	 * @note	平均メモリ使用量は O(log n)。
				ただし n は、部分木のノードの総数と引数 @a node のノードの総数のうち、小さい方。
	 * @note	補助メソッドを除いて、本メソッドそのものは幅優先探索で実装している。
	 */
	const Node<TYPE>*
	have_subtree(const Node<TYPE>* node) const
		{
			assert(node);

			const TYPE data = node->data_;
			const Node<TYPE>* subhead = search(data);

			if (subhead) {
				std::deque<const Node<TYPE>*> buffer;
				buffer.push_back(subhead);

				while (!buffer.empty()) {
					subhead = buffer.front();
					buffer.pop_front();

					if (subhead->have_subtree_routine(node)) return subhead;

					for (size_t i(0); i < 2; ++i) {
						if (!subhead->children_[i]) continue;
						buffer.push_back(subhead->children_[i]);
					}
				}
			}

			return 0;
		}

#ifdef	_USE_TRACE_BACK_TREE_

	/**
	 * 値の合計が指定値になる親〜子孫のシーケンス群を取得
	 * @param[out]	results	シーケンス群 (各要素は始端と終端のノードの組)
	 * @param[in]	value	合計値
	 * @note	計算量は O(n log n)。ただし n は木のノードの総数。
	 */
	void
	get_sequence(std::vector< std::pair<const Node<TYPE>*, const Node<TYPE>*> >& results,
				 const TYPE& value) const
		{
			const Node<TYPE>* base = get_min();
			const Node<TYPE>* node;
			TYPE sum;

			while (base) {
				sum = (TYPE)0;
				node = base;
				while (node) {
					sum += node->data_;
					if (sum == value) results.push_back(std::pair<const Node<TYPE>*, const Node<TYPE>*>(node, base));
					node = node->parent_;
				}
				base = base->get_next();
			}
		}

#endif	// _USE_TRACE_BACK_TREE_

	/**
	 * ツリーを出力
	 * @param[out]	file	出力先
	 * @param[in]	type	各要素に付与する飾り文字
	 * @param[in]	depth	各要素のインデントの深さ
	 */
	void
	print(FILE* file,
		  char type = 'C',
		  size_t depth = 0) const
		{
			if (children_[1]) children_[1]->print(file, 'R', depth+1);
			for (size_t i(0); i < depth; ++i) std::fprintf(file, "  ");
			std::fprintf(file, "%c:%G\n", type, (double)data_);
			if (children_[0]) children_[0]->print(file, 'L', depth+1);
		}

	/**
	 * ソート済み配列から二部探索木を生成 (問題4.3の解答)
	 * @param[in]	array	ソート済み配列
	 * @param[in]	length	引数 @a array の要素数
	 * @return	二部探索木のルート・ノード
	 * @note	引数 @a array に重複がない時、平衡二分探索木を生成する。
	 * @note	書籍の解答例では重複データが考慮されていない。
	 */
	static Node<TYPE>*
	Build(const TYPE* array,
		  size_t length)
		{
			assert(array);

			Node* node(0);

			if (0 < length) {
				size_t i = length / 2;
				// 重複データへの簡易対策
				size_t j(i), k(i);
				while (j + 1 < length && array[i] == array[j+1]) ++j;
				while (1 < k && array[k] == array[i]) --k;
				if (array[k] != array[i] && i - k <= j - i) i = k;
				else i = j;
				// ノード生成
				node = new Node(array[i]);
				node->children_[0] = Node<TYPE>::Build(array, i);
				node->children_[1] = Node<TYPE>::Build(array + i + 1, length - i - 1);
#ifdef	_USE_TRACE_BACK_TREE_
				for (size_t i(0); i < 2; ++i) {
					if (!node->children_[i]) continue;
					node->children_[i]->parent_ = node;
				}
#endif	// _USE_TRACE_BACK_TREE_
			}

			return node;
		}

#ifdef	_USE_TRACE_BACK_TREE_

	/**
	 * 2つのノードを含む最小の部分木を探索 (問題4.7の解答)
	 * @param[in]	left	ノード (その1)
	 * @param[in]	right	ノード (その2)
	 * @return	部分木の根のノード
	 * @note	最悪計算量は O(n)。ただし n は木のノードの総数。
	 * @note	出題の意図を考慮し、二分探索木の大小関係を条件として使っていない。
	 */
	static const Node<TYPE>*
	FindMinimumSubtree(const Node<TYPE>* left,
					   const Node<TYPE>* right)
		{
			assert(left);
			assert(right);

			int i(0);
			int j(0);
			const Node<TYPE>* node;

			node = left;
			while (node->parent_) {
				++i;
				node = node->parent_;
			}

			node = right;
			while (node->parent_) {
				++j;
				node = node->parent_;
			}

			if (i < j) {
				while (i < j--) right = right->parent_;
			}
			else {
				while (j < i--) left = left->parent_;
			}

			while (left != right) {
				left = left->parent_;
				right = right->parent_;
			}

			return left;
		}

#endif	// _USE_TRACE_BACK_TREE_
};

#endif	// _BINARY_SEARCH_TREE_HPP_
