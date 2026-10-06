#include "Game/AI/Action/actionGuardianMoveToPosition.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

GuardianMoveToPosition::GuardianMoveToPosition(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianMoveToPosition::~GuardianMoveToPosition() = default;

bool GuardianMoveToPosition::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianMoveToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
    mFlags.set(Flag::Changeable);
    _48 = 1.0f;
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F76790();
        nav->inlineReset();
    } else {
        setFailed();
    }
}

void GuardianMoveToPosition::leave_() {
    GuardianMoveTo::leave_();
    if (auto* nav = mActor->m45())
        nav->inlineReset();
}

void GuardianMoveToPosition::m0(Data* data, ksys::act::Actor* actor) {
    if (auto* guardian = sub_7100192798(); guardian && guardian == actor) {
        if (sub_710003955C(actor)->_70 == 2)
            sub_710019992C(data);
        else
            sub_7100199AD4(data, actor);
    } else {
        Unk_7100041da4::m0(data, actor);
    }
}

// NON_MATCHING: the original computes max(dir.y, -0.1f) before the first normalisation and schedules the
// stores of data->_c / _18 differently.
void GuardianMoveToPosition::sub_710019992C(Data* data) {
    sead::Vector3f dir = *mDynTargetPos_d;
    dir -= mActor->getMtx().getTranslation();
    const f32 len = dir.normalize();
    data->_18 = sead::Mathf::clampMax(len, 12.0f);
    data->_0.set(dir.x, 0.0f, dir.z);
    data->_c = dir;
    data->_0.normalize();
    data->_0.y = sead::Mathf::max(dir.y, -0.1f);
    data->_0.normalize();
    data->_34 = data->_b8;
    data->_40 = sead::Vector3f::ey;
}

// NON_MATCHING: the original keeps both lock-protected state reads in stack slots (stur/ldur) and loads the
// target and the actor translation before the branch; ours differs in those loads/stack slots only.
void GuardianMoveToPosition::sub_7100199AD4(Data* data, ksys::act::Actor* actor) {
    auto* nav = actor->m45();
    if (!nav) {
        Unk_7100041da4::m0(data, actor);
        return;
    }
    nav->_1e0.lock();
    const u8 state = nav->_294;
    nav->_1e0.unlock();
    bool has_path;
    if (state == 3) {
        has_path = false;
    } else {
        nav->_1e0.lock();
        const u8 state2 = nav->_294;
        nav->_1e0.unlock();
        has_path = state2 != 0;
    }
    const sead::Vector3f& target = *mDynTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    bool valid = false;
    if (has_path) {
        nav->_1e0.lock();
        data->_0.set(nav->_248);
        nav->_1e0.unlock();
        nav->_1e0.lock();
        data->_c.set(nav->_23c);
        nav->_1e0.unlock();
        const f32 len = data->_c.normalize();
        data->_18 = sead::Mathf::min(len, *mSpeed_s);
        valid = !sead::Mathf::isNan(data->_c.x) && !sead::Mathf::isNan(data->_c.y) &&
                !sead::Mathf::isNan(data->_c.z);
    }
    if (!valid) {
        sead::Vector3f dir = target - pos;
        dir.normalize();
        data->_18 = 0.0f;
        data->_0 = dir;
        data->_c = dir;
    }
    data->_34 = data->_b8;
    data->_40 = sead::Vector3f::ey;
}

void GuardianMoveToPosition::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDecelerate_s, "Decelerate");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

void GuardianMoveToPosition::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
