#include "Game/AI/Action/actionForkASTrgAerialTurn.h"
#include <algorithm>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

ForkASTrgAerialTurn::ForkASTrgAerialTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgAerialTurn::~ForkASTrgAerialTurn() = default;

bool ForkASTrgAerialTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgAerialTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASTrgAerialTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgAerialTurn::loadParams_() {
    getStaticParam(&mPosStayRatio_s, "PosStayRatio");
    getStaticParam(&mRotStayRatio_s, "RotStayRatio");
    getStaticParam(&mAngSpd_s, "AngSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsOnASEventChangeable_s, "IsOnASEventChangeable");
    getStaticParam(&mIsUpdateRotSpd_s, "IsUpdateRotSpd");
}

void ForkASTrgAerialTurn::calc_() {
    const f32 ratio = *mPosStayRatio_s;
    const f32 diff = ratio - 1.0f;
    if (!(diff <= sead::Mathf::epsilon() && diff >= -sead::Mathf::epsilon()))
        sub_7100738488(mActor, ratio, -sead::Vector3f::ey);
    sub_71001400E8();
}

void ForkASTrgAerialTurn::m32(sead::Vector3f* axis, f32* angle) {
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const sead::Vector3f up = getUpDir(actor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    ksys::util::sub_71011EEB08(axis, angle, front, to_target, sead::Vector3f::ey);
}

// NON_MATCHING: scheduling of the angular-velocity loads in the dot product (same operations)
void ForkASTrgAerialTurn::sub_7100140390(bool check_ang_vel) {
    const f32 rate = std::max(_5c, 1.0f);
    auto* actor = mActor;
    sead::Vector3f dir;
    f32 speed;
    m32(&dir, &speed);
    if (check_ang_vel) {
        const sead::Vector3f vel = dir * speed;
        if (vel.dot(mActor->getAngVelocity()) < 0.0f)
            sub_7100738AA8(mActor, 0.99f);
    }
    if (rate > 5.0f)
        speed *= 1.05f;
    speed /= rate;
    const sead::Vector3f ang_vel = dir * speed;
    ksys::act::sub_7100EE5A14(actor, ang_vel);
}

// NON_MATCHING: identical instructions; the allocator swaps x8/x9 (the loaded query._10 lands in w9, the
// vtable pointer in x8) around the `ldp x?, x20, [x19]` before the m32 call
void ForkASTrgAerialTurn::sub_71001400E8() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;

    sead::Vector3f dir;
    f32 speed;
    sead::Vector3f ang_vel;
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 41, &query, 0, 0)) {
        if (!*mIsOnASEventChangeable_s)
            mFlags.reset(Flag::Changeable);
        auto* actor = mActor;
        _5c = query._10;
        const f32 rate = std::max(query._10, 1.0f);
        m32(&dir, &speed);
        if (rate > 5.0f)
            speed *= 1.05f;
        speed /= rate;
        ang_vel = dir * speed;
        ksys::act::sub_7100EE5A14(actor, ang_vel);
    } else if (as_list->x(41, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        ksys::Timer::update(&_5c, -1.0f);
        if (*mIsOnASEventChangeable_s) {
            sub_7100140390(true);
            return;
        }
        sub_7100738AA8(mActor, 0.99f);
    } else {
        mFlags.set(Flag::Changeable);
        const f32 ratio = *mRotStayRatio_s;
        const f32 diff = ratio - 1.0f;
        if (!(diff <= sead::Mathf::epsilon() && diff >= -sead::Mathf::epsilon()))
            sub_7100738AA8(mActor, ratio);
    }
}

}  // namespace uking::action
