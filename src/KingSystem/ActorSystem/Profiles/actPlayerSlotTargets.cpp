#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include "Game/gameSceneSubsys14.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::act {

void Player::x_40() {
    _1d6c = 1.0f;
    _c40.reset(0x1200000);
    _1d64 = 0.0f;
    _1d68 = 0.0f;
    _1f8c = 0;
    _1f84 = 0;
    if (_c44.isOnBit(8)) {
        if (mASList->x_1(1, 1) != "WeaponThrow") {
            _c44.resetBit(8);
            x_18(true);
        }
    }
}

// These two sit in their own file: Player::m296 / m298 tail-call them in the original.
s32 Player::sub_7100892824() {
    if (_cf4.isOnBit(15))
        return _17f1 ? 1 : 2;
    if (!m224())
        return 0;
    if (_d24 != 0)
        return 0;
    if (mASList->sub_710115ED5C(0x42, 0x24) && mASList->sub_710115ED5C(0x42, 0x26))
        return 0;
    return _1f8c == 2 ? 1 : 2;
}

s32 Player::sub_71008923B0(int a1) {
    switch (a1) {
    case 0:
        return 4;
    case 1:
        return 2;
    case 2:
        return 5;
    default:
        return 0;
    }
}

// Placeholder name: whether AS slot 0 plays a sword cut (CutL1, CutS1-4, CutSF, CutDash).
bool Player::sub_71008923D0() {
    return mASList->x_1(0, 0) == "CutL1" || mASList->x_1(0, 0) == "CutS1" ||
           mASList->x_1(0, 0) == "CutS2" || mASList->x_1(0, 0) == "CutS3" ||
           mASList->x_1(0, 0) == "CutS4" || mASList->x_1(0, 0) == "CutSF" ||
           mASList->x_1(0, 0) == "CutDash";
}

// NON_MATCHING: the inlined copy of x_40 has its stores scheduled differently (the original keeps the order of the
// out-of-line x_40)
void Player::x_16() {
    _c40.resetBit(24);
    if (x_17())
        x_18(true);
    x_40();
    x_19(-1.0f);
}

// NON_MATCHING: load scheduling only (_1770.y before the parameter buffer, the angle mask before _1c84).
// In this file because the original calls sub_710087F360 out of line.
// Sets the move animation rate (AS slot 0): the stick tilt (or 1.5 / _1fa8), capped while the scene limits it,
// slowed in deep water and stopped when facing the grabbed / pushed actor.
void Player::x_27() {
    f32 rate;
    if (m178()) {
        _1fa8 = 1.5f;
        _c48.resetBit(27);
        rate = 1.5f;
    } else {
        rate = _1fa8;
        if (!(rate > 1.0f))
            rate = std::min(_17d0->getLeftStick().length(), 1.0f);
    }

    if (GameSceneSubsys14::instance()->sub_7100904F10() && !m178()) {
        const f32 max = getParam()->getRes().mGParamList->getPlayer()->mStickMaxInStore.ref();
        if (rate > max)
            rate = max;
    }

    if (_cfc.isOn(0x12)) {
        f32 depth;
        if (_cfc.isOnBit(4))
            depth = getParam()->getRes().mGParamList->getPlayer()->mWaterDepthInGrudge.ref();
        else
            depth = _20d4 - _1770.y;
        const auto* param = getParam()->getRes().mGParamList->getPlayer();
        depth -= param->mMoveIgnoreWaterHeight.ref();
        f32 factor;
        if (depth > 0.0f) {
            const f32 ratio = std::min(
                depth / (param->mMoveDecRateMaxHeight.ref() - param->mMoveIgnoreWaterHeight.ref()), 1.0f);
            factor = sead::Mathf::min(1.0f - param->mMoveDecRateByBog.ref() * ratio, 1.0f);
        } else {
            factor = 1.0f;
        }
        rate *= factor;
    }

    if (_cfc.isOnBit(6) || _c48.isOnBit(27)) {
        auto* child = sead::DynamicCast<Actor>(getConnectedCalcChild());
        if (child) {
            if (auto* body = child->getPhysicsMainBody()) {
                sead::Vector3f dir;
                _1b18.getBase(dir, 2);
                dir.normalize();
                const sead::Vector3f start = body->getCenterOfMassInWorld();
                const sead::Vector3f end = start + dir * _1fec * 1.5f;
                sead::Vector3f hit;
                if (sub_710087F360(start, end, nullptr, &hit)) {
                    _1c84 = sead::Mathf::atan2Idx(hit.x, hit.z);
                } else {
                    _cfc.reset(0x60);
                    _c48.resetBit(27);
                }
            }
        }
    }

    if (_cfc.isOnBit(5) || _c48.isOnBit(27)) {
        if (_cfc.isOnBit(6)) {
            _c48.setBit(27);
            _1c78 = _1c74;
        }
        if (util::sub_71011EE4C0(s64(_1c84) - (util::sUnk_7101EC6BA0 & (_1c74 ^ 0x80000000))) < 0x4000000)
            rate = 0.0f;
        else if (rate > 0.15f)
            rate = 0.15f;
    }

    if (x_44())
        rate *= getParam()->getRes().mGParamList->getPlayer()->mStickDiamTired.ref();
    mASList->sub_710115EFD0(0, false, false, rate);
}

}  // namespace ksys::act
