#include "Game/AI/Action/actionTeleportBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

// 0x710072bb70 / 0x710072bec4 (declarations only): prepare the actor for / restore it after the
// teleport (disable attention, character controller contact layers, ...); `state` saves the
// character controller settings. The last parameter of the first one is unknown.
void sub_710072BB70(ksys::act::Actor* actor, TeleportBase::SavedState* state, bool a3, bool a4);
void sub_710072BEC4(ksys::act::Actor* actor, TeleportBase::SavedState* state, bool a3);

TeleportBase::TeleportBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TeleportBase::~TeleportBase() = default;

bool TeleportBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeleportBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _70 = 0;
    sub_710072BB70(actor, &_64, *mIsLifeGageKeep_s, false);
    if (auto* lod = actor->getLodState())
        lod->mFlags26.set(1);
    if (!mEffectName_s.isEmpty())
        xlinkSearchAndEmit(actor, mEffectName_s.cstr(), 2, nullptr);
    if (!actor->getCharacterController() && !actor->getMainBody()) {
        _70 = 4;
        setFailed();
    }
}

void TeleportBase::leave_() {
    sub_710072BEC4(mActor, &_64, *mIsLifeGageKeep_s);
    if (auto* lod = mActor->getLodState())
        lod->mFlags26.reset(1);
}

void TeleportBase::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mIsUseChangePos_s, "IsUseChangePos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mEffectName_s, "EffectName");
    getStaticParam(&mIsLifeGageKeep_s, "IsLifeGageKeep");
}

void TeleportBase::calc_() {
    switch (_70) {
    case 0:
        _70 = *mIsUseChangePos_s ? 2 : 1;
        break;
    case 1: {
        m36();
        auto& dest = m33();
        auto& target = m34();
        sub_7100294F68(dest, target);
        _70 = 3;
        const int wait_time = *mWaitTime_s;
        const u32 rand_range = m35();
        const f32 time = wait_time + s32(sead::GlobalRandom::instance()->getU32(rand_range));
        _58 = ksys::Timer(time, time);
        break;
    }
    case 2: {
        sead::Vector3f pos{0, 0, 0};
        if (m39(m32(), &pos))
            ksys::act::sub_7100EE5B18(mActor, pos);
        _70 = 1;
        break;
    }
    case 3:
        _58.update();
        if (_58.value <= sead::Mathf::epsilon()) {
            _70 = 4;
            m37();
            setFinished();
        } else {
            m36();
            auto& dest = m33();
            auto& target = m34();
            sub_7100294F68(dest, target);
        }
        break;
    case 4:
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5E7F0(0.0f);
        } else if (auto* body = mActor->getMainBody()) {
            body->setLinearVelocity(sead::Vector3f::zero);
        }
        break;
    }
}

void TeleportBase::m37() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(0.0f);
    } else if (auto* body = mActor->getMainBody()) {
        body->setLinearVelocity(sead::Vector3f::zero);
    }
    sead::Vector3f dir = m34() - mActor->getMtx().getTranslation();
    m38(dir);
}

void TeleportBase::m38(const sead::Vector3f& dir) {
    sead::Vector3f out;
    const sead::Vector3f up = getUpDir(mActor);
    ksys::util::sub_71011EFA00(&out, dir, up);
    out.y = 0;
    if (out.x != 0 || out.z != 0) {
        out.normalize();
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5FDF0(out);
        } else if (auto* body = mActor->getMainBody()) {
            sead::Matrix34f result;
            sead::Vector3f body_up;
            const sead::Matrix34f transform = body->getTransform();
            transform.getBase(body_up, 1);
            ksys::util::sub_71011F00EC(&result, out, body_up, sead::Vector3f::zero, false);
        }
    }
}

void TeleportBase::sub_7100294F68(const sead::Vector3f& dest, const sead::Vector3f& target) {
    auto* actor = mActor;
    const sead::Vector3f to_target = target - actor->getMtx().getTranslation();
    const sead::Vector3f to_dest = dest - actor->getMtx().getTranslation();
    if (auto* controller = actor->getCharacterController()) {
        if (to_dest.x == 0 && to_dest.y == 0 && to_dest.z == 0) {
            controller->sub_7100F5E7F0(0.0f);
        } else {
            controller->sub_7100F5EDD8(1.0f);
            sead::Vector3f velocity = to_dest * 30.0f;
            const f32 distance = to_dest.length();
            if (ksys::VFR::instance()->getDeltaFrame() > 0) {
                const f32 max_speed = distance / ksys::VFR::instance()->getDeltaFrame();
                if (velocity.squaredLength() > max_speed * max_speed) {
                    const f32 length = velocity.length();
                    if (length > 0)
                        velocity *= max_speed / length;
                }
            }
            sub_7100737710(controller, velocity);
        }
    } else if (auto* body = mActor->getMainBody()) {
        if (to_dest.x == 0 && to_dest.y == 0 && to_dest.z == 0) {
            body->setLinearVelocity(sead::Vector3f::zero);
        } else {
            sead::Matrix34f result;
            sead::Vector3f body_up;
            const sead::Matrix34f transform = body->getTransform();
            transform.getBase(body_up, 1);
            ksys::util::sub_71011F00EC(&result, to_dest, body_up, sead::Vector3f::zero, false);
            result.setTranslation(dest);
            body->changePositionAndRotation(result);
        }
    }
    m38(to_target);
}

const sead::Vector3f& TeleportBase::sub_71002955BC() const {
    return *mTargetPos_d;
}

}  // namespace uking::action
