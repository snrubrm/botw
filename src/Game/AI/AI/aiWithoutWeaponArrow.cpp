#include "Game/AI/AI/aiWithoutWeaponArrow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

namespace uking::ai {

WithoutWeaponArrow::WithoutWeaponArrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
WithoutWeaponArrow::~WithoutWeaponArrow() {
    ;
}

bool WithoutWeaponArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WithoutWeaponArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    _13c = *mAtAttr_s;
    if (mActor->getRootAi()->getI() == 2) {
        m34(mActor->getVelocity(), false, "発射");
    } else {
        _114 = false;
        _118 = sead::Vector3f::zero;
        ksys::act::ai::InlineParamPack pack;
        pack.addString(mBindNodeName_s, "NodeName", -1);
        pack.addVec3(*mRotOffset_s, "RotOffset", -1);
        pack.addVec3(*mTransOffset_s, "TransOffset", -1);
        changeChild("所持", &pack);
    }

    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        parent->getMtx().getTranslation(_124);
        _116 = true;
    } else {
        _116 = false;
    }
    _115 = false;

    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkEnemyBody"))
        body->enableContactLayer(ksys::phys::ContactLayer::SensorEnemy);
}

bool WithoutWeaponArrow::handleMessage_(const ksys::Message* message) {
    // Payload of message 0x800003a (no sender found; layout read from this function)
    struct Payload {
        sead::Vector3f pos;
        s32 attr;
    };

    if (!message || message->getBrokerId() != u32(-1) || message->getType() != 0x800003a)
        return false;
    if (!message->getUserData())
        return false;
    auto* payload = static_cast<Payload*>(message->getUserData());
    _118 = payload->pos;
    _13c = payload->attr;
    _114 = true;
    return true;
}

void WithoutWeaponArrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WithoutWeaponArrow::loadParams_() {
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mStickTime_s, "StickTime");
    getStaticParam(&mAccel_s, "Accel");
    getStaticParam(&mAimSpeed_s, "AimSpeed");
    getStaticParam(&mFallAccel_s, "FallAccel");
    getStaticParam(&mFallAimSpeed_s, "FallAimSpeed");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mAtRange_s, "AtRange");
    getStaticParam(&mAtImpulse_s, "AtImpulse");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mReflectDamageRate_s, "ReflectDamageRate");
    getStaticParam(&mCanReflect_s, "CanReflect");
    getStaticParam(&mIsReflectToParent_s, "IsReflectToParent");
    getStaticParam(&mIsDelete_s, "IsDelete");
    getStaticParam(&mIsBreakIceBlock_s, "IsBreakIceBlock");
    getStaticParam(&mIsAtHitPlayerIgnore_s, "IsAtHitPlayerIgnore");
    getStaticParam(&mIsDeleteAtHit_s, "IsDeleteAtHit");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getStaticParam(&mCallHitSEKey_s, "CallHitSEKey");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getStaticParam(&mRotOffset_s, "RotOffset");
    getStaticParam(&mTransOffset_s, "TransOffset");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void WithoutWeaponArrow::m36() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c0 != 4)
            chemical->sub_7100D909A4();
    }
    changeChild("爆発");
}

bool WithoutWeaponArrow::m39() {
    return true;
}

void WithoutWeaponArrow::m40() {
    if (*mIsDelete_s)
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    else
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

s32 WithoutWeaponArrow::m41() {
    return _13c;
}

s32 WithoutWeaponArrow::m47() {
    return *mStickTime_s;
}

bool WithoutWeaponArrow::m48() {
    return isCurrentChild("発射");
}

bool WithoutWeaponArrow::m38() {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->mMaterial->attribute.ref() & 0x10;
}

void WithoutWeaponArrow::m35() {
    if (!mCallHitSEKey_s.isEmpty())
        ksys::eft::searchAndEmitSLink(mActor, mCallHitSEKey_s.cstr(), false);

    if (m47() != 0) {
        const f32 time = m47();
        _108 = ksys::Timer(time, time);
        if (auto* body = mActor->getMainBody()) {
            body->setLinearVelocity(sead::Vector3f::zero);
            body->setGravityFactor(0);
        }
        changeChild("刺さる");
        ksys::act::disableAllAttClients(mActor);
    } else {
        m40();
    }
}

bool WithoutWeaponArrow::m37(bool* broke_ice_block, bool* hit_player) {
    if (!hasAttackInfo(mActor))
        return false;
    const s32 num = getNumAttackInfoMaybe(mActor);
    if (num < 1)
        return false;

    bool hit = false;
    for (s32 i = 0; i < num; ++i) {
        auto* info = getAttackInfo(mActor, i);
        if (!info)
            continue;

        auto* link = &info->_50;
        if (*mIsBreakIceBlock_s && ksys::act::hasTag(link, ksys::act::tags::IsIceMakerBlock)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004),
                                nullptr, true);
            *broke_ice_block = true;
        }
        hit = true;
        if (ksys::act::isPlayerProfile(link))
            *hit_player = true;
    }
    return hit;
}

}  // namespace uking::ai
