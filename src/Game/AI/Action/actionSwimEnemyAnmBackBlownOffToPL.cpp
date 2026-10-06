#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffToPL.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffToPL::SwimEnemyAnmBackBlownOffToPL(const InitArg& arg)
    : SwimEnemyAnmBackBlownOff(arg) {}

SwimEnemyAnmBackBlownOffToPL::~SwimEnemyAnmBackBlownOffToPL() = default;

bool SwimEnemyAnmBackBlownOffToPL::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOff::init_(heap);
}

void SwimEnemyAnmBackBlownOffToPL::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOff::enter_(params);
}

void SwimEnemyAnmBackBlownOffToPL::leave_() {
    SwimEnemyAnmBackBlownOff::leave_();
}

void SwimEnemyAnmBackBlownOffToPL::loadParams_() {
    SwimEnemyAnmBackBlownOff::loadParams_();
}

void SwimEnemyAnmBackBlownOffToPL::calc_() {
    SwimEnemyAnmBackBlownOff::calc_();
}

// NON_MATCHING: same instructions; x / z live in swapped callee-saved registers (s8 / s9) and the normalisation
// multiplies are scheduled differently
void SwimEnemyAnmBackBlownOffToPL::m32(sead::Vector3f* out) {
    const sead::Vector3f& player = getPlayerPosition();
    sead::Vector3f dir = player - mActor->getMtx().getTranslation();
    dir.y = 0;
    dir.normalize();
    *out = dir;
}

}  // namespace uking::action
