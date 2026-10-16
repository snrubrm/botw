#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/aiUnk_7101E7C2B4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/Action/actionPlayerBackJump.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/Utils/MathUtil.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "Game/Actor/Damage/dmgDamageMgrPlayer.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"

// Declaration only (CSV name; original namespace unknown).
bool fadeSlowEffect();

namespace ksys::act {

// Own file: the original calls these out of line (x_5 from sub_7100877BD8, stillAlive from m375); a
// same-file definition would be inlined into the callers.
// NON_MATCHING: operand order of the XZ length addition (z*z + x*x in the original)
Player::Unk1 Player::x_5() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    if (sead::Vector2f(dir.x, dir.z).length() == 0.0f) {
        _1b18.getBase(dir, 1);
        dir.normalize();
    }
    return Unk1(sead::Mathf::atan2Idx(dir.x, dir.z));
}

// NON_MATCHING: the original computes the matrix product with scalar lane multiplies; ours is vectorised
void Player::sub_710086800C(f32 a1) {
    const sead::Vector3f rotation = _20f0 * sead::Vector3f(0.0f, a1, 0.0f);
    sead::Matrix34f rotation_mtx;
    rotation_mtx.makeR(rotation);
    _1b18.setMul(rotation_mtx, _1b18);
}

bool Player::stillAlive() {
    auto* life = getLife();
    if (!life || *life > 0 || hasFairy())
        return true;
    return canUseMiphaGrace();
}

void Player::sub_7100884578() {
    if (auto* mgr = sead::DynamicCast<uking::act::DamageMgrPlayer>(getDamageMgr()))
        mgr->_22c = uking::sUnk_7101e7c2b0;
}

void Player::sub_710088A854() {
    getWeapons()->mWeapons[1]._10 = true;
    _c40.resetBit(3);
    sub_7100888278();
    snd::Unk_7102502138::instance()->sub_710103B430(false);
}

void Player::sub_710086952C() {
    if (auto* physics = mPhysics) {
        if (auto* set = physics->findBodyByName("Tgt")) {
            if (auto* body = set->findBodyByHavokName("Body"))
                physics->sub_7100FBD918(body, 0);
        }
    }
}

// NON_MATCHING: the original returns the value with `mov w0, w19` (ours: `mov x0, x19`, the struct built from an int)
AttActionCodeValue sub_710086B194() {
    ActorLinkConstDataAccess accessor;
    Attention::instance()->sub_7100D7482C(&accessor);
    return AttActionCodeValue(accessor.sub_7100D10FB8() ? 0x1800000 :
                                                          int(Attention::instance()->sub_7100D74880()));
}

// Placeholder name: sets the ui tip type _1cb0 from the Attention target type (not while the camera rune is
// selected).
void Player::sub_710086BB68() {
    auto* rune_mgr = uking::RuneMgr::instance();
    if (rune_mgr->_90 & 0x20)
        return;
    if ((rune_mgr->_90 & 0x10) && rune_mgr->isSelectedRune(5))
        return;
    const AttActionCodeValue type = sub_710086B194();
    if (type == AttActionCodeValue(0x1800001))
        _1cb0 = 0x12;
    else if (type == AttActionCodeValue(0x1800010))
        _1cb0 = 0x27;
}

// Placeholder name: same for the other target types.
void Player::sub_710086BC30() {
    const AttActionCodeValue type = sub_710086B194();
    if (type == AttActionCodeValue(0x1800001)) {
        _1cb0 = 0x12;
    } else if (type == AttActionCodeValue(0x180001a)) {
        _1cb0 = 0x3b;
    } else if (type == AttActionCodeValue(0x1800023)) {
        if (_207f)
            _1cb0 = 0x3c;
    }
}

