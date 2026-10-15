#include "Game/Actor/AI/aiSiteBossSwordIronPileRoot.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadQuat.h>

namespace uking::ai {

SiteBossSwordIronPileRoot::SiteBossSwordIronPileRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg), _c0() {}

SiteBossSwordIronPileRoot::~SiteBossSwordIronPileRoot() {
    if (_b0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    if (_c0.sub_7101241AD8(1))
        _c0.fadeXLink();
}

bool SiteBossSwordIronPileRoot::init_(sead::Heap* heap) {
    if (sub_71005D6D10())
        return true;

    ksys::act::InstParamPack pack;
    pack->add(*mAttackPower_m, "AttackPower");
    pack->add(*mAttackPowerForPlayer_m + *mAddAtkPower_m, "AttackPowerForPlayer");
    pack->add(*mAtMinDamage_m, "AtMinDamage");
    auto* actor = ksys::act::ActorCreator::instance()->createActor(
        mActorName_m.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &pack, true,
        false);
    if (actor)
        _b0.acquire(actor, false);
    return true;
}

void SiteBossSwordIronPileRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c = ksys::Timer(*mFallWaitCount_s, *mFallWaitCount_s);
    _84 = 0;
    _88 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi2();
    if (auto* body = mActor->getMainBody()) {
        body->changeMotionType(ksys::phys::MotionType::Keyframed);
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
    }
    changeChild("待機");
    _80 = false;
    _81 = false;
    _82 = false;
}

// NON_MATCHING: current-child strings and contact-position temporary slots.
void SiteBossSwordIronPileRoot::calc_() {
    if (_80) {
        _81 = false;
        if (_b0.hasProc()) {
            if (mActor->getConnectedCalcChild())
                mActor->resetConnectedCalcChild(false);
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_b0, &accessor);
            if (accessor.isStateCalc())
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        if (_c0.sub_7101241AD8(1))
            _c0.fadeXLink();
        changeChild("消滅");
        return;
    }
    if (_82 && _b0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        if (accessor.isStateCalc()) {
            auto* controller = mActor->m128();
            if (controller && controller->m2()) {
                if (mActor->getConnectedCalcChild() && !_c0.sub_7101241AD8(1))
                    xlinkSearchAndEmit(mActor, "SignWithGloved", 1, &_c0);
            } else if (_c0.sub_7101241AD8(1)) {
                _c0.fadeXLink();
            }
        } else {
            if (_c0.sub_7101241AD8(1))
                _c0.fadeXLink();
            auto* controller = mActor->m128();
            if (!controller || controller->m2()) {
                _a4 = ksys::Timer(90.0f, 90.0f);
            } else {
                _a4.update();
                if (_a4.value <= sead::Mathf::epsilon()) {
                    changeChild("消滅");
                    return;
                }
            }
        }
    }
    if (isCurrentChild("刺さる") && _81) {
        _81 = false;
        sub_71005979BC();
    }
    if (isCurrentChild("待機")) {
        _8c.update();
        if (_8c.value <= sead::Mathf::epsilon()) {
            _84 = 0.0f;
            changeChild("落下");
        }
    } else if (isCurrentChild("落下")) {
        sub_7100597AE0();
        sead::Vector3f contact;
        if (!sub_7100597E04(&contact))
            return;
        if (auto* body = mActor->getMainBody()) {
            body->changeMotionType(ksys::phys::MotionType::Keyframed);
            sead::Vector3f position = contact;
            position.y += 1.0f;
            body->setPosition(position, ksys::phys::PropagateToLinkedMotions{true});
            body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        }
        ksys::eft::searchAndEmitSLink(mActor, "StickGround", false);
        changeChild("刺さる");
    }
}

void SiteBossSwordIronPileRoot::sub_71005979BC() {
    const sead::Matrix34f mtx = mActor->getMtx();
    sead::Vector3f scale = sead::Vector3f::ones;
    if (_b0.hasProc()) {
        if (auto* controller = mActor->m128(); controller && controller->m2())
            scale *= 1.5f;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        if (!accessor.isStateCalc()) {
            accessor.setThisActorAsChild(mActor, false);
            accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 0, -1);
        }
        _82 = true;
        _a4 = ksys::Timer(90.0f, 90.0f);
    }
}

// NON_MATCHING: quaternion-matrix and saved vector register scheduling.
void SiteBossSwordIronPileRoot::sub_7100597AE0() {
    ksys::VFR::lerp(&_84, *mFallSpeed_s, 0.03f);
    if (auto* body = mActor->getMainBody()) {
        sead::Vector3f position = mActor->getMtx().getTranslation();
        sead::Quatf slope_quaternion;
        slope_quaternion.setAxisRadian({1.0f, 0.0f, 0.0f}, *mSlopeRate_s);
        sead::Matrix34f slope;
        slope.makeQT(slope_quaternion, sead::Vector3f::zero);
        sead::Quatf yaw_quaternion;
        yaw_quaternion.setAxisRadian(sead::Vector3f::ey, _88);
        sead::Matrix34f yaw;
        yaw.makeQT(yaw_quaternion, sead::Vector3f::zero);
        sead::Vector3f velocity(0.0f, -1.0f, 0.0f);
        velocity.rotate(slope);
        velocity.rotate(yaw);
        velocity *= _84;
        position += velocity;
        velocity.normalize();
        sead::Matrix34f mtx;
        ksys::util::sub_71011F00EC(&mtx, sead::Vector3f::ez, -velocity, position, false);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
}

bool SiteBossSwordIronPileRoot::sub_7100597E04(sead::Vector3f* out) {
    auto* body = mActor->getMainBody();
    if (!body || !body->isAddedToWorld())
        return false;
    auto* points = body->getContactPointInfo();
    if (!points || points->getNumContactPoints() == 0 || points->begin().isEnd())
        return false;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    f32 nearest = 100.0f;
    for (auto it = points->begin(), end = points->end(); it != end; ++it) {
        sead::Vector3f point;
        it.getPointPosition(&point, ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
        const f32 distance = (point - position).length();
        if (distance < nearest) {
            *out = point;
            nearest = distance;
        }
    }
    return true;
}

void SiteBossSwordIronPileRoot::leave_() {
    if (!mActor->getConnectedCalcChild())
        return;
    mActor->resetConnectedCalcChild(false);
    if (_b0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_b0, &accessor);
        if (accessor.isStateCalc())
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void SiteBossSwordIronPileRoot::loadParams_() {
    getStaticParam(&mFallWaitCount_s, "FallWaitCount");
    getStaticParam(&mFallSpeed_s, "FallSpeed");
    getStaticParam(&mSlopeRate_s, "SlopeRate");
    getMapUnitParam(&mAddAtkPower_m, "AddAtkPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mActorName_m, "ActorName");
}

bool SiteBossSwordIronPileRoot::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;
    if (message->getType() == 0x8000004 || message->getType() == 0x3000007) {
        _80 = true;
        return true;
    }
    if (message->getType() == 0x800005b) {
        _81 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
