#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::tera {

Terrain* Terrain::sInstance;

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
void* Terrain::sub_710114DEE0() { return _360->_f8; }
bool Terrain::sub_710114DD40() { return false; }
f64 Terrain::sub_710114D9E8() { return _a48; }
void* Terrain::sub_710114DED4() { return _360->_f0; }
void* Terrain::sub_710114D8D0() { return _360 ? _360->_168 : nullptr; }
sead::Vector2f Terrain::sub_710114D8E4(const Unk_710114D8E4* params) {
    return params->_10 * _3c8;
}
f32 Terrain::sub_710114D8F8(const Unk_710114D8E4* params) { return params->_18 * _3c8; }

}  // namespace ksys::tera
