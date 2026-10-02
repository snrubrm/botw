#include "Game/AI/AI/aiGiantSleepNormal.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GiantSleepNormal::GiantSleepNormal(const InitArg& arg) : SpecialEnemySleep(arg) {}

GiantSleepNormal::~GiantSleepNormal() = default;

bool GiantSleepNormal::init_(sead::Heap* heap) {
    if (!SpecialEnemySleep::init_(heap))
        return false;
    _78 = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), mAwakeRbName_s.cstr());
    return true;
}

void GiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void GiantSleepNormal::leave_() {
    SpecialEnemySleep::leave_();
}

void GiantSleepNormal::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mForceAwakeDist_s, "ForceAwakeDist");
    getStaticParam(&mAwakeRbName_s, "AwakeRbName");
}

void GiantSleepNormal::m34() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E9BC(0);
    SpecialEnemySleep::m34();
}

void GiantSleepNormal::m35() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E9BC(0);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_80, "TargetPos", -1);
    changeChild("待機", &params);
}

}  // namespace uking::ai
