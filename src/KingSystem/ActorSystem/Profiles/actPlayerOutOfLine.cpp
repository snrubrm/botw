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
#include "KingSystem/Utils/MathUtil.h"
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


}  // namespace ksys::act
