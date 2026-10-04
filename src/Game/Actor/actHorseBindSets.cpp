#include "Game/Actor/actHorseBindSets.h"

namespace uking::act {

Unk_71024e8e18::Unk_71024e8e18() : ActorBindSet(12, mStorage) {}

Unk_71024e8e18::~Unk_71024e8e18() {
    mEntries = nullptr;
}

Unk_71024e92c0::Unk_71024e92c0() : ActorBindSet(20, mStorage) {}

Unk_71024e92c0::~Unk_71024e92c0() {
    mEntries = nullptr;
}

Unk_71024e9710::Unk_71024e9710() : ActorBindSet(36, mStorage) {}

bool Unk_71024e9450::m5(ksys::act::BaseProc* proc) {
    return false;
}

}  // namespace uking::act
