#include "Game/gameSaveSystem.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/E3Mgr.h"
#include "Game/gameRoot38.h"
#include "Game/gameScene.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(SaveSystem)

// 0x71025d1d18: the all-zero slot returned for a slot that does not exist.
static SaveSlot sUnk_71025D1D18;

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

s32 SaveSystem::sub_7100915F58(s32 idx) {
    return _1880.sub_710090C954(idx);
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

bool SaveSystem::sub_710091410C() const {
    if (auto* e3 = E3Mgr::instance(); e3 && e3->isDemoMode())
        return false;
    return _30 == 8;
}

bool SaveSystem::sub_7100913160() {
    auto* save_mgr = ksys::SaveMgr::instance();
    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!save_mgr || !gdt_mgr)
        return false;

    save_mgr->_f94 = 2;
    _34 = 0;
    _3c = 22;
    return true;
}

void SaveSystem::sub_71009157E4() {
    if (_30 != 8)
        _1880.sub_710090CD84(&_40[_30], false);
    _30 = 8;
}

SaveSlot* SaveSystem::sub_7100914DA0(s32 slot) {
    return &_40[(_38 & 1) ? slot : 0];
}

SaveSlot* SaveSystem::sub_7100914DC8(s32 index, bool a) {
    if (0 <= index && index < 8) {
        const s32 slot = sub_7100914E20(index, a);
        if (slot >= 0)
            return &_40[slot];
    }
    return &sUnk_71025D1D18;
}

bool SaveSystem::sub_7100915A00() {
    if (!(_38 & 0x10))
        return false;
    SaveSlot* slot = sub_7100914DC8(0, true);
    return slot->_300 && slot->_304;
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

// NON_MATCHING: block layout only (the original keeps one `mov w0, wzr` per failing test and places the shared
// epilogue after the first checks; every nesting / early-return variant tried gives one merged `mov w0, wzr`)
bool SaveSystem::x_3(s32 slot) {
    if (u32(slot) > 7 || _3c != 0)
        return false;

    if (ksys::SaveMgr::instance()) {
        if (ksys::SaveMgr::instance()->get38() == 0) {
            if (!ksys::gdt::getFlag_IsPlayed_Demo102_0())
                return false;
            if (ksys::gdt::isSaveProhibited())
                return false;
            if (_1a42)
                return false;
            if (_1a50 & 0x1008)
                return false;
            if (GameScene::getCurrentMapType().isEmpty())
                return false;

            _1a50 |= 0x4200;
            _30 = slot;
            _3c = 30;
            return true;
        }
    }
    return false;
}

void SaveSystem::calculateTrackBlockSaveNumberFlagHash() {
    auto* save_mgr = ksys::SaveMgr::instance();
    if (!save_mgr)
        return;
    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!gdt_mgr)
        return;

    save_mgr->auto5();
    if (!save_mgr->someCheck())
        return;

    const char* flag_name;
    if (aoc::HardModeManager::instance() &&
        aoc::HardModeManager::instance()->checkFlag(aoc::HardModeManager::Flag::EnableHardMode)) {
        flag_name = ksys::gdt::flagname::TrackBlockFileNumber_Hard();
    } else {
        flag_name = ksys::gdt::flagname::TrackBlockFileNumber();
    }

    const u32 hash = sead::HashCRC32::calcStringHash(flag_name);
    gdt_mgr->mBitFlags.set(ksys::gdt::Manager::BitFlag::_2);
    gdt_mgr->mStr.format("%s", "caption.sav");
    gdt_mgr->mTrackerBlockSaveNumberFlagCrc32 = hash;
    _3c = 38;
}

}  // namespace uking
