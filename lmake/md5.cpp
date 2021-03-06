#include "md5.hpp"

#define f1(x, y, z) (z ^ (x & (y ^ z)))
#define f2(x, y, z) (f1(z, x, y))
#define f3(x, y, z) (x ^ y ^ z)
#define f4(x, y, z) (y ^ (x | ~z))

#define step(f, w, x, y, z, data, s) (w += f(x, y, z) + data,  w = w<<s | w>>(32-s), w += x)

static void md5_transform(unsigned int buf[4], const unsigned in[16])
{
	register unsigned int a = buf[0];
	register unsigned int b = buf[1];
	register unsigned int c = buf[2];
	register unsigned int d = buf[3];

	step(f1, a, b, c, d, in[ 0] + 0xd76aa478, 7);
	step(f1, d, a, b, c, in[ 1] + 0xe8c7b756, 12);
	step(f1, c, d, a, b, in[ 2] + 0x242070db, 17);
	step(f1, b, c, d, a, in[ 3] + 0xc1bdceee, 22);
	step(f1, a, b, c, d, in[ 4] + 0xf57c0faf, 7);
	step(f1, d, a, b, c, in[ 5] + 0x4787c62a, 12);
	step(f1, c, d, a, b, in[ 6] + 0xa8304613, 17);
	step(f1, b, c, d, a, in[ 7] + 0xfd469501, 22);
	step(f1, a, b, c, d, in[ 8] + 0x698098d8, 7);
	step(f1, d, a, b, c, in[ 9] + 0x8b44f7af, 12);
	step(f1, c, d, a, b, in[10] + 0xffff5bb1, 17);
	step(f1, b, c, d, a, in[11] + 0x895cd7be, 22);
	step(f1, a, b, c, d, in[12] + 0x6b901122, 7);
	step(f1, d, a, b, c, in[13] + 0xfd987193, 12);
	step(f1, c, d, a, b, in[14] + 0xa679438e, 17);
	step(f1, b, c, d, a, in[15] + 0x49b40821, 22);

	step(f2, a, b, c, d, in[ 1] + 0xf61e2562, 5);
	step(f2, d, a, b, c, in[ 6] + 0xc040b340, 9);
	step(f2, c, d, a, b, in[11] + 0x265e5a51, 14);
	step(f2, b, c, d, a, in[ 0] + 0xe9b6c7aa, 20);
	step(f2, a, b, c, d, in[ 5] + 0xd62f105d, 5);
	step(f2, d, a, b, c, in[10] + 0x02441453, 9);
	step(f2, c, d, a, b, in[15] + 0xd8a1e681, 14);
	step(f2, b, c, d, a, in[ 4] + 0xe7d3fbc8, 20);
	step(f2, a, b, c, d, in[ 9] + 0x21e1cde6, 5);
	step(f2, d, a, b, c, in[14] + 0xc33707d6, 9);
	step(f2, c, d, a, b, in[ 3] + 0xf4d50d87, 14);
	step(f2, b, c, d, a, in[ 8] + 0x455a14ed, 20);
	step(f2, a, b, c, d, in[13] + 0xa9e3e905, 5);
	step(f2, d, a, b, c, in[ 2] + 0xfcefa3f8, 9);
	step(f2, c, d, a, b, in[ 7] + 0x676f02d9, 14);
	step(f2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);

	step(f3, a, b, c, d, in[ 5] + 0xfffa3942, 4);
	step(f3, d, a, b, c, in[ 8] + 0x8771f681, 11);
	step(f3, c, d, a, b, in[11] + 0x6d9d6122, 16);
	step(f3, b, c, d, a, in[14] + 0xfde5380c, 23);
	step(f3, a, b, c, d, in[ 1] + 0xa4beea44, 4);
	step(f3, d, a, b, c, in[ 4] + 0x4bdecfa9, 11);
	step(f3, c, d, a, b, in[ 7] + 0xf6bb4b60, 16);
	step(f3, b, c, d, a, in[10] + 0xbebfbc70, 23);
	step(f3, a, b, c, d, in[13] + 0x289b7ec6, 4);
	step(f3, d, a, b, c, in[ 0] + 0xeaa127fa, 11);
	step(f3, c, d, a, b, in[ 3] + 0xd4ef3085, 16);
	step(f3, b, c, d, a, in[ 6] + 0x04881d05, 23);
	step(f3, a, b, c, d, in[ 9] + 0xd9d4d039, 4);
	step(f3, d, a, b, c, in[12] + 0xe6db99e5, 11);
	step(f3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
	step(f3, b, c, d, a, in[ 2] + 0xc4ac5665, 23);

	step(f4, a, b, c, d, in[ 0] + 0xf4292244, 6);
	step(f4, d, a, b, c, in[ 7] + 0x432aff97, 10);
	step(f4, c, d, a, b, in[14] + 0xab9423a7, 15);
	step(f4, b, c, d, a, in[ 5] + 0xfc93a039, 21);
	step(f4, a, b, c, d, in[12] + 0x655b59c3, 6);
	step(f4, d, a, b, c, in[ 3] + 0x8f0ccc92, 10);
	step(f4, c, d, a, b, in[10] + 0xffeff47d, 15);
	step(f4, b, c, d, a, in[ 1] + 0x85845dd1, 21);
	step(f4, a, b, c, d, in[ 8] + 0x6fa87e4f, 6);
	step(f4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
	step(f4, c, d, a, b, in[ 6] + 0xa3014314, 15);
	step(f4, b, c, d, a, in[13] + 0x4e0811a1, 21);
	step(f4, a, b, c, d, in[ 4] + 0xf7537e82, 6);
	step(f4, d, a, b, c, in[11] + 0xbd3af235, 10);
	step(f4, c, d, a, b, in[ 2] + 0x2ad7d2bb, 15);
	step(f4, b, c, d, a, in[ 9] + 0xeb86d391, 21);

	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}

void md5_init(md5_ctx *ctx)
{
	ctx->buf[0] = 0x67452301;
	ctx->buf[1] = 0xefcdab89;
	ctx->buf[2] = 0x98badcfe;
	ctx->buf[3] = 0x10325476;

	ctx->bits[0] = 0;
	ctx->bits[1] = 0;
}

void md5_update(md5_ctx *ctx, const unsigned char *buf, unsigned int len)
{
	unsigned int t = ctx->bits[0];

	if ((ctx->bits[0] = t + ((unsigned int)len << 3)) < t)
	{
		ctx->bits[1]++;
	}

	ctx->bits[1] += len >> 29;

	if (t = (t >> 3) & 0x3f)
	{
		unsigned char *p = (unsigned char *)ctx->in + t;

		t = 64 - t;

		if (len < t)
		{
			memcpy(p, buf, len);
			return;
		}


		memcpy(p, buf, t);
		md5_transform(ctx->buf, (unsigned int *)ctx->in);

		buf += t;
		len -= t;
	}

	while (len >= 64)
	{
		memcpy(ctx->in, buf, 64);
		md5_transform(ctx->buf, (unsigned int *)ctx->in);

		buf += 64;
		len -= 64;
	}

	memcpy(ctx->in, buf, len);
}

void md5_final(md5_ctx *ctx, unsigned char digest[16])
{
	unsigned int count;
	unsigned char *p;

	count = (ctx->bits[0] >> 3) & 0x3f;

	p = ctx->in + count;
	*p++ = 0x80;

	count = 64 - 1 - count;

	if (count < 8)
	{
		memset(p, 0, count);
		md5_transform(ctx->buf, (unsigned int *)ctx->in);

		memset(ctx->in, 0, 56);
	}
	else
	{
		memset(p, 0, count - 8);
	}


	((unsigned int *)ctx->in)[14] = ctx->bits[0];
	((unsigned int *)ctx->in)[15] = ctx->bits[1];

	md5_transform(ctx->buf, (unsigned int *)ctx->in);
	memcpy(digest, ctx->buf, 16);
	memset(ctx, 0, 4);
}

unsigned int md5_random(unsigned int seed)
{
	md5_ctx ctx = {0};
	unsigned char digest[16];

	md5_init(&ctx);
	md5_update(&ctx, (unsigned char *)&seed, sizeof(seed));
	md5_final(&ctx, digest);

	return *(unsigned int *)(digest + 6);
}