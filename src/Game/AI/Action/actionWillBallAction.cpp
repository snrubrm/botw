#include "Game/AI/Action/actionWillBallAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_7c in x20 across the memset)
WillBallAction::WillBallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WillBallAction::~WillBallAction() = default;

bool WillBallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the direction math differs (the original negates x / z after the length test and merges the no-body
// path into the shared tail; the sign handling of y is an eor + csel).
void WillBallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getTranslation(_70);
    _90 = mActor->getVelocity().y > 0.0f ? 1 : -1;
    _7c.value = 0.01f;
    _7c.prev_value = 0.01f;
    f32 height;
    auto* body = mActor->getMainBody();
    if (body) {
        _88 = body->getGravityFactor();
        body->setGravityFactor(*mParams.mIsGround_s ? 1.0f : 0.0f);
        if (*mParams.mIsAddAABBHeight_s) {
            sead::BoundBox3f aabb;
            body->getAabbInLocal(&aabb);
            height = (aabb.getMax().y - aabb.getMin().y) * 0.5f + 0.1f;
            _8c = height;
        } else {
            height = 0.0f;
            _8c = 0.0f;
        }
    } else {
        height = _8c;
    }
    const sead::Vector3f target = *mParams.mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir(pos.x - target.x, pos.y - (target.y + height), pos.z - target.z);
    if (*mParams.mIsGround_s)
        dir.y = 0.0f;
    dir.negate();
    dir.normalize();
    dir *= _7c.value;
    if (body)
        ksys::act::sub_7100EE6268(body, dir);
    _91 = true;
}

void WillBallAction::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(_88);
}

void WillBallAction::loadParams_() {
    getStaticParam(&mParams.mRotBaseRatio_s, "RotBaseRatio");
    getStaticParam(&mParams.mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mReachRange_s, "ReachRange");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
    getStaticParam(&mParams.mIsIgnoreLastSpRot_s, "IsIgnoreLastSpRot");
    getStaticParam(&mParams.mIsAddAABBHeight_s, "IsAddAABBHeight");
    getStaticParam(&mParams.mIsGround_s, "IsGround");
    getStaticParam(&mParams.mAccel_s, "Accel");
}

void WillBallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
