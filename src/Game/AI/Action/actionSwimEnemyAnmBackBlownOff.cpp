#include "Game/AI/Action/actionSwimEnemyAnmBackBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
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

// NON_MATCHING: the original keeps `this + 0x9c` in a register (pre-indexed load) and reads _9c.z through it
void SwimEnemyAnmBackBlownOff::m33() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    sub_7100737C0C(controller, *mPosReduceRatio_s, controller->get7c());
    if (_9c.x == 0.0f && _9c.z == 0.0f) {
        sub_7100738660(controller, *mRotReduceRatio_s);
        return;
    }

    const sead::Vector3f up = -controller->get7c();
    sub_710073FA94(&_78, mActor);
    sub_71007407F0(&_78, _9c, up, true, *mRotSpeed_s);
    sub_7100740E04(_78, controller);
}

}  // namespace uking::action
