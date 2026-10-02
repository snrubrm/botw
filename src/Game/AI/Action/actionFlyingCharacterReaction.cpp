#include "Game/AI/Action/actionFlyingCharacterReaction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

FlyingCharacterReaction::FlyingCharacterReaction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FlyingCharacterReaction::~FlyingCharacterReaction() = default;

bool FlyingCharacterReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlyingCharacterReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FlyingCharacterReaction::leave_() {
    if (*mIsSetBackLastState_s)
        mCCAccessor.resetMotionType(mCCAccessor.sub_710072ACF8(mActor));
}

void FlyingCharacterReaction::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsControlRotation_s, "IsControlRotation");
    getStaticParam(&mIsSetBackLastState_s, "IsSetBackLastState");
}

void FlyingCharacterReaction::calc_() {
    ksys::act::ai::Action::calc_();
}

void FlyingCharacterReaction::m32() {}

void FlyingCharacterReaction::m33() {}

void FlyingCharacterReaction::m34(ksys::phys::CharacterController* controller) {
    sub_7100737C0C(controller, *mPosReduceRatio_s, controller->get70());
    if (!*mIsControlRotation_s) {
        sub_7100738660(controller, *mRotReduceRatio_s);
        return;
    }

    sead::Vector3f dir = mActor->getVelocity();
    dir.negate();
    dir.normalize();
    if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f)
        dir = -controller->get7c();
    sub_710073FA94(&_40, mActor);
    sub_7100740118(&_40, dir, 0.3f, 2 * sead::Mathf::pi(), 0.0f);
    sub_7100740E04(_40, controller);
}

void FlyingCharacterReaction::m35() {}

void FlyingCharacterReaction::m36() {}

void FlyingCharacterReaction::m37(ksys::phys::CharacterController* controller) {}

bool FlyingCharacterReaction::m38() {
    auto* actor = mActor;
    if (ksys::act::sub_71007A4638(actor, false))
        return true;
    return ksys::act::sub_71007A4864(actor, false);
}

}  // namespace uking::action
