/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_09.07.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題9.7の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
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
 */
template<size_t H, size_t W>
void
fill_color(char canvas[H][W],
		   size_t x,
		   size_t y,
		   char color)
{
	const char original = canvas[y][x];	// 画像の配列は「高さ×幅」

	if (color == original) return;

	std::deque<size_t> queue_x;
	std::deque<size_t> queue_y;

	queue_x.push_back(x);
	queue_y.push_back(y);

	while (!queue_x.empty()) {
		x = queue_x.front();
		y = queue_y.front();

		if (canvas[y][x] == original) {	// 未処理のみ扱う
			canvas[y][x] = color;
			if (0 < x && canvas[y][x-1] == original) {
				queue_x.push_back(x - 1);
				queue_y.push_back(y);
			}
			if (0 < y && canvas[y-1][x] == original) {
				queue_x.push_back(x);
				queue_y.push_back(y - 1);
			}
			if (x < W && canvas[y][x+1] == original) {
				queue_x.push_back(x + 1);
				queue_y.push_back(y);
			}
			if (y < H && canvas[y+1][x] == original) {
				queue_x.push_back(x);
				queue_y.push_back(y + 1);
			}
		}

		queue_x.pop_front();
		queue_y.pop_front();
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
