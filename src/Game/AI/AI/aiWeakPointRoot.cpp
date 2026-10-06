#include "Game/AI/AI/aiWeakPointRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

WeakPointRoot::WeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeakPointRoot::~WeakPointRoot() = default;

bool WeakPointRoot::init_(sead::Heap* heap) {
    _60 = mActor->getCreateArgBaseProcLink();
    _60.hasProc();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void WeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    _70._24 = *mIsShowCriticalEffect_s;
    _70._25 = mActor->getParam()->getRes().mDamageParam->mWeakPointNoUIFlag.ref();
    if (auto* mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<dmg::DamageManager>(mgr))
            manager->addDamageCallback(0, &_70);
    }
    _70._28 = false;
    _70._29 = false;
    changeChild("通常");
}

void WeakPointRoot::leave_() {
    if (auto* mgr = mActor->getDamageMgr())
        mgr->removeDamageCallback(&_70);
}

void WeakPointRoot::loadParams_() {
    getStaticParam(&mOwnerDamage_s, "OwnerDamage");
    getStaticParam(&mIsBreakable_s, "IsBreakable");
    getStaticParam(&mIsSyncDamage_s, "IsSyncDamage");
    getStaticParam(&mIsShowCriticalEffect_s, "IsShowCriticalEffect");
    getStaticParam(&mIsNoReaction_s, "IsNoReaction");
}

bool WeakPointRoot::handleMessage_(const ksys::Message* message) {
    if (_a0.m2(*message)) {
        _d8.x();
        return true;
    }
    if (_d8.m2(*message)) {
        _a0.x();
        return true;
    }
    if (_110.m2(*message)) {
        sub_71007A36BC(mActor);
        _110.x();
        return true;
    }
    if (_148.m2(*message)) {
        sub_71007A3540(mActor);
        _148.x();
        return true;
    }
    return false;
}

s32 WeakPointRoot::m34(dmg::DamageManagerBase* mgr) {
    return mgr->getField54();
}

s32 WeakPointRoot::m35(dmg::DamageManagerBase* mgr) {
    if (auto* manager = sead::DynamicCast<dmg::DamageManager>(mgr))
        return manager->_8c;
    return 0;
}

// NON_MATCHING: the original loads `_24` before the callback info's flags (ours the other way round) and
// multiplies `velocity * delta` (ours emits `delta * velocity`); everything else is identical
// 0x71005edb04
void Unk_710242fcf0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a1 <= 0 || *a5 <= 2)
        return;

    if (auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6)) {
        u32 flags = info->mFlags;
        if (_24) {
            flags |= 0x80;
            info->mFlags = flags;
        }
        info->mFlags = flags | 1;
        if (*a4 != 3 || _25)
            info->mFlags = flags | 0x2001;
    }

    if (*a4 != 4)
        return;

    auto* actor = mDamageManager->mActor;
    const s32 count = sub_71007A26AC(actor);
    for (s32 i = 0; i < count; ++i) {
        auto* entry = sub_71007A255C(actor, i);
        if (!entry || !entry->sub_71007A1F68(0x10))
            continue;

        sead::Vector3f end;
        end.x = entry->_0.x;
        end.y = entry->_0.y;
        end.z = entry->_0.z;
        if (!entry->_d8.hasProc())
            return;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_d8, &accessor);
        const sead::Matrix34f& mtx = accessor.getActorMtx();
        sead::Vector3f start;
        start.x = mtx.m[0][3];
        start.y = mtx.m[1][3];
        start.z = mtx.m[2][3];
        if (accessor.hasTag(0x19f6c13a)) {
            const f32 delta = ksys::VFR::instance()->getDeltaFrame();
            const sead::Vector3f& velocity = accessor.getVelocity();
            start.x -= velocity.x * delta;
            start.y -= velocity.y * delta;
            start.z -= velocity.z * delta;
        }

        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.setStart(start);
        query.setEnd(end);
        query.enableLayer(ksys::phys::ContactLayer::EntityRagdoll);
        query.enableLayer(ksys::phys::ContactLayer::EntityNPC);
        query.enableLayer(ksys::phys::ContactLayer::EntityObject);
        query.enableLayer(ksys::phys::ContactLayer::EntityGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        query.setRigidBody(actor->getMainBody());
        query.worldRayCast(ksys::phys::ContactLayerType::Entity);
        if (!query.hasHitSpecifiedRigidBody() && query.hasHit()) {
            *a1 = 0;
            *a2 = 0;
            *a3 = 0;
            *a4 = -1;
            *a5 = -1;
        }
        return;
    }
}

}  // namespace uking::ai
