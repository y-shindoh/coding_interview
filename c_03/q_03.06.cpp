/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_03.06.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題3.6の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

/**
 * スタックをソーティング
 * @param[in,out]	stack	ソーティング対象のスタック
 * @param	buffer	作業領域
 * @note	計算量はΘ(n^2)。
 */
template<typename TYPE>
void
sort_stack(std::vector<TYPE>& stack,
		   std::vector<TYPE>& buffer)
{
	bool flag(true);
	size_t length(0);
	size_t done(0);
	size_t h, i;
	TYPE tmp, max;

	while ('-') {
		// forward
		h = i = 0;
		for (size_t j(done); flag ? !stack.empty() : j < length ; ++j) {
			tmp = stack.back();
			stack.pop_back();
			buffer.push_back(tmp);
			if (i == 0 || max <= tmp) {
				h = i;
				max = tmp;
			}
			++i;	// 対になるように (1)
			if (flag) ++length;
		}
		stack.push_back(max);
		// backward
		while (!buffer.empty()) {
			--i;	// 対になるように (2)
			tmp = buffer.back();
			buffer.pop_back();
			if (i != h) stack.push_back(tmp);
		}
		// check
		if (length <= ++done) break;
		flag = false;
	}
}

/**
 * スタック (配列) を表示
 * @param[in]	stack	表示対象のスタック
 */
template<typename TYPE>
void
print(const std::vector<TYPE>& stack)
{
	const size_t l = stack.size();
	for (size_t i(0); i < l; ++i) {
		if (0 < i) std::printf(", ");
		std::printf("%G", (double)stack[i]);
	}
	std::printf("\n");
}

/**
 * 動作確認用コマンド
 */
int main()
{
	int data[] = {1, 3, 5, 7, 9, 0, 2, 4, 6, 8};
	std::vector<int> stack;
	std::vector<int> buffer;

	for (size_t i(0); i < sizeof(data)/sizeof(data[0]); ++i) {
		stack.push_back(data[i]);
	}

	print<int>(stack);
	sort_stack<int>(stack, buffer);
	print<int>(stack);

	return 0;
}
