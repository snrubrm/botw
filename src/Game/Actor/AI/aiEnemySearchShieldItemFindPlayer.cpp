#include "Game/Actor/AI/aiEnemySearchShieldItemFindPlayer.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/aiUnk_71007302CC.h"
#include "Game/Actor/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

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

// NON_MATCHING: same work; the original keeps the loop header (awareness query) at the bottom of the loop
// (entered with a branch) and schedules the direction / front-vector loads differently.
ksys::act::BaseProcLink* EnemySearchShieldItemFindPlayer::sub_71003BB3A4() {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return &ksys::act::getDummyBaseProcLink();

    Unk_71024516c8 filter;
    filter._28 = mActor;
    filter._30 = *mParams.mCanGrabHeavy_s;
    ksys::act::BaseProcLink* result;
    while (true) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter);
        if (!entry) {
            result = &ksys::act::getDummyBaseProcLink();
            break;
        }
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
            if (level && level->mIsAvoidDanger.ref() &&
                ksys::act::hasTag(&entry->_0.mLink, 0xf3a5f416))
                continue;
        }
        if (entry->_a8 > *mParams.mSearchObjectDist_s)
            continue;

        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_0.mLink, &accessor);
        if (accessor.sub_7100D10E6C(30))
            continue;
        if (!accessor.isAttClientEnabled("Grab") || accessor.sub_7100D12E64())
            continue;

        sead::Vector3f target;
        accessor.getActorMtx().getTranslation(target);
        sead::Vector3f direction = target - mActor->getMtx().getTranslation();
        direction.y = 0.0f;
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        direction.normalize();
        if (front.dot(direction) < sead::Mathf::cos(*mParams.mItemChasealeRot_s))
            continue;
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        if (!sub_710072F7D0(mActor, position, target, nullptr, -1))
            continue;
        if (*mParams.mItemChaseableSpd_s < entry->_94.length())
            continue;

        result = &entry->_0.mLink;
        break;
    }
    return result;
}

// 0x71003baa9c
bool EnemySearchShieldItemFindPlayer::sub_71003BAA9C(ksys::act::BaseProcLink* out) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && !enemy->sub_7100016284(*mParams.mShieldIdx_s) &&
        !enemy->sub_71000161A4(*mParams.mShieldIdx_s)) {
        auto* weapon = sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mParams.mShieldIdx_s].getProc(nullptr, nullptr));
        if (sead::IsDerivedFrom<act::Weapon>(weapon) && !weapon->sub_71002E9A50()) {
            if (out)
                *out = enemy->_c38[*mParams.mShieldIdx_s];
            return true;
        }
    }
    return false;
}

// 0x71003ba99c
bool EnemySearchShieldItemFindPlayer::sub_71003BA99C() {
    auto* link = sub_71003BB3A4();
    if (!link->hasProc())
        return false;
    _230 = *link;
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_230, "TargetActor", -1);
    changeChild("アイテム発見", &pack);
    return true;
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

void EnemySearchShieldItemFindPlayer::calc_() {
    auto* child = getCurrentChild();
    bool find_player = false;
    bool pick_up_shield = false;
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("アイテム発見")) {
            if (!child->isFinished() && sub_71003BA99C())
                return;
        } else if (isCurrentChild("盾拾い")) {
            if (child->isFinished()) {
                find_player = true;
            } else if (_108.mValue <= 0.0f) {
                setFailed();
                return;
            }
        } else {
            LandHumEnemyFindPlayer::calc_();
            return;
        }
        if (!find_player) {
            auto* actor = mActor;
            auto* target = sub_71005D9050(actor);
            if ((!target || !sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) &&
                sub_71003BADD8())
                pick_up_shield = true;
            else
                find_player = true;
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("アイテム発見")) {
            if (_108.mValue <= 0.0f) {
                setFailed();
                return;
            }
        } else if (isCurrentChild("盾拾い")) {
            if (_108.mValue <= 0.0f) {
                setFailed();
                return;
            }
            if (isCurrentChild("アイテム発見") || !sub_71003BA99C()) {
                auto* actor = mActor;
                auto* target = sub_71005D9050(actor);
                if (target && sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) {
                    find_player = true;
                } else if (!_220.hasProc()) {
                    if (sub_71003BADD8()) {
                        auto* weapon = sead::DynamicCast<act::Weapon>(
                            _220.getProc(nullptr, nullptr));
                        child->sub_710039D2D0(weapon, "TargetWeapon",
                                             &ksys::act::ai::ParamPack::getActor);
                    } else {
                        find_player = true;
                    }
                }
            }
        } else if (_240) {
            if (sub_71003BA99C())
                return;
            auto* actor = mActor;
            auto* target = sub_71005D9050(actor);
            if ((!target || !sub_710073033C(actor, target, *mParams.mNoShieldSearchDist_s)) &&
                sub_71003BADD8())
                pick_up_shield = true;
        }
    }
    if (pick_up_shield) {
        sub_71003BAC8C();
    } else if (find_player) {
        if (m35())
            m40();
        else
            sub_710037EDA4();
    } else {
        LandHumEnemyFindPlayer::calc_();
    }
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
