#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "ffmpeg.h"

#define DIMENSION 1000
#define ITER 100000
#define STEP 0.001

#define FPS 30
#define DURATION 10

static uint32_t pixels[DIMENSION][DIMENSION] = {0};

int main(int argc, char *argv[])
{
	FFMPEG *ffmpeg = ffmpeg_start_rendering(DIMENSION, DIMENSION, FPS);

	double phase = 0;
	for (int f = 0; f < FPS*DURATION; f++) {
		long double t = 0;
		for (unsigned long n = 0; n < ITER; n += 1) {
			int y = sin(2.123*t) * 450 + 500;
			int x = sin(t + phase) * 450 + 500;
			pixels[y][x] = 0xFFFFFFFF;
			t += STEP;
		}
		phase += 0.01;
		ffmpeg_send_frame(ffmpeg, pixels, DIMENSION, DIMENSION);
	}

	ffmpeg_end_rendering(ffmpeg);

	/* if (!stbi_write_png("out.png", DIMENSION, DIMENSION, 4, pixels, DIMENSION*sizeof(uint32_t))) {
		printf("could not write file");
		return 1;
	} */
}
