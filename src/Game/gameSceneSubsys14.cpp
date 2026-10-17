#include "Game/gameSceneSubsys14.h"
#include "Game/Scene/gameScene.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/StageInfo.h"

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
    mSlot.id = payload->_8;
    mSlot.link.operator=(payload->_10);
    return true;
}

// NON_MATCHING: register allocation (the original keeps the lock address in x21 and the link
// destination in x20 and loads the two unrolled entries with ldp); the structure matches.
int GameSceneSubsys14::handleMessage(const ksys::Message* message) {
    if (!_12e2) {
        if (_1c8.m2(*message)) {
            if (_1c8._38)
                sub_7100904ACC(_1c8._40);
            else
                sub_7100904CA4(_1c8._40);

            u32 mask = 0;
            const s32 count = _f80.size();
            for (s32 i = 0; i < count; ++i)
                mask |= 1 << _f80[i]->_11c;
            _168 = mask;
            return 1;
        }
    }

    if (message->getType() != 0x08830000)
        return 0;

    auto* payload = static_cast<Unk_71024735b0_Payload*>(message->getUserData());
    if (!payload)
        return 1;

    {
        sead::ScopedLock<sead::JobQueueLock> lock(&payload->mLock);
        _340._38 = payload->_0;
        _340.mSlot.id = payload->_8;
        _340.mSlot.link = payload->_10;
    }

    if (_340._38) {
        if (_340.mSlot.id == -1)
            return 1;
        auto* slot = static_cast<Unk_7100903948::Slot*>(mFreeSlots.popBack());
        if (!slot)
            return 1;
        *slot = _340.mSlot;
        mActiveSlots.pushBack(slot);
        mSlotsChanged = true;
    } else {
        sub_7100904DD4(_340.mSlot);
    }
    return 1;
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

// 0x7100903d00: resets the entry / slot tables and reads the saved location name (the current map
// name in a dungeon). Placeholder name.
void GameSceneSubsys14::initCurrentLocation() {
    _12e0 = false;
    mSlotsChanged = false;
    _12e2 = false;
    _12e3 = false;
    _f80.clear();
    _fe0.clear();

    for (auto& entry : mEntries) {
        entry.name.clear();
        entry.id = -1;
        entry._11c = -1;
        entry.link.reset();
        _fe0.pushBack(&entry);
    }

    _38.name.clear();
    _38.id = -1;
    _38._11c = -1;
    _38.link.reset();
    _168 = 0;
    _16c = 0;

    mActiveSlots.clear();
    mFreeSlots.clear();
    for (s32 i = 0; i < 16; ++i) {
        auto& slot = _1040.slots[i];
        slot.id = -1;
        slot.link.reset();
        mFreeSlots.pushBack(&slot);
    }

    if (ksys::StageInfo::sIsCDungeon || ksys::StageInfo::sIsMainFieldDungeon) {
        _12e2 = true;
        const sead::SafeString& name = uking::GameScene::getCurrentMapName();
        _38.name = name;
        ksys::gdt::setFlag_SaveLocationName(name, false);
        return;
    }

    const char* saved = nullptr;
    ksys::gdt::getFlag_SaveLocationName(&saved, false);
    if (saved && _38.name.getStringTop() != saved)
        _38.name = saved;
    _12e0 = true;
}

void GameSceneSubsys14::postCalc() {
    if (uking::ui::Manager::instance()->isPausedMaybe())
        return;
    if (!_12e2) {
        if (sub_7100904128())
            _12e0 = true;
        if (_12e0)
            sub_7100904274();
    }
    if (sub_7100904704())
        mSlotsChanged = true;
    else if (!mSlotsChanged)
        return;

    u32 flags = 0;
    const s32 count = mActiveSlots.size();
    for (s32 i = 0; i < count; ++i) {
        const u32 id = mActiveSlots[i]->id;
        flags |= id < 9 ? 1 << id : 0;
    }
    _16c = flags;
    mSlotsChanged = false;
}

void GameSceneSubsys14::sub_7100904ACC(const Unk_GameSceneSubsys14Entry& entry) {
    // `entry.name.isEmpty()`: the original inlines the check against cNullChar.
    if (entry.name.getStringTop()[0] == sead::SafeStringBase<char>::cNullChar)
        return;

    const int count = _f80.size();
    for (int i = 0; i < count; ++i) {
        if (_f80[i]->link == entry.link)
            return;
    }

    auto* dst = static_cast<Unk_GameSceneSubsys14Entry*>(_fe0.popBack());
    if (!dst)
        return;

    dst->name = entry.name;
    dst->id = entry.id;
    dst->_11c = entry._11c;
    // C++14 evaluation order: the original evaluates the destination first.
    dst->link.operator=(entry.link);
    if (dst->_11c == 0x2b)
        dst->_11c = 0x11;
    _f80.pushBack(dst);
    _12e0 = true;
}

void GameSceneSubsys14::sub_7100904CA4(const Unk_GameSceneSubsys14Entry& entry) {
    const int count = _f80.size();
    for (int i = 0; i < count; ++i) {
        if (!(_f80[i]->link == entry.link))
            continue;
        auto* e = _f80[i];
        e->name.clear();
        e->id = -1;
        e->_11c = -1;
        e->link.reset();
        _fe0.pushBack(_f80[i]);
        _f80.erase(i);
        _12e0 = true;
        return;
    }
}

// 0x7100904128 (placeholder name): removes every entry of _f80 whose link lost its proc (clearing the
// entry and returning it to _fe0); true if any was removed.
bool GameSceneSubsys14::sub_7100904128() {
    bool changed = false;
    int count = _f80.size();
    if (count < 1)
        return false;
    for (int i = 0; i < count;) {
        if (_f80[i]->link.hasProc()) {
            ++i;
            continue;
        }
        auto* e = _f80[i];
        e->name.clear();
        e->id = -1;
        e->_11c = -1;
        e->link.reset();
        _fe0.pushBack(_f80[i]);
        _f80.erase(i);
        count = _f80.size();
        changed = true;
    }
    return changed;
}

void GameSceneSubsys14::init() {
    initCurrentLocation();
}

void GameSceneSubsys14::sub_7100904DD4(const Unk_7100903948::Slot& slot) {
    const int count = mActiveSlots.size();
    for (int i = 0; i < count; ++i) {
        if (mActiveSlots[i]->id != slot.id || !(mActiveSlots[i]->link == slot.link))
            continue;
        auto* active = mActiveSlots(i);
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
