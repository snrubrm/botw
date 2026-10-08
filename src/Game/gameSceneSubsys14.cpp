#include "Game/gameSceneSubsys14.h"

// 0x710090325c. `.operator=(...)` for the link: C++14 evaluation order: the original evaluates the
// destination first.
bool Unk_7102473580::m2(const ksys::Message& message) {
    if (message.getType() != 0x8000082)
        return false;

    auto* payload = static_cast<Unk_7102473580_Payload*>(message.getUserData());
    if (!payload)
        return false;

    sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
    _38 = payload->_0;
    _40.name = payload->entry.name;
    _40.id = payload->entry.id;
    _40._11c = payload->entry._11c;
    _40.link.operator=(payload->entry.link);
    return true;
}

// 0x7100903408. `.operator=(...)` instead of `a = b`: C++14 evaluation order: the original evaluates
// the destination first.
bool Unk_71024735b0::m2(const ksys::Message& message) {
    if (message.getType() != 0x8000083)
        return false;

    auto* payload = static_cast<Unk_71024735b0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
    _38 = payload->_0;
    _40 = payload->_8;
    _48.operator=(payload->_10);
    return true;
}

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys14)

// NON_MATCHING: the members now have the layout of the original, but the library's FixedSafeString<256> constructor
// differs from the original's (which clears the buffer with memset after assureTerminationImpl_()), 12 times here.
GameSceneSubsys14::GameSceneSubsys14() = default;

GameSceneSubsys14::~GameSceneSubsys14() = default;

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