bool Player::sub_7100892724() {
    bool result = false;
    if (m224()) {
        result = true;
        if (!getASList()->sub_710115FBC8(0, nullptr, &as::ASList::Unk2::sub_71011638DC, true)) {
            if (!getASList()->sub_710115ED5C(0x42, 0x24) ||
                !getASList()->sub_710115ED5C(0x42, 0x26) ||
                getASList()->x(0x16, nullptr, 0, 0, &as::ASList::Unk2::sub_71011638DC, true)) {
                result = false;
            }
        }
    }
    return result;
}

void Player::m229() {
    if (_c40.isOnBit(13)) {
        const f32 value = mActorParam->getRes().mGParamList->getPlayer()->mBowSlowInvalidTime.ref();
        _1d7c = value;
        _1d80 = value;
        _1d84 = -1.0f;
    }
    if (_c40.isOnBit(14))
        sub_710084AA0C();
    _c40.reset(0xe000);
    _1d70 = Timer(0.0f, 0.0f);
    VFR::instance()->resetTimeMultiplier(0);
    VFR::instance()->resetTimeMultiplier(1);
    VFR::instance()->resetTimeMultiplier(2);
    fadeSlowEffect();
    _20ec = 1.0f;
}

// Out of line in the original: sub_7100884FCC (actPlayer.cpp) calls both.
// NON_MATCHING: the two magnitude comparisons share a branch before selecting the signed angle side.
u8 Player::sub_7100869814(Unk1 a, Unk1 b) {
    const s64 magnitude_a = util::sub_71011EE4C0(a.value);
    const s64 magnitude_b = util::sub_71011EE4C0(b.value);
    const s64 opposite_b = util::sub_71011EE4C0(s64(b.value) - 0x80000000LL);
    if (magnitude_a > opposite_b)
        return 1;
    if (magnitude_a >= magnitude_b && s32(a.value) >= 0)
        return 2;
    if (magnitude_a >= magnitude_b && s32(a.value) < 0)
        return 3;
    return 0;
}

sead::Vector3f Player::sub_710087386C() {
    sead::Vector3f dir = sead::Vector3f::zero;
    if (auto* manager = sub_710072BA90(this))
        manager->m30(&dir);
    return dir;
}

// Out of line in the original: m287 tail-calls it.
bool Player::sub_710088873C() {
    if (!m225() && !m226())
        return false;
    return _d68 == getEquipmentTypeName(7);
}


// Out of line in the original: getSwimMoveSpeed tail-calls it.
f32 Player::getStatusEffectSwimingAnimRate(s32 level) {
    eco::StatusEffectInfo info;
    eco::Ecosystem::instance()->getStatusEffectInfo(eco::StatusEffect_SwimingAnimRate, level, &info);
    return info.val._f32;
}


// Kept apart from sub_710086C9E0 (actPlayer.cpp): the original calls it out of line here but inlines it into
// sub_710086C928.
bool Player::sub_7100878044() {
    if (sub_710086C9E0()) {
        const f32 time = getParam()->getRes().mGParamList->getPlayer()->mPostureContinueTime.ref();
        _1e60 = Timer(time, time, -1.0f);
        return true;
    }
    if (_17d0->playerCheckController(13) && !m202() && _c44.isOffBit(13) && !m178())
        return true;
    if (snd::sub_7100FFED80())
        return true;
    if (!(_1e60.value <= sead::Mathf::epsilon()))
        return true;
    return !(_1e90 <= sead::Mathf::epsilon());
}


// Out of line in the original: sub_7100893F1C calls it.
bool Player::sub_710087F360(const sead::Vector3f& start, const sead::Vector3f& end,
                            sead::Vector3f* hit_pos, sead::Vector3f* hit_normal) {
    return sub_710072E928(start, end, hit_pos, hit_normal, nullptr, 0.0f);
}


