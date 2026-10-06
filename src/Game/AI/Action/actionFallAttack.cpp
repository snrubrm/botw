#include "Game/AI/Action/actionFallAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

FallAttack::FallAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FallAttack::~FallAttack() = default;

bool FallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;

    setDamageCallbackTiming(actor, 4, &_60);
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), mAtkBodyName_s.cstr()))
        body->setTransform(actor->getMtx());

    sead::Vector3f dir;
    dir.set(controller->get70());
    _58 = dir.normalize();
    dir *= *mGravity_s;
    controller->sub_7100F5EE1C(dir);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

// NON_MATCHING: same calls and arithmetic; the original loads `_58` into a callee-saved register before the sqrt, puts the
// 16-byte direction vector below the Unk_71002edaec request on the stack (frame 0x90, ours 0x80) and keeps four fp registers.
void FallAttack::leave_() {
    auto* actor = mActor;
    sub_71005DA114(actor, &_60);
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;

    sead::Vector3f dir;
    dir.set(controller->get70());
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= _58 / length;
    controller->sub_7100F5EE1C(dir);
    const uking::act::Unk_71002edaec request(1);
    sub_71005D79AC(actor, *mWeaponIdx_s, request);
    sub_71007A2D7C(actor, mAtkBodyName_s);
    controller->sub_7100F60604();
}

void FallAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtkBodyName_s, "AtkBodyName");
    getStaticParam(&mJustAvoidDist_s, "JustAvoidDist");
}

void FallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

int FallAttack::m32() {
    return 12;
}

int FallAttack::m33() {
    return 4;
}

bool FallAttack::isFinished() const {
    return isBgGroundHit(mActor, false);
}

}  // namespace uking::action
