/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	list.hpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の2章の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#ifndef	__LIST_HPP__
#define	__LIST_HPP__ "list.hpp"

#include <cstddef>
#include <cstdio>
#include <cassert>

//#define	USE_DOUBLY_LINKED_LIST	"use_doubly_linked_list"

/**
 * リストを構成するノード
 */
template<typename TYPE>
class Node
{
private:

	TYPE data_;				///< データ
#ifdef	USE_DOUBLY_LINKED_LIST
	Node<TYPE>* previous_;	///< 前のノード
#endif	// USE_DOUBLY_LINKED_LIST
	Node<TYPE>* next_;		///< 次のノード

public:

#ifdef	USE_DOUBLY_LINKED_LIST

	/**
	 * コンストラクタ
	 * @param[in]	data	格納するデータ
	 * @param[in]	previous	前のノード
	 * @param[in]	next	次のノード
	 */
	Node(const TYPE& data,
		 Node<TYPE>* previous = 0,
		 Node<TYPE>* next = 0)
		: data_(data), previous_(previous), next_(next)
		{
			;
		}

#else	// USE_DOUBLY_LINKED_LIST

	/**
	 * コンストラクタ
	 * @param[in]	data	格納するデータ
	 * @param[in]	next	次のノード
	 */
	Node(const TYPE& data,
		 Node<TYPE>* next = 0)
		: data_(data), next_(next)
		{
			;
		}

#endif	// USE_DOUBLY_LINKED_LIST

	/**
	 * データを格納
	 * @param[in]	data	データ
	 */
	void
	set_data(const TYPE& data)
		{
			data_ = data;
		}

	/**
	 * データを取得
	 * @return	データ
	 */
	TYPE
	get_data() const
		{
			return data_;
		}

#ifdef	USE_DOUBLY_LINKED_LIST

	/**
	 * 前のノードを格納
	 * @param[in]	previous	前のノードのポインタ
	 */
	void
	set_previous(Node<TYPE>* previous)
		{
			previous_ = previous;
		}

	/**
	 * 前のノードを取得
	 * @return	前のノードのポインタ
	 */
	Node<TYPE>*
	get_previous() const
		{
			return previous_;
		}

#endif	// USE_DOUBLY_LINKED_LIST

	/**
	 * 次のノードを格納
	 * @param[in]	next	次のノード
	 */
	void
	set_next(Node<TYPE>* next)
		{
			next_ = next;
		}

	/**
	 * 次のノードを取得
	 * @return	次のノード
	 */
	Node<TYPE>*
	get_next() const
		{
			return next_;
		}

	/**
	 * 配列からリストを生成
	 * @param[in]	array	配列
	 * @param[in]	length	引数 @a array の要素数
	 * @return	リストの先頭のノード
	 */
	static Node<TYPE>*
	MakeLinkedList(const TYPE* array,
				   size_t length)
		{
			Node<TYPE>* top(0);
			Node<TYPE>* c;
			Node<TYPE>* p(0);

			for (size_t i(0); i < length; ++i) {
				c = new Node<TYPE>(array[i]);
#ifdef	USE_DOUBLY_LINKED_LIST
				c->set_previous(p);
#endif	// USE_DOUBLY_LINKED_LIST
				if (p) p->set_next(c);
				if (!top) top = c;
				p = c;
			}

			return top;
		}

	/**
	 * リストを削除
	 * @param[in,out]	node	リストの先頭ノード
	 */
	static void
	DeleteLinkedList(Node<TYPE>* node)
		{
			Node<TYPE>* n;

			while (node) {
				n = node->get_next();
				delete node;
				node = n;
			}
		}

	/**
	 * リストの各ノードのデータを表示
	 * @param[in]	node	リストの先頭ノード
	 */
	static void
	PrintLinkedList(const Node<TYPE>* node)
		{
			bool flag = false;

			while (node) {
				if (flag) std::printf(", ");
				std::printf("%G", (double)node->get_data());
				node = node->get_next();
				flag = true;
			}
			if (flag) std::printf("\n");
		}
};

#endif	// __LIST_HPP__
