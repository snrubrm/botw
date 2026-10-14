#include "Game/Actor/AI/aiSandwormRRoot.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

void Unk_710241c878::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          act::DamageCallbackInfo* a6) {
    if (auto* damage_mgr = sead::DynamicCast<act::DamageManager>(mDamageManager))
        mOwner->m45(a1, a2, a3, a4, a5, a6, damage_mgr);
}

SandwormRRoot::SandwormRRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRRoot::~SandwormRRoot() = default;

bool SandwormRRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_1650 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Spine_1");
    return true;
}

void SandwormRRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SandwormRRoot::leave_() {
    sub_71005DA114(mActor, &_258);
    if (_298 != 0) {
        auto* actor = mActor;
        sub_7100720140(actor);
        sub_7100720A70(actor);
    }
    _298 = 0;
    EnemyRoot::leave_();
}

void SandwormRRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
    getStaticParam(&mWeakChimicalDamageRate_s, "WeakChimicalDamageRate");
}

// NON_MATCHING: regalloc (same as SandwormRoot::handleMessage_)
// A hit by a weak-point attack (message 0x8000042): remembers the attacker and applies its attack power as
// damage type 22.
bool SandwormRRoot::handleMessage_(const ksys::Message* message) {
    if (!_1f0.m2(*message))
        return EnemyRoot::handleMessage_(message);

    sub_7100720A00(mActor, nullptr);
    if (auto* manager = mActor->getDamageMgr()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_1f0._38.mLink, &accessor)) {
            act::Struct20_2 damage;
            damage.mField_8 = accessor.getAttackPower();
            damage.mField_14 = 4;
            damage.mField_18 = 22;
            if (manager->mStruct20_a) {
                manager->mField_30.lock();
                manager->mStruct20_a->combineMaybe(&damage);
                manager->mField_30.unlock();
            }
        }
    }
    return true;
}

}  // namespace uking::ai
