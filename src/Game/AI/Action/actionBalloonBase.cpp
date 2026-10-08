#include "Game/AI/Action/actionBalloonBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::action {

BalloonBase::BalloonBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BalloonBase::~BalloonBase() {
    if (_20.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_20, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool BalloonBase::init_(sead::Heap* heap) {
    _a4 = mActor->getMtx().m[1][3];
    return true;
}

void BalloonBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _b5 = ksys::StageInfo::sIsMainFieldDungeon;
    if (auto* set = actor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        auto* body = set->findBodyByHavokName("Body");
        if (!body && set->getRigidBodies().size() > 0)
            body = set->getRigidBodies()(0);
        if (body)
            body->setFlag200();
    }

    actor = mActor;
    const f32 scale = actor->getScale().y;
    _ac = scale;
    _b0 = (scale - 1.0f) * 0.3f + 1.0f;
    _a8 = *mUpLimitSpeed_s * 30.0f;
    if (auto* body = actor->getMainBody())
        _a0 = body->getMass();
    actor->getMtx().getTranslation(_e0);
    _d0 = ksys::Timer(*mBreakTimer_s, *mBreakTimer_s);
    if (mIsFlyingBalloon_a)
        *mIsFlyingBalloon_a = true;
}

// NON_MATCHING: stack slot of the MessageType temporary / an extra saved register
void BalloonBase::leave_() {
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        auto* body = set->findBodyByHavokName("Body");
        if (!body && set->getRigidBodies().size() > 0)
            body = set->getRigidBodies()(0);
        if (body)
            body->resetFlag200();
    }

    if (_20.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_20, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    if (_b8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_b8, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                ksys::MessageType(0x80000bd), nullptr, false);
        }
    }
    _b8.reset();

    if (mBalloonHungActorBaseProcID_a)
        *mBalloonHungActorBaseProcID_a = -1;
    if (mIsFlyingBalloon_a)
        *mIsFlyingBalloon_a = false;
}

bool BalloonBase::m32() {
    const auto* life = mActor->getLife();
    if (life && *life < 1)
        return true;
    if (*mBreakTimer_s > 0.0f && _d0.value <= sead::Mathf::epsilon())
        return true;
    const f32 limit = _b5 ? *mRemainsHeightLimit_s : *mHeightLimit_s;
    if (limit > 0.0f && mActor->getMtx().m[1][3] >= limit)
        return true;
    return false;
}

// NON_MATCHING: the original builds the result from three separately computed member addresses (+4 / +8) in both
// arms of the select and loads z, y, x in that order.
sead::Vector3f BalloonBase::sub_71000B7980() {
    const sead::Vector3f* vec = &sead::Vector3f::zero;
    if (auto* chemical = mActor->getChemicalStuff())
        vec = (chemical->_c & 0x1000000) ? &sead::Vector3f::zero : &chemical->_d8;
    return *vec;
}

// NON_MATCHING: the original loads _b0 before the vector component (pre-indexed load)
// NON_MATCHING: the original loads the three components separately (x/y/z addresses computed per branch)
// where ours uses ldp + ldr.
float BalloonBase::m33() {
    const sead::Vector3f* vec = &sead::Vector3f::zero;
    if (auto* chemical = mActor->getChemicalStuff())
        vec = (chemical->_c & 0x1000000) ? &sead::Vector3f::zero : &chemical->_d8;
    return vec->y * _b0;
}

void BalloonBase::loadParams_() {
    getStaticParam(&mUpLimitSpeed_s, "UpLimitSpeed");
    getStaticParam(&mMaxAccel_s, "MaxAccel");
    getStaticParam(&mMassScale_s, "MassScale");
    getStaticParam(&mHeightLimit_s, "HeightLimit");
    getStaticParam(&mBreakTimer_s, "BreakTimer");
    getStaticParam(&mWindAccScale_s, "WindAccScale");
    getStaticParam(&mWindSpdScale_s, "WindSpdScale");
    getStaticParam(&mStayAccScale_s, "StayAccScale");
    getStaticParam(&mReturnStrengthFactor_s, "ReturnStrengthFactor");
    getStaticParam(&mRemainsHeightLimit_s, "RemainsHeightLimit");
    getStaticParam(&mIsChaseInitHeight_s, "IsChaseInitHeight");
    getStaticParam(&mReturnToOriginalPos_s, "ReturnToOriginalPos");
    getAITreeVariable(&mBalloonHungActorBaseProcID_a, "BalloonHungActorBaseProcID");
    getAITreeVariable(&mIsFlyingBalloon_a, "IsFlyingBalloon");
}

void BalloonBase::calc_() {
    ksys::act::ai::Action::calc_();
}

f32 BalloonBase::m34(f32 current, f32 target, f32 step) {
    return target;
}

// 0x71000b7f94: messages 0x3000011 to the rope actor unless the actor is held or its LOD flag is set.
void BalloonBase::sub_71000B7F94() {
    ksys::act::Actor* actor = mActor;
    const auto* map_object = actor->getMapObject();
    bool skip = false;
    if (actor->get1a0() == nullptr && (!map_object || !map_object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        skip = true;
    if (_20.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_20, &accessor)) {
            if (!accessor.sub_7100D10F0C() && !skip)
                actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000011), nullptr, true);
        }
    }
}

// NON_MATCHING: same as leave_ (the accessor address is kept in an extra saved register).
void BalloonBase::sub_71000B8054() {
    if (_20.hasProc()) {
        ksys::act::acc::RopeBase accessor;
        ksys::act::acquireActor(&_20, &accessor);
        accessor.requestCutOffHungPoint(1);
    }
    if (_b8.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_b8, &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                ksys::MessageType(0x80000bd), nullptr, false);
        }
    }
    _b8.reset();
    if (mBalloonHungActorBaseProcID_a)
        *mBalloonHungActorBaseProcID_a = -1;
}

bool BalloonBase::sub_71000B89DC() const {
    const f32 limit = _b5 ? *mRemainsHeightLimit_s : *mHeightLimit_s;
    if (!(limit > 0.0f))
        return false;
    return mActor->getMtx().m[1][3] >= limit;
}

void BalloonBase::sub_71000B782C(f32 value) {
    _a4 = value;
}

}  // namespace uking::action
