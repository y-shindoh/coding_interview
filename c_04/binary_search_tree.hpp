/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	binary_search_tree.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の4章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#ifndef	__BINARY_SEARCH_TREE_HPP__
#define	__BINARY_SEARCH_TREE_HPP__	"binary_search_tree.hpp"

//#define	__BINARY_SEARCH_TREE_GET_RAW_DATA__	"ノードに直接アクセス可能にする。"
//#define	__BINARY_SEARCH_TREE_ENABLE_PARENT__	"ノードの親ポインタを有効にする。"

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 二分探索木のノード
 * @note	テンプレートの型 @a TYPE は木が保持する型。
 */
template<typename TYPE>
class BinarySearchNode
{
private:

#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
	BinarySearchNode<TYPE>* parent_;		///< 親ノード (ルートは @a 0)
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
	BinarySearchNode<TYPE>* children_[2];	///< 子ノード (葉ノードは @a 0 )
	TYPE key_;								///< キー

public:

	/**
	 * コンストラクタ
	 * @param[in]	key	ノードが保持するキー
	 */
	BinarySearchNode(const TYPE& key)
#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
		: parent_(0), key_(key)
#else	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
		: key_(key)
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
		{
			children_[0] = 0;
			children_[1] = 0;
		}

	/**
	 * デストラクタ
	 */
	~BinarySearchNode()
		{
			if (children_[0]) delete children_[0];
			if (children_[1]) delete children_[1];
		}

#ifdef	__BINARY_SEARCH_TREE_GET_RAW_DATA__
	/**
	 * ノードにキーを直接設定
	 * @param[in]	key	設定するキー
	 */
	void
	set_key(const TYPE& key)
		{
			key_ = key;
		}

	/**
	 * ノードのキーを直接取得
	 * @return	ノードのキー
	 */
	TYPE
	get_key() const
		{
			return key_;
		}
#endif	// __BINARY_SEARCH_TREE_GET_RAW_DATA__

	/**
	 * メソッド @a BinarySearchTree::prepare の本体
	 * @param[in]	input	処理対象の降順ソート済み配列
	 * @param[in]	start	引数 @a input の処理対象の始点
	 * @param[in]	end	引数 @a input の処理対象の終点
	 */
	static BinarySearchNode<TYPE>*
	PrepareTree(const TYPE* input,
				size_t start,
				size_t end)
		{
			size_t center = (end + start) / 2;
			BinarySearchNode<TYPE>* node = new BinarySearchNode<TYPE>(input[center]);

			if (start < center) {
				node->children_[0] = PrepareTree(input, start, center - 1);
#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
				if (node->children_[0]) node->children_[0]->parent_ = node;
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
			}
			if (center < end) {
				node->children_[1] = PrepareTree(input, center + 1, end);
#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
				if (node->children_[1]) node->children_[1]->parent_ = node;
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
			}

			return node;
		}

	/**
	 *  メソッド @a BinarySearchTree::add の本体
	 * @param[in]	node	追加対象のノード
	 * @param[in]	compare	キー比較の関数
	 * @param[in]	data	追加対象のキー
	 * @return	処理対象のノード (基本的には引数 @a node に等しい)
	 * @note	引数 @a node が @a 0 の場合、新規生成したノードを返す。
	 */
	static BinarySearchNode<TYPE>*
	AddNode(BinarySearchNode<TYPE>* node,
			int (* compare)(const TYPE&, const TYPE&),
			const TYPE& data)
		{
			assert(compare);

			int v;

			if (node) {
				v = compare(data, node->key_);
				if (v < 0) {
					node->children_[0] = AddNode(node->children_[0], compare, data);
#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
					if (node->children_[0]) node->children_[0]->parent_ = node;
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
				}
				else if (0 < v) {
					node->children_[1] = AddNode(node->children_[1], compare, data);
#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
					if (node->children_[1]) node->children_[1]->parent_ = node;
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__
				}
				else {
					assert(!"Found a duplicated key!");
				}
				return node;
			}

			return new BinarySearchNode<TYPE>(data);
		}

	/**
	 *  メソッド @a BinarySearchTree::search の本体
	 * @param[in]	node	探索対象のノード
	 * @param[in]	compare	キー比較の関数
	 * @param[in]	data	探索対象のキー
	 * @return	ヒットしたノード (ヒットしなかった場合は @a 0 が返る)
	 */
	static const BinarySearchNode<TYPE>*
	SearchKey(const BinarySearchNode<TYPE>* node,
			  int (* compare)(const TYPE&, const TYPE&),
			  const TYPE& data)
		{
			assert(node);
			assert(compare);

			int v;

			while (node) {
				v = compare(data, node->key_);
				if (v < 0) {
					node = node->children_[0];
					continue;
				}
				if (0 < v) {
					node = node->children_[1];
					continue;
				}
				return node;
			}

			return 0;
		}

