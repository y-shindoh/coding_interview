/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  多くの画像編集プログラムに見られるような「塗りつぶし」機能を実装してください。
  つまり、スクリーン (色の2次元配列で表現されたもの) と座標、
  塗りつぶす色が与えられた時に、
  その地点と同じ色で囲まれている領域をすべて塗りつぶす機能ということです。
 */

#include <cstddef>
#include <cstdio>
#include <cassert>
#include <deque>

/**
 * 画像の塗りつぶし
 * @param[in,out]	canvas	処理対象の画像
 * @param[in]	x	塗りつぶし始点のX座標
 * @param[in]	y	塗りつぶし始点のY座標
 * @param[in]	color	塗りつぶしで用いる色
 * @note	テンプレートの整数 @a H , @a W はそれぞれ画像の高さと幅。
 * @note	最悪計算量は O(HW)。
 */
template<size_t H, size_t W>
void
fill_color(char canvas[H][W],
		   size_t x,
		   size_t y,
		   char color)
{
	std::deque< std::pair<size_t, size_t> > queue;
	std::pair<size_t, size_t> pixel;

	queue.push_back(std::pair<size_t, size_t>(x, y));

	while (!queue.empty()) {
		pixel = queue.front();
		queue.pop_front();
		x = pixel.first;
		y = pixel.second;
		if (0 < x && canvas[y][x] == canvas[y][x-1]) {
			queue.push_back(std::pair<size_t, size_t>(x-1, y));
		}
		if (x + 1 < W && canvas[y][x] == canvas[y][x+1]) {
			queue.push_back(std::pair<size_t, size_t>(x+1, y));
		}
		if (0 < y && canvas[y][x] == canvas[y-1][x]) {
			queue.push_back(std::pair<size_t, size_t>(x, y-1));
		}
		if (y + 1 < H && canvas[y][x] == canvas[y+1][x]) {
			queue.push_back(std::pair<size_t, size_t>(x, y+1));
		}
		canvas[y][x] = color;
	}
}

/**
 * 画像の表示
 * @param[in]	canvas	処理対象の画像
 * @note	テンプレートの整数 @a H , @a W はそれぞれ画像の高さと幅。
 */
template<size_t H, size_t W>
void
print_canvas(const char canvas[H][W])
{
	for (size_t y(0); y < H; ++y) {
		std::printf("%lu\t", y);
		for (size_t x(0); x < W; ++x) {
			std::printf("%02X ", (unsigned int)canvas[y][x]);
		}
		std::printf("\n");
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char canvas[3][3] = {{0, 0, 0},
						 {0, 1, 2},
						 {3, 0, 0}};

	print_canvas<3, 3>(canvas);
	fill_color<3, 3>(canvas, 1, 0, 4);
	std::printf("----\n");
	print_canvas<3, 3>(canvas);

	return 0;
}
