#include "Game/AI/Action/actionThrown.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

// NON_MATCHING: store scheduling (0x60/0x88 and 0xa0/0xac zero stores)
Thrown::Thrown(const InitArg& arg) : ActionEx(arg) {}

void Thrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Thrown::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    if (*mParams.mIsOnImpact_s)
        sub_71005DC02C(actor);

    if (auto* chemical = actor->getChemicalStuff())
        chemical->sub_7100D91098(_a7);

    sub_7100738DC8(actor);

    if (!actor->getCharacterController()) {
        if (auto* body = actor->getMainBody()) {
            body->setLinearDamping(_a8);
            body->setAngularDamping(_ac);
        }
    }

    sub_71005DA114(actor, &_78);
    if (!ksys::act::isEnemyProfile(actor))
        actor->setFlag(ksys::act::Actor::ActorFlag::_2c, false);
}

void Thrown::loadParams_() {
    getStaticParam(&mParams.mReactionLevel_s, "ReactionLevel");
    getStaticParam(&mParams.mIsForceOnly_s, "IsForceOnly");
    getStaticParam(&mParams.mIsOnImpact_s, "IsOnImpact");
    getStaticParam(&mParams.mAS_s, "AS");
    getStaticParam(&mParams.mThrownKey_s, "ThrownKey");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getDynamicParam(&mParams.mPower_d, "Power");
    getDynamicParam(&mParams.mIsShootByPlayer_d, "IsShootByPlayer");
    getDynamicParam(&mParams.mTargetDir_d, "TargetDir");
}

void Thrown::calc_() {
    auto* actor = mActor;
    if (_a4) {
        _a4 = false;
    } else if (!_a5) {
        if (_a6 && thrownStalfosPartsStuff()) {
            sub_7100738428(mActor, 0.5f);
        } else {
            sead::Vector3f vel = *mParams.mTargetDir_d;
            auto* unk = actor->m100();
            if (unk && unk->_129) {
                sub_71005DC8AC(actor, &vel);
            } else {
                const f32 power = *mParams.mPower_d;
                vel *= power / f32(ksys::act::sub_7100EDD218(actor));
            }
            ksys::act::sub_7100EE5980(actor, sead::Vector3f::zero);
            ksys::act::sub_7100EE5A14(actor, sead::Vector3f::zero);

            sead::Vector3f ang_vel = *mParams.mRotSpd_s * (1.0f / 30.0f);
            if (const auto* param = actor->getParam()) {
                if (const auto* gparams = param->getRes().mGParamList) {
                    if (const auto* liftable = gparams->getLiftable()) {
                        ang_vel.set(liftable->mThrownRotSpd.ref());
                        ang_vel *= sead::Mathf::deg2rad(1.0f);
                        ang_vel *= 1.0f / 30.0f;
                    }
                }
            }
            ang_vel.setRotated(actor->getMtx(), ang_vel);
            m32(actor, vel, ang_vel);
        }
        actor->resetConnectedCalcParent(false);
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
        _a5 = true;
    }

    if (thrownStalfosPartsStuff() || actor->get68f())
        setFinished();
}

void Thrown::m32(ksys::act::Actor* actor, const sead::Vector3f& vel,
                 const sead::Vector3f& ang_vel) {
    if (!mParams.mThrownKey_s.isEmpty()) {
        auto* unk = mActor->m100();
        if (unk && !unk->_128)
            xlinkSearchAndEmit(mActor, mParams.mThrownKey_s.cstr(), 1, nullptr);
    }
    ksys::act::sub_7100EE5980(actor, vel);
    ksys::act::sub_7100EE5A14(actor, ang_vel);
}

bool Thrown::thrownStalfosPartsStuff() const {
    auto* actor = mActor;
    if (_a4 || !_a5) {
        if (ksys::act::hasTag(actor, 0x72d6e7a4u))  // StalfosParts
            return false;
    }

    ksys::phys::ContactPointInfo* info = nullptr;
    if (auto* controller = actor->getCharacterController()) {
        info = controller->sub_7100F635E4();
    } else if (auto* body = actor->getMainBody()) {
        info = body->getContactPointInfo();
    }
    if (info && info->getNumContactPoints() != 0 && !info->begin().isEnd())
        return true;

    if (auto* manager = sub_710072BA90(actor)) {
        if (sub_7100736BBC(manager->getField54()))
            return true;
    }
    if (isLandedMaybe(actor, false))
        return true;
    if (isBgGroundHit(actor, false))
        return true;
    return sub_71007A4178(actor, false);
}

bool Thrown::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (thrownStalfosPartsStuff())
        return true;
    return mActor->get68f();
}

}  // namespace uking::action
