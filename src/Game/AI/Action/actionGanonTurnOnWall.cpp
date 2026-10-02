#include "Game/AI/Action/actionGanonTurnOnWall.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

GanonTurnOnWall::GanonTurnOnWall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonTurnOnWall::~GanonTurnOnWall() = default;

bool GanonTurnOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonTurnOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonTurnOnWall::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonTurnOnWall::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonTurnOnWall::calc_() {
    ksys::act::ai::Action::calc_();
}

void GanonTurnOnWall::m32(f32 x) {
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, x, controller->get70());
}

void GanonTurnOnWall::m33(sead::Vector3f* up) {
    if (auto* controller = mActor->getCharacterController())
        up->set(controller->get70());
    else
        up->set(sead::Vector3f::ey);
}

}  // namespace uking::action