// Here, not in actPlayer.cpp: the original calls sub_7100881B14 out of line.
// NON_MATCHING: the original loads the height once after selecting its address and does not tail-call
// sub_7100881B14 (returns 1 / 0 after it); form unknown.
bool Player::x_30() {
    const bool flags_ok = !_cec.isOnBit(1) && !_cf8.isOnBit(8);
    if (isSlowTime())
        return false;
    if (!flags_ok || !gdt::getFlag_App_Slowtimer_OnOff())
        return false;
    if (_cec.isOnBit(14))
        return false;
    if (x_44())
        return false;
    if (m373() && gdt::getFlag_Water_Relic_BattleTime())
        return false;
    if (m378() == 0)
        return false;

    const auto* gparam = getParam()->getRes().mGParamList->getPlayer();
    if (_cf0.isOnBit(23))
        return sub_7100881B14(gparam->mBowSlowInvalidHeightOnShield.ref());
    if (!(_1e9c <= sead::Mathf::epsilon()))
        return sub_7100881B14(gparam->mBowSlowInvalidHeightWeaponChange.ref());
    f32 height = gparam->mBowSlowInvalidHeight.ref();
    if (x_48())
        height = uking::sUnk_7101e7c2a8;
    return sub_7100881B14(height);
}

// Here, not in actPlayer.cpp: the original calls sub_7100867D68 out of line.
void Player::sub_710085C55C() {
    sead::Vector3f start = _1770;
    start.y = _20d4;
    sead::Vector3f end = start;
    start.y += 1.0f;
    end.y -= 1.0f;
    sead::Vector3f normal = sead::Vector3f::ey;
    sub_710087F4F8(start, end, nullptr, &normal);
    const f32 normal_yaw = std::atan2(normal.x, normal.z);
    const f32 factor = std::cos(sub_7100867D68() - normal_yaw);
    const f32 pitch = std::atan2(normal.y, std::sqrt(normal.x * normal.x + normal.z * normal.z));
    const f32 target = factor * (sead::Mathf::piHalf() - pitch);
    sead::Mathf::chase(&_1fa0, target, VFR::instance()->getDeltaFrame() * 0.01f);
}

// Here, not in actPlayer.cpp: there the call to x_24 drops the unused -1.0f argument, which the original passes.
void Player::sub_71008B5B8() {
    if (_c40.isOnBit(3) || !m226())
        return;
    if (_17d0->playerCheckController(13) && !m202() && !_c44.isOnBit(13) && !m178())
        return;
    if (_d68 != getEquipmentTypeName(2))
        return;
    x_24(-1.0f);
    _d68 = getEquipmentTypeName(0);
}

// Here, not in actPlayer.cpp: the original calls playerWeapons_return0 out of line.
void Player::x_10(bool on) {
    getWeapons()->mWeapons[0]._10 = false;
    snd::Unk_7102502138::instance()->sub_710103B41C(true);
    if (!on && sub_710000759C() && _d24 == 0 && !_cf0.isOnBit(23) && !isRidingHorse() && !m193() &&
        !_cf4.isOnBit(29)) {
        x_7();
    }
    const s32 slot = playerWeapons_return0();
    auto* weapon = getWeapons()->getEquippedWeapon(slot);
    if (auto* sword = sead::DynamicCast<uking::act::Weapon>(weapon))
        mASList->goLimpFromHeadShotMaybe(44, sword->getProfile(), 0);
    _1d04 = 15.0f;
    _1d08 = 15.0f;
    _1d0c = -1.0f;
    x_40();
    _c44.resetBit(11);
}

