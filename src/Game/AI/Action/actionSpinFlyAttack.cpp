#include "Game/AI/Action/actionSpinFlyAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMatrix.h>

namespace uking::action {

SpinFlyAttack::SpinFlyAttack(const InitArg& arg) : LinearFlyAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SpinFlyAttack::~SpinFlyAttack() {
    ;
}

bool SpinFlyAttack::init_(sead::Heap* heap) {
    return LinearFlyAttack::init_(heap);
}

void SpinFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    LinearFlyAttack::enter_(params);
    _e0.value = 0;
    _e0.prev_value = 0;
}

void SpinFlyAttack::leave_() {
    LinearFlyAttack::leave_();
}

void SpinFlyAttack::loadParams_() {
    LinearFlyAttack::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SpinFlyAttack::calc_() {
    _e0.lerp(*mRotSpeed_s, 0.5f);
    _e0.updateStats();
    LinearFlyAttack::calc_();
}

// NON_MATCHING: floating-point operation order and register allocation in the rotation (makeR + multiply)
void SpinFlyAttack::m33(sead::Vector3f* dir) {
    sead::Vector3f axis;
    mActor->getMtx().getBase(axis, 2);
    axis.normalize();
    sead::Vector3f up;
    mActor->getMtx().getBase(up, 1);
    up.normalize();
    sead::Matrix33f rot;
    rot.makeR(axis * _e0.mean);
    dir->setMul(rot, up);
}

}  // namespace uking::action
