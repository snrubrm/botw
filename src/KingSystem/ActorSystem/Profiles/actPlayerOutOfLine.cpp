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

}  // namespace ksys::act
