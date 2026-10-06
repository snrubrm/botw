#include "Game/AI/Action/actionNavMeshSlippedWalk.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

NavMeshSlippedWalk::NavMeshSlippedWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshSlippedWalk::~NavMeshSlippedWalk() = default;

bool NavMeshSlippedWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshSlippedWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshSlippedWalk::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSlippedWalk::calc_() {
    NavMeshAction::calc_();
}

void NavMeshSlippedWalk::m32() {
    auto* actor = mActor;
    auto* nav = actor->m45();
    if (!nav)
        return;
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    sead::Vector3f velocity;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        velocity.set(nav->_23c);
    }
    velocity.y = 0.0f;
    const f32 speed = velocity.normalize() / 30.0f;
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, velocity, sead::Vector3f::ey);
    const f32 limit = angle > sub_71001F135C() * 2 ? sub_71001F1350() * 0.5f : sub_71001F1350();
    const f32 clamped = speed > limit ? limit : speed;
    const sead::Vector3f target_velocity = velocity * clamped;
    if (auto* controller = actor->getCharacterController())
        sub_71005E2540(controller, actor, target_velocity, *mAccRatio_s);
}

void NavMeshSlippedWalk::m34() {
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

}  // namespace uking::action
