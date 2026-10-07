#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/UI/uiManager.h"
#include "Game/DLC/aocManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Resource/resGameResourceSystem.h"
#include "KingSystem/System/CameraMgr.h"
#include <gfx/seadCamera.h>

// UI wrapper functions around uking::ui::Manager (the 0x7100a94000 TU).
namespace uking::ui {

ksys::act::Actor* getPlayerActor(ksys::act::Actor* actor);

void sub_7100945320(f32, f32);
// 0x7100a9ed78 (uiMiscFacade.cpp)
void sub_7100A9ED78(const char* from, const char* to, ksys::act::Actor* actor);
// 0x7100a9c374 (declared only)
void sub_7100A9C374(s32 rune);
void sub_7100945344(f32, f32);

// 0x7100a9c0dc (placeholder name): table lookup, -1 when out of range.
s32 sub_7100A9C0DC(s32 index) {
    static const s32 sTable[] = {10, 11, 0, 1, 2, 3, 12, 13};
    if (u32(index) < 8)
        return sTable[index];
    return -1;
}

// 0x7100a9e27c
void sub_7100A9E27C() {
    auto* manager = Manager::instance();
    auto lock = sead::makeScopedLock(manager->_650f8);
    manager->_650f0 = 0;
}

// 0x7100a9eea4 (placeholder name): the map name of the current dungeon-type state (null: none).
const char* sub_7100A9EEA4() {
    auto* manager = Manager::instance();
    if (!manager)
        return nullptr;
    switch (manager->_64c38) {
    case 0:
        return "MainField/B-2";
    case 1:
        return "MainField/H-2";
    case 2:
        return "MainField/I-4";
    case 3:
        return "MainField/B-8";
    case 4:
        return "MainField/D-6";
    default:
        break;
    }
    return manager->_64c38 == 5 ? "MainField/E-4" : nullptr;
}

// 0x7100a9eef4 (placeholder name): the escape destination of the current dungeon-type state (null: none).
const char* sub_7100A9EEF4() {
    auto* manager = Manager::instance();
    if (!manager)
        return nullptr;
    switch (manager->_64c38) {
    case 0:
        return "RemainsWind_Escape";
    case 1:
        return "RemainsFire_Escape";
    case 2:
        return "RemainsWater_Escape";
    case 3:
        return "RemainsElectric_Escape";
    case 4:
        return "FinalTrial_Escape";
    default:
        break;
    }
    return manager->_64c38 == 5 ? "HyruleCastleExit" : nullptr;
}

// 0x7100a9ee24 (CSV ui::doRequestExitFromMap): the two name functions above are inlined here in the original
void doRequestExitFromMap(ksys::act::Actor* actor) {
    sub_7100A9ED78(sub_7100A9EEA4(), sub_7100A9EEF4(), actor);
}

// 0x7100aa4a2c (placeholder name): table lookup, -1 when out of range.
s32 sub_7100AA4A2C(s32 index) {
    static const s32 sTable[] = {4, 5, 6, 16, 10, 11, 12, 13};
    if (u32(index) < 8)
        return sTable[index];
    return -1;
}

// 0x7100aa6f90 (placeholder name): 1 without a value; with one, 2 for the true form Master Sword and 0 otherwise.
s32 sub_7100AA6F90(const PouchItem& item) {
    if (item.getValue() < 1)
        return 1;
    return dmg::DamageInfoMgr::instance()->isTrueFormMasterSword() ? 2 : 0;
}

// 0x7100aa8294 (placeholder name)
bool sub_7100AA8294() {
    if (auto* mgr = uking::act::CreatePlayerEquipActorMgr::instance())
        return mgr->areAllWeaponActorsReady();
    return true;
}

// 0x7100aa9838 / 0x7100aa9848 (CSV ResourceSystem::stopCompactionIfTooLong1_0 / unnamed)
void sub_7100AA9838() {
    ksys::res::GameResourceSystem::instance()->pauseCompaction();
}

void sub_7100AA9848() {
    ksys::res::GameResourceSystem::instance()->resumeCompaction();
}

// 0x7100a94158
bool uiManagerInitialised() {
    return Manager::instance() != nullptr;
}

// 0x7100a94170
void setPauseStateMaybe(bool paused) {
    if (auto* manager = Manager::instance())
        manager->_38 = paused;
}

// 0x7100a9418c
bool sub_7100A9418C() {
    if (auto* manager = Manager::instance())
        return manager->_38 != 0;
    return false;
}

// 0x7100a941b4
void sub_7100A941B4() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A76424();
}

