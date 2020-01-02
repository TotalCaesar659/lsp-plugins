/*
 * op_vv.h
 *
 *  Created on: 28 нояб. 2019 г.
 *      Author: sadko
 */

#ifndef DSP_ARCH_X86_AVX_PMATH_OP_VV_H_
#define DSP_ARCH_X86_AVX_PMATH_OP_VV_H_

#ifndef DSP_ARCH_X86_AVX_IMPL
    #error "This header should not be included directly"
#endif /* DSP_ARCH_X86_AVX_IMPL */

namespace avx
{
#define OP_VV_CORE(DST, SRC1, SRC2, OP) \
    __ASM_EMIT("xor         %[off], %[off]") \
    __ASM_EMIT("sub         $64, %[count]") \
    __ASM_EMIT("jb          2f")    \
    /* 64x blocks */ \
    __ASM_EMIT("1:") \
    __ASM_EMIT("vmovups     0x000(%[" SRC1 "], %[off]), %%ymm0") \
    __ASM_EMIT("vmovups     0x020(%[" SRC1 "], %[off]), %%ymm1") \
    __ASM_EMIT("vmovups     0x040(%[" SRC1 "], %[off]), %%ymm2") \
    __ASM_EMIT("vmovups     0x060(%[" SRC1 "], %[off]), %%ymm3") \
    __ASM_EMIT("vmovups     0x080(%[" SRC1 "], %[off]), %%ymm4") \
    __ASM_EMIT("vmovups     0x0a0(%[" SRC1 "], %[off]), %%ymm5") \
    __ASM_EMIT("vmovups     0x0c0(%[" SRC1 "], %[off]), %%ymm6") \
    __ASM_EMIT("vmovups     0x0e0(%[" SRC1 "], %[off]), %%ymm7") \
    __ASM_EMIT(OP "ps       0x000(%[" SRC2 "], %[off]), %%ymm0, %%ymm0") \
    __ASM_EMIT(OP "ps       0x020(%[" SRC2 "], %[off]), %%ymm1, %%ymm1") \
    __ASM_EMIT(OP "ps       0x040(%[" SRC2 "], %[off]), %%ymm2, %%ymm2") \
    __ASM_EMIT(OP "ps       0x060(%[" SRC2 "], %[off]), %%ymm3, %%ymm3") \
    __ASM_EMIT(OP "ps       0x080(%[" SRC2 "], %[off]), %%ymm4, %%ymm4") \
    __ASM_EMIT(OP "ps       0x0a0(%[" SRC2 "], %[off]), %%ymm5, %%ymm5") \
    __ASM_EMIT(OP "ps       0x0c0(%[" SRC2 "], %[off]), %%ymm6, %%ymm6") \
    __ASM_EMIT(OP "ps       0x0e0(%[" SRC2 "], %[off]), %%ymm7, %%ymm7") \
    __ASM_EMIT("vmovups     %%ymm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm1, 0x020(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm2, 0x040(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm3, 0x060(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm4, 0x080(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm5, 0x0a0(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm6, 0x0c0(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm7, 0x0e0(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x100, %[off]") \
    __ASM_EMIT("sub         $64, %[count]") \
    __ASM_EMIT("jae         1b") \
    /* 32x block */ \
    __ASM_EMIT("2:") \
    __ASM_EMIT("add         $32, %[count]") \
    __ASM_EMIT("jl          4f") \
    __ASM_EMIT("vmovups     0x000(%[" SRC1 "], %[off]), %%ymm0") \
    __ASM_EMIT("vmovups     0x020(%[" SRC1 "], %[off]), %%ymm1") \
    __ASM_EMIT("vmovups     0x040(%[" SRC1 "], %[off]), %%ymm2") \
    __ASM_EMIT("vmovups     0x060(%[" SRC1 "], %[off]), %%ymm3") \
    __ASM_EMIT(OP "ps       0x000(%[" SRC2 "], %[off]), %%ymm0, %%ymm0") \
    __ASM_EMIT(OP "ps       0x020(%[" SRC2 "], %[off]), %%ymm1, %%ymm1") \
    __ASM_EMIT(OP "ps       0x040(%[" SRC2 "], %[off]), %%ymm2, %%ymm2") \
    __ASM_EMIT(OP "ps       0x060(%[" SRC2 "], %[off]), %%ymm3, %%ymm3") \
    __ASM_EMIT("vmovups     %%ymm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm1, 0x020(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm2, 0x040(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm3, 0x060(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x80, %[off]") \
    __ASM_EMIT("sub         $32, %[count]") \
    /* 16x block */ \
    __ASM_EMIT("4:") \
    __ASM_EMIT("add         $16, %[count]") \
    __ASM_EMIT("jl          6f") \
    __ASM_EMIT("vmovups     0x000(%[" SRC1 "], %[off]), %%ymm0") \
    __ASM_EMIT("vmovups     0x020(%[" SRC1 "], %[off]), %%ymm1") \
    __ASM_EMIT(OP "ps       0x000(%[" SRC2 "], %[off]), %%ymm0, %%ymm0") \
    __ASM_EMIT(OP "ps       0x020(%[" SRC2 "], %[off]), %%ymm1, %%ymm1") \
    __ASM_EMIT("vmovups     %%ymm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("vmovups     %%ymm1, 0x020(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x40, %[off]") \
    __ASM_EMIT("sub         $16, %[count]") \
    /* 8x block */ \
    __ASM_EMIT("6:") \
    __ASM_EMIT("add         $8, %[count]") \
    __ASM_EMIT("jl          8f") \
    __ASM_EMIT("vmovups     0x000(%[" SRC1 "], %[off]), %%ymm0") \
    __ASM_EMIT(OP "ps       0x000(%[" SRC2 "], %[off]), %%ymm0, %%ymm0") \
    __ASM_EMIT("vmovups     %%ymm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x20, %[off]") \
    __ASM_EMIT("sub         $8, %[count]") \
    /* 4x block */ \
    __ASM_EMIT("8:") \
    __ASM_EMIT("add         $4, %[count]") \
    __ASM_EMIT("jl          10f") \
    __ASM_EMIT("vmovups     0x000(%[" SRC1 "], %[off]), %%xmm0") \
    __ASM_EMIT(OP "ps       0x000(%[" SRC2 "], %[off]), %%xmm0, %%xmm0") \
    __ASM_EMIT("vmovups     %%xmm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x10, %[off]") \
    __ASM_EMIT("sub         $4, %[count]") \
    \
    /* 1x blocks */ \
    __ASM_EMIT("10:") \
    __ASM_EMIT("add         $3, %[count]")          /* 8 - 4 */ \
    __ASM_EMIT("jl          12f") \
    __ASM_EMIT("11:") \
    __ASM_EMIT("vmovss      0x000(%[" SRC1 "], %[off]), %%xmm0") \
    __ASM_EMIT(OP "ss       0x000(%[" SRC2 "], %[off]), %%xmm0, %%xmm0") \
    __ASM_EMIT("vmovss      %%xmm0, 0x000(%[" DST "], %[off])") \
    __ASM_EMIT("add         $0x04, %[off]") \
    __ASM_EMIT("dec         %[count]") \
    __ASM_EMIT("jge         11b") \
    __ASM_EMIT("12:")

    void add2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "dst", "src", "vadd")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void sub2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "dst", "src", "vsub")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void rsub2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src", "dst", "vsub")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void mul2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "dst", "src", "vmul")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void div2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "dst", "src", "vdiv")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void rdiv2(float *dst, const float *src, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src", "dst", "vdiv")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src] "r" (src)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void add3(float *dst, const float *src1, const float *src2, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src1", "src2", "vadd")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src1] "r" (src1), [src2] "r" (src2)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void sub3(float *dst, const float *src1, const float *src2, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src1", "src2", "vsub")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src1] "r" (src1), [src2] "r" (src2)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void mul3(float *dst, const float *src1, const float *src2, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src1", "src2", "vmul")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src1] "r" (src1), [src2] "r" (src2)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    void div3(float *dst, const float *src1, const float *src2, size_t count)
    {
        IF_ARCH_X86(size_t off);
        ARCH_X86_ASM
        (
            OP_VV_CORE("dst", "src1", "src2", "vdiv")
            : [off] "=&r" (off), [count] "+r" (count)
            : [dst] "r" (dst), [src1] "r" (src1), [src2] "r" (src2)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3",
              "%xmm4", "%xmm5", "%xmm6", "%xmm7"
        );
    }

    #undef OP_VV_CORE
}

#endif /* DSP_ARCH_X86_AVX_PMATH_OP_VV_H_ */