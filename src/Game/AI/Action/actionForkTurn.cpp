#include "Game/AI/Action/actionForkTurn.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void ForkTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkTurn::m32() {
    return true;
}

void ForkTurn::m33(sead::Vector3f* dir) {}

// NON_MATCHING: the original copies the gravity vector to another stack temporary before the call
void ForkTurn::m34(f32 ratio) {
    auto* actor = mActor;
    sub_7100738488(actor, ratio, getGravity(actor));
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
