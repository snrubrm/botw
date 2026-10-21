#include "Game/Actor/Action/actionZoraSurfing.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/System/VFR.h"

extern const f32 sUnk_7101EC1934;
extern const f32 sUnk_7101EC1938;
extern const f32 sUnk_7101EC193C;

static const f32 sUnk_7101E79EC4 = 0.6f;
static const f32 sUnk_7101E79EC8 = 0.15f;
static const f32 sUnk_7101E79ECC = 0.002f;
static const f32 sUnk_7101E79ED0 = 0.4f;

namespace uking::action {

ZoraSurfing::ZoraSurfing(const InitArg& arg)
    : ksys::act::ai::Action(arg),
      _160{&sUnk_7101E79EC4, &sUnk_7101E79EC8, &sUnk_7101E79ECC,
           &sUnk_7101EC1934, &sUnk_7101EC1938, &sUnk_7101EC193C, 0.0f, 0.0f, 0.0f},
      _1a0{&sUnk_7101E79ED0, 0.0f}, _1b0(0.0f, 0.0f, 0.0f), _1c8(1.309f), _1cc(1.0f), _1d0(0.0f),
      _1d4(true), _1d5(0) {}

ZoraSurfing::~ZoraSurfing() = default;

bool ZoraSurfing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ZoraSurfing::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    ksys::act::disableAllAttClients(actor);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body")) {
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackEnemy);
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackPlayer);
        body->enableContactLayer(ksys::phys::ContactLayer::SensorAttackCommon);
    }
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild()))
        sub_7100738D28(actor, child);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    actor->emitBasicSigOn();
    ksys::gdt::setFlag_Water_Relic_firstPrinceRide(true);
    if (auto* set = mActor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
        auto* body = set->findBodyByHavokName("Body");
        if (!body && set->getRigidBodies().size() >= 1)
            body = set->getRigidBodies()[0];
        if (body)
            body->setFlag200();
    }
    _20.sub_7100EEBAE0(m33(), 0.0f);
    _20.sub_7100EEBE9C(1);
    m35();
}

void ZoraSurfing::leave_() {
    ksys::act::ai::Action::leave_();
}

void ZoraSurfing::loadParams_() {
    getStaticParam(&mRotRadPerSec_s, "RotRadPerSec");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinHeight_s, "FinHeight");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASNameJump_s, "ASNameJump");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void ZoraSurfing::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: instruction scheduling only (the original loads the target x/y pair before the actor translation).
float ZoraSurfing::m32() {
    const auto& target = _20._8.sub_7100EEB370();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const float distance = (pos - target).length();
    const float t = sead::Mathf::clamp((distance - *mOnRailDistance_s) / (*mFarDistance_s - *mOnRailDistance_s), 0.0f, 1.0f);
    return (1.0f - t) * 10.0f;
}

ksys::map::Rail* ZoraSurfing::m33() {
    if (!mUniqueName_d.isEmpty()) {
        for (s32 i = 0; i < 10; ++i) {
            auto* rail = sub_7100EEF264(mActor, i);
            if (rail && rail->getUniqueName() &&
                mUniqueName_d == sead::SafeString(rail->getUniqueName()))
                return rail;
        }
    }
    return sub_7100EEF264(mActor, 0);
}

// NON_MATCHING: the common distance variable keeps -1.0f in a saved register; the original uses a separate fallback block.
void ZoraSurfing::m34() {
    if (!_20.sub_7100EEBB74())
        return;
    if (!_20.sub_7100EEBE88() && _20.m3() && m37())
        _20.sub_7100EEBE9C(-_20._58);
    f32 distance = -1.0f;
    if (_20._8.rail && _20._8.rail->isBezier())
        distance = m32() * ksys::VFR::instance()->getDeltaFrame();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m4(distance, nullptr, nullptr);
}

// NON_MATCHING: regalloc (the original reuses the rail register for &_20 in both branches).
void ZoraSurfing::m35() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f rail_pos;
    if (auto* rail = _20._8.rail) {
        const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
        rail->calcTranslate(&rail_pos, progress);
    } else {
        _20.sub_7100EEBAE0(m33(), 0.0f);
        _20.sub_7100EEBE9C(1);
    }

    if (_20.sub_7100EEBB74()) {
        if ((rail_pos - pos).length() > *mOnRailDistance_s) {
            sub_71002C30A4(rail_pos, pos);
        } else {
            m34();
            if (_20._8.rail && _20._8.rail->isBezier())
                sub_71002C2354();
            else
                sub_71002C2770();
        }
        return;
    }

    mActor->getMtx().getTranslation(_88);
    _ac = 9999.0f;
    sead::Vector3f direction = _20._8.sub_7100EEB370();
    direction -= _20._30.sub_7100EEB370();
    direction.normalize();
    _a0 = direction;
    _80 = 0;
}

void ZoraSurfing::m36() {
    sub_71002C2AD0(sub_7100EEF078(_20._8.rail, _20._30.progress));
}

// NON_MATCHING: the compiler hoists the current rail-position member address before the two rail branches.
void ZoraSurfing::sub_71002C2AD0(f32 wait_time) {
    if (_20._8.rail)
        _20._8.rail->calcTranslate(&_88, s32(_20._30.progress));
    else
        _88 = _20._8.sub_7100EEB370();
    if (_20._8.rail)
        _20._8.rail->calcTranslate(&_94, s32(_20._30.progress));
    else
        _94 = _20._8.sub_7100EEB370();
    _ac = wait_time;
    sead::Vector3f direction = _20._8.sub_7100EEB370();
    direction -= _20._30.sub_7100EEB370();
    direction.normalize();
    _a0 = direction;
    _80 = 0;
}

// NON_MATCHING: same as sub_71002C2AD0 (the rail-position member address is hoisted before the branch).
void ZoraSurfing::sub_71002C2770() {
    if (_20._8.rail)
        _20._8.rail->calcTranslate(&_88, s32(_20._30.progress));
    else
        _88 = _20._8.sub_7100EEB370();
    _94 = _20._8.sub_7100EEB370();
    sead::Vector3f direction = _20._8.sub_7100EEB370();
    direction -= _20._30.sub_7100EEB370();
    direction.normalize();
    _a0 = direction;
    _80 = 2;
}

bool ZoraSurfing::m37() {
    return true;
}

void ZoraSurfing::m38() {
    if (m39()->isEmpty())
        return;
    playAS(m39()->cstr(), true, 0, 0, -1.0f);
}

const sead::SafeString* ZoraSurfing::m39() {
    if (_1d5)
        return &mASNameJump_s;
    return &mASName_s;
}

}  // namespace uking::action
