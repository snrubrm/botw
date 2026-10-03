#include "Game/AI/AI/aiSiteBossIceSplinterRoot.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SiteBossIceSplinterRoot::SiteBossIceSplinterRoot(const InitArg& arg)
    : SiteBossChemicalProjectile(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossIceSplinterRoot::~SiteBossIceSplinterRoot() {
    ;
}

bool SiteBossIceSplinterRoot::init_(sead::Heap* heap) {
    return SiteBossChemicalProjectile::init_(heap);
}

void SiteBossIceSplinterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossChemicalProjectile::enter_(params);
}

void SiteBossIceSplinterRoot::leave_() {
    SiteBossChemicalProjectile::leave_();
}

void SiteBossIceSplinterRoot::loadParams_() {
    SiteBossChemicalProjectile::loadParams_();
    getStaticParam(&mReflectAtkPower_s, "ReflectAtkPower");
    getStaticParam(&mChaseAngleMin_s, "ChaseAngleMin");
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mBindNodeName0_s, "BindNodeName0");
    getStaticParam(&mBindNodeName1_s, "BindNodeName1");
    getStaticParam(&mChaseParentNode_s, "ChaseParentNode");
    getStaticParam(&mBindOffset0_s, "BindOffset0");
    getStaticParam(&mBindOffset1_s, "BindOffset1");
    getStaticParam(&mBindOffset2_s, "BindOffset2");
    getStaticParam(&mBindOffset3_s, "BindOffset3");
    getStaticParam(&mBindOffset4_s, "BindOffset4");
    getStaticParam(&mBindOffset5_s, "BindOffset5");
    getStaticParam(&mBindOffset6_s, "BindOffset6");
    getStaticParam(&mBindOffset7_s, "BindOffset7");
    getStaticParam(&mBindOffset8_s, "BindOffset8");
    getStaticParam(&mRotateSpeedAtHit_s, "RotateSpeedAtHit");
    getStaticParam(&mRotateSpeedAtFall_s, "RotateSpeedAtFall");
    getMapUnitParam(&mCount_m, "Count");
}

const sead::SafeString& SiteBossIceSplinterRoot::m34() {
    return mBindNodeName1_s;
}

sead::Vector3f SiteBossIceSplinterRoot::m35() {
    sead::SafeArray<sead::Vector3f, 9> offsets;
    offsets[0] = *mBindOffset0_s;
    offsets[1] = *mBindOffset1_s;
    offsets[2] = *mBindOffset2_s;
    offsets[3] = *mBindOffset3_s;
    offsets[4] = *mBindOffset4_s;
    offsets[5] = *mBindOffset5_s;
    offsets[6] = *mBindOffset6_s;
    offsets[7] = *mBindOffset7_s;
    offsets[8] = *mBindOffset8_s;
    sead::Vector3f result = offsets[*mCount_m];
    result.y -= 10.0f;
    return result;
}

bool SiteBossIceSplinterRoot::m39() {
    return false;
}

bool SiteBossIceSplinterRoot::m40() {
    return _22a;
}

u32 SiteBossIceSplinterRoot::m50() {
    return 8;
}

u32 SiteBossIceSplinterRoot::m51() {
    return 10;
}

bool SiteBossIceSplinterRoot::m54() {
    if (!*mIsAdjustHeight_s || m55())
        return false;
    return !_228;
}

bool SiteBossIceSplinterRoot::m56() {
    if (m55())
        return false;
    return !_228;
}

void SiteBossIceSplinterRoot::m44() {
    if (!(getAttackInfo(mActor, 0)->_18 & 0xa)) {
        SiteBossChemicalProjectile::m44();
        return;
    }

    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        sead::Vector3f position;
        body->getPosition(&position);
        sead::Vector3f velocity = m45();
        const f32 length = velocity.length();
        velocity.set(-1.5f * length, 0.5f, -1.5f * length);
        m46(velocity);
        m49({0.0f, 0.4f, 0.4f});
    }
}

// NON_MATCHING: the original loads the mChaseAngleMin_s pointer before the powf call (x20 live across it)
f32 SiteBossIceSplinterRoot::m57() {
    _240 += (1.0f - std::pow(0.99f, ksys::VFR::instance()->getDeltaFrame())) *
            (*mChaseAngleMin_s - _240);
    return _240;
}

}  // namespace uking::ai
