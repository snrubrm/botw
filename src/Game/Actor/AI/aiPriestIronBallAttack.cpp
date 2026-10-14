#include "Game/Actor/AI/aiPriestIronBallAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

PriestIronBallAttack::PriestIronBallAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestIronBallAttack::~PriestIronBallAttack() = default;

bool PriestIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("投擲", &pack);

    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body)
        return;

    const sead::Vector3f target = *mTargetPos_d;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const f32 noise = *mNoise_s;
    const sead::Vector3f min_angle{*mShootPitchMin_s, -sead::Mathf::pi() / 2.0f, 0.0f};
    const sead::Vector3f max_angle{*mShootPitchMax_s, sead::Mathf::pi() / 2.0f, 0.0f};
    const auto& mtx = actor->getMtx();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    front.normalize();
    const f32 speed = *mSpeed_s;
    sead::Vector3f velocity;
    sub_71005DDF80(&velocity, &target, &pos, &front, &min_angle, &max_angle, speed,
                   getGravity(mActor).y * (1.0f / 900.0f), noise);
    body->setLinearVelocity(velocity * 30.0f);
}

void PriestIronBallAttack::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void PriestIronBallAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestIronBallAttack::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mShootPitchMin_s, "ShootPitchMin");
    getStaticParam(&mShootPitchMax_s, "ShootPitchMax");
    getStaticParam(&mNoise_s, "Noise");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
