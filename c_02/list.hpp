/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	list.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の2章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>

/**
 * @class	単方向リストのノード
 * @note	テンプレートの型 @a TYPE はリストのキーの型。
 */
template<typename TYPE>
class Node
{
private:

	TYPE key_;			///< ノードのキー
	Node<TYPE>* next_;	///< 次のノード (次がなければ @a 0 )

public:

	/**
	 * コンストラクタ
	 * @param[in]	key	ノードのキー
	 */
	Node(const TYPE& key,
		 Node<TYPE>* next = 0)
		: key_(key), next_(next)
		{
			;
		}

	/**
	 * キーの設定
	 * @param[in]	ノードのキー
	 */
	void
	set_key(const TYPE& key)
		{
			key_ = key;
		}

	/**
	 * キーの取得
	 * @return	ノードのキー
	 */
	TYPE
	get_key() const
		{
			return key_;
		}

	/**
	 * 次のノードの設定
	 * @param[in]	次のノード
	 */
	void
	set_next(Node<TYPE>* node)
		{
			next_ = node;
		}

	/**
	 * 次のノードの取得
	 * @return	次のノード
	 */
	Node<TYPE>*
	get_next() const
		{
			return next_;
		}

	/**
	 * リストを生成
	 * @param[in]	keys	リストに含める値の配列
	 * @param[in]	length	引数 @a keys の長さ
	 * @return	生成したリストの先頭ノード
	 */
	static Node<TYPE>*
	MakeList(const TYPE* keys,
			 size_t length)
		{
			Node<TYPE>* head(0);
			Node<TYPE>* previous(0);
			Node<TYPE>* current;

			for (size_t i(0); i < length; ++i) {
				current = new Node<TYPE>(keys[i]);
				if (previous) previous->set_next(current);
				if (!head) head = current;
				previous = current;
			}

			return head;
		}

	/**
	 * リストを削除
	 * @param[in]	head	リストの先頭ノード
	 */
	static void
	DeleteList(Node<TYPE>* head)
		{
			Node<TYPE>* current(head);
			Node<TYPE>* next;

			while (current) {
				next = current->get_next();
				delete current;
				current = next;
			}
		}

	/**
	 * リスト (ノード列) を出力
	 * @param[out]	file	出力
	 * @param[in]	node	リストの先頭ノード
	 */
	static void
	Print(FILE* file,
		  const Node<TYPE>* node)
		{
			bool first(true);

			std::fprintf(file, "[");

			while (node) {
				if (!first) std::fprintf(file, "->");
				std::fprintf(file, "%G", (double)node->get_key());
				node = node->get_next();
				first = false;
			}

			std::fprintf(file, "]\n");
		}
};
