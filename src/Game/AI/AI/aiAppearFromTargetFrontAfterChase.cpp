#include "Game/AI/AI/aiAppearFromTargetFrontAfterChase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

AppearFromTargetFrontAfterChase::AppearFromTargetFrontAfterChase(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearFromTargetFrontAfterChase::~AppearFromTargetFrontAfterChase() = default;

void AppearFromTargetFrontAfterChase::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
}

void AppearFromTargetFrontAfterChase::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("湧出")) {
            changeToSpawnAppear();
            return;
        }
    }

    if (isCurrentChild("湧出準備")) {
        sub_71005DD34C(mActor, false);
        AppearNearTarget::calc_();
        return;
    }

    if (getCurrentChild()->isChangeable() && isCurrentChild("湧出")) {
        sub_71005DD34C(mActor, false);
        const sead::Vector3f target = sub_71005D9330(mActor);
        getCurrentChild()->setDynamicParam(target, "TargetPos");
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const sead::Vector2f diff(target.x - pos.x, target.z - pos.z);
        if (diff.length() <= *mAppearDist_s)
            changeToSpawnAppear();
        return;
    }

    if (!isCurrentChild("湧出出現")) {
        AppearNearTarget::calc_();
        return;
    }

    if (!(_98.value <= sead::Mathf::epsilon())) {
        _98.update();
        if (_98.value <= sead::Mathf::epsilon()) {
            ksys::act::enableAllAttClients(mActor);
            sub_71007A3800(mActor);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            mActor->getXLink()->_cc.set(0x80000);
            sub_71005DD34C(mActor, true);
        }
    }
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
}

void AppearFromTargetFrontAfterChase::leave_() {
    ksys::act::enableAllAttClients(mActor);
    sub_71007A3800(mActor);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.set(0x80000);
    sub_71005DD34C(mActor, true);
    AppearNearTarget::leave_();
}

void AppearFromTargetFrontAfterChase::loadParams_() {
    AppearNearTarget::loadParams_();
    getStaticParam(&mAppearDist_s, "AppearDist");
}

void AppearFromTargetFrontAfterChase::m37(const sead::Vector3f& pos) {
    ksys::act::disableAllAttClients(mActor);
    sub_71007A397C(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->getXLink()->_cc.reset(0x80000);
    sub_71005DD34C(mActor, false);
    AppearNearTarget::m37(pos);
}

void AppearFromTargetFrontAfterChase::changeToSpawnAppear() {
    _98 = ksys::Timer(3.0f, 3.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("湧出出現", &pack);
}

}  // namespace uking::ai
