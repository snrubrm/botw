#include "Game/gameSaveSystem.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/E3Mgr.h"
#include "Game/gameRoot38.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameScene.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/PlayReportMgr.h"

// 0xa9bd38 (CSV isSelectedRuneEqualToItemType; lane2 UI code, declared only)
bool isSelectedRuneEqualToItemType(s32 type, void* arg);

namespace uking::ui {
// 0x7100a9e228 / 0x7100a9e260 (lane2 UI code, declared only)
s32 sub_7100A9E228();
s32 getSomeUiManagerField();
// 0x7100a9e244 (declared only)
void* sub_7100A9E244();
// 0x7100b61f4 (CSV showLoadSaveIcon_0; declared only)
void showLoadSaveIcon_0(bool show);
// 0x7100a9e27c (declared only)
void sub_7100A9E27C();
}  // namespace uking::ui

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

bool SaveSystem::sub_7100915838() {
    if (_3c != 0)
        return false;

    for (auto& slot : _40) {
        if (slot._300 && slot._301)
            slot._300 = false;
    }
    return true;
}

bool SaveSystem::sub_7100912BE0(bool check_ui) {
    if (!ksys::gdt::getFlag_IsPlayed_Demo102_0() || ksys::gdt::isSaveProhibited())
        return true;
    if (_1a42)
        return true;
    if (_1a50 & 0x1008)
        return true;

    if (check_ui) {
        if (isSelectedRuneEqualToItemType(3, nullptr))
            return true;
        if (ui::return0())
            return true;
    }

    return GameScene::getCurrentMapType().isEmpty();
}

void SaveSystem::sub_7100911BB8() {
    auto* save_mgr = ksys::SaveMgr::instance();
    if (!save_mgr)
        return;

    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (gdt_mgr && gdt_mgr->mBitFlags.isOn(ksys::gdt::Manager::BitFlag::_2))
        return;

    if (ui::sub_7100A9E228() == 7 || ui::sub_7100A9E228() == 0) {
        const s32 field = ui::getSomeUiManagerField();
        _40[_30]._2f8 = field;
        save_mgr->x_5(field);
    } else if (ui::sub_7100A9E228() != -1) {
        return;
    }

    save_mgr->x_0(_30);
    _3c = 11;
}

void SaveSystem::sub_710091171C() {
    auto* save_mgr = ksys::SaveMgr::instance();
    if (!save_mgr)
        return;

    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!gdt_mgr || gdt_mgr->mBitFlags.isOn(ksys::gdt::Manager::BitFlag::_2))
        return;

    if (ui::sub_7100A9E228() == 7 || ui::sub_7100A9E228() == 0) {
        if (!(_1a50 & 0x180)) {
            _40[_30]._2f8 = ui::getSomeUiManagerField();
            save_mgr->x_5(ui::getSomeUiManagerField());
        }
    } else if (ui::sub_7100A9E228() != -1) {
        return;
    }

    if (!(_1a50 & 0x80)) {
        if (_1a50 & 0x100)
            save_mgr->auto6(0);
        else
            save_mgr->x_0(_30);
    }
    _3c = 2;
}

bool SaveSystem::setRetryData() {
    if (!ksys::SaveMgr::instance())
        return false;

    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!gdt_mgr)
        return false;

    s32 current_hart = 0;
    gdt_mgr->getParam().get().getS32(&current_hart, "CurrentHart");
    if (current_hart == 0)
        return false;

    const sead::Vector3f pos{-255.616898f, 130.3125f, 394.561890f};
    ksys::gdt::setFlag_Last_Ridden_Horse_Pos(pos, false);
    ksys::gdt::setFlag_PlayerSavePos(pos, false);
    gdt_mgr->allocRetryBuffer(ui::getHeap());
    _38 &= ~2;
    _1a50 |= 0x22;
    return true;
}

