#include "Game/Actor/AI/aiSandwormRoot.h"
#include "Game/Actor/aiUnk_7102451120.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSandworm.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <limits>

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
    _250._24 = *mWeakPointDamageRate_s;
    auto* actor = mActor;
    setDamageCallbackTiming(actor, 0, &_250);
    sub_7100720140(actor);
    _288 = 0;
    if (isRootAiParamINot5()) {
        if (auto* as_list = mActor->getASList())
            as_list->startAnimationMaybe(-1.0f, -1.0f, "SwimNormal", 0, 0, true);
    }
    EnemyRoot::enter_(params);
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(actor)) {
        const f32 offset = *mSandOffset_s;
        sandworm->_159c = offset;
        sandworm->_15b0 = offset;
    }
    sub_71007A397C(actor);
    _1e8.x();
    _240 = 0;
    _248 = -1.0f;
    _278.sub_7100721380(std::numeric_limits<f32>::infinity(), mActor);
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
void Unk_710241c6c0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, act::DamageCallbackInfo* a6) {
    if (*a1 < 1)
        return;
    auto* manager = sead::DynamicCast<act::DamageManager>(mDamageManager);
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
            if (auto* info = sead::DynamicCast<act::DamageCallbackInfo>(a6))
                info->mFlags |= 0x2001;
        }
    }
}

// NON_MATCHING: regalloc (ours keeps &_1e8._38.mLink in a callee-saved register; the original recomputes it)
// A hit by a weak-point attack (message 0x8000042): remembers the attacker and applies its attack power as
// damage type 22.
bool SandwormRoot::handleMessage_(const ksys::Message* message) {
    if (!_1e8.m2(*message))
        return EnemyRoot::handleMessage_(message);

    sub_7100720A00(mActor, nullptr);
    if (auto* manager = mActor->getDamageMgr()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_1e8._38.mLink, &accessor)) {
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
