#include "Game/AI/AI/aiGuardianRoam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianRoam::GuardianRoam(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoam::~GuardianRoam() = default;

bool GuardianRoam::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    auto* guardian = sub_710040DA6C();
    if (!guardian) {
        setFailed();
        return;
    }

    sead::Vector3f home_pos;
    guardian->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home_pos, "DynTargetPos", -1);
    pack.addVec3(mActor->getMtx().getTranslation(), "DynStartPos", -1);
    changeChild("移動", &pack);
    _48 = 0;
    _4c = 0;
}

void GuardianRoam::leave_() {
    GuardianAI::leave_();
}

void GuardianRoam::loadParams_() {
    GuardianAI::loadParams_();
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mMoveRadius_s, "MoveRadius");
}

}  // namespace uking::ai
