#include "Game/NXArgs.h"
#include <prim/seadScopedLock.h>
#include "Game/Scene/gameScene.h"
#include "Game/gameRoot4.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/System/StageInfo.h"

// 0x7100901a90 sits just before nxargs::createInstance; its owner class is unknown.
bool Unk_71025d1740::sub_7100901A90(bool value) {
    auto lock = sead::makeScopedLock(_28);
    _20 = value;
    return true;
}

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

nxargs::~nxargs() {
    for (s32 i = 0; i < mEntries.size(); ++i)
        mEntries[i].conditions.freeBuffer();
    mEntries.freeBuffer();
}

// NON_MATCHING: our sead isEqual calls the virtual assureTerminationImpl_ for each map-type comparison (the original
// build has those calls removed / devirtualised), so this is 404 bytes instead of 320.
void nxargs::handleArgs() {
    if (mHasHandledArgs)
        return;
    if (DebugBoardMgr::instance()->hasLoadingScreenStarted())
        return;
    if (!uking::Root4::instance()->checkFlag(uking::Root4::FlagIdx::_1))
        return;
    if (ksys::evt::Manager::instance()->hasActiveEvent())
        return;
    if (mType == ArgsType::None)
        return;

    const sead::SafeString& map_type = GameScene::getCurrentMapType();
    if (map_type == "TitleMenu")
        return;
    if (map_type == "STAGESELECT")
        return;
    if (map_type.isEmpty())
        return;

    if (ksys::gdt::getFlag_IsGet_PlayerStole2(false) && ksys::StageInfo::sIsMainField) {
        if (!mHasHandledArgs)
            spawnActors();
    } else {
        mHasHandledArgs = true;
    }
}

void nxargs::init(sead::Heap* heap) {
    sead::Heap* nxargsheap = sead::ExpHeap::create(
        0x13E8, "nxargsHeap", heap, 8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    auto* data = new (nxargsheap) u8[0x1000];
    size_t unknown;

    while (nn::oe::TryPopLaunchParameter(&unknown, data, 0x1000)) {
        {
            sead::FixedSafeString<5> inputmagic("");
            inputmagic.format("%s", reinterpret_cast<char*>(data));
            if (inputmagic != "BotW")
                continue;
        }
        using sead::BitUtil::bitCastPtr;
        mResField4 = bitCastPtr<u16>(data, 4);
        mResField6 = bitCastPtr<u8>(data, 6);
        mType = bitCastPtr<ArgsType>(data, 7);
        if (mType == ArgsType::CreateActors) {
            mNumEntries = bitCastPtr<u8>(data, 0xC);
            nxargs::allocEntries(heap, data);
        } else {
            mType = ArgsType::None;
        }
        break;
    }
    nxargsheap->destroy();
}

void nxargs::allocEntries(sead::Heap* heap, const u8* data) {
    const s32 size = mNumEntries;

    if (mNumEntries == 0)
        return;
    mEntries.allocBufferAssert(size, heap);

    using sead::BitUtil::bitCastPtr;
    u32 offset = 0x10;
    for (u8 i = 0; i < mNumEntries; i++) {
        LaunchParamEntry* currEntry = &mEntries[i];
        currEntry->actorNameHash = bitCastPtr<u32>(data, offset + 0);
        currEntry->dropActorNameHash = bitCastPtr<u32>(data, offset + 4);
        currEntry->positionOffset.x = bitCastPtr<f32>(data, offset + 8);
        currEntry->positionOffset.y = bitCastPtr<f32>(data, offset + 0xc);
        currEntry->positionOffset.z = bitCastPtr<f32>(data, offset + 0x10);
        currEntry->rotation.x = bitCastPtr<f32>(data, offset + 0x14);
        currEntry->rotation.y = bitCastPtr<f32>(data, offset + 0x18);
        currEntry->rotation.z = bitCastPtr<f32>(data, offset + 0x1c);
        currEntry->velocity.x = bitCastPtr<f32>(data, offset + 0x20);
        currEntry->velocity.y = bitCastPtr<f32>(data, offset + 0x24);
        currEntry->velocity.z = bitCastPtr<f32>(data, offset + 0x28);
        currEntry->flags = bitCastPtr<LaunchParamFlag>(data, offset + 0x2c);
        s64 numConditions = bitCastPtr<u8>(data, offset + 0x2d);
        currEntry->numConditions = numConditions;
        offset += 0x30;

        if (numConditions > 0) {
            currEntry->conditions.allocBufferAssert(numConditions, heap);
            for (u8 j = 0; j < currEntry->numConditions; j++) {
                LaunchParamEntryCondition* currCondition = &currEntry->conditions[j];
                currCondition->flagNameHash = bitCastPtr<u32>(data, offset);
                currCondition->flagDataType =
                    bitCastPtr<LaunchParamEntryConditionDataType>(data, offset + 4);
                currCondition->operation =
                    bitCastPtr<ActorEntryConditionOperation>(data, offset + 5);
                currCondition->rhsValue = bitCastPtr<f32>(data, offset + 8);
                offset += 0xc;
            }
        }
    }
}

}  // namespace uking
