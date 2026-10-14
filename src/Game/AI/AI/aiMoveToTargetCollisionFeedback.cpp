#include "Game/AI/AI/aiMoveToTargetCollisionFeedback.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

MoveToTargetCollisionFeedback::MoveToTargetCollisionFeedback(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MoveToTargetCollisionFeedback::~MoveToTargetCollisionFeedback() = default;

bool MoveToTargetCollisionFeedback::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoveToTargetCollisionFeedback::enter_(ksys::act::ai::InlineParamPack* params) {
    _a0.set(*mTargetPos_d);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_a0, "TargetPos", -1);
    changeChild("移動", &pack);
    _ac = 1.0f;
}

// NON_MATCHING: register allocation of the push direction / position components; same operations.
void MoveToTargetCollisionFeedback::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }

    if (*mRetryOriginalPos_s) {
        _94.update();
        if (_94.value <= sead::Mathf::epsilon()) {
            _94 = ksys::Timer(1, 1, 0);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_a0, "TargetPos", -1);
            changeChild("移動", &pack);
        }
    }

    _88.update();
    if (!(_88.value <= sead::Mathf::epsilon()))
        return;

    auto* actor = mActor;
    if (!isLandedMaybe(actor, false) && !isBgGroundHit(actor, false))
        return;

    _88.value = _88.previous_value = *mCooldownFramesTargetAdjust_s;

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(0.0f);
        sead::Vector3f dir(0.0f, 0.0f, 0.0f);
        const s32 num = sub_71007A49F0(mActor);
        for (s32 i = 0; i < num; ++i) {
            auto* contact = sub_71007A4948(mActor, i);
            if (!contact || contact->_c.y >= *mIgnoreYComponentThreshold_s)
                continue;
            dir.x += contact->_c.x;
            dir.z += contact->_c.z;
        }
        if (dir.x == 0.0f && dir.z == 0.0f)
            return;

        dir.normalize();
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        if (!*mUseMoveAwayFromPos_s) {
            sead::Vector3f to_target = _a0 - pos;
            to_target.normalize();
            if (to_target.dot(dir) > 0.0f)
                dir += to_target * 0.75f;
        } else {
            sead::Vector3f away(mMoveAwayFromPos_d->x - pos.x, 0.0f, mMoveAwayFromPos_d->z - pos.z);
            away.normalize();
            if (away.dot(dir) > 0.0f)
                dir -= away * 0.25f;
            else
                _ac = 0.1f;
        }
        dir.normalize();

        const f32 dist = sead::Vector2f(pos.x - _a0.x, pos.z - _a0.z).length();
        const f32 scale = _ac;
        _ac = scale - 0.25f;
        if (_ac > 0.0f) {
            sead::Vector3f target = pos + dir * (dist * scale);
            if (*mIsAdjustDepthOnCollision_s) {
                const f32 depth = mActor->getDepthInWater();
                if (depth < *mIdealDepthMin_s)
                    target.y += sead::Mathf::abs(*mIdealDepthMin_s - depth) * -0.5f;
                else if (depth > *mIdealDepthMax_s)
                    target.y += sead::Mathf::abs(*mIdealDepthMax_s - depth) * 0.5f;
            }
            child->setFinished();
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("移動", &pack);
            if (*mRetryOriginalPos_s)
                _94 = ksys::Timer(*mFramesUntilRetryOriginalPos_s, *mFramesUntilRetryOriginalPos_s);
            return;
        }
    }
    setFailed();
}

void MoveToTargetCollisionFeedback::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveToTargetCollisionFeedback::loadParams_() {
    getStaticParam(&mCooldownFramesTargetAdjust_s, "CooldownFramesTargetAdjust");
    getStaticParam(&mFramesUntilRetryOriginalPos_s, "FramesUntilRetryOriginalPos");
    getStaticParam(&mIdealDepthMin_s, "IdealDepthMin");
    getStaticParam(&mIdealDepthMax_s, "IdealDepthMax");
    getStaticParam(&mIgnoreYComponentThreshold_s, "IgnoreYComponentThreshold");
    getStaticParam(&mUseMoveAwayFromPos_s, "UseMoveAwayFromPos");
    getStaticParam(&mRetryOriginalPos_s, "RetryOriginalPos");
    getStaticParam(&mIsAdjustDepthOnCollision_s, "IsAdjustDepthOnCollision");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveAwayFromPos_d, "MoveAwayFromPos");
}

}  // namespace uking::ai
