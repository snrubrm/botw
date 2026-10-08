#include "Game/AI/Action/actionAnimalStop.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

AnimalStop::AnimalStop(const InitArg& arg) : HorseWaitAction(arg) {}

AnimalStop::~AnimalStop() = default;

bool AnimalStop::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void AnimalStop::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
    auto* asl = mActor->getASList();
    auto* rideable = mActor->m132();
    if (!asl || !rideable) {
        setFailed();
        return;
    }
    if (!(rideable->_18._52 & 2))
        rideable->_18._52 |= 2;
}

void AnimalStop::leave_() {
    HorseWaitAction::leave_();
    if (auto* rideable = mActor->m132())
        rideable->sub_7100E63424();
}

void AnimalStop::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mIsFixAxisY_s, "IsFixAxisY");
}

// NON_MATCHING: two fadd operand orders only (a0: original keeps (mtx, axis),
// a2: original keeps (mtx, axis); ours puts the axis local first in both). Source order
// swaps were tried and do not change the output (reassociation ranks the local first).
// The velocity-z load schedule matches via named f32 locals (each used twice).
void AnimalStop::calc_() {
    HorseWaitAction::calc_();
    if (!*mIsFixAxisY_s)
        return;
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    const sead::Vector3f& as_vel = as_list->sub_710115D3B8();
    if (!(as_vel.x * as_vel.x + as_vel.y * as_vel.y + as_vel.z * as_vel.z <
          sead::Mathf::epsilon())) {
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    {
        sead::Vector3f velocity;
        controller->sub_7100F635BC(&velocity);
        const f32 vx = velocity.x;
        const f32 vy = velocity.y;
        const f32 vz = velocity.z;
        if (!(vx * vx + vy * vy + vz * vz < sead::Mathf::epsilon())) {
            return;
        }
    }
    sead::Matrix34f mtx;
    controller->sub_7100F626E8(&mtx);
    const auto& axis = controller->get7c();
    const f32 ax = axis.x;
    const f32 ay = axis.y;
    const f32 az = axis.z;
    f32 a0, a1, a2;
    if ((a0 = mtx.m[0][1] + ax) <= 0.001f && a0 >= -0.001f &&
        (a1 = mtx.m[1][1] + ay) <= 0.001f && a1 >= -0.001f &&
        (a2 = mtx.m[2][1] + az) <= 0.001f && a2 >= -0.001f) {
    } else {
        sead::Vector3f out;
        {
            const sead::Vector3f neg(-axis.x, -axis.y, -axis.z);
            controller->sub_7100F60088(&out, &neg, true);
        }
        controller->sub_7100F5FB24(out * 0.05f);
    }
}

}  // namespace uking::action
