#include "Game/AI/Action/actionForkTurn.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ForkTurn::ForkTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkTurn::~ForkTurn() = default;

bool ForkTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f up;
    m35(&up);
    m36(&_b0);

    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    const f32 speed = actor->getAngVelocity().length();
    _80.value = speed;
    _80.prev_value = speed;
    sub_7100741034(&_8c, actor);

    sead::Vector3f to_target = _b0;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    actor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);

    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
}

void ForkTurn::sub_7100168770(sead::Vector3f* to_target, sead::Vector3f* up) {
    if (*mIsUpdateTarget_s)
        m36(&_b0);
    sead::Vector3f up_dir;
    m35(&up_dir);

    auto* actor = mActor;
    sead::Vector3f dir = _b0;
    dir -= actor->getMtx().getTranslation();
    if (!*mIsUpFollow_s)
        ksys::util::sub_71011EFA00(&dir, dir, up_dir);
    dir.normalize();

    sead::Vector3f result_up;
    bool found = false;
    if (*mIsFollowGround_s) {
        if (auto* controller = actor->getCharacterController())
            found = controller->sub_7100F5F234(&result_up);
    }
    if (!found)
        result_up = up_dir;

    m33(&dir);
    *to_target = dir;
    *up = result_up;
}

void ForkTurn::leave_() {
    if (*mIsFinishForceStopRot_s)
        sub_7100738AA8(mActor, 0.0f);
}

void ForkTurn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotAccMaxSpeedRatio_s, "RotAccMaxSpeedRatio");
    getStaticParam(&mIsUpdateTarget_s, "IsUpdateTarget");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsRotEndFinish_s, "IsRotEndFinish");
    getStaticParam(&mIsFinishForceStopRot_s, "IsFinishForceStopRot");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsUpFollow_s, "IsUpFollow");
}

// NON_MATCHING: only the scheduling of the loads for the sub_7100741578 arguments (front components, base ratio and
// the up-follow flag, which the original negates with `eor #1` instead of `cmp / cset`).
void ForkTurn::calc_() {
    auto* actor = mActor;
    sub_7100741038(&_8c, actor);
    m34(*mPosReduceRatio_s);
    _80.lerp(*mRotSpd_s, *mRotAccRatio_s, *mRotSpd_s * *mRotAccMaxSpeedRatio_s);
    _80.updateStats();

    sead::Vector3f up;
    sead::Vector3f to_target;
    sub_7100168770(&to_target, &up);
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    sub_7100741578(&_8c, to_target, up, !*mIsUpFollow_s, *mBaseRotRatio_s, _80.value, _80.value / 10);
    if (m32())
        sub_7100741B0C(_8c, actor);

    front.normalize();
    to_target.y = 0.0f;
    to_target.normalize();
    const f32 dot = front.x * to_target.x + front.y * to_target.y + front.z * to_target.z;
    if (dot >= sead::Mathf::cos(*mFinRotate_s)) {
        if (*mIsRotEndFinish_s)
            setFinished();
        else
            mFlags.set(Flag::Changeable);
    }
}

bool ForkTurn::m32() {
    return true;
}

void ForkTurn::m33(sead::Vector3f* dir) {}

void ForkTurn::m34(f32 ratio) {
    auto* actor = mActor;
    const sead::Vector3f gravity = getGravity(actor);
    sub_7100738488(actor, ratio, gravity);
}

void ForkTurn::m35(sead::Vector3f* up) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sead::Vector3f dir = -gravity;
    if (dir.normalize() < sead::Mathf::epsilon())
        dir.set(sead::Vector3f::ey);
    up->set(dir);
}

void ForkTurn::m36(sead::Vector3f* target) {}

}  // namespace uking::action
