#include <math/seadMathCalcCommon.h>
#include "KingSystem/World/worldWindMgr.h"
#include <cstring>
#include <limits>
#include <prim/seadBitUtil.h>
#include <prim/seadPtrUtil.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <common/aglTextureDataInitializerRAW.h>
#include <g3d/aglTextureUtilG3D.h>
#include <common/aglTextureData.h>
#include <common/aglGPUMemBlock.h>

namespace ksys::world {

// 0x7102660d10 (placeholder name): two 64-entry tables cleared by the render-wind constructor;
// hidden visibility keeps the loads direct without folding them.
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102660D10[2][64];

// NON_MATCHING: the two adjacent table clears merge into one memset.
Unk_710251F868::Unk_710251F868()
    : _8(0.0f), _c(0.0f), _10(4800.0f), _18(1280), _1c(16), _20(1280), _24(16),
      _40(nullptr), _258(65.5f), _25c(0.07f), _260(0.062f), _264(0.5f) {
    std::memset(sUnk_7102660D10[0], 0, sizeof(sUnk_7102660D10[0]));
    std::memset(sUnk_7102660D10[1], 0, sizeof(sUnk_7102660D10[1]));
}

// NON_MATCHING: the existing TextureData destructor remains an out-of-line call.
Unk_710251F868::~Unk_710251F868() {
    if (_40) {
        _28.deleteGPUMemBlock();
        delete _40;
        _40 = nullptr;
        _28.invalidate();
    }
}

// NON_MATCHING: GPU address assignment and texture allocation use different temporary scheduling.
void Unk_710251F868::sub_71012FEAA8(sead::Heap* heap) {
    _c = 0.0f;
    _18 = 320;
    _1c = 64;
    _20 = 320;
    _24 = 64;
    _40 = new (heap, 8) agl::TextureData;
    _40->initialize_(agl::TextureType::cTextureType_2D, agl::TextureFormat::cTextureFormat_R16_float,
                     _18, _1c, 1, 1, agl::TextureAttribute{}, agl::MultiSampleType{}, true);
    const u32 alignment = _40->getImageAlignment();
    const u32 size = _40->getImageByteSize();
    auto* memory = new (heap, 8) agl::GPUMemBlock<u8>;
    memory->allocBuffer_(size, heap, alignment, agl::MemoryAttribute::Default);
    _28 = agl::GPUMemAddrBase(*memory, 0);
    _40->setImagePtr(_28, 0);
    std::memset(&_1b8, 0, sizeof(_1b8));
    sub_71012FEBE4();
}

// NON_MATCHING: loop temporaries and half-float case selection differ.
void Unk_710251F868::sub_71012FEBE4() {
    if (s32(_20) > s32(_18))
        _20 = _18;
    if (s32(_24) > s32(_1c))
        _24 = _1c;
    _40->initialize_(agl::TextureType::cTextureType_2D, agl::TextureFormat::cTextureFormat_R16_float,
                     _20, _24, 1, 1, agl::TextureAttribute{}, agl::MultiSampleType{}, true);
    void* mapped = _28.isValid() ? nvnMemoryPoolMap(_28.getMemoryPool()->getDriverPool()) : nullptr;
    auto* pixels = static_cast<u16*>(sead::PtrUtil::addOffset(mapped, _28.getByteOffset()));
    for (u32 y = 0; s32(y) < s32(_24); ++y) {
        f32 minimum = std::numeric_limits<f32>::max();
        f32 maximum = -std::numeric_limits<f32>::max();
        if (s32(_20) > 0) {
            const f32 t = f32(y) / f32(_24);
            const f32 envelope = sead::Mathf::clamp(2.0f * sead::Mathf::min(t, 1.0f - t),
                                                   0.0f, 1.0f);
            const f32 high = sead::Mathf::clamp(t - 0.3f, 0.0f, 1.0f) / 0.7f;
            for (u32 x = 0; s32(x) < s32(_20); ++x) {
                const f32 phase = f32(x) / f32(_20) * 6.2831855f;
                const f32 cos2 = sead::Mathf::cos(phase + phase);
                const f32 cos3 = sead::Mathf::cos(phase * 3.0f);
                const f32 cos5 = sead::Mathf::cos(phase * 5.0f);
                const f32 sin3 = sead::Mathf::sin(phase * 3.0f);
                const f32 sin5 = sead::Mathf::sin(phase * 5.0f);
                const f32 sin7 = sead::Mathf::sin(phase * 7.0f);
                const f32 value = (envelope * (1.0f - envelope * cos2 * cos3 * cos5) *
                                   0.23333333f + high * (high * 0.6f * sin3 * sin5 * sin7 + 1.0f)) *
                                  0.3f;
                // The texture conversion truncates the mantissa, flushes half subnormals,
                // saturates overflow, and preserves the distinction between quiet/signaling NaNs.
                const u32 bits = sead::BitUtil::bitCast<u32>(value);
                const u32 sign = (bits >> 16) & 0x8000;
                const u32 exponent_bits = bits & 0x7f800000;
                const u32 mantissa = bits & 0x7fffff;
                const s32 exponent = s32(exponent_bits >> 23) - 0x70;
                u32 half = sign | ((bits >> 13) & 0x3ff) | ((u32(exponent) & 0x1f) << 10);
                if (exponent_bits <= 0x38000000)
                    half = sign;
                if (exponent > 30)
                    half = sign | 0x7c00;
                if (exponent_bits == 0x7f800000) {
                    if (mantissa == 0)
                        half = sign | 0x7c00;
                    else if (mantissa >> 22)
                        half = sign | 0x7fff;
                    else
                        half = sign | 0x7dff;
                }
                *pixels++ = u16(half);
                minimum = minimum < value ? minimum : value;
                maximum = maximum > value ? maximum : value;
            }
        }
        sUnk_7102660D10[0][y] = minimum;
        sUnk_7102660D10[1][y] = maximum;
    }
    agl::TextureDataInitializerRAW::initialize(_40, _28, _40->getImageByteSize(),
                                             _40->getFormat(), s32(_20), s32(_24), nullptr);
    _28.flushCPUCache(_40->getImageByteSize());
    _48.applyTextureData(*_40);
    _48.setWrap(1, 6, 1);
    _48.setFilter(1, 1, 1);
    agl::g3d::TextureUtilG3D::convertToResTexture(&_1b8, *_40, nullptr);
}

void Unk_710251F868::sub_71012FEFF0(f32 delta) {
    _c += delta;
    if (_c >= _10 + _10)
        _c -= _10 + _10;
    _8 = _c / _10;
}

// NON_MATCHING: trigonometric result registers and table-index scheduling differ.
f32 Unk_710251F868::sub_71012FF01C(const sead::Vector3f* position,
                                   const sead::Vector2f* direction, f32 strength, f32 value) const {
    const f32 phase = (((value * 1.56985867f + _8 * 313.97174f) -
                        direction->x * position->x) - direction->y * position->y) *
                      0.022295f * 6.2831855f;
    const f32 envelope = sead::Mathf::clamp(2.0f * sead::Mathf::min(strength, 1.0f - strength),
                                          0.0f, 1.0f);
    const f32 high_strength = sead::Mathf::clamp(strength - 0.3f, 0.0f, 1.0f);
    const f32 cos2 = sead::Mathf::cos(phase + phase);
    const f32 cos3 = sead::Mathf::cos(phase * 3.0f);
    const f32 cos5 = sead::Mathf::cos(phase * 5.0f);
    const f32 sin3 = sead::Mathf::sin(phase * 3.0f);
    const f32 sin5 = sead::Mathf::sin(phase * 5.0f);
    const f32 sin7 = sead::Mathf::sin(phase * 7.0f);
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    const f32 lower = sUnk_7102660D10[0][s32(t * 63.0f)] / 0.619999766f;
    const f32 upper = sUnk_7102660D10[1][s32(t * 63.0f)] / 0.619999766f;
    const f32 range = upper - lower;
    if (range <= 0.01f)
        return 1.0f;
    const f32 high = high_strength / 0.7f;
    const f32 sample = ((envelope * (1.0f - envelope * cos2 * cos3 * cos5) * 0.23333333f +
                         high * (high * 0.6f * sin3 * sin5 * sin7 + 1.0f)) * 0.3f) /
                       0.619999766f;
    return (sead::Mathf::max(sample, 0.0f) - lower) / range;
}

f32 Unk_710251F868::sub_71012FF268(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[0][s32(t * 63.0f)] / 0.619999766f;
}

f32 Unk_710251F868::sub_71012FF2B0(f32 strength) {
    const f32 t = sead::Mathf::clamp(strength, 0.0f, 1.0f);
    return sUnk_7102660D10[1][s32(t * 63.0f)] / 0.619999766f;
}

}  // namespace ksys::world