// Here, not in actPlayer.cpp: the original calls sub_7100885818 out of line.
// NON_MATCHING: switch block layout (the original places case 1 last) and tail merging of the level loads.
f32 Player::m233(int type) {
    if (sub_710084CBE4())
        return 0.0f;
    f32 rate;
    s32 level;
    switch (type) {
    case 0:
        rate = _23e0.sub_7100E2F61C()->isOnBit(13) ?
                   getParam()->getRes().mGParamList->getPlayer()->mArmorCompWeaponBrakeRate.ref() :
                   1.0f;
        level = _2060;
        break;
    case 2:
        rate = _23e0.sub_7100E2F61C()->isOnBit(15) ?
                   getParam()->getRes().mGParamList->getPlayer()->mArmorCompWeaponBrakeRate.ref() :
                   1.0f;
        level = _2068;
        break;
    case 3:
        rate = (_23e0.sub_7100E2F61C()->_2 & 1) ?
                   getParam()->getRes().mGParamList->getPlayer()->mArmorCompWeaponBrakeRate.ref() :
                   1.0f;
        level = _206c;
        break;
    case 4:
        rate = (_23e0.sub_7100E2F61C()->_2 & 2) ?
                   getParam()->getRes().mGParamList->getPlayer()->mArmorCompWeaponBrakeRate.ref() :
                   1.0f;
        level = _2070;
        break;
    default:
        return 1.0f;
    case 1:
        rate = _23e0.sub_7100E2F61C()->isOnBit(14) ?
                   getParam()->getRes().mGParamList->getPlayer()->mArmorCompWeaponBrakeRate.ref() :
                   1.0f;
        level = _2064;
        break;
    }
    return rate * sub_7100885818(level);
}

// Here, not in actPlayer.cpp: the original calls isSurfingOnGround and sub_7100887554 out of line.
// NON_MATCHING: instruction order of the _cf4 load and the 0.0f in the first branch.
void Player::m74() {
    f32 angle = 0.0f;
    bool flag;
    if ((!_cec.isOnBit(1) || mASList->x_1(0, 0) == "WallDash") && !_cf0.isOnBit(10)) {
        flag = _cf4.isOnBit(1);
    } else if (_209c > 0.05f && !isSurfingOnGround()) {
        const f32 value = mASList->sub_710115EC98(6, nullptr, 0);
        const f32 max = getParam()->getRes().mGParamList->getPlayer()->mPredictDiffAngleMax.ref();
        flag = true;
        angle = sead::Mathf::clamp(value, -max, max);
    } else {
        flag = true;
    }
    if (_2080) {
        _1870->sub_7100EB58A4(angle, this, _1b18, flag);
        _2080 = false;
    }
    Actor::m74();
    sub_7100887554();
}

// In this file because x_24 is out of line: a same-file call drops the 3.0 argument the original passes.
// Placeholder name (CSV Player::m69_x_5): with m225() or m226(), while _d68 names the equipment of type 4:
// on AS 0x53 hands the connected calc child to sub_71005DC208 at the bone _19f0[45] and sets _d11, then
// sub_710088D654 on AS 0x45; otherwise sub_710088D654 on AS 0x53 / 0x54 / 0x45, and x_24(3) once AS slot 2 is done.
void Player::m69_x_5() {
    if (!m225() && !m226())
        return;

    if (_d68 == getEquipmentTypeName(4)) {
        if (mASList->x(0x53, nullptr, 1, 1, &as::ASList::Unk2::sub_71011637EC, true)) {
            if (auto* child = getConnectedCalcChild()) {
                const auto& key = _19f0[45];
                sead::Matrix34f mtx;
                mModel->getUnits()[key.model_unit_index]->mModelUnit->getBoneWorldMatrix(
                    &mtx, key.bone_index);
                ActorLinkConstDataAccess accessor(child);
                accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
                sub_71005DC208(this, static_cast<Actor*>(child), 0);
                _d11 = true;
            }
        }
        if (mASList->x(0x45, nullptr, 1, 1, &as::ASList::Unk2::sub_71011637EC, true))
            sub_710088D654();
        return;
    }

    if (mASList->x(0x53, nullptr, 2, 0, &as::ASList::Unk2::sub_71011637EC, true) ||
        mASList->x(0x54, nullptr, 2, 0, &as::ASList::Unk2::sub_71011637EC, true) ||
        mASList->x(0x45, nullptr, 1, 1, &as::ASList::Unk2::sub_71011637EC, true)) {
        sub_710088D654();
    }
    if (mASList->x_4(2, 0))
        x_24(3.0f);
}

