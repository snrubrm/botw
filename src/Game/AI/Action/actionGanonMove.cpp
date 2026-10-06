#include "Game/AI/Action/actionGanonMove.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModelAccessKey.h"
#include "gsys/gsysModel.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

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
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    if (*mIsUpEqualGravity_s) {
        _8c = controller->get70();
        _8c.normalize();
    } else {
        _8c = sead::Vector3f::ey;
    }
    mActor->getASList()->x_6(9, 0, 0.0f);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    _70 = sead::Mathf::sqrt(mActor->getVelocity().x * mActor->getVelocity().x +
                            mActor->getVelocity().z * mActor->getVelocity().z);
    sub_7100741034(&_98, mActor);
    _74 = *mDstPos_d;
    _80 = mActor->getVelocity();
    if (*mIsChangeable_d)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    _bc[1] = 0;
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
