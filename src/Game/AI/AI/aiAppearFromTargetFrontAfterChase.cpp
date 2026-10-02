#include "Game/AI/AI/aiAppearFromTargetFrontAfterChase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

AppearFromTargetFrontAfterChase::AppearFromTargetFrontAfterChase(const InitArg& arg)
    : AppearNearTarget(arg) {}

AppearFromTargetFrontAfterChase::~AppearFromTargetFrontAfterChase() = default;

void AppearFromTargetFrontAfterChase::enter_(ksys::act::ai::InlineParamPack* params) {
    AppearNearTarget::enter_(params);
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

}  // namespace uking::ai
