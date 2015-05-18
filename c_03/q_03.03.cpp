/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <iterator>

/**
 * @class	複数のサブスタックで1つのスタックを実現
 * @note	テンプレートの型 @a TYPE はスタックのキーの型。
 * @note	テンプレートの整数 @a MAX_LENGTH はサブスタックの最大長
 */
template<typename TYPE, size_t MAX_LENGTH>
class MultiStack
{
private:

	typedef std::vector<TYPE> MyStack;	///< サブスタックの型

	std::vector<MyStack*> stacks_;	///< 使用中サブスタック列
	std::vector<MyStack*> buffer_;	///< 未使用サブスタック列
	size_t length_;					///< スタックの長さ

public:

	/**
	 * コンストラクタ
	 */
	MultiStack()
		: length_(0)
		{
			;
		}

	/**
	 * デストラクタ
	 */
	virtual
	~MultiStack()
		{
			size_t l = stacks_.size();
			for (size_t i(0); i < l; ++i) {
				delete stacks_[i];
			}

			l = buffer_.size();
			for (size_t i(0); i < l; ++i) {
				delete buffer_[i];
			}
		}

	/**
	 * 使用中サブスタックの数を取得
	 * @return	使用中サブスタックの数
	 */
	size_t
	substack_size() const
		{
			return stacks_.size();
		}

	/**
	 * 未使用サブスタックのメモリ領域を開放
	 */
	void
	release_buffer()
		{
			size_t l = buffer_.size();
			for (size_t i(0); i < l; ++i) {
				delete buffer_[i];
			}

			buffer_.clear();
		}

	/**
	 * スタックの全ての要素を削除
	 */
	void
	clear()
		{
			size_t l = stacks_.size();
			for (size_t i(0); i < l; ++i) {
				stacks_[i]->clear();
				buffer_.push_back(stacks_[i]);
			}

			stacks_.clear();
			length_ = 0;
		}

	/**
	 * スタックが空かどうか確認
	 * @return	true: 空, false: 空でない
	 * @note	最悪計算量はO(1)。
	 */
	bool
	empty() const
		{
			return stacks_.empty();
		}

	/**
	 * 指定のサブスタックが空かどうか確認
	 * @param[in]	i	サブスタックのインデックス
	 * @return	true: 空, false: 空でない
	 * @note	最悪計算量はO(1)。
	 */
	bool
	empty(size_t i) const
		{
			if (stacks_.size() <= i) return false;
			return stacks_[i]->empty();
		}

	/**
	 * スタックの長さを取得
	 * @return	スタックの長さ
	 * @note	最悪計算量はO(1)。
	 */
	size_t
	size() const
		{
			return length_;
		}

	/**
	 * 指定のサブスタックの長さを取得
	 * @param[in]	i	サブスタックのインデックス
	 * @return	サブスタックの長さ
	 * @note	最悪計算量はO(1)。
	 */
	size_t
	size(size_t i) const
		{
			if (stacks_.size() <= i) return 0;
			return stacks_[i]->size();
		}

	/**
	 * スタックからデータを取得 (削除はしない)
	 * @return	取得した要素
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	top() const
		{
			assert(!stacks_.empty());

			return stacks_.back()->back();
		}

	/**
	 * 指定のサブスタックからデータを取得 (削除はしない)
	 * @param[in]	i	サブスタックのインデックス
	 * @return	取得した要素
	 * @note	事前にサブスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(1)。
	 */
	TYPE
	top(size_t i) const
		{
			assert(i < stacks_.size());
			assert(!stacks_[i]->empty());

			return stacks_[i]->back();
		}

	/**
	 * スタックに要素を追加
	 * @param[in]	data	追加するデータ
	 * @note	ならし解析の計算量はO(1)となる。最悪計算量はO(n)で、nは @a stacks_ の長さ。
	 */
	void
	push(const TYPE& data)
		{
			if (stacks_.empty() || MAX_LENGTH <= stacks_.back()->size()) {
				MyStack* stack;
				if (buffer_.empty()) {
					stack = new MyStack();
					stack->reserve(MAX_LENGTH);
				}
				else {
					stack = buffer_.back();
					buffer_.pop_back();
				}
				stacks_.push_back(stack);
			}

			stacks_.back()->push_back(data);
			++length_;
		}

	/**
	 * 指定のサブスタックに要素を追加
	 * @param[in]	i	サブスタックのインデックス
	 * @param[in]	data	追加するデータ
	 * @note	ならし解析の計算量はO(1)となる。最悪計算量はO(n)で、nは指定サブスタックの長さ。
	 */
	void
	push(size_t i,
		 const TYPE& data)
		{
			assert(i < stacks_.size());

			stacks_[i]->push_back(data);
			++length_;
		}

	/**
	 * スタックから要素を削除
	 * @note	事前にスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(n)。ただしnは @a buffer_ の長さ。
	 */
	void
	pop()
		{
			assert(!stacks_.empty());

			stacks_.back()->pop_back();
			--length_;

			while (!stacks_.empty() && stacks_.back()->empty()) {
				buffer_.push_back(stacks_.back());
				stacks_.pop_back();
			}
		}

	/**
	 * 指定のサブスタックから要素を削除
	 * @param[in]	i	サブスタックのインデックス
	 * @note	事前にサブスタックが空でないことを確認しておくこと。
	 * @note	最悪計算量はO(n)。ただしnは @a buffer_ の長さ。
	 */
	void
	pop(size_t i)
		{
			assert(i < stacks_.size());
			assert(!stacks_[i]->empty());

			stacks_[i]->pop_back();
			--length_;

			while (!stacks_.empty() && stacks_.back()->empty()) {
				buffer_.push_back(stacks_.back());
				stacks_.pop_back();
			}
		}

	/**
	 * スタックの状態を出力
	 * @param	file	出力先
	 */
	void
	print(FILE* file) const
		{
			size_t l = stacks_.size();
			size_t m;

			for (size_t i(0); i < l; ++i) {
				std::fprintf(file, "[%lu] ", i);
				m = stacks_[i]->size();
				for (size_t j(0); j < m; ++j) {
					if (0 < j) std::printf(", ");
					std::fprintf(file, "%G", (double)stacks_[i]->at(j));
				}
				std::fprintf(file, "\n");
			}
		}
};

/**
 * 動作確認用コマンド
 */
int main()
{
	MultiStack<int, 2>* stack = new MultiStack<int, 2>();

	std::printf("**PUSH**\n");
	stack->push(5);
	stack->push(6);
	stack->push(2);
	stack->push(8);
	stack->push(1);
	stack->push(1);
	stack->push(1, 7);
	stack->push(10);
	stack->push(12);
	stack->print(stdout);
	std::printf("size: %lu\n", stack->size());
	std::printf("**POP**\n");
	if (!stack->empty()) stack->pop();
	if (!stack->empty(0)) stack->pop(0);	// 発展問題の popAt<f> に該当
	if (!stack->empty()) stack->pop();
	stack->print(stdout);
	std::printf("size: %lu\n", stack->size());
	std::printf("**TOP**\n");
	if (!stack->empty()) std::printf("[-] %d\n", stack->top());
	if (!stack->empty(1)) std::printf("[1] %d\n", stack->top(1));
	std::printf("**CLEAR**\n");
	stack->clear();
	stack->print(stdout);
	std::printf("size: %lu\n", stack->size());

	delete stack;

	return 0;
}
