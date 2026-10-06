#include "Game/AI/AI/aiSandwormRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSandworm.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

// 0x71002ccc20 (free function, declared only): one of the SiteBoss / Enemy part names by index (a static table).
const sead::SafeString& sub_71002CCC20(s32 idx);

namespace uking::ai {

SandwormRoot::SandwormRoot(const InitArg& arg) : EnemyRoot(arg) {}

SandwormRoot::~SandwormRoot() = default;

bool SandwormRoot::init_(sead::Heap* heap) {
    if (!EnemyRoot::init_(heap))
        return false;

    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_1650 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), "Spine_1");
    return true;
}

void SandwormRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SandwormRoot::leave_() {
    sub_71005DA114(mActor, &_250);
    if (_288 != 0) {
        auto* actor = mActor;
        sub_7100720140(actor);
        sub_7100720A70(actor);
    }
    _288 = 0;
    EnemyRoot::leave_();
}

void SandwormRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSandOffset_s, "SandOffset");
    getStaticParam(&mWeakPointDamageRate_s, "WeakPointDamageRate");
}

// 0x710055d7c8
void Unk_710241c6c0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;
    auto* manager = sead::DynamicCast<dmg::DamageManager>(mDamageManager);
    if (!manager)
        return;
    auto* enemy = sead::DynamicCast<act::Enemy>(manager->mActor);
    if (!enemy)
        return;

    if (*a4 == 4) {
        auto* attacker = manager->getAttacker();
        if (enemy->_1128.getActorPartsActor(sub_71002CCC20(0)) == *attacker ||
            enemy->_1128.getActorPartsActor(sub_71002CCC20(1)) == *attacker) {
            *a1 = 0;
            *a4 = -1;
            *a5 = -1;
            return;
        }
    }

    if (*a4 == 3) {
        auto* attacker = manager->getAttacker();
        ksys::act::acc::Bullet accessor;
        if (ksys::act::acquireActor(attacker, &accessor)) {
            if (accessor.getName() == "BombArrow_A" && !accessor.sub_71000057DC()) {
                *a5 = 22;
                return;
            }
        }
    }

    if (auto* body = enemy->findPhysicsBodyByName(sub_71007A24D0()->cstr(), "Body")) {
        if (manager->m38(body)) {
            *a1 = s32(_24 * f32(*a1));
            if (auto* info = sead::DynamicCast<dmg::DamageCallbackInfo>(a6))
                info->mFlags |= 0x2001;
        }
    }
}

}  // namespace uking::ai
