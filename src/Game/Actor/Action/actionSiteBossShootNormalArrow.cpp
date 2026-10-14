#include "Game/Actor/Action/actionSiteBossShootNormalArrow.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SiteBossShootNormalArrow::SiteBossShootNormalArrow(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShootNormalArrow::~SiteBossShootNormalArrow() = default;

bool SiteBossShootNormalArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShootNormalArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (!*mIsCheckASEvent_s)
        sub_7100263C64();
    sub_710073FA90(&_b0, mActor);
}

void SiteBossShootNormalArrow::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void SiteBossShootNormalArrow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mIsCheckASEvent_s, "IsCheckASEvent");
    getStaticParam(&mIsTurnToTarget_s, "IsTurnToTarget");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mIndex_d, "Index");
    getDynamicParam(&mAtAttr_d, "AtAttr");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteActor_d, "IgniteActor");
    getDynamicParam(&mArrowHandle_d, "ArrowHandle");
}

// NON_MATCHING: horizontal vectors use floating-point registers and different save slots.
void SiteBossShootNormalArrow::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    sub_7100737C0C(controller, 0.95f, -sead::Vector3f::ey);
    if (*mIsTurnToTarget_s) {
        sub_710073FA94(&_b0, mActor);
        sead::Vector3f target = *mTargetPos_d;
        target -= mActor->getMtx().getTranslation();
        target.normalize();
        sead::Vector3f forward = mActor->getMtx().getBase(2);
        forward.y = 0;
        forward.normalize();
        target.y = 0;
        target.normalize();
        if (!(forward.dot(target) >= 0.9848077f)) {
            sub_710074006C(&_b0, target, sead::Vector3f::ey, true, 0.01f,
                          sead::Mathf::pi2(), 0.0f);
            sub_7100740E04(_b0, controller);
        }
    }
    if (*mIsCheckASEvent_s && sub_71005DD780(mActor, 0x47, nullptr, 0, 0))
        sub_7100263C64();
    if (isFinishedAS(0, 0))
        setFinished();
}

bool SiteBossShootNormalArrow::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    return isFinishedAS(0, 0);
}

// NON_MATCHING: token iterator registers and stack layout.
void SiteBossShootNormalArrow::m32(sead::BufferedSafeString* bone_name) {
    if (!mBaseNode_s.isEmpty() && mBaseNode_s.findIndex(",") != -1) {
        auto it = mBaseNode_s.tokenBegin(",");
        for (s32 i = 0; i <= *mIndex_d; ++i)
            it.getAndForward(bone_name);
    } else {
        bone_name->copy(mBaseNode_s);
    }
}

}  // namespace uking::action
