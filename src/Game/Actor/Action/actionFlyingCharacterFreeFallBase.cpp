#include "Game/Actor/Action/actionFlyingCharacterFreeFallBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

FlyingCharacterFreeFallBase::FlyingCharacterFreeFallBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FlyingCharacterFreeFallBase::~FlyingCharacterFreeFallBase() = default;

bool FlyingCharacterFreeFallBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: ours hoists the mActor load of both branches above the branch
void FlyingCharacterFreeFallBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    mCCAccessor.changeMotionType(controller, ksys::act::MotionType::_1);
    sub_710073FA90(&_40, mActor);
    _64 = isBgGroundHit(mActor, false);
    if (_64) {
        ksys::eft::searchAndEmitSLink(mActor, "FallGround", false);
        if (auto* as_list = mActor->getASList())
            as_list->x_2(66, 17, false, false);
        m35();
        m36();
    } else {
        if (auto* as_list = mActor->getASList())
            as_list->x_2(66, 17, true, false);
        m32();
        m33();
    }
}

void FlyingCharacterFreeFallBase::leave_() {
    if (*mIsSetBackLastState_s)
        mCCAccessor.resetMotionType(mCCAccessor.sub_710072ACF8(mActor));
}

void FlyingCharacterFreeFallBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsControlRotation_s, "IsControlRotation");
    getStaticParam(&mIsSetBackLastState_s, "IsSetBackLastState");
}

void FlyingCharacterFreeFallBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    if (m38()) {
        if (!_64) {
            ksys::eft::searchAndEmitSLink(mActor, "FallGround", false);
            if (auto* as_list = mActor->getASList())
                as_list->x_2(66, 17, false, false);
            m35();
            m36();
        }
        _64 = true;
        m37(controller);
    } else {
        if (_64) {
            if (auto* as_list = mActor->getASList())
                as_list->x_2(66, 17, true, false);
            m32();
            m33();
        }
        _64 = false;
        m34(controller);
    }
}

void FlyingCharacterFreeFallBase::m32() {}

void FlyingCharacterFreeFallBase::m33() {}

void FlyingCharacterFreeFallBase::m34(ksys::phys::CharacterController* controller) {
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

void FlyingCharacterFreeFallBase::m35() {}

void FlyingCharacterFreeFallBase::m36() {}

void FlyingCharacterFreeFallBase::m37(ksys::phys::CharacterController* controller) {}

bool FlyingCharacterFreeFallBase::m38() {
    auto* actor = mActor;
    if (isLandedMaybe(actor, false))
        return true;
    return isBgGroundHit(actor, false);
}

}  // namespace uking::action
