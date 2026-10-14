#include "Game/AI/AI/aiLynelNavMoveTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LynelNavMoveTarget::LynelNavMoveTarget(const InitArg& arg) : LynelNavMoveNoStop(arg) {}

LynelNavMoveTarget::~LynelNavMoveTarget() = default;

bool LynelNavMoveTarget::init_(sead::Heap* heap) {
    return LynelNavMoveNoStop::init_(heap);
}

void LynelNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelNavMoveNoStop::enter_(params);
}

void LynelNavMoveTarget::leave_() {
    LynelNavMoveNoStop::leave_();
}

void LynelNavMoveTarget::loadParams_() {
    LynelNavMoveNoStop::loadParams_();
    getStaticParam(&mStopGear_s, "StopGear");
    getStaticParam(&mCliffCheckDist_s, "CliffCheckDist");
}

void LynelNavMoveTarget::calc_() {
    const auto changeToLookAround = [this] {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("見まわす", &pack);
    };

    auto* child = getCurrentChild();
    if (isCurrentChild("ブレーキ")) {
        if (!child->isFinished() && !child->isFailed()) {
            sub_7100493058();
            sub_71004930D0();
            return;
        }
        if (sub_7100493790(false))
            return;
        if (!sub_7100492DDC()) {
            changeToLookAround();
            return;
        }
    } else if (isCurrentChild("回転")) {
        if (!child->isFinished() && !child->isFailed()) {
            sub_7100493058();
            return;
        }
        if (sub_710072E154(mActor, *mTargetPos_d, nullptr, -1)) {
            changeToGoStraight();
            return;
        }
        if (sub_7100492CB8()) {
            changeToMove();
            return;
        }
        if (!sub_7100492DDC()) {
            changeToLookAround();
            return;
        }
    } else if (isCurrentChild("見まわす")) {
        if (!child->isFinished() && !child->isFailed()) {
            if (child->isChangeable() && sub_7100493790(false))
                return;
            sub_7100493058();
            sub_71004930D0();
            return;
        }
        if (sub_7100493790(false))
            return;
    } else {
        LynelNavMoveNoStop::calc_();
        return;
    }
    sub_71004923C0();
    setFailed();
}

// NON_MATCHING: the CliffCheckDist load is scheduled before the front axis copy (the original loads it after).
void LynelNavMoveTarget::m34() {
    // Whether the rider's gear is at most StopGear.
    const auto isAtStopGear = [this] {
        auto* rideable = mActor->m132();
        if (!rideable)
            return false;
        const act::Rideable::Gear gear(
            *(rideable->_18._b == 0 ? &rideable->_18._9 : &rideable->_18._b));
        return int(gear) <= int(act::Rideable::Gear(*mStopGear_s));
    };
    const auto changeToLookAround = [this] {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("見まわす", &pack);
    };

    // sub_710072FEC4 along the actor's front axis over CliffCheckDist.
    const auto checkFront = [this] {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        return sub_710072FEC4(mActor, front, *mCliffCheckDist_s, nullptr, true, nullptr);
    };
    if (!checkFront()) {
        if (isAtStopGear() && !sub_7100492CB8()) {
            sub_7100492574();
            changeToLookAround();
            return;
        }
        LynelNavMoveNoStop::m34();
        return;
    }

    if (sub_7100493790(false))
        return;
    sub_7100492574();
    if (isAtStopGear()) {
        changeToLookAround();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("ブレーキ", &pack);
}

bool LynelNavMoveTarget::sub_7100493790(bool a1) {
    if (sub_710072E154(mActor, *mTargetPos_d, nullptr, -1)) {
        if (!a1 && !sub_7100492E34()) {
            const sead::Vector3f* target_pos = mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*target_pos, "TargetPos", -1);
            changeChild("回転", &pack);
            return true;
        }
        changeToGoStraight();
        return true;
    }

    if (!sub_7100492CB8())
        return false;

    if (a1) {
        changeToMove();
        return true;
    }

    sead::Vector3f dir;
    if (auto* nav = mActor->m45()) {
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            dir = nav->_248;
        }
        if (dir.dot(mActor->getMtx().getBase(2)) >= std::cos(sead::Mathf::pi() / 4)) {
            changeToMove();
            return true;
        }
    } else {
        dir.set(0.0f, 0.0f, 0.0f);
    }
    const sead::Vector3f target = dir * 5.0f + mActor->getMtx().getTranslation();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("回転", &pack);
    return true;
}

bool LynelNavMoveTarget::m35() {
    return true;
}

}  // namespace uking::ai
