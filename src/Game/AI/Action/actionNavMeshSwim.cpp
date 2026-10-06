#include "Game/AI/Action/actionNavMeshSwim.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// Name and signature are inferred from the call sites (also used by SwimGetUp and others).
void sub_71005DF820(f32* out, f32 velY, f32 depth, f32 a, f32 b, f32 c, f32 d, f32 e);

namespace uking::action {

NavMeshSwim::NavMeshSwim(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshSwim::~NavMeshSwim() = default;

bool NavMeshSwim::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
    _c8.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::Hover);
}

void NavMeshSwim::leave_() {
    _c8.resetMotionType(mActor->getCharacterController());
    NavMeshAction::leave_();
}

void NavMeshSwim::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSwim::calc_() {
    NavMeshAction::calc_();
}

void NavMeshSwim::m34() {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void NavMeshSwim::m36(ksys::phys::CharacterController* controller, f32 speed,
                      const sead::Vector3f& up) {
    sead::Vector3f vel;
    controller->sub_7100F5F598(&vel);
    const f32 velY = vel.y / 30.0f;
    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }
    f32 out;
    sub_71005DF820(&out, velY, depth, *mFloatDepth_s, *mInWaterDepth_s, 0.1f, 30.0f, -1.0f);
    vel = up * speed;
    vel.y += out;
    sub_7100737710(controller, vel);
}

}  // namespace uking::action
