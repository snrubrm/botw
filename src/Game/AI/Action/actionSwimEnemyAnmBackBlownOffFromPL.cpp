#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOffFromPL.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SwimEnemyAnmBackBlownOffFromPL::SwimEnemyAnmBackBlownOffFromPL(const InitArg& arg)
    : SwimEnemyAnmBackBlownOff(arg) {}

SwimEnemyAnmBackBlownOffFromPL::~SwimEnemyAnmBackBlownOffFromPL() = default;

bool SwimEnemyAnmBackBlownOffFromPL::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOff::init_(heap);
}

void SwimEnemyAnmBackBlownOffFromPL::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimEnemyAnmBackBlownOff::enter_(params);
}

void SwimEnemyAnmBackBlownOffFromPL::leave_() {
    SwimEnemyAnmBackBlownOff::leave_();
}

void SwimEnemyAnmBackBlownOffFromPL::loadParams_() {
    SwimEnemyAnmBackBlownOff::loadParams_();
}

void SwimEnemyAnmBackBlownOffFromPL::calc_() {
    SwimEnemyAnmBackBlownOff::calc_();
}

// NON_MATCHING: same instructions; x / z live in swapped callee-saved registers (s8 / s9) and the normalisation
// multiplies are scheduled differently
void SwimEnemyAnmBackBlownOffFromPL::m32(sead::Vector3f* out) {
    const sead::Vector3f& player = getPlayerPosition();
    sead::Vector3f dir = mActor->getMtx().getTranslation() - player;
    dir.y = 0;
    dir.normalize();
    *out = dir;
}

}  // namespace uking::action