	/**
	 * 葉ノードまでの最短・最長距離を算出
	 * @param[in]	node	ノード
	 * @param[out]	min	最短距離 (呼び出し時に @a ~0 を含む変数を指定)
	 * @param[out]	max	最長距離 (呼び出し時に @a 0 を含む変数を指定)
	 * @param[in]	現時点での呼び出し元からの距離
	 * @note	タスクによっては、
				maxとminの差が一定以上大きくなった時点で終了させることも考える。
	 */
	static void
	GetDepth(const BinarySearchNode<TYPE>* node,
			 size_t& min,
			 size_t& max,
			 size_t depth = 0)
		{
			if (node) {
				GetDepth(node->children_[0], min, max, depth + 1);
				GetDepth(node->children_[1], min, max, depth + 1);
			}
			else {
				if (depth < min) min = depth;
				if (max < depth) max = depth;
			}
		}

	/**
	 * メソッド @a BinarySearchTree::is_correct の本体
	 * @param[in]	node	処理対象のノード
	 * @param[in]	compare	キー比較の関数
	 * @param[in]	min	部分木の最小値
	 * @param[in]	max	部分木の最大値
	 * @return	true: 親子関係を守っている, false: 親子関係を守ってない
	 */
	static bool
	CheckRule(const BinarySearchNode<TYPE>* node,
			  int (* compare)(const TYPE&, const TYPE&),
			  const TYPE& min,
			  const TYPE& max)
		{
			assert(compare);

			if (node) {
				if (0 > compare(node->key_, min)) return false;
				if (0 < compare(node->key_, max)) return false;
				if (node->children_[0]) {
					if (0 > compare(node->key_, node->children_[0]->key_)) return false;
					if (!CheckRule(node->children_[0], compare, min, node->key_)) return false;
				}
				if (node->children_[1]) {
					if (0 < compare(node->key_, node->children_[1]->key_)) return false;
					if (!CheckRule(node->children_[1], compare, node->key_, max)) return false;
				}
			}

			return true;
		}

	/**
	 * メソッド @a BinarySearchTree::get_nodes_with_same_depth の本体
	 * @param[in]	node	処理対象のノード
	 * @param[in]	depth	深さ
	 * @param[out]	array	深さ毎のノード
	 */
	static void
	GetNodesWithSameDepth(const BinarySearchNode<TYPE>* node,
						  size_t depth,
						  std::vector<std::vector<const BinarySearchNode<TYPE>*> >& array)
		{
			assert(node);

			while (array.size() <= depth) array.resize(depth + 1);
			array[depth].push_back(node);

			if (node->children_[0]) GetNodesWithSameDepth(node->children_[0], depth + 1, array);
			if (node->children_[1]) GetNodesWithSameDepth(node->children_[1], depth + 1, array);
		}

	/**
	 * メソッド @a PrintTree の補助関数
	 * @param[out]	file	出力先ファイル
	 * @param[in]	node	出力対象のノード
	 * @param[in]	prefix	ノード前に記述する文字
	 * @param[in]	depth	深さ
	 */
	static void
	PrintTreeRoutine(FILE* file,
					 const BinarySearchNode<TYPE>* node,
					 const char prefix,
					 size_t depth)
		{
			for (size_t i(0); i < depth; ++i) std::printf("  ");
			std::printf("%c:%G\n", prefix, (double)node->key_);
		}

	/**
	 * メソッド @a BinarySearchTree::print の本体
	 * @param[out]	file	出力先ファイル
	 * @param[in]	node	出力対象のノード
	 * @param[in]	prefix	ノード前に記述する文字
	 * @param[in]	depth	深さ
	 * @param[in]	position	処理手順 (負: pre-order, 0: in-order, 正: post-order)
	 */
	static void
	PrintTree(FILE* file,
			  const BinarySearchNode<TYPE>* node,
			  int position,
			  const char prefix = '*',
			  size_t depth = 0)
		{
			if (position < 0) PrintTreeRoutine(file, node, prefix, depth);	// pre-order処理
			if (node->children_[0]) PrintTree(file, node->children_[0], position, 'L', depth+1);
			if (position == 0) PrintTreeRoutine(file, node, prefix, depth);	// in-order処理
			if (node->children_[1]) PrintTree(file, node->children_[1], position, 'R', depth+1);
			if (0 < position) PrintTreeRoutine(file, node, prefix, depth);	// post-order処理
		}

};

