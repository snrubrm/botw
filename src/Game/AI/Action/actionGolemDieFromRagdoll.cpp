#include "Game/AI/Action/actionGolemDieFromRagdoll.h"
#include <prim/seadFormatPrint.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"

namespace uking::action {

GolemDieFromRagdoll::GolemDieFromRagdoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GolemDieFromRagdoll::~GolemDieFromRagdoll() = default;

bool GolemDieFromRagdoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GolemDieFromRagdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GolemDieFromRagdoll::leave_() {
    ksys::act::ai::Action::leave_();
}

void GolemDieFromRagdoll::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRagdollMoveLimitDist_s, "RagdollMoveLimitDist");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mBlownSpeed_s, "BlownSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mRagdollControllerKey_s, "RagdollControllerKey");
    sead::FixedSafeString<64> key;
    for (u32 i = 1; i <= 4; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RagdollBodyName%d", i) << sead::flush;
        getStaticParam(&mRagdollBodies_s[i - 1].mRagdollBodyName_s, key);
        (sead::StringCutOffPrintFormatter(&key) << "MaterialName%d", i) << sead::flush;
        getStaticParam(&mRagdollBodies_s[i - 1].mMaterialName_s, key);
    }
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getStaticParam(&mImpulseXLinkKey_s, "ImpulseXLinkKey");
}

void GolemDieFromRagdoll::calc_() {
    if (!(mTimer.value <= sead::Mathf::epsilon())) {
        ++_120;
        mTimer.update();
    } else {
        setFinished();
    }
    sub_710018C27C();
    if (_120 == 2 && (*mBlownHeight_s > 0.0f || *mBlownSpeed_s > 0.0f))
        sub_710018C3A4();
    else
        sub_710018C59C();
}

// NON_MATCHING: the preserved controller position is loaded from the stack instead of saved registers.
void GolemDieFromRagdoll::sub_710018C27C() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    auto* ragdoll = mActor->getRagdollInstance();
    if (!ragdoll)
        return;
    auto* body = ragdoll->getBoneRigidBodyByName(mPosBaseRagdollRbName_s);
    if (!body)
        return;
    sead::Vector3f body_pos;
    controller->sub_7100F5F6E0(&body_pos);
    const sead::Vector3f controller_pos = body_pos;
    body->getPosition(&body_pos);
    if (!((body_pos - controller_pos).length() <= *mRagdollMoveLimitDist_s)) {
        controller->sub_7100F5FBE0(controller_pos);
        body->setPosition(controller_pos);
        body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    } else {
        controller->sub_7100F5FBE0(body_pos);
    }
}

}  // namespace uking::action
