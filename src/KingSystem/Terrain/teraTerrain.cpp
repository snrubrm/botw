#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

Terrain* Terrain::sInstance;

// NON_MATCHING: the SDK Matrix44 assignment copies scalar elements; the original copies rows.
// The flag selection also has different temporary allocation.
void Terrain::sub_710114D804(bool enabled, const sead::Matrix44f* projection,
                           const sead::Matrix34f* view) {
    if (enabled)
        _a58 |= 0x1000;
    else
        _a58 &= ~0x1000;
    mProjectionMatrix = *projection;
    mViewMatrix = *view;
}

void Terrain::sub_710114DDF8(u32 index, const sead::Vector3f* position, bool update) {
    _360->sub_7101300B4C(index, position, update);
}

void Terrain::sub_710114DE04(u32 index, const sead::Vector3f* position, bool update) {
    _360->sub_7101300F1C(index, position, update);
}

void Terrain::setPauseState(bool paused) {
    _a58 = paused ? _a58 | 8 : _a58 & ~u32(8);
    auto* grass = _360->_138;
    grass->mFlags = paused ? grass->mFlags | 0x10000 : grass->mFlags & ~u32(0x10000);
}

s32 Terrain::sub_710114DD84(s32 index) { return _360->mStates[index].mIndex; }

void Terrain::sub_710114DDA4(const Core::Unk_71013010d4* states, u32 count) {
    for (u32 i = 0; i < count; ++i)
        _360->sub_71013010D4(states[i], i);
}

Core::Grass* Terrain::sub_710114DE4C() { return _360->_138; }
Core::Grass* Terrain::sub_710114DE58() { return _360->_138; }
void* Terrain::sub_710114DE64() { return _360->_140; }
void* Terrain::sub_710114DE70() { return _360->_140; }
// NON_MATCHING: the compiler orders the AND before the OR; the original orders them oppositely.
void Terrain::sub_710114DE7C(bool value) {
    if (value)
        _360->_37c |= 1;
    else
        _360->_37c &= ~1;
}
bool Terrain::sub_710114DE9C() { return (_360->_37c & 1) != 0; }
gsys::Model* Terrain::sub_710114DEE0() { return _360->_f8; }
bool Terrain::sub_710114DD40() { return false; }
f64 Terrain::sub_710114D9E8() { return _a48; }
void* Terrain::sub_710114DED4() { return _360->_f0; }
void* Terrain::sub_710114D8D0() { return _360 ? _360->_168 : nullptr; }
sead::Vector2f Terrain::sub_710114D8E4(const Unk_710114D8E4* params) {
    return params->_10 * _3c8;
}
f32 Terrain::sub_710114D8F8(const Unk_710114D8E4* params) { return params->_18 * _3c8; }

}  // namespace ksys::tera