// 0x7100a941cc
void sub_7100A941CC() {
    Manager::instance()->sub_7100A79968();
}

// 0x7100a941dc
void sub_7100A941DC() {
    Manager::instance()->sub_7100A79ED4();
}

// 0x7100a94460
void sub_7100A94460() {
    auto* manager = Manager::instance();
    if (manager && manager->_38)
        manager->sub_7100A76420();
}

// 0x7100a94480
void sub_7100A94480() {
    Manager::instance()->sub_7100A7A4C0();
}

// 0x7100a94490
void sub_7100A94490() {
    Manager::instance()->_64c30 |= 0x20;
}

// 0x7100a944b4
void sub_7100A944B4() {
    Manager::instance()->_64c30 &= ~0x20ull;
}

// 0x7100a94788
void sub_7100A94788() {
    Manager::instance()->_64c30 &= ~0x40ull;
}

// 0x7100a94a50
void sub_7100A94A50(bool set) {
    auto* manager = Manager::instance();
    manager->_64c30 = set ? (manager->_64c30 | 0x80) : (manager->_64c30 & ~0x80ull);
}

// 0x7100a94aa8
void sub_7100A94AA8(bool value) {
    Manager::instance()->set64c68(value);
}

// 0x7100a9b2ac
void sub_7100A9B2AC() {
    if (auto* manager = Manager::instance())
        manager->_64c4d = true;
}

// 0x7100a9b2d0
void sub_7100A9B2D0() {
    if (auto* manager = Manager::instance())
        manager->_64c4d = false;
}

// 0x7100a9b468
void updateLifeAndMaxLife(s32 life, s32 max_life) {
    if (auto* manager = Manager::instance()) {
        manager->_48 = sead::Mathi::clamp(life, 0, 120);
        manager->_4c = sead::Mathi::clamp(max_life, 0, 120);
    }
}

// 0x7100a9b4a4
// The third argument is passed by the callers but ignored.
void updateStaminaAndMax(f32 stamina, f32 max_stamina, f32) {
    if (Manager::instance())
        sub_7100945320(sead::Mathf::clampMin(stamina, 0.0f), sead::Mathf::clampMin(max_stamina, 0.0f));
}

// 0x7100a9b4c8
void sub_7100A9B4C8(f32 a0, f32 a1) {
    if (Manager::instance())
        sub_7100945344(sead::Mathf::clampMin(a0, 0.0f), sead::Mathf::clampMin(a1, 0.0f));
}

// 0x7100a9b4ec
void sub_7100A9B4EC(f32 a0, f32 a1) {
    if (auto* manager = Manager::instance()) {
        manager->_74 = true;
        manager->_68 = a0;
        manager->_6c = a1;
    }
}

// 0x7100a9b510
void sub_7100A9B510(s32 a0, s32 a1) {
    if (auto* manager = Manager::instance()) {
        manager->_78 = a0;
        manager->_7c = a1;
    }
}

// 0x7100a9b528
void sub_7100A9B528(f32 a0) {
    if (auto* manager = Manager::instance())
        manager->_70 = a0;
}

// 0x7100a9b540
void sub_7100A9B540(const sead::Vector3f* a0, const sead::Vector3f* a1) {
    if (auto* manager = Manager::instance()) {
        manager->_80 = *a0;
        manager->_8c = *a1;
    }
}

// 0x7100a9b654
void sub_7100A9B654(const sead::Vector2f* a0) {
    if (auto* manager = Manager::instance())
        manager->_98 = *a0;
}

// 0x7100a9b678
void sub_7100A9B678(f32 a0) {
    if (auto* manager = Manager::instance())
        manager->_a0 = a0;
}

