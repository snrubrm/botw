#include "Game/Actor/AI/aiGuardianChase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianChase::GuardianChase(const InitArg& arg) : GuardianAI(arg) {}

GuardianChase::~GuardianChase() = default;

bool GuardianChase::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianChase::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    if (sub_710040DEE0())
        changeChild("戦闘");
    else
        changeChild("移動");
}

void GuardianChase::calc_() {
    GuardianAI::calc_();
    auto* guardian = sub_710040DA6C();
    if (!guardian) {
        setFailed();
        return;
    }

    const f32 range = *mChaseRange_m;
    if (guardian->_18c8._34 > range * range) {
        sead::Vector3f home;
        guardian->getHomePos(&home);
        sead::Vector3f dir = guardian->_c48._18 - home;
        dir.normalize();
        const sead::Vector3f target = dir * range + home;

        auto* child = getCurrentChild();
        if (!child->isFinished() && !child->isFailed() && isCurrentChild("範囲外")) {
            child->setDynamicParam(target, "DynTargetPos");
            return;
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "DynTargetPos", -1);
        pack.addVec3(mActor->getMtx().getTranslation(), "DynStartPos", -1);
        changeChild("範囲外", &pack);
        return;
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        child->isChangeable();
        return;
    }

    if (isCurrentChild("回避")) {
        if (sub_710040DEE0())
            changeChild("戦闘");
        else
            changeChild("移動");
    } else if (isCurrentChild("戦闘")) {
        if (child->isFinished()) {
            setFinished();
            return;
        }
        changeChild("移動");
    } else if (isCurrentChild("移動")) {
        if (!child->isFinished()) {
            setFailed();
            return;
        }
        changeChild("戦闘");
    }
}

void GuardianChase::leave_() {
    GuardianAI::leave_();
}

void GuardianChase::loadParams_() {
    GuardianAI::loadParams_();
    getMapUnitParam(&mChaseRange_m, "ChaseRange");
}

}  // namespace uking::ai
