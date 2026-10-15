#include "Game/Actor/Action/actionGuardianMoveToPosition.h"
#include <container/seadObjArray.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

GuardianMoveToPosition::GuardianMoveToPosition(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianMoveToPosition::~GuardianMoveToPosition() = default;

bool GuardianMoveToPosition::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianMoveToPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
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
    GuardianActionBase::leave_();
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
    GuardianActionBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDecelerate_s, "Decelerate");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
}

// NON_MATCHING: array setup scheduling and pointer index extension differ.
void GuardianMoveToPosition::calc_() {
    GuardianActionBase::calc_();
    auto* nav = mActor->m45();
    auto* guardian = sub_7100192770();
    if (!nav || !guardian) {
        setFailed();
        return;
    }
    nav->_1e0.lock();
    const u8 state = nav->_294;
    nav->_1e0.unlock();
    if (state == 2) {
        setFinished();
        return;
    }
    const sead::Vector3f target = *mDynTargetPos_d;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    const sead::Vector3f direction = target - position;
    const f32 distance = direction.length();
    if (distance < 4.0f) {
        setFinished();
        return;
    }
    if (_48 > 0.0f) {
        ksys::Timer::update(&_48, -1.0f);
        if (_48 <= 0.0f) {
            sead::FixedObjArray<sead::Vector3f, 16> points;
            const s32 count = sead::Mathi::min(sead::Mathf::ceil(distance * 0.125f), 4);
            for (s32 i = 0; i < count; ++i) {
                const f32 ratio = (f32(i) + 3.0f) / (f32(count) + 2.0f);
                const sead::Vector3f sample = position + direction * ratio;
                sead::Vector3f point;
                const bool valid = nav->sub_7100F76078(&point, sample, 10.0f).sub_7100F7EB40();
                if (valid)
                    points.pushBack(point);
            }
            _48 = 30.0f;
            if (!points.isEmpty())
                nav->sub_710019960C(points.data(), points.data() + points.size());
        }
    }
}

}  // namespace uking::action
