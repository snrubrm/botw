#include "KingSystem/Sound/sndOcclusionMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// Whole 1056A68 reads this writable float; native initial bits are 3e4ccccd.
KSYS_VISIBILITY_HIDDEN f32 sUnk_710250294C = 0.2f;

f32 OcclusionMgr::sub_7101056A4C() const {
    return _24 == 3 ? _20 : _1c;
}

// NON_MATCHING: the global float access has an extra GOT load and different register allocation.
f32 OcclusionMgr::sub_7101056A68() const {
    return _24 == 2 ? sUnk_710250294C : 0.0f;
}

void OcclusionMgr::sub_71010560D4(sead::Heap* heap) {}

void OcclusionMgr::sub_7101056868() {
    _74 = true;
    _7c = 2;
}

// NON_MATCHING: only the schedule of the constant stores (the original stores the vtable pointer and the pair at +0x20 after
// the first group of members).
OcclusionMgr::OcclusionMgr() = default;

OcclusionMgr::~OcclusionMgr() {
    if (_28) {
        delete _28;
        _28 = nullptr;
    }
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
    if (_80) {
        delete _80;
        _80 = nullptr;
    }
}

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x71010576a8) also destroys members or bases
// this class does not declare yet.
Unk_7102502978::~Unk_7102502978() = default;

void Unk_7102502978::sub_7101057588(const sead::SafeString& name) {
    mFileName.copy(name);
    mAudioResource->setFilename(&mFileName);
}

// NON_MATCHING: placeholder destructor; the original (0x7101059518) also destroys members or bases
// this class does not declare yet.
Unk_7102502b50::~Unk_7102502b50() = default;
