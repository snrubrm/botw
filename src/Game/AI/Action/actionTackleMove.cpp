#include "Game/AI/Action/actionTackleMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TackleMove::TackleMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TackleMove::~TackleMove() = default;

bool TackleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    sub_710072C1B4(controller, front);
    sub_710073FA90(&_64, actor);
    _58 = ksys::Timer(0.0f, 0.0f, 1.0f);
}

void TackleMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void TackleMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFailAngle_s, "FailAngle");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void TackleMove::calc_() {
    ksys::act::ai::Action::calc_();
}

void TackleMove::m32(sead::Vector3f* pos) {
    pos->set(*mTargetPos_d);
}

void TackleMove::m33() {
    setFailed();
}

f32 TackleMove::m34() {
    return *mSpeed_s;
}

f32 TackleMove::m35() {
    return 0.2f;
}

}  // namespace uking::action
