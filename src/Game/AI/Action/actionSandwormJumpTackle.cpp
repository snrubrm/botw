#include "Game/AI/Action/actionSandwormJumpTackle.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// Declaration-only native helpers; source namespaces are unknown.
void sub_71007201C8(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_71007201FC(ksys::act::Actor* actor, const sead::SafeString& name);
void sub_710072027C(ksys::act::Actor* actor, bool a1, u32 a2);
void sub_7100720330(ksys::act::Actor* actor);

namespace uking::action {

SandwormJumpTackle::SandwormJumpTackle(const InitArg& arg) : JumpTackle(arg) {}

SandwormJumpTackle::~SandwormJumpTackle() {
    _c0.sub_71F858();
}

bool SandwormJumpTackle::init_(sead::Heap* heap) {
    if (!JumpTackle::init_(heap))
        return false;
    return _c0.sub_71F6DC(heap);
}

void SandwormJumpTackle::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpTackle::enter_(params);
}

void SandwormJumpTackle::leave_() {
    auto* actor = mActor;
    _100.getKey().reset();
    JumpTackle::leave_();
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(1);
    _c0.sub_71FEFC();
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5EE1C(_e8);
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0.0f)
            sub_71007377D4(controller, 0.1f);
    }
    sub_71007A397C(actor);
    sub_71007A44E4(actor, false);
    sub_71007208EC(actor);
    if (_138.sub_7101241B6C())
        _138.fadeXLink();
}

void SandwormJumpTackle::loadParams_() {
    JumpTackle::loadParams_();
    getStaticParam(&mPosReduceRate_s, "PosReduceRate");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getStaticParam(&mAtkColName_s, "AtkColName");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SandwormJumpTackle::calc_() {
    JumpTackle::calc_();
}

void SandwormJumpTackle::m33() {
    auto* actor = mActor;
    sub_71007201FC(actor, mAtkColName_s);
    sub_7100720330(actor);
}

void SandwormJumpTackle::m32() {
    auto* actor = mActor;
    sub_71007201C8(actor, mAtkColName_s);
    sub_710072027C(actor, true, 8);
}

bool SandwormJumpTackle::m34() const {
    if (!isFinishedAS(0, 0))
        return false;
    if (JumpTackle::m34())
        return true;
    auto* controller = mActor->getCharacterController();
    if (controller && controller->sub_7100F5F0E4() == ksys::act::MotionType::_0)
        return true;
    return false;
}

}  // namespace uking::action
