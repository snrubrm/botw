#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SwimEnemyAnmBackBlownOff::SwimEnemyAnmBackBlownOff(const InitArg& arg)
    : SwimEnemyAnmBackBlownOffBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SwimEnemyAnmBackBlownOff::~SwimEnemyAnmBackBlownOff() {
    ;
}

bool SwimEnemyAnmBackBlownOff::init_(sead::Heap* heap) {
    return SwimEnemyAnmBackBlownOffBase::init_(heap);
}

void SwimEnemyAnmBackBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the original copies the character controller position into a second Vector3f before
    // the call (and reuses its stack slot for the matrix); the stack frame differs
    SwimEnemyAnmBackBlownOffBase::enter_(params);
    sub_710073FA90(&_78, mActor);
    if (auto* cc = mActor->getCharacterController()) {
        const sead::Vector3f vel = cc->get64();
        _9c.set(-vel.x, -vel.y, -vel.z);
        sead::Vector3f pos;
        cc->sub_7100F5F6E0(&pos);
        sead::Matrix34f mtx;
        ksys::util::sub_71011F0260(&mtx, _9c, sead::Vector3f::ey, pos, false);
    }
}

void SwimEnemyAnmBackBlownOff::leave_() {
    SwimEnemyAnmBackBlownOffBase::leave_();
}

void SwimEnemyAnmBackBlownOff::loadParams_() {
    SwimEnemyAnmBackBlownOffBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SwimEnemyAnmBackBlownOff::calc_() {
    SwimEnemyAnmBackBlownOffBase::calc_();
}

}  // namespace uking::action
