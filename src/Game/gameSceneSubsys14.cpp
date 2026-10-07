#include "Game/gameSceneSubsys14.h"

bool GameSceneSubsys14::sub_7100904ED4() const {
    return _168 & 1;
}

bool GameSceneSubsys14::sub_7100904EE0() const {
    return _168 & 0x20004;
}

bool GameSceneSubsys14::sub_7100904EF8() const {
    return _16c & 1;
}

bool GameSceneSubsys14::sub_7100904F04() const {
    return _16c >> 1 & 1;
}

bool GameSceneSubsys14::sub_7100904F10() const {
    return _16c >> 2 & 1;
}

bool GameSceneSubsys14::sub_7100904F1C() const {
    return _16c >> 3 & 1;
}

bool GameSceneSubsys14::sub_7100904F28() const {
    return _16c >> 4 & 1;
}

bool GameSceneSubsys14::sub_7100904F34() const {
    return _16c >> 5 & 1;
}

bool GameSceneSubsys14::sub_7100904F40() const {
    return _16c >> 6 & 1;
}

bool GameSceneSubsys14::sub_7100904F4C() const {
    return (_16c >> 7 & 1) || (_168 & 1);
}

bool GameSceneSubsys14::sub_7100904F68() const {
    return _16c >> 8 & 1;
}

Unk_7100903948::Unk_7100903948() = default;

Unk_7100903948::~Unk_7100903948() = default;

void GameSceneSubsys14::init() {
    initCurrentLocation();
}

// NON_MATCHING: the active slot lookup retains an additional checked-array access.
void GameSceneSubsys14::sub_7100904DD4(const Unk_7100903948::Slot& slot) {
    const int count = mActiveSlots.size();
    for (int i = 0; i < count; ++i) {
        if (mActiveSlots[i]->id != slot.id || !(mActiveSlots[i]->link == slot.link))
            continue;
        auto* active = mActiveSlots[i];
        active->id = -1;
        active->link.reset();
        mFreeSlots.pushBack(mActiveSlots[i]);
        mActiveSlots.erase(i);
        mSlotsChanged = true;
        return;
    }
}

// NON_MATCHING: the active slot lookup retains an additional checked-array access.
bool GameSceneSubsys14::sub_7100904704() {
    bool changed = false;
    int count = mActiveSlots.size();
    for (int i = 0; i < count;) {
        if (mActiveSlots[i]->link.hasProc()) {
            ++i;
            continue;
        }
        auto* slot = mActiveSlots[i];
        slot->id = -1;
        slot->link.reset();
        mFreeSlots.pushBack(mActiveSlots[i]);
        mActiveSlots.erase(i);
        count = mActiveSlots.size();
        changed = true;
    }
    return changed;
}
