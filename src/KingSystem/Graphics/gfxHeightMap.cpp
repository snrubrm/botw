#include "Game/gameGraphics.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadPtrUtil.h>
#include <cstring>

// NON_MATCHING: sampler indexing and the clamp/interpolation loads are scheduled differently.
bool Graphics::Unk_ab0::sub_7100F29EB4(f32* height, const sead::Vector2f& pos) {
    const sead::Vector2f relative = pos - mMapCenter;
    const f32 inv_size = 1.0f / mMapSize;
    f32 u = relative.x * inv_size + 0.5f;
    f32 v = relative.y * inv_size + 0.5f;
    const u32 sampler_index = 1 - mCurrentSampler;
    const auto& texture = mSamplers[1 + sampler_index].getTextureData();
    const auto* pixels = static_cast<const u8*>(texture.getImagePtr().getAddress());
    const f32 size = static_cast<f32>(sead::Mathu::max(texture.getWidth(), 1));
    const s32 stride = texture.getSurface_1c();
    const f32 half_texel = 0.5f / size;
    bool clamped = false;
    if (u < half_texel) {
        u = half_texel;
        clamped = true;
    } else if (u > 1.0f - half_texel) {
        u = 1.0f - half_texel;
        clamped = true;
    }
    if (v < half_texel) {
        v = half_texel;
        clamped = true;
    } else if (v > 1.0f - half_texel) {
        v = 1.0f - half_texel;
        clamped = true;
    }
    const f32 x = size * (u - half_texel);
    const f32 y = size * (v - half_texel);
    const s32 ix = s32(x);
    const s32 iy = s32(y);
    const s32 next_x = s32(sead::Mathf::min(static_cast<f32>(ix) + 1.0f, size - 1.0f));
    const s32 next_y = s32(sead::Mathf::min(static_cast<f32>(iy) + 1.0f, size - 1.0f));
    const f32 dx = x - static_cast<f32>(ix);
    const f32 dy = y - static_cast<f32>(iy);
    // Native sampling reads each u16 as two bytes; the mapped image has byte alignment.
    const auto sample = [pixels, stride](s32 col, s32 row) {
        u16 value;
        std::memcpy(&value, sead::PtrUtil::addOffset(pixels, u32(row * stride + col * 2)),
                    sizeof(value));
        return static_cast<f32>(value) / 65535.0f;
    };
    const f32 a = sample(ix, iy);
    const f32 b = sample(next_x, iy);
    const f32 c = sample(ix, next_y);
    const f32 d = sample(next_x, next_y);
    const f32 top = a + dx * (b - a);
    const f32 bottom = c + dx * (d - c);
    *height = mHeightScale * (1.0f - (top + dy * (bottom - top)));
    _e48 |= 0x100;
    return clamped;
}