// 0x7100a9b690
s32 sub_7100A9B690() {
    if (auto* manager = Manager::instance())
        return manager->_48;
    return 0;
}

// 0x7100a9b6b0
s32 sub_7100A9B6B0() {
    if (auto* manager = Manager::instance())
        return manager->_4c;
    return 0;
}

// 0x7100a9b6d0
f32 sub_7100A9B6D0() {
    if (auto* manager = Manager::instance())
        return manager->_50;
    return 0;
}

// 0x7100a9b6f0
f32 sub_7100A9B6F0() {
    if (auto* manager = Manager::instance())
        return manager->_54;
    return 0;
}

// 0x7100a9b710
f32 sub_7100A9B710() {
    if (auto* manager = Manager::instance())
        return manager->_5c;
    return 0;
}

// 0x7100a9b730
bool sub_7100A9B730(f32* a0, f32* a1) {
    if (auto* manager = Manager::instance()) {
        if (manager->_74) {
            *a0 = manager->_68;
            *a1 = manager->_6c;
            return true;
        }
    }
    return false;
}

// 0x7100a9b770
void sub_7100A9B770(s32* a0, s32* a1) {
    if (auto* manager = Manager::instance()) {
        if (a0)
            *a0 = manager->_78;
        if (a1)
            *a1 = manager->_7c;
    }
}

// 0x7100a9b79c
f32 sub_7100A9B79C() {
    if (auto* manager = Manager::instance())
        return manager->_70;
    return 0;
}

// 0x7100a9b800
void sub_7100A9B800(sead::Vector3f* out) {
    if (out) {
        if (auto* manager = Manager::instance())
            *out = manager->_80;
    }
}

// NON_MATCHING: the original loads `_8c.x` / `_8c.z` first but still compares x, y, z in that order; ours compares x, z, y
// 0x7100a9b830 (placeholder name): the heading in degrees (0 - 360) of the manager's direction `_8c` (0 if it is zero).
f32 sub_7100A9B830() {
    auto* manager = Manager::instance();
    if (!manager)
        return 0;
    const sead::Vector3f dir = manager->_8c;
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)
        return 0;
    return sub_7100AA0B6C(sead::Mathf::idx2deg(sead::Mathf::atan2Idx(dir.x, dir.z)) + 180.0f);
}

// 0x7100a9b89c (placeholder name): the heading in degrees of the look-at camera's direction (0 without a camera).
f32 sub_7100A9B89C() {
    if (auto* mgr = ksys::CameraMgr::instance()) {
        if (auto* camera = mgr->getLookAtCamera()) {
            const sead::Vector3f dir = camera->getAt() - camera->getPos();
            if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f)
                return sub_7100AA0B6C(sead::Mathf::idx2deg(sead::Mathf::atan2Idx(dir.x, dir.z)) + 180.0f);
        }
    }
    return 0;
}

// 0x7100a9b928 (placeholder name)
const sead::Vector2f& sub_7100A9B928() {
    auto* manager = Manager::instance();
    return manager ? manager->_98 : sead::Vector2f::zero;
}

// 0x7100a9c728 (placeholder name): the UI rune of the RuneMgr item `item` (false for a bad item); the callee 0x7100a9c374
// is declared only
bool sub_7100A9C728(s32 item) {
    s32 rune;
    switch (item) {
    case 0:
        rune = 10;
        break;
    case 1:
        rune = 11;
        break;
    case 2:
        rune = 0;
        break;
    case 3:
        rune = 1;
        break;
    case 4:
        rune = 2;
        break;
    case 5:
        rune = 3;
        break;
    case 6:
        rune = 12;
        break;
    case 7:
        rune = 13;
        break;
    default:
        return false;
    }
    sub_7100A9C374(rune);
    return true;
}

// NON_MATCHING: the original does not tail-call the flag getters: it re-normalises their result (`tbz w8, #0; orr w0, wzr, #1`)
// 0x7100a9cdb4 (placeholder name)
bool sub_7100A9CDB4(s32 rune) {
    bool owned = false;
    if (rune == 0 || rune == 1)
        owned = ksys::gdt::getFlag_IsGet_Obj_RemoteBombLv2(false);
    else if (rune == 3)
        owned = ksys::gdt::getFlag_IsGet_Obj_StopTimerLv2(false);
    else
        return false;
    return owned ? true : false;
}

