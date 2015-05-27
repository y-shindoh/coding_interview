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
#endif	// __BINARY_SEARCH_TREE_GET_RAW_DATA__

	/**
	 * ノードのキーを直接取得
	 * @return	ノードのキー
	 */
	TYPE
	get_key() const
		{
			return key_;
		}

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

			if (array.size() <= depth) array.resize(depth + 1);
			array[depth].push_back(node);

			if (node->children_[0]) GetNodesWithSameDepth(node->children_[0], depth + 1, array);
			if (node->children_[1]) GetNodesWithSameDepth(node->children_[1], depth + 1, array);
		}

	/**
	 * 2つの木が等しいか否かを確認 (メソッド @a BinarySearchTree::has_subtree の本体)
	 * @param[in]	first	木 (その1)
	 * @param[in]	second	木 (その2)
	 * @return	true: 等しい, false: 等しくない
	 */
	static bool
	CheckSame(const BinarySearchNode<TYPE>* first,
			  const BinarySearchNode<TYPE>* second)
		{
			assert(first);
			assert(second);

			if (first->key_ != second->key_) return false;
			if (first->children_[0]) {
				if (!second->children_[0]) return false;
				if (!CheckSame(first->children_[0], second->children_[0])) return false;
			}
			else {
				if (second->children_[0]) return false;
			}
			if (first->children_[1]) {
				if (!second->children_[1]) return false;
				if (!CheckSame(first->children_[1], second->children_[1])) return false;
			}
			else {
				if (second->children_[1]) return false;
			}

			return true;
		}

#ifdef	__BINARY_SEARCH_TREE_ENABLE_PARENT__
	/**
	 * 次のノードを取得
	 * @param[in]	node	処理対象のノード
	 * @param[in]	direction	0: 順方向, 1: 逆方向 (in-orderの順で)
	 * @return	引数 @a node の次のノード
	 */
	static const BinarySearchNode<TYPE>*
	GetNextNode(const BinarySearchNode<TYPE>* node,
				size_t direction = 0)
		{
			assert(node);
			assert(direction < 2);

			size_t i = 1 - direction;
			size_t j = direction;

			// direction = 0: 自分より大きい子孫の最小ノード
			// direction = 1: 自分より小さい子孫の最大ノード
			if (node->children_[i]) {
				node = node->children_[i];
				while (node->children_[j]) {
					node = node->children_[j];
				}
				return node;
			}

			// direction = 0: 自分より大きい祖先の最小ノード
			// direction = 1: 自分より小さい祖先の最大ノード
			const BinarySearchNode<TYPE>* parent = node->parent_;
			while (parent && parent->children_[i] == node) {
				node = parent;
				parent = node->parent_;
			}
			return parent;
		}

	/**
	 * メソッド @a FindSameParent の補助関数
	 * @param[in]	first	ノード1
	 * @param[in]	second	ノード2
	 * @param[in]	ignore	処理対象外のノード (呼び出し直後のみ有効)
	 * @retval	true: ノード @a second はノード @a first かその子孫
	 * @retval	false: ノード @a second はノード @a first やその子孫でない
	 */
	static bool
	FindSameParentRoutine(const BinarySearchNode<TYPE>* first,
						  const BinarySearchNode<TYPE>* second,
						  const BinarySearchNode<TYPE>* ignore = 0)
		{
			if (first == second) return true;

			// 子方向に下りながら探索
			for (size_t i(0); i < 2; ++i) {
				if (!first->children_[i]) continue;
				if (first->children_[i] == ignore) continue;
				if (FindSameParentRoutine(first->children_[i], second)) return true;
			}

			return false;
		}

	/**
	 * 2つのノードに共通するもっとも深い位置の親ノードを取得
	 * @param[in]	first	ノード1
	 * @param[in]	second	ノード2
	 * @return	2つのノードに共通するもっとも深い位置の親ノード
	 */
	static const BinarySearchNode<TYPE>*
	FindSameParent(const BinarySearchNode<TYPE>* first,
				   const BinarySearchNode<TYPE>* second)
		{
			assert(first);
			assert(second);

			const BinarySearchNode<TYPE>* ignore(0);

			// 親方向にさかのぼりながら子を探索
			while (first) {
				if (FindSameParentRoutine(first, second, ignore)) return first;
				if (!first->parent_) break;
				ignore = first;
				first = first->parent_;
			}

			return 0;
		}
#endif	// __BINARY_SEARCH_TREE_ENABLE_PARENT__

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
			assert(root_);

			BinarySearchNode<TYPE>::GetNodesWithSameDepth(root_, 0, array);
		}

	/**
	 * 部分木を持つか否かを確認
	 * @param[in]	tree	部分木の候補
	 * @return	true: 引数 @a tree は部分木, false: 引数 @a tree は部分木でない
	 */
	bool
	has_subtree(const BinarySearchTree<TYPE>& tree) const
		{
			assert(root_);
			assert(compare_);

			const BinarySearchNode<TYPE>* node = BinarySearchNode<TYPE>::SearchKey(root_, compare_, tree.root_->get_key());

			if (!node) return false;

			return BinarySearchNode<TYPE>::CheckSame(node, tree.root_);
		}

	/**
	 * 二分探索木をファイルに出力
	 * @param[out]	file	出力先ファイル
	 * @param[in]	position	処理手順 (負: pre-order, 0: in-order, 正: post-order)
	 */
	void
	print(FILE* file,
		  int position = -1) const
		{
			assert(file);
			assert(root_);

			BinarySearchNode<TYPE>::PrintTree(file, root_, position);
		}
};

#endif	// __BINARY_SEARCH_TREE_HPP__
