#include "Game/AI/AI/aiEnemySearchShieldItemFindPlayer.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_71007302CC.h"
#include "Game/AI/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

bool EnemySearchShieldItemFindPlayer::sub_71003BADD8() {
    bool result = false;
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
            _220.reset();
            Unk_7102451808 filter;
            while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
                auto* weapon = sead::DynamicCast<act::Weapon>(sead::DynamicCast<ksys::act::Actor>(
                    entry->_0.mLink.getProc(nullptr, nullptr)));
                if (weapon && weapon->_cf0 == 4 && !weapon->sub_71002E9A50() &&
                    sub_710072E154(mActor, entry->_88, nullptr, -1) &&
                    enemy->_f54.isOnBit(weapon->_cf0) && !weapon->hasParentActor())
                    _220.acquire(weapon, false);
            }
            result = _220.hasProc();
        }
    }
    return result;
}

void EnemySearchShieldItemFindPlayer::sub_71003BAC8C() {
    ksys::act::ai::InlineParamPack pack;
    auto* weapon = sead::DynamicCast<act::Weapon>(_220.getProc(nullptr, nullptr));
    pack.acquireActor(weapon, "TargetWeapon", -1);
    changeChild("盾拾い", &pack);
}

EnemySearchShieldItemFindPlayer::EnemySearchShieldItemFindPlayer(const InitArg& arg)
    : LandHumEnemyFindPlayer(arg) {}

EnemySearchShieldItemFindPlayer::~EnemySearchShieldItemFindPlayer() = default;

bool EnemySearchShieldItemFindPlayer::init_(sead::Heap* heap) {
    return LandHumEnemyFindPlayer::init_(heap);
}

// NON_MATCHING: RTTI guard branching differs.
void EnemySearchShieldItemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
    _240 = sub_7100726F20(mActor);
    _220.reset();
    if (!_240) {
        LandHumEnemyFindPlayer::enter_(params);
        return;
    }
    if (sub_71003BA99C())
        return;
    ksys::act::BaseProcLink link;
    if (!sub_71003BAA9C(&link)) {
        LandHumEnemyFindPlayer::enter_(params);
        return;
    }
    auto* actor = mActor;
    auto* target = sub_71005D9050(actor);
    bool ready = false;
    if (!target || !sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) {
        auto* weapon = sead::DynamicCast<act::Weapon>(link.getProc(nullptr, nullptr));
        if (weapon && sub_71007302CC(mActor, weapon, *mParams.mSearchShieldDist_s)) {
            _220 = link;
            ready = true;
        }
    }
    if (!ready)
        ready = sub_71003BADD8();
    if (ready)
        sub_71003BAC8C();
    else
        LandHumEnemyFindPlayer::enter_(params);
}

void EnemySearchShieldItemFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void EnemySearchShieldItemFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
    getStaticParam(&mParams.mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mParams.mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mParams.mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mParams.mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mParams.mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mParams.mItemChasealeRot_s, "ItemChasealeRot");
    getStaticParam(&mParams.mCanGrabHeavy_s, "CanGrabHeavy");
}

}  // namespace uking::ai
