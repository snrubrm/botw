#include "KingSystem/Sound/sndOcclusionMgr.h"

namespace ksys::snd {

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