// 0x7100a9d244 (placeholder name)
void sub_7100A9D244(f32 value) {
    auto* obj = Unk_71025d6550::instance();
    auto* manager = Manager::instance();
    if (!obj || !manager)
        return;
    obj->_b68 = value;
    obj->_b70 = value;
    if (manager->_64c38 == 2)
        obj->sub_7100948F48(-value);
    else
        obj->sub_7100948F48(value);
}

// 0x7100a9b94c
f32 sub_7100A9B94C() {
    if (auto* manager = Manager::instance())
        return manager->_a0;
    return 0;
}

// 0x7100a9b9f8
void sub_7100A9B9F8(s32 bit) {
    if (auto* manager = Manager::instance())
        manager->_649ec.setBit(bit);
}

// 0x7100a9ba28
void sub_7100A9BA28() {
    if (auto* manager = Manager::instance())
        manager->_649ec.makeAllZero();
}

// 0x7100a9ba48
bool sub_7100A9BA48() {
    if (auto* manager = Manager::instance())
        return !manager->_649ec.isZero();
    return false;
}

// 0x7100a9ba78
bool sub_7100A9BA78(s32 bit) {
    if (auto* manager = Manager::instance())
        return manager->_649ec.isOnBit(bit);
    return false;
}

// 0x7100a9bab4
void sub_7100A9BAB4(s32 idx, s32 value) {
    Manager::instance()->_b0[idx] = value;
}

// 0x7100a9bad8
void sub_7100A9BAD8(s32 value) {
    Manager::instance()->_c4 = value;
}

// 0x7100a9bca4
void sub_7100A9BCA4(const u64* value) {
    Manager::instance()->setD8(value);
}

// 0x7100a9bcbc
void sub_7100A9BCBC(const u64* value) {
    Manager::instance()->setE0(value);
}

// 0x7100a9c0fc
void sub_7100A9C0FC(s32 value) {
    Manager::instance()->_cc = value;
}

// 0x7100a9c110
bool sub_7100A9C110(s32 value) {
    return Manager::instance()->_d0 == value;
}

// 0x7100a9c12c
bool sub_7100A9C12C(s32 value) {
    auto* manager = Manager::instance();
    if (manager->_d0 != value)
        return false;
    return manager->_d4 != value;
}

// 0x7100a9e200
void loadSaveForStageUnload() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A76180();
}

// 0x7100a9e218
void sub_7100A9E218() {
    Manager::instance()->sub_7100A7F81C();
}

// 0x7100a9e228
s32 sub_7100A9E228() {
    return Manager::instance()->_650f0;
}

// 0x7100a9e244
u64 sub_7100A9E244() {
    return Manager::instance()->_65160;
}

// 0x7100a9e260
s32 getSomeUiManagerField() {
    return Manager::instance()->_65168;
}

// 0x7100a9e2c4
void uiManagerUpdateIsDungeon() {
    Manager::instance()->sub_7100A7FBA4();
}

// 0x7100a9e5e0
void sub_7100A9E5E0() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A7C8D4();
}

// 0x7100aa8f10
bool sub_7100AA8F10() {
    return (Manager::instance()->_64c30_bytes[1] >> 4) & 1;
}

// 0x7100aa9728
void sub_7100AA9728() {
    Manager::instance()->_652e8 = true;
}

// 0x7100a9f5e4
bool checkSomeFlagImpl() {
    if (auto* manager = Manager::instance())
        return (manager->_64c30_bytes[5] >> 3) & 1;
    return false;
}

// 0x7100a9f950
void return0_2() {
    Manager::instance()->sub_7100A7FDAC();
}

// 0x7100a9b96c (placeholder name; getPlayerActor is out of line in the original)
bool sub_7100A9B96C() {
    if (auto* player = static_cast<ksys::act::PlayerBase*>(getPlayerActor(nullptr)))
        return player->sub_710084CF24();
    return false;
}

}  // namespace uking::ui
