#include "Game/gameEventCounter.h"
#include <mc/seadCoreInfo.h>
#include "KingSystem/GameData/gdtManager.h"

Unk_7102518b60::Unk_7102518b60() {
    mCount = 0;
    for (auto& count : mPendingCounts)
        count = 0;
}

// The body keeps the native vtable store, as in upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
Unk_7102518b60::~Unk_7102518b60() { ; }

void Unk_7102518b60::sub_710127F594() {
    if (mActorName.isEmpty())
        return;
    s32 pending = 0;
    for (const auto count : mPendingCounts)
        pending += count;
    if (pending == 0)
        return;
    if (!ksys::gdt::Manager::instance()->setS32(mCount + pending, mGameDataName) &&
        !ksys::gdt::Manager::instance()->setS32NoCheck(mCount + pending, mGameDataName))
        return;
    for (auto& count : mPendingCounts)
        count = 0;
    mCount += pending;
}

bool Unk_7102518b60::sub_710127F648() const {
    return mActorName.isEmpty();
}

void Unk_7102518b60::sub_710127F668(s16 value) {
    mPendingCounts[sead::CoreInfo::getCurrentCoreId()] += value;
}

void Unk_7102518b60::sub_710127F6C8() {
    mActorName.clear();
    mGameDataName.clear();
    for (auto& count : mPendingCounts)
        count = 0;
    mCount = 0;
}

bool Unk_7102518b60::sub_710127F6F4(const sead::SafeString& actor_name,
                                 const sead::SafeString& game_data_name, bool initialize) {
    if (!mActorName.isEmpty())
        return false;
    mGameDataName.clear();
    for (auto& count : mPendingCounts)
        count = 0;
    mCount = 0;
    if (initialize) {
        if (!ksys::gdt::Manager::instance()->setS32(0, game_data_name) &&
            !ksys::gdt::Manager::instance()->setS32NoCheck(0, game_data_name))
            return false;
    } else if (!ksys::gdt::Manager::instance()->getParam().get().getS32(&mCount, game_data_name)) {
        return false;
    }
    mActorName.copy(actor_name);
    mGameDataName.copy(game_data_name);
    return true;
}
