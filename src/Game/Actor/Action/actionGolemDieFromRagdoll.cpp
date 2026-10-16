#include "Game/Actor/Action/actionGolemDieFromRagdoll.h"
#include "KingSystem/Physics/System/physSystem.h"
#include <prim/seadFormatPrint.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/Ragdoll/physRagdollRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

GolemDieFromRagdoll::GolemDieFromRagdoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GolemDieFromRagdoll::~GolemDieFromRagdoll() = default;

bool GolemDieFromRagdoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GolemDieFromRagdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710072BB28(mActor);
    const f32 time = static_cast<f32>(*mTime_s);
    mTimer = ksys::Timer(time, time);
    auto* actor = mActor;
    auto* physics = actor->getPhysics();
    if (!physics || !physics->getRagdollInstance()) {
        setFailed();
        return;
    }
    auto* ragdoll = physics->getRagdollInstance();
    auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor);
    if (!dynamic_actor || !dynamic_actor->_868) {
        setFailed();
        return;
    }
    auto* handler = dynamic_actor->_868;
    s32 controller_idx = -1;
    if (!mRagdollControllerKey_s.isEmpty())
        controller_idx = physics->sub_7100FBDA2C(mRagdollControllerKey_s);
    if (controller_idx < 0)
        controller_idx = physics->get112();
    _11c = controller_idx;
    if (!actor->sub_71011CEA90() || !handler->sub_71006ED9EC())
        handler->sub_71006ED484();
    physics->sub_7100FBC838(_11c);
    physics->sub_7100FBDB90(_11c, -1.0f);
    ragdoll->x_22(-1, 0.0f);
    for (const auto& body : mRagdollBodies_s)
        sub_71007282F8(actor, body);
    if (auto* current_physics = mActor->getPhysics()) {
        if (auto* current_ragdoll = current_physics->getRagdollInstance()) {
            for (s32 i = 0; i < current_ragdoll->getRigidBodies_().size(); ++i)
                current_ragdoll->getRigidBodies_()[i]->changeMotionType(ksys::phys::MotionType::Dynamic);
        }
    }
    sub_71005E1B7C(mActor, false);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F60AE0();
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->sub_7100F62CA8(false);
    }
    _120 = 0;
    if (!mXLinkKey_s.isEmpty())
        xlinkSearchAndEmit(mActor, mXLinkKey_s.cstr(), 2, nullptr);
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
    if ((body_pos - controller_pos).length() > *mRagdollMoveLimitDist_s) {
        controller->sub_7100F5FBE0(controller_pos);
        body->setPosition(controller_pos);
        body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
    } else {
        controller->sub_7100F5FBE0(body_pos);
    }
}

// Blows the ragdoll up (and away from the base body).
// NON_MATCHING: the original loads BlownHeight before the physics System instance (scheduling only).
void GolemDieFromRagdoll::sub_710018C3A4() {
    auto* ragdoll = mActor->getRagdollInstance();
    if (!ragdoll)
        return;
    auto* base_body = ragdoll->getBoneRigidBodyByName(mPosBaseRagdollRbName_s);
    if (!base_body)
        return;

    sead::Vector3f base_pos;
    base_body->getPosition(&base_pos);
    const f32 up_speed =
        sub_710072D068(&ksys::phys::System::instance()->getField48(), *mBlownHeight_s);
    const f32 speed = *mBlownSpeed_s * 30.0f;
    for (s32 i = 0; i < ragdoll->getRigidBodies_().size(); ++i) {
        auto* body = ragdoll->getRigidBodies_()[i];
        if (body == base_body) {
            base_body->setLinearVelocity({0, up_speed, 0}, sead::Mathf::epsilon());
            continue;
        }
        sead::Vector3f pos;
        body->getPosition(&pos);
        sead::Vector3f velocity = pos;
        velocity -= base_pos;
        velocity.y = 0;
        const f32 length = velocity.length();
        if (length > 0.0f)
            velocity *= speed / length;
        velocity.y = up_speed;
        body->setLinearVelocity(velocity, sead::Mathf::epsilon());
    }

    if (!mImpulseXLinkKey_s.isEmpty())
        xlinkSearchAndEmit(mActor, mImpulseXLinkKey_s.cstr(), 2, nullptr);
}

// NON_MATCHING: saved scalar registers and the near-limit setup are reordered.
void GolemDieFromRagdoll::sub_710018C59C() {
    auto* actor = mActor;
    auto* ragdoll = actor->getRagdollInstance();
    if (!ragdoll || ragdoll->getRigidBodies_().size() < 1)
        return;
    const f32 limit = *mRagdollMoveLimitDist_s;
    const f32 near_limit = limit * 0.9f;
    const auto actor_position = actor->getMtx().getTranslation();
    for (s32 i = 0; i < ragdoll->getRigidBodies_().size(); ++i) {
        auto* body = ragdoll->getRigidBodies_()[i];
        sead::Vector3f position;
        body->getPosition(&position);
        const sead::Vector2f offset(actor_position.x - position.x, actor_position.z - position.z);
        const f32 distance = offset.length();
        const f32 height = actor_position.y - position.y;
        if (distance > limit || height > limit) {
            body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            body->changeMotionType(ksys::phys::MotionType::Keyframed);
        } else if (distance > near_limit || height > near_limit) {
            sub_7100738084(body, *mPosReduceRatio_s * 0.8f, -sead::Vector3f::ey);
            sub_7100738898(body, *mRotReduceRatio_s * 0.8f);
        } else {
            sub_7100738084(body, *mPosReduceRatio_s, -sead::Vector3f::ey);
            sub_7100738898(body, *mRotReduceRatio_s);
        }
    }
}

}  // namespace uking::action