/**
 * @class	二分探索木
 * @note	テンプレートの型 @a TYPE は木が保持する型。
 */
template<typename TYPE>
class BinarySearchTree
{
private:

	BinarySearchNode<TYPE>* root_;	///< 二分探索木の根
	TYPE max_;						///< 最大値
	TYPE min_;						///< 最小値

	/**
	 * 探索に用いる比較関数
	 * @note	2つの引数が等しい時は0を、
				第1引数が大きい場合は負の数を、そうでない場合は正の数を返す。
	 */
	int (* compare_)(const TYPE&, const TYPE&);

public:

	/**
	 * コンストラクタ
	 * @param[in]	compare	比較関数
	 */
	BinarySearchTree(int (* compare)(const TYPE&, const TYPE&) = 0)
		: root_(0), compare_(compare)
		{
			;
		}

	/**
	 * デストラクタ
	 */
	~BinarySearchTree()
		{
			if (root_) delete root_;
		}

	/**
	 * 昇順ソート済み配列から平衡二分探索木を構築
	 * @param[in]	input	処理対象の昇順ソート済み配列
	 * @param[in]	length	引数 @a input の長さ
	 */
	void
	prepare(const TYPE* input,
			size_t length)
		{
			assert(input);
			assert(length);

			if (root_) delete root_;

			min_ = input[0];
			max_ = input[length-1];
			root_ = BinarySearchNode<TYPE>::PrepareTree(input, 0, length - 1);
		}

	/**
	 * データ追加
	 * @param[in]	key	追加対象のキー
	 * @note	本実装ではキーの重複はないものと仮定する。
	 */
	void
	add(const TYPE& key)
		{
			if (0 < compare_(key, min_)) min_ = key;
			if (0 > compare_(key, max_)) max_ = key;
			root_ = BinarySearchNode<TYPE>::AddNode(root_, compare_, key);
		}

#ifdef	__BINARY_SEARCH_TREE_GET_RAW_DATA__
	/**
	 * データ探索
	 * @param[in]	data	探索対象のデータ
	 * @return	引数 @a data にヒットしたノード
	 */
	BinarySearchNode<TYPE>*
	search(const TYPE& data)
		{
			assert(compare_);

			return (BinarySearchNode<TYPE>*)BinarySearchNode<TYPE>::SearchKey(root_, compare_, data);
		}
#else	// __BINARY_SEARCH_TREE_GET_RAW_DATA__
	/**
	 * データ探索
	 * @param[in]	data	探索対象のデータ
	 * @return	true: 引数 @a data にヒット, false: ヒットしなかった
	 */
	bool
	search(const TYPE& data) const
		{
			assert(compare_);

			return BinarySearchNode<TYPE>::SearchKey(root_, compare_, data) != 0;
		}
#endif	// __BINARY_SEARCH_TREE_GET_RAW_DATA__

	/**
	 * 平衡二分探索木か否かを確認
	 * @return	true: 平衡である, false: 平衡でない
	 */
	bool
	is_balanced() const
		{
			size_t min = (size_t)~(size_t)0;
			size_t max(0);
			BinarySearchNode<TYPE>::GetDepth(root_, min, max);

			return max <= min + 1;
		}

	/**
	 * 親子関係の正しさをチェック
	 * @return	true: 正しい, false: 正しくない
	 */
	bool
	is_correct() const
		{
			return BinarySearchNode<TYPE>::CheckRule(root_, compare_, min_, max_);
		}

	/**
	 * 深さ毎のノードを取得
	 * @param[out]	array	深さ毎のノード
	 */
	void
	get_nodes_with_same_depth(std::vector<std::vector<const BinarySearchNode<TYPE>*> >& array)
		{
			BinarySearchNode<TYPE>::GetNodesWithSameDepth(root_, 0, array);
		}

	/**
	 * 二分探索木をファイルに出力
	 * @param[out]	file	出力先ファイル
	 */
	void
	print(FILE* file,
		  int position = -1) const
		{
			assert(root_);

			BinarySearchNode<TYPE>::PrintTree(file, root_, position);
		}
};

#endif	// __BINARY_SEARCH_TREE_HPP__
