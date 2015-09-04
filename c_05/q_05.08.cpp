/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	q_05.08.cpp
 * @brief	「世界で闘うプログラミング力を鍛える150問」の問題5.8の回答
 * @author	Yasutaka SHINDOH / 新堂 安孝
 * @note	see http://www.amazon.co.jp/dp/4839942390 .
 */

/*
  問題:
  モノクロのスクリーンが1次元のバイト型配列として保持されています。
  1バイトには連続した8ピクセルを保持することができます。
  スクリーンの幅は8の倍数で、
  バイトの途中で切れるような形にはなっていないことにします。
  当然ですが、水平な直線を描く関数
  drawHorizontalLine(byte[] screen, int width, int x1, int x2, int y) を
  実装してください。
 */

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cassert>

/**
 * スクリーンに水平の直線を引く
 * @param[out]	screen	スクリーン
 * @param[in]	x1	直線の始端のx座標
 * @param[in]	x2	直線の終端のx座標
 * @param[in]	y	直線のy座標
 */
template<size_t W, size_t H>
void
draw_horizontal_line(char screen[H][W/8],
					 size_t x1,
					 size_t x2,
					 size_t y)
{
	assert(x1 < W);
	assert(x2 < W);
	assert(y < H);

	bool flag(false);

	size_t x11 = x1 / 8;
	size_t x12 = x1 % 8;
	size_t x21 = x2 / 8;
	size_t x22 = x2 % 8;

	for (size_t i(x11); i <= x21; ++i) {
		for (size_t j(0); j < 8; ++j) {
			if (!flag) {
				if (i == x11 && j == x12) flag = true;
			}
			if (flag) {
				screen[i][y] |= 1 << j;
				if (i == x21 && j == x22) flag = false;
			}
		}
	}
}

/**
 * スクリーンを出力
 * @param[in]	screen	スクリーン
 */
template<size_t W, size_t H>
void
print_screen(const char screen[H][W/8])
{
	for (size_t h(0); h < H; ++h) {
		for (size_t w(0); w < W; ++w) {
			if (screen[h][w/8] & (1 << w %8)) {
				std::printf("X");
			}
			else {
				std::printf(".");
			}
		}
		std::printf("\n");
	}
}

/**
 * 動作確認用コマンド
 */
int main()
{
	char screen[4][16/8];

	std::memset((void*)screen, 0, sizeof(screen));

	std::printf("<<befoer>>\n");
	print_screen<16, 4>(screen);

	draw_horizontal_line<16, 4>(screen, 5, 7, 2);
	draw_horizontal_line<16, 4>(screen, 8, 14, 3);

	std::printf("<<after>>\n");
	print_screen<16, 4>(screen);

	return 0;
}