// NON_MATCHING: scheduling (the original stores the zero of `hash_id` after loading the SafeString vtable)
bool SaveSystem::triggerAutoSaveFromArea(ksys::act::Actor* actor) {
    if (actor && actor->getMapObject()) {
        u32 hash_id = 0;
        actor->getMapObject()->getMubinIter().tryGetParamUIntByKey(&hash_id, "HashId");
        if (_1a30 == hash_id && !(_1a24 <= 0.0f))
            return false;
        _1a30 = hash_id;
    }

    _1a24 = f32(ksys::VFR::instance()->getFrameRate() * 60);
    return sub_71009109EC(false, true);
}

bool SaveSystem::sub_71009145F8() {
    auto* save_mgr = ksys::SaveMgr::instance();
    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!save_mgr || !gdt_mgr)
        return false;
    if (save_mgr->get38() != 0)
        return false;
    if (_3c != 0)
        return false;

    if (!save_mgr->_105b) {
        const char* flag_name;
        if (aoc::HardModeManager::instance() &&
            aoc::HardModeManager::instance()->checkFlag(
                aoc::HardModeManager::Flag::EnableHardMode)) {
            flag_name = ksys::gdt::flagname::TrackBlockFileNumber_Hard();
        } else {
            flag_name = ksys::gdt::flagname::TrackBlockFileNumber();
        }

        const u32 hash = sead::HashCRC32::calcStringHash(flag_name);
        gdt_mgr->mBitFlags.set(ksys::gdt::Manager::BitFlag::_2);
        gdt_mgr->mStr.format("%s", "option.sav");
        gdt_mgr->mTrackerBlockSaveNumberFlagCrc32 = hash;
        _3c = 24;
    }

    sub_7100913CC8(true);
    return true;
}

void SaveSystem::finishLoadCb() {
    switch (_3c) {
    case 6:
    case 7:
    case 22:
    case 23:
    case 26:
    case 27:
    case 32:
    case 39:
    case 40:
        return;
    default:
        break;
    }

    _3c = 35;
    sub_7100912C94(_30);

    if (E3Mgr::instance()) {
        bool is_demo;
        if (E3Mgr::instance()->isDemoMode0AndNotStageSelect()) {
            is_demo = true;
        } else if (auto* e3 = E3Mgr::instance()) {
            // discarded call in the original
            e3->getDemoStage();
            is_demo = e3->isDemoMode2AndNotStageSelect();
        } else {
            is_demo = false;
        }
        if (is_demo) {
            ksys::gdt::setFlag_AmiiboItemOnOff(true, false);
            ksys::gdt::setFlag_IsGet_Obj_AmiiboItem(true, false);
        }
    }

    if (ksys::gdt::getFlag_LastBossGanonBeastGenerateFlag(false)) {
        if (auto* gdt_mgr = ksys::gdt::Manager::instance()) {
            gdt_mgr->setBoolNoCheck(true, "SaveProhibition");
            gdt_mgr->setBoolNoCheck(true, "WarpProhibition");
            gdt_mgr->setBoolNoCheck(true, "KillTimeProhibition");
            gdt_mgr->setBoolNoCheck(true, "EnterDungeonProhibition");
        }
    } else if (auto* gdt_mgr = ksys::gdt::Manager::instance()) {
        gdt_mgr->mBitFlags.reset(ksys::gdt::Manager::BitFlag::_80000);
        gdt_mgr->destroyRetryBuffer();
    }

    if (!ksys::gdt::getFlag_IsPlayed_Demo102_0(false))
        ksys::gdt::setFlag_IsPlayed_Demo102_0(true, false);

    if (auto* mgr = ksys::gdt::Manager::instance())
        mgr->startSyncOnLoadEnd();

    _1a20 = f32(_1a2c);
    _1a50 = (_1a50 & ~0xc) | 4;
}

void SaveSystem::callback() {
    switch (_3c) {
    case 14:
    case 15:
    case 20:
    case 21:
    case 28:
    case 29:
        return;
    case 2:
    case 11:
        _1a43 = _3c == 11;
        _3c = 28;
        return;
    case 13:
        ui::sub_7100A9E27C();
        ui::showLoadSaveIcon_0(false);
        break;
    default:
        break;
    }

    if (_3c != 2 && _3c != 11) {
        _1a44 = false;
        _3c = 0;
        if (auto* save_mgr = ksys::SaveMgr::instance())
            save_mgr->auto3();
        if (auto* gdt_mgr = ksys::gdt::Manager::instance())
            gdt_mgr->mBitFlags.reset(ksys::gdt::Manager::BitFlag::_100000);
        _1a50 &= ~0x4180;
    }
}

