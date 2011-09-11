#include "tbox.h"

static tb_void_t tb_test_bits_swap_u16()
{
	__tb_volatile__ tb_uint16_t x = 0x1234;
	__tb_volatile__ tb_size_t 	n = 1000001;
	__tb_volatile__ tb_int64_t 	dt = tb_mclock();

	while (n--) x = tb_bits_swap_u16(x);

	dt = tb_int64_sub(tb_mclock(), dt);
	tb_printf("[bitops]: swap_u16: %x => %x, %llu ms\n", 0x1234, x, dt);
}
static tb_void_t tb_test_bits_swap_u32()
{
	__tb_volatile__ tb_uint32_t x = 0x12345678;
	__tb_volatile__ tb_size_t 	n = 1000001;
	__tb_volatile__ tb_int64_t 	dt = tb_mclock();

	while (n--) x = tb_bits_swap_u32(x);

	dt = tb_int64_sub(tb_mclock(), dt);
	tb_printf("[bitops]: swap_u32: %x => %x, %llu ms\n", 0x12345678, x, dt);
}
static tb_void_t tb_test_bits_swap_u64()
{
	__tb_volatile__ tb_uint64_t x = tb_uint32_to_uint64(0x12345678);
	__tb_volatile__ tb_size_t 	n = 1000001;
	__tb_volatile__ tb_int64_t 	dt = tb_mclock();

	while (n--) x = tb_bits_swap_u64(x);

	dt = tb_int64_sub(tb_mclock(), dt);
	tb_printf("[bitops]: swap_u64: %x => %llx, %llu ms\n", 0x12345678, x, dt);
}
static tb_void_t tb_test_bits_ubits32(tb_uint32_t x)
{
	__tb_volatile__ tb_size_t 	b = 0;
	__tb_volatile__ tb_size_t 	n = 0;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	for (b = 0; b < 8; ++b)
	{
		tb_printf("[bitops]: ubits32 b: %d x: %x\n", b, x);
		for (n = 0; n <= 32; ++n)
		{
			__tb_volatile__ tb_byte_t 	p[256] = {0};
			__tb_volatile__ tb_size_t 	n1 = 10000;
			__tb_volatile__ tb_size_t 	n2 = 10000;
			__tb_volatile__ tb_uint32_t y = 0;
			__tb_volatile__ tb_int64_t 	t1, t2;
			__tb_volatile__ tb_uint32_t xx = n < 32? (x & ((1 << n) - 1)) : x;

			t1 = tb_mclock();
			while (n1--) tb_bits_set_ubits32(p, b, x, n);
			t1 = tb_int64_sub(tb_mclock(), t1);
			ts = tb_int64_add(ts, t1);

			t2 = tb_mclock();
			while (n2--) y = tb_bits_get_ubits32(p, b, n);
			t2 = tb_int64_sub(tb_mclock(), t2);
			tg = tb_int64_add(tg, t2);

			if (xx != y)
			{
				tb_printf("[bitops]: ubits32 set: b: %x, n: %x, x: %x, %llu ms\n", b, n, xx, t1);
				tb_printf("[bitops]: ubits32 get: b: %x, n: %x, y: %x, %llu ms\n", b, n, y, t2);
			}
		}
	}
	tb_printf("[bitops]: ubits32 set: %llu ms, get: %llu ms\n", ts, tg);
}
static tb_void_t tb_test_bits_sbits32(tb_sint32_t x)
{
	__tb_volatile__ tb_size_t 	b = 0;
	__tb_volatile__ tb_size_t 	n = 0;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	for (b = 0; b < 8; ++b)
	{
		tb_printf("[bitops]: sbits32 b: %d x: %d\n", b, x);
		for (n = 2; n <= 32; ++n)
		{
			__tb_volatile__ tb_byte_t 	p[256] = {0};
			__tb_volatile__ tb_size_t 	n1 = 10000;
			__tb_volatile__ tb_size_t 	n2 = 10000;
			__tb_volatile__ tb_sint32_t y = 0;
			__tb_volatile__ tb_int64_t 	t1, t2;
			__tb_volatile__ tb_sint32_t xx = ((x >> 31) << (n - 1)) | (x & ((1 << (n - 1)) - 1));

			t1 = tb_mclock();
			while (n1--) tb_bits_set_sbits32(p, b, x, n);
			t1 = tb_int64_sub(tb_mclock(), t1);
			ts = tb_int64_add(ts, t1);

			t2 = tb_mclock();
			while (n2--) y = tb_bits_get_sbits32(p, b, n);
			t2 = tb_int64_sub(tb_mclock(), t2);
			tg = tb_int64_add(tg, t2);

			if (xx != y)
			{
				tb_printf("[bitops]: sbits32 set: b: %d, n: %u, x: %d, %llu ms\n", b, n, xx, t1);
				tb_printf("[bitops]: sbits32 get: b: %u, n: %u, y: %d, %llu ms\n", b, n, y, t2);
			}
		}
	}
	tb_printf("[bitops]: sbits32 set: %llu ms, get: %llu ms\n", ts, tg);
}
static tb_void_t tb_test_bits_u32_be(tb_uint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u32_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u32_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u32_be set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_u32_le(tb_uint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u32_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u32_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u32_le set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_u24_be(tb_uint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u24_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u24_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u24_be set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_u24_le(tb_uint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u24_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u24_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u24_le set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_u16_be(tb_uint16_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint16_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u16_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u16_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u16_be set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_u16_le(tb_uint16_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_uint16_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_u16_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_u16_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: u16_le set: x: %x, %llu ms, get: y: %x, %llu ms\n", x, ts, y, tg);
}

static tb_void_t tb_test_bits_s32_be(tb_sint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s32_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s32_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s32_be set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_s32_le(tb_sint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s32_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s32_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s32_le set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_s24_be(tb_sint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s24_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s24_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s24_be set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_s24_le(tb_sint32_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint32_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s24_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s24_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s24_le set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_s16_be(tb_sint16_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint16_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s16_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s16_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s16_be set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_s16_le(tb_sint16_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_sint16_t y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_s16_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_s16_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: s16_le set: x: %d, %llu ms, get: y: %d, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_double_bbe(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_double_bbe(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_double_bbe(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: double_bbe set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_double_ble(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_double_ble(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_double_ble(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: double_ble set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_double_lbe(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_double_lbe(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_double_lbe(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: double_lbe set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_double_lle(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_double_lle(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_double_lle(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: double_lle set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_float_be(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_float_be(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_float_be(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: float_be set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
static tb_void_t tb_test_bits_float_le(tb_float_t x)
{
	__tb_volatile__ tb_byte_t 	p[8] = {0};
	__tb_volatile__ tb_float_t 	y = 0;
	__tb_volatile__ tb_size_t 	n1 = 10000000;
	__tb_volatile__ tb_size_t 	n2 = 10000000;
	__tb_volatile__ tb_int64_t 	ts = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	tg = TB_INT64_ZERO;
	__tb_volatile__ tb_int64_t 	t1, t2;

	t1 = tb_mclock();
	while (n1--) tb_bits_set_float_le(p, x);
	t1 = tb_int64_sub(tb_mclock(), t1);
	ts = tb_int64_add(ts, t1);

	t2 = tb_mclock();
	while (n2--) y = tb_bits_get_float_le(p);
	t2 = tb_int64_sub(tb_mclock(), t2);
	tg = tb_int64_add(tg, t2);

	tb_printf("[bitops]: float_le set: x: %lf, %llu ms, get: y: %lf, %llu ms\n", x, ts, y, tg);
}
int main(int argc, char** argv)
{
	if (!tb_init(malloc(1024 * 1024), 1024 * 1024)) return 0;

	tb_test_bits_swap_u16();
	tb_test_bits_swap_u32();
	tb_test_bits_swap_u64();

	tb_printf("\n");
	tb_test_bits_ubits32(0x87654321);
	tb_test_bits_ubits32(0x12345678);
	
	tb_printf("\n");
	tb_test_bits_sbits32(0x87654321);
	tb_test_bits_sbits32(0x12345678);

	tb_printf("\n");
	tb_test_bits_sbits32(-300);
	tb_test_bits_sbits32(300);

	tb_printf("\n");
	tb_test_bits_u32_be(0x87654321);
	tb_test_bits_u32_be(0x12345678);

	tb_test_bits_u32_le(0x87654321);
	tb_test_bits_u32_le(0x12345678);

	tb_printf("\n");
	tb_test_bits_u24_be(0x654321);
	tb_test_bits_u24_be(0x345678);

	tb_test_bits_u24_le(0x654321);
	tb_test_bits_u24_le(0x345678);

	tb_printf("\n");
	tb_test_bits_u16_be(0x4321);
	tb_test_bits_u16_be(0x5678);

	tb_test_bits_u16_le(0x4321);
	tb_test_bits_u16_le(0x5678);

	tb_printf("\n");
	tb_test_bits_s32_be(0x8765F321);
	tb_test_bits_s32_be(0x1234F678);

	tb_test_bits_s32_le(0x8765F321);
	tb_test_bits_s32_le(0x1234F678);

	tb_printf("\n");
	tb_test_bits_s24_be(123456);
	tb_test_bits_s24_be(-123456);

	tb_test_bits_s24_le(123456);
	tb_test_bits_s24_le(-123456);

	tb_printf("\n");
	tb_test_bits_s16_be(4321);
	tb_test_bits_s16_be(-4321);

	tb_test_bits_s16_le(4321);
	tb_test_bits_s16_le(-4321);

	tb_printf("\n");
	tb_test_bits_double_bbe(3.1415926);
	tb_test_bits_double_ble(3.1415926);

	tb_test_bits_double_lbe(3.1415926);
	tb_test_bits_double_lle(3.1415926);

	tb_printf("\n");
	tb_test_bits_float_be(3.1415926);
	tb_test_bits_float_le(3.1415926);

	tb_test_bits_float_be(3.1415926);
	tb_test_bits_float_le(3.1415926);

	tb_exit();
	return 0;
}
