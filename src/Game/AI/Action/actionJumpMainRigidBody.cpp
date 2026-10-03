#include "Game/AI/Action/actionJumpMainRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

JumpMainRigidBody::JumpMainRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpMainRigidBody::~JumpMainRigidBody() = default;

bool JumpMainRigidBody::init_(sead::Heap* heap) {
    return _70.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void JumpMainRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_70._0)) {
            if (*mVibrateMemoryStep_s > 0.0f)
                checker->_84 = *mVibrateMemoryStep_s;
            if (*mVibrateCheckFrame_s > 0.0f)
                checker->_88 = *mVibrateCheckFrame_s;
            checker->_78 = checker->_88;
            checker->_7c = 0;
            checker->_80 = 0;
            checker->_90.setUndef();
            checker->_8c = false;
        }
    }
    _7c = false;
    _7b = mPostBoundReactionKeys_s.isEmpty();
    mFlags.set(Flag::Changeable);
    auto* actor = mActor;
    auto* body = actor->getMainBody();
    if (!body) {
        setFailed();
        return;
    }
    if (body->getWaterBuoyancyScale() > 0.0f)
        _7c = true;
    _7a = !body->hasFlag(ksys::phys::RigidBody::Flag::_2000000);
    body->clearFlag2000000(false);
    if (isBgGroundHit(actor, false) || (_7c && actor->get68f())) {
        sead::Vector3f dir = sub_71001C4494();
        sub_71007379FC(body, 0.1f);
        dir *= *mPower_s;
        body->applyLinearImpulse(dir * actor->m38());
        _78 = true;
        _79 = true;
    } else {
        _78 = false;
        _79 = false;
    }
}

void JumpMainRigidBody::sub_71001C4AC0() {
    if (!mPostBoundReactionKeys_s.isEmpty()) {
        const sead::SafeString keys = mPostBoundReactionKeys_s;
        sead::FixedSafeString<64> key;
        auto it = keys.tokenBegin(",");
        const auto end = keys.tokenEnd(",");
        while (end != it) {
            it.getAndForward(&key);
            if (!key.isEmpty())
                ksys::eft::searchAndEmitSLink(mActor, key.cstr(), false);
        }
    }
    _7b = true;
}

void JumpMainRigidBody::leave_() {
    if (!_7b && isFinished())
        sub_71001C4AC0();
    if (auto* body = mActor->getMainBody())
        body->clearFlag2000000(_7a);
}

void JumpMainRigidBody::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mIsRotJumpDir_s, "IsRotJumpDir");
    getStaticParam(&mPostBoundReactionKeys_s, "PostBoundReactionKeys");
    getStaticParam(&mJumpDir_s, "JumpDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void JumpMainRigidBody::calc_() {
    if (_78) {
        _78 = false;
        return;
    }

    auto* actor = mActor;
    Unk_7100716408* data = nullptr;
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_70._0)) {
            data = checker;
            data->sub_7100716408(actor->getMtx().getTranslation());
        }
    }

    if (isFinished() && !_7b)
        sub_71001C4AC0();
    if (isFinished())
        return;
    if (isFailed())
        return;

    bool vibrating = false;
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_70._0)) {
            if (checker->_78 <= 0.0f ||
                (*mVibrateStopCheck_s > 0.0f && checker->sub_71007169CC(*mVibrateStopCheck_s))) {
                if (_79) {
                    setFailed();
                    return;
                }
                if (data)
                    data->reset(data->_88);
                vibrating = true;
            }
        }
    }

    if (!actor)
        return;
    if (!(isBgGroundHit(actor, false) || (_7c && actor->get68f()) || vibrating))
        return;

    if (_79) {
        if (!_7b)
            sub_71001C4AC0();
        setFinished();
        return;
    }

    sead::Vector3f dir = sub_71001C4494();
    if (auto* body = actor->getMainBody()) {
        sub_71007379FC(body, 0.1f);
        dir *= *mPower_s;
        body->applyLinearImpulse(dir * actor->m38());
    }
    _78 = true;
    _79 = true;
}

// NON_MATCHING: the length of the fallback direction is summed as z*z + (x*x + y*y) instead of
// (x*x + y*y) + z*z
sead::Vector3f JumpMainRigidBody::sub_71001C4494() {
    auto* actor = mActor;
    if (*mIsRotJumpDir_s) {
        sead::Vector3f dir = *mJumpDir_s;
        dir.normalize();
        dir.rotate(actor->getMtx());
        return dir;
    }

    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f to_target = *mTargetPos_d;
    to_target.x -= pos.x;
    to_target.z -= pos.z;
    to_target.y = 0.0f;
    to_target.normalize();
    if (!(std::sqrt(to_target.x * to_target.x + to_target.z * to_target.z) > 0.0f)) {
        actor->getMtx().getBase(to_target, 2);
        to_target.normalize();
    }

    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, to_target, sead::Vector3f::ey, sead::Vector3f::zero, false);
    sead::Vector3f dir = *mJumpDir_s;
    dir.normalize();
    dir.rotate(mtx);
    return dir;
}

}  // namespace uking::action