void SaveSystem::sub_7100911524() {
    u32 state;
    if (ui::sub_7100A9E228() == 7 || ui::sub_7100A9E228() == 0) {
        sead::FormatFixedSafeString<32> path("%d/caption.jpg", _30);
        if (auto* save_mgr = ksys::SaveMgr::instance()) {
            void* data = ui::sub_7100A9E244();
            const s32 field = ui::getSomeUiManagerField();
            if (!(_1a50 & 0x180))
                _40[_30]._2f8 = field;
            if (!(_1a50 & 0x180))
                save_mgr->sub_7100E044A8(path, data, field, 0x2800);
        }
        state = 4;
    } else if (ui::sub_7100A9E228() == -1) {
        if (auto* gdt_mgr = ksys::gdt::Manager::instance())
            gdt_mgr->mBitFlags.reset(ksys::gdt::Manager::BitFlag::_100000);
        state = 0;
    } else {
        return;
    }
    _3c = state;
}

void SaveSystem::sub_7100911620() {
    if (ui::sub_7100A9E228() == 7 || ui::sub_7100A9E228() == 0) {
        sead::FormatFixedSafeString<32> path("%d/caption.jpg", _30);
        if (auto* save_mgr = ksys::SaveMgr::instance()) {
            void* data = ui::sub_7100A9E244();
            const s32 field = ui::getSomeUiManagerField();
            if (!(_1a50 & 0x180))
                _40[_30]._2f8 = field;
            if (!(_1a50 & 0x180))
                save_mgr->sub_7100E044A8(path, data, field, 0x2800);
        }
        _3c = 13;
    } else if (ui::sub_7100A9E228() == -1) {
        ui::showLoadSaveIcon_0(false);
        _3c = 0;
        if (auto* gdt_mgr = ksys::gdt::Manager::instance())
            gdt_mgr->mBitFlags.reset(ksys::gdt::Manager::BitFlag::_100000);
    }
}

void SaveSystem::sub_7100912464() {
    auto* save_mgr = ksys::SaveMgr::instance();
    if (!save_mgr || save_mgr->get38() != 0)
        return;

    sead::FormatFixedSafeString<32> path("tracker/trackblock%02d.sav", _1a10);
    if (aoc::HardModeManager::instance() &&
        aoc::HardModeManager::instance()->checkFlag(aoc::HardModeManager::Flag::EnableHardMode)) {
        path.format("tracker/trackblock_hard%02d.sav", _1a10);
    }

    if (save_mgr->sub_7100E0402C(path)) {
        if (auto* report_mgr = ksys::PlayReportMgr::instance()) {
            if (report_mgr->getPlayerTrackReporter()) {
                save_mgr->x(path, _1a18, 0xe480);
                _3c = 40;
                return;
            }
        }
    }

    const s32 slot = _30;
    sub_7100912EA4(true);
    _3c = 0;
    _30 = slot;
}

void SaveSystem::sub_7100912A50() {
    auto* save_mgr = ksys::SaveMgr::instance();
    if (!save_mgr)
        return;
    auto* gdt_mgr = ksys::gdt::Manager::instance();
    if (!gdt_mgr)
        return;
    if (save_mgr->get38() != 0 || gdt_mgr->mBitFlags.isOn(ksys::gdt::Manager::BitFlag::_40000))
        return;

    if (_1a00)
        _1a00->sub_710090CDF4();

    if (!(_1a50 & 0x4000)) {
        gdt_mgr->setBool(true, ksys::gdt::FlagHandle(_1a34));
        gdt_mgr->setS32(1, ksys::gdt::FlagHandle(_1a38));
    } else {
        ksys::gdt::setFlag_IsSaveByAuto(true, false);
    }

    _1a50 |= 0x200;
    if (_1a08) {
        _1a08->m4();
        _1a00 = nullptr;
        _1a08 = nullptr;
    }
    _3c = 37;
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
