#include "Game/AI/Action/actionGanonMove.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModel.h"

namespace uking::action {

GanonMove::GanonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonMove::~GanonMove() = default;

bool GanonMove::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _c8.search(model, "Head");
    else
        _c8.getKey().reset();
    return true;
}

void GanonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonMove::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void GanonMove::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveAccel_s, "MoveAccel");
    getStaticParam(&mAvoidMoveSpeed_s, "AvoidMoveSpeed");
    getStaticParam(&mAvoidMoveAccel_s, "AvoidMoveAccel");
    getStaticParam(&mIsUpEqualGravity_s, "IsUpEqualGravity");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mDstPos_d, "DstPos");
}

void GanonMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
