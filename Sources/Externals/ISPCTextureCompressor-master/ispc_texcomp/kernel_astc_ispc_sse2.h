//
// D:\projects\tix2\Sources\Externals\ISPCTextureCompressor-master\ispc_texcomp\kernel_astc_ispc_sse2.h
// (Header automatically generated by the ispc compiler.)
// DO NOT EDIT THIS FILE.
//

#ifndef ISPC_D__PROJECTS_TIX2_SOURCES_EXTERNALS_ISPCTEXTURECOMPRESSOR_MASTER_ISPC_TEXCOMP_KERNEL_ASTC_ISPC_SSE2_H
#define ISPC_D__PROJECTS_TIX2_SOURCES_EXTERNALS_ISPCTEXTURECOMPRESSOR_MASTER_ISPC_TEXCOMP_KERNEL_ASTC_ISPC_SSE2_H

#include <stdint.h>



#ifdef __cplusplus
namespace ispc { /* namespace */
#endif // __cplusplus

#ifndef __ISPC_ALIGN__
#if defined(__clang__) || !defined(_MSC_VER)
// Clang, GCC, ICC
#define __ISPC_ALIGN__(s) __attribute__((aligned(s)))
#define __ISPC_ALIGNED_STRUCT__(s) struct __ISPC_ALIGN__(s)
#else
// Visual Studio
#define __ISPC_ALIGN__(s) __declspec(align(s))
#define __ISPC_ALIGNED_STRUCT__(s) __ISPC_ALIGN__(s) struct
#endif
#endif

#ifndef __ISPC_STRUCT_rgba_surface__
#define __ISPC_STRUCT_rgba_surface__
struct rgba_surface {
    uint8_t * ptr;
    int32_t width;
    int32_t height;
    int32_t stride;
};
#endif

#ifndef __ISPC_STRUCT_astc_enc_context__
#define __ISPC_STRUCT_astc_enc_context__
struct astc_enc_context {
    int32_t width;
    int32_t height;
    int32_t channels;
    bool dual_plane;
    int32_t partitions;
    int32_t color_endpoint_pairs;
};
#endif

#ifndef __ISPC_STRUCT_astc_enc_settings__
#define __ISPC_STRUCT_astc_enc_settings__
struct astc_enc_settings {
    int32_t block_width;
    int32_t block_height;
    int32_t channels;
    int32_t fastSkipTreshold;
    int32_t refineIterations;
};
#endif

#ifndef __ISPC_STRUCT_astc_block__
#define __ISPC_STRUCT_astc_block__
struct astc_block {
    int32_t width;
    int32_t height;
    bool dual_plane;
    int32_t weight_range;
    uint8_t weights[64];
    int32_t color_component_selector;
    int32_t partitions;
    int32_t partition_id;
    int32_t color_endpoint_pairs;
    int32_t channels;
    int32_t color_endpoint_modes[4];
    int32_t endpoint_range;
    uint8_t endpoints[18];
};
#endif


///////////////////////////////////////////////////////////////////////////
// Functions exported from ispc code
///////////////////////////////////////////////////////////////////////////
#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
extern "C" {
#endif // __cplusplus
    extern void astc_encode_ispc(struct rgba_surface * src, float * block_scores, uint8_t * dst, uint64_t * list, struct astc_enc_context * list_context, struct astc_enc_settings * settings);
    extern void astc_rank_ispc(struct rgba_surface * src, int32_t xx, int32_t yy, uint32_t * mode_buffer, struct astc_enc_settings * settings);
    extern int32_t get_programCount();
#if defined(__cplusplus) && (! defined(__ISPC_NO_EXTERN_C) || !__ISPC_NO_EXTERN_C )
} /* end extern C */
#endif // __cplusplus


#ifdef __cplusplus
} /* namespace */
#endif // __cplusplus

#endif // ISPC_D__PROJECTS_TIX2_SOURCES_EXTERNALS_ISPCTEXTURECOMPRESSOR_MASTER_ISPC_TEXCOMP_KERNEL_ASTC_ISPC_SSE2_H