// In this file because x_35 is out of line in the original (actPlayer.cpp inlines it).
// Placeholder name: false with x_35(); true unless AS slot 1 (x_7) is busy or plays WaitUpper / MoveUpper /
// SquatWaitUpper / SquatMoveUpper, else sub_71007D86B4.
bool Player::sub_710087B1F0() {
    if (x_35())
        return false;
    if (!mASList->x_7(1, 1, &as::ASList::Unk2::sub_710002E82C))
        return true;
    return mASList->x_1(1, 1) == "WaitUpper" || mASList->x_1(1, 1) == "MoveUpper" ||
           mASList->x_1(1, 1) == "SquatWaitUpper" || mASList->x_1(1, 1) == "SquatMoveUpper" ||
           sub_71007D86B4(this);
}

// In this file because getStatusEffectQuietness is out of line in the original.
// Placeholder name: _2094 = quietness for the level _1fd8 + _2024.
void Player::sub_710086DD00() {
    _2094 = getStatusEffectQuietness(s32(_1fd8 + static_cast<f32>(_2024)));
}

// In this file because sub_710086DB94 is out of line in the original.
// NON_MATCHING: argument setup order of the first x_3 call in the x_30() branch (scheduling only).
// Placeholder name: bow reload start (controller check 18 or `force`): plays BowReload and sets the AS rates, with
// the bow slow time (BowSlowRateDiam / BowSlowMaxTime) when x_30() allows it.
bool Player::sub_7100883220(bool force) {
    if (_c44.isOnBit(9)) {
        if (_17d0->playerCheckController(18))
            return false;
        _c44.resetBit(9);
    }
    if (_1d40.value <= sead::Mathf::epsilon() && (_17d0->playerCheckController(18) || force)) {
        _c50.setBit(5);
        x_23("BowReload", false, -1.0f);
        if (isSlowTime()) {
            f32 rate = 1.0f;
            if (isSlowTime() && _cf4.isOnBit(17))
                rate = getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
            mASList->x_3(1, 1, &as::ASList::Unk2::sub_71011631BC, rate);
            return true;
        }
        if (!x_30())
            return true;

        mASList->x_3(1, 1, &as::ASList::Unk2::sub_71011631BC,
                     getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref());
        const f32 rate = getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
        mASList->x_3(0, 0, &as::ASList::Unk2::sub_71011631BC, rate);
        mASList->x_3(1, 0, &as::ASList::Unk2::sub_71011631BC, rate);
        mASList->x_3(2, 0, &as::ASList::Unk2::sub_71011631BC,
                     getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref());
        if (!isSlowTime()) {
            _c50.setBit(11);
            _1cc1 = false;
            const f32 time =
                sub_710086DB94(getParam()->getRes().mGParamList->getPlayer()->mBowSlowMaxTime.ref());
            _1d70.reset(time);
        }
        return true;
    }
    return false;
}

