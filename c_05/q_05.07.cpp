/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  0からnまでの整数が入った配列Aがあります。
  ただし、その配列には1つだけ含まれていない整数があります。
  また、配列Aの要素には1回の操作でアクセスすることはできません。
  Aの要素は2進表現されており、
  1回の操作では「A[i]の要素のjビット目を定数時間で読み込む」ことしかできません。
  このとき、0からnまでの整列で配列に含まれていない整数を探すコードを書いてください。
  これをO(n)の計算時間でできますか?
 */

#include <cstddef>
#include <cstdio>
#include <deque>

/**
 * 動作確認用コマンド
 */
int main()
{
	// 入力データ
	// ※ 要素数を m とする。
	const int data[] = {1, 3, 5, 7, 9, 11, 15, 14, 12, 10, 8, 6, 4, 2, 0};
	const int max = (int)(sizeof(data) / sizeof(data[0]));

	std::deque<size_t> queue[2][2];

	for (size_t i(0); i < sizeof(data) / sizeof(data[0]); ++i) {
		queue[0][0].push_back(i);
		std::printf("%d ", data[i]);
	}
	std::printf("\n");

	size_t h, k, x;

	// 基数ソート (昇順)
	// ※ 入力データのビット幅を定数と考えれば、計算量は O(m)。
	for (size_t i(0); i < sizeof(int) * 8; ++i) {
		h = i % 2;
		k = (h + 1) % 2;
		if (!(max & (~0 << i))) break;	// これ以上は変化なし。
		for (size_t j(0); j < 2; ++j) {
			while (!queue[h][j].empty()) {
				x = queue[h][j].front();
				queue[h][j].pop_front();
				if (data[x] & (1 << i)) {
					queue[k][1].push_back(x);
				}
				else {
					queue[k][0].push_back(x);
				}
			}
		}
	}

	// 0ビット目が連続で同じ値になる箇所を検出
	// ※ 計算量は O(m)。
	x = 1;
	for (size_t i(0); i < 2; ++i) {
		for (size_t j(0); j < 2; ++j) {
			while (!queue[i][j].empty()) {
				h = queue[i][j].front();
				queue[i][j].pop_front();
				if ((data[h] & 1) == x) {
					x = 2;
					break;
				}
				x = data[h] & 1;
			}
		}
	}

	if (1 < x) {
		// 検出
		std::printf("=> %d\n", data[h] - 1);
	}
	else {
		// 未検出 (末尾がなかった)
		std::printf("=> %lu\n", sizeof(data) / sizeof(data[0]));
	}

	return 0;
}
