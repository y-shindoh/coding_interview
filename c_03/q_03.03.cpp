/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.03.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.3の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  皿が積み上がっている状況をイメージしてください。
  もし、高く積み上がり過ぎたら倒れてしまうでしょう。
  ですから、実生活ではスタックがある領域を超えたとき、
  新しいスタックを用意することになるでしょう。
  これをまねたデータ構造 SetOfStacks を実装してください。
  SetOfStacks はいくつかのスタックを持ち、
  スタックのデータが一杯になったらスタックを新たに作らなければなりません。
  また、SetOfStacks.push() と SetOfStacks.pop() は
  普通のスタックのようにふるまうようにしてください
  (つまり、pop() は通常の1つのスタックの場合と同じ値を返さなければなりません)。

  発展問題:
  任意の部分スタックから pop する関数 popAt(int index) を実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <vector>

/**
 * 複数のサブ・スタックをまとめたスタック
 */
template<typename TYPE, size_t N>
class SetOfStacks
{
private:

	typedef	std::vector<TYPE>	SubStack;	///< サブ・スタックの型

	std::vector<SubStack*> stack_;	///< 使用中サブ・スタック群 (空にしてはいけない)
	std::vector<SubStack*> buffer_;	///< 未使用のサブ・スタック
	size_t length_;					///< 合計要素数

	/**
	 * 空になった使用中サブ・スタックをバッファに格納
	 * @note	ならし計算量は O(1)。
	 */
	void
	adjust()
		{
			while (!stack_.empty() && stack_.back()->empty()) {
				buffer_.push_back(stack_.back());
				stack_.pop_back();
			}
		}

public:

	/**
	 * コンストラクタ
	 */
	SetOfStacks()
		: length_(0)
		{
			;
		}

	/**
	 * デストラクタ
	 */
	~SetOfStacks()
		{
			size_t l = stack_.size();
			for (size_t i(0); i < l; ++i) {
				delete stack_[i];
			}

			l = buffer_.size();
			for (size_t i(0); i < l; ++i) {
				delete buffer_[i];
			}
		}

	/**
	 * スタック全体の要素数を取得
	 * @return	スタック全体の要素数
	 * @note	計算量は O(1)。
	 */
	size_t
	size() const
		{
			return length_;
		}

	/**
	 * サブ・スタックの要素数を取得
	 * @param[in]	index	サブ・スタックのインデックス
	 * @return	サブ・スタックの要素数
	 * @note	計算量は O(1)。
	 */
	size_t
	size(size_t index) const
		{
			if (stack_.size() <= index) return 0;

			return stack_[index]->size();
		}

	/**
	 * スタック全体の先頭要素を取得
	 * @return	スタック全体の先頭要素
	 * @note	計算量は O(1)。
	 */
	TYPE
	top() const
		{
			assert(0 < length_);

			return stack_.back()->back();
		}

	/**
	 * サブ・スタックの先頭要素を取得
	 * @param[in]	index	サブ・スタックのインデックス
	 * @return	サブ・スタックの先頭要素
	 * @note	計算量は O(1)。
	 * @note	発展問題の @a SubStack::popAt に相当。
	 */
	TYPE
	top(size_t index) const
		{
			assert(index < stack_.size());
			assert(!stack_[index]->empty());

			return stack_[index]->back();
		}

	/**
	 * スタック全体に対して要素を追加
	 * @param[in]	data	追加する要素
	 * @note	ならし計算量は O(1)。
	 */
	void
	push(const TYPE& data)
		{
			if (stack_.empty() || N <= stack_.back()->size()) {
				if (buffer_.empty()) {
					stack_.push_back(new SubStack);
					stack_.back()->reserve(N);
				}
				else {
					stack_.push_back(buffer_.back());
					buffer_.pop_back();
				}
			}

			stack_.back()->push_back(data);
			++length_;
		}

	/**
	 * サブ・スタックに対して要素を追加
	 * @param[in]	index	サブ・スタックのインデックス
	 * @param[in]	data	追加する要素
	 * @note	ならし計算量は O(1)。
	 */
	void
	push(size_t index,
		 const TYPE& data)
		{
			assert(index < stack_.size());

			stack_[index]->push_back(data);
			++length_;
		}

	/**
	 * スタック全体の先頭要素を取得
	 * @return	スタック全体の先頭要素
	 * @note	ならし計算量は O(1)。
	 */
	TYPE
	pop()
		{
			assert(0 < length_);

			TYPE data = stack_.back()->back();
			--length_;

			stack_.back()->pop_back();
			adjust();

			return data;
		}

	/**
	 * サブ・スタックの先頭要素を取得
	 * @param[in]	index	サブ・スタックのインデックス
	 * @return	サブ・スタックの先頭要素
	 * @note	ならし計算量は O(1)。
	 */
	TYPE
	pop(size_t index)
		{
			assert(index < stack_.size());
			assert(!stack_.empty());

			TYPE data = stack_[index]->back();
			--length_;

			stack_[index]->pop_back();
			adjust();

			return data;
		}

	/**
	 * スタック全体の様子を出力
	 * @param[in,out]	file	出力先
	 */
	void
	print(FILE* file) const
		{
			size_t l;

			for (size_t i(0); i < stack_.size(); ++i) {
				l = stack_[i]->size();
				std::fprintf(file, "[%lu] ", i);
				for (size_t j(0); j < l; ++j) {
					if (0 < j) std::fprintf(file, ", ");
					std::fprintf(file, "%G", (double)stack_[i]->at(j));
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
	SetOfStacks<int, 2>* stack = new SetOfStacks<int, 2>;

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
	if (0 < stack->size()) stack->pop();
	if (0 < stack->size(0)) stack->pop(0);	// 発展問題の popAt<f> に該当
	if (0 < stack->size()) stack->pop();
	stack->print(stdout);
	std::printf("size: %lu\n", stack->size());
	std::printf("**TOP**\n");
	if (0 < stack->size()) std::printf("[-] %d\n", stack->top());
	if (0 < stack->size(1)) std::printf("[1] %d\n", stack->top(1));

	delete stack;

	return 0;
}
