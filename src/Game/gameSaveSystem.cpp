#include "Game/gameSaveSystem.h"
#include "Game/gameRoot38.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

namespace uking {

bool SaveSystem::isFinishedSavingMaybe() const {
    auto* mgr = ksys::SaveMgr::instance();
    return mgr && mgr->get38() == 0 && _3c == 0;
}

bool SaveSystem::loadDone() const {
    auto* mgr = ksys::SaveMgr::instance();
    return mgr && mgr->get38() == 0 && _3c == 0;
}

bool SaveSystem::sub_7100914CE4() const {
    auto* mgr = ksys::SaveMgr::instance();
    return mgr && mgr->get38() == 0 && _3c == 0;
}

bool SaveSystem::sub_7100914504() const {
    auto* mgr = ksys::SaveMgr::instance();
    return mgr && mgr->get38() == 0 && _3c == 0;
}

bool SaveSystem::isFirstLaunch() const {
    return !(_38 & 4);
}

void SaveSystem::noop() {}

void SaveSystem::newDayCallback() {
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        mgr->mBitFlags.set(ksys::gdt::Manager::BitFlag::_8);
        mgr->mResetFlags.set(ksys::gdt::Manager::ResetFlag::_8);
    }
}

void SaveSystem::setGameDataMgrResetFlag2() {
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        mgr->mBitFlags.set(ksys::gdt::Manager::BitFlag::_8);
        mgr->mResetFlags.set(ksys::gdt::Manager::ResetFlag::_2);
    }
}

void SaveSystem::setGdmFlagsBeforeStageGen() {
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        mgr->mBitFlags.set(ksys::gdt::Manager::BitFlag::_8);
        mgr->mResetFlags.set(ksys::gdt::Manager::ResetFlag::_4);
    }
}

bool SaveSystem::sub_7100910CD0() const {
    switch (_3c) {
    case 5:
    case 6:
    case 7:
    case 22:
    case 23:
    case 26:
    case 27:
    case 31:
    case 32:
    case 39:
    case 40:
        return true;
    default:
        return false;
    }
}

bool SaveSystem::sub_7100914D48() {
    auto* save_mgr = ksys::SaveMgr::instance();
    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!save_mgr || !gdt_mgr)
        return false;

    save_mgr->_f94 = 2;
    _1a50 &= ~2;
    _34 = 0;
    _3c = 6;
    return true;
}

SaveSystem::Slot* SaveSystem::sub_7100914DA0(s32 slot) {
    return &_40[(_38 & 1) ? slot : 0];
}

void SaveSystem::sub_7100910C94(f32 value) {
    if (!sub_7100910CD0()) {
        _1a50 |= 8;
        _1a28 = value;
    }
}

s32 SaveSystem::sub_7100910D04() const {
    if (Root38::instance()) {
        if (Root38::instance()->testFlag(6))
            return 2;
        if (Root38::instance()->doNotFreezeScene())
            return 1;
    }
    return 0;
}

// NON_MATCHING: the original loads the TriggerParam buffer pointer after the flag name hash call (C++14
// evaluation order of the object expression and the arguments); ours loads it first
void SaveSystem::requestAutoSaveForGameClear(const sead::SafeString& game_clear_flag) {
    if (_3c != 0)
        return;

    if (auto* mgr = ksys::gdt::Manager::instance()) {
        _1a34 = mgr->mCurrentFlagHandlePrefix << 24 |
                mgr->getParam().get1().getBuffer1()->getBoolIdx(
                    sead::HashCRC32::calcStringHash(game_clear_flag.cstr()));
        _1a38 = mgr->mCurrentFlagHandlePrefix << 24 |
                mgr->getParam().get1().getBuffer1()->getS32Idx(
                    sead::HashCRC32::calcStringHash("Defeated_Enemy_GanonBeast_Num"));
    }

    _3c = 30;
}

}  // namespace uking
