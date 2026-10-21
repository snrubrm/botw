#include "Game/Actor/Action/actionGuardianMoveToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>

namespace uking::action {

GuardianMoveToTarget::GuardianMoveToTarget(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianMoveToTarget::~GuardianMoveToTarget() = default;

bool GuardianMoveToTarget::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
    mFlags.set(Flag::Changeable);
    _30 = 1.0f;
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F76790();
        nav->inlineReset();
    } else {
        setFailed();
    }
}

void GuardianMoveToTarget::leave_() {
    GuardianActionBase::leave_();
    if (auto* nav = mActor->m45())
        nav->inlineReset();
}

void GuardianMoveToTarget::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
}

// NON_MATCHING: the FixedObjArray constructor stores are scheduled differently (one store and the size
// argument move).
void GuardianMoveToTarget::m0(Data* data, ksys::act::Actor* actor) {
    auto* nav = mActor->m45();
    if (!nav) {
        Unk_7100041da4::m0(data, actor);
        return;
    }

    bool follow_path = false;
    if (int(nav->getPathState()) != ksys::phys::NavMeshPathState::State3 &&
        int(nav->getPathState()) != ksys::phys::NavMeshPathState::State0) {
        follow_path = sub_710003955C(actor)->_70 == 1;
    }

    auto* unk = sub_71001928B0();
    if (!unk)
        return;

    sead::FixedObjArray<sead::Vector3f, 16> targets;
    unk->sub_710004B1D4(&targets);

    bool has_direction = false;
    if (follow_path) {
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            data->_0.set(nav->_248);
        }
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            data->_c.set(nav->_23c);
        }
        const f32 length = data->_c.normalize();
        data->_18 = sead::Mathf::min(length, *mSpeed_s);
        has_direction = !sead::Mathf::isNan(data->_c.x) && !sead::Mathf::isNan(data->_c.y) &&
                        !sead::Mathf::isNan(data->_c.z);
    }

    if (!has_direction) {
        if (targets.size() > 0) {
            const sead::Vector3f target = *targets[0];
            sead::Vector3f dir = target - mActor->getMtx().getTranslation();
            dir.normalize();
            data->_18 = 0.0f;
            data->_0 = dir;
            data->_c = dir;
        } else {
            data->_18 = 0.0f;
            data->_0 = data->_1c;
            data->_c = data->_1c;
        }
    }
    data->_34 = data->_b8;
    data->_40 = sead::Vector3f::ey;
}

void GuardianMoveToTarget::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