// NON_MATCHING: the original calls getPosCopyMagnesis() separately in each branch of the draw ratio and passes
// constant flags (block layout).
// Placeholder name: fires the bow (weapon slot 2 request with the aim position; the draw ratio when _1f88 is 2), starts
// the _1d40 cooldown and plays BowShoot. In this file because sub_7100883698 is out of line in the original.
void Player::sub_710088349C() {
    if (_1cb0 == 0x47)
        uking::ui::sub_7100A95F5C(0x47);
    const bool charged = _1f88 == 2;
    const sead::Vector3f* target = m245();
    f32 ratio = 0.0f;
    if (charged) {
        ratio = (mASList->x_5(1, 1, &as::ASList::Unk2::sub_71011632F8) -
                 mASList->x_5(1, 1, &as::ASList::Unk2::sub_71011630A4)) /
                (mASList->x_5(1, 1, &as::ASList::Unk2::sub_710116323C) -
                 mASList->x_5(1, 1, &as::ASList::Unk2::sub_71011630A4));
    }
    sub_71005D80FC(this, 2, *target, charged, ratio, getPosCopyMagnesis(), &_22d8);
    _1d40.reset(sub_7100883698());
    _c50.setBit(6);
    x_23("BowShoot", false, -1.0f);
    if (isSlowTime()) {
        f32 rate = 1.0f;
        if (isSlowTime() && _cf4.isOnBit(17))
            rate = getParam()->getRes().mGParamList->getPlayer()->mBowSlowRateDiam.ref();
        mASList->x_3(1, 1, &as::ASList::Unk2::sub_71011631BC, rate);
    }
}

// Placeholder name: whether the player is busy (bow, push, upper-body damage or item ready animations, ...). In this
// file because sub_710087B0CC is out of line in the original.
bool Player::sub_7100890394() {
    return _d11 || _cf0.isOnBit(22) || m224() || playerIsReloadingOrChargingOrShootingBow(this) ||
           (_c44.isOnBit(8) && !_d11) || sub_71007D86B4(this) || sub_710087B0CC() ||
           mASList->x_1(1, 1) == "DamageSUpper" || mASList->x_1(1, 1) == "ItemCommonReady" ||
           mASList->x_1(1, 1) == "ItemBombReady";
}

// Placeholder name: when the upper body (AS slot 1) plays ItemCommonReady / ItemMagneCatchStart / ItemCommonStart
// and the full body does not, switches the full body to it. In this file because sub_7100855824 is out of line.
void Player::sub_710088C5A4() {
    if (mASList->x_1(1, 1) == "ItemCommonReady" && mASList->x_1(0, 0) != "ItemCommonReady") {
        switchToAnimSequenceMaybe("ItemCommonReady", true, -1.0f);
        sub_7100855824();
    }
    if (mASList->x_1(1, 1) == "ItemMagneCatchStart" && mASList->x_1(0, 0) != "ItemMagneCatchStart") {
        switchToAnimSequenceMaybe("ItemMagneCatchStart", true, -1.0f);
        sub_7100855824();
    }
    if (mASList->x_1(1, 1) == "ItemCommonStart" && mASList->x_1(0, 0) != "ItemCommonStart") {
        switchToAnimSequenceMaybe("ItemCommonStart", true, -1.0f);
        sub_7100855824();
    }
}

// Placeholder name: item equip animation follow-up (ItemEquipLeftOn / ItemEquipRight) for weapon slots 0 / 1.
void Player::sub_710088A388() {
    if (mASList->x_1(2, 0) == "ItemEquipLeftOn" && _d68 != getEquipmentTypeName(6) &&
        _d68 != getEquipmentTypeName(0)) {
        getWeapons()->mWeapons[1]._10 = true;
        _c40.resetBit(3);
        sub_7100888278();
        snd::Unk_7102502138::instance()->sub_710103B430(false);
        return;
    }

    x_16();
    getWeapons()->mWeapons[0]._10 = true;
    snd::Unk_7102502138::instance()->sub_710103B41C(false);
    if (mASList->x_1(2, 0) == "ItemEquipRight")
        return;
    if (!_c40.isOnBit(3) || !sub_71008921A8() || _cf0.isOnBit(23))
        return;
    if (mASList->x_1(0, 0) == "WeaponThrow" || mASList->x_1(1, 1) == "WeaponThrow")
        return;
    if (_cf0.isOnBit(25) && _d68 == getEquipmentTypeName(0))
        return;
    getWeapons()->mWeapons[1]._10 = true;
    _c40.resetBit(3);
    sub_7100888278();
    snd::Unk_7102502138::instance()->sub_710103B430(false);
}

}  // namespace ksys::act
