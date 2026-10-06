#include "Game/AI/AI/aiSandwormRRoot.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

void Unk_710241c878::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          dmg::DamageCallbackInfo* a6) {
    if (auto* damage_mgr = sead::DynamicCast<dmg::DamageManager>(mDamageManager))
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

}  // namespace uking::ai
