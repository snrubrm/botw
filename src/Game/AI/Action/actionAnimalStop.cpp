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

// NON_MATCHING: register assignment and load/scheduling order only — the velocity-z load goes
// to s2 before the squares in the original (ours uses s1 after the x/y sum) and the a0 fadd keeps
// (m, axis) operand order in s5 (ours swaps to s1-first). The deadband shape needs the six-way &&
// with assignment-in-condition and an empty then-block (plain > gives b.gt, the original's b.hi
// needs !(x <= c)); the temp scopes reproduce the 0x70 frame exactly.
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
        if (!(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z <
              sead::Mathf::epsilon())) {
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
