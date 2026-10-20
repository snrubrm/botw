#include "Game/Actor/AI/aiUnarmedEnemyNoiseTarget.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: scheduling / register allocation of the inlined FixedObjList setup stores (the node addresses now match)
UnarmedEnemyNoiseTarget::UnarmedEnemyNoiseTarget(const InitArg& arg) : NavMove(arg) {}

UnarmedEnemyNoiseTarget::~UnarmedEnemyNoiseTarget() = default;

void UnarmedEnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _e0 = sub_71005D9330(mActor);
    _100.clear();
    _c8 = *mLostTime_s;
    NavMove::enter_(params);
}

void UnarmedEnemyNoiseTarget::m35(const sead::Vector3f& target) {
    sub_71005D4C28();
    NavMove::m35(target);
}

void UnarmedEnemyNoiseTarget::leave_() {
    NavMove::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mWeaponIdx_s));
        enemy->sub_7100019D38(_d0);
    }
    _100.clear();
}

void UnarmedEnemyNoiseTarget::loadParams_() {
    NavMove::loadParams_();
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mAbsorpDist_s, "AbsorpDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// 0x71005d4ab0
void UnarmedEnemyNoiseTarget::sub_71005D4AB0() {
    ksys::act::ai::InlineParamPack pack;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_d0.getProc(nullptr, nullptr));
    pack.acquireActor(actor, "TargetWeapon", -1);
    changeChild("武器発見", &pack);
}

// NON_MATCHING: scheduling of the accessor initialisation stores
// Picks the awareness entry nearest to the navigation target as the new target link (the dummy link if none) and
// moves the enemy's target from the old link to it.
void UnarmedEnemyNoiseTarget::sub_71005D4C28() {
    const ksys::act::BaseProcLink* nearest = nullptr;
    if (auto* nav = mActor->m45()) {
        const sead::Vector3f target = nav->_194;
        f32 min_dist = sead::Mathf::maxNumber();
        for (auto& entry : _100) {
            auto& link = entry._0.mLink;
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            const f32 dist = (target - accessor.getActorMtx().getTranslation()).length();
            if (dist <= min_dist) {
                min_dist = dist;
                nearest = &link;
            }
        }
    }
    if (!nearest)
        nearest = &ksys::act::getDummyBaseProcLink();

    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019D38(_d0);
        enemy->sub_7100019A9C(*nearest);
    }
    _d0 = *nearest;
}

// 0x71005d40e8
// NON_MATCHING: iterator setup and accessor initialization stores are scheduled differently.
bool UnarmedEnemyNoiseTarget::sub_71005D40E8() {
    if (isGoStraightOrMove() && _d0.hasProc()) {
        sead::Vector3f target;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_d0, &accessor);
        accessor.getActorMtx().getTranslation(target);
        if (sub_710072E154(mActor, target, nullptr, -1)) {
            if (isMove())
                startMoveToTargetMaybe(target);
            return true;
        }
    }

    {
        _100.clear();
        sead::FixedObjList<sead::Vector3f, 8> points;
        sub_71005D56B4();
        if (_100.size() != 0) {
            for (auto& entry : _100) {
                auto& link = entry._0.mLink;
                sead::Vector3f target;
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                accessor.getActorMtx().getTranslation(target);
                if (sub_710072E154(mActor, target, nullptr, -1)) {
                    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                        enemy->sub_7100019D38(_d0);
                        enemy->sub_7100019A9C(link);
                    }
                    _d0 = link;
                    if (!isGoStraight())
                        startMoveToTargetMaybe(target);
                    return true;
                }
                points.emplaceBack(target);
            }
            if (!isGoStraightOrMove())
                changeToLookAround();
            m41(points);
            return true;
        }
    }
    {
        _100.clear();
        sead::FixedObjList<sead::Vector3f, 8> points;
        sub_71005D5A58();
        if (_100.size() == 0)
            return false;
        for (auto& entry : _100) {
            auto& link = entry._0.mLink;
            sead::Vector3f target;
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            accessor.getActorMtx().getTranslation(target);
            if (sub_710072E154(mActor, target, nullptr, -1)) {
                if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                    enemy->sub_7100019D38(_d0);
                    enemy->sub_7100019A9C(link);
                }
                _d0 = link;
                if (!isGoStraight())
                    startMoveToTargetMaybe(target);
                return true;
            }
            points.emplaceBack(target);
        }
        if (!isGoStraightOrMove())
            changeToLookAround();
        m41(points);
        return true;
    }
}

// 0x71005d46fc: switch to the anger child with the target position (the equipped weapon's owner, the
// current target's translation, or the player).
void UnarmedEnemyNoiseTarget::sub_71005D46FC() {
    ksys::act::ai::InlineParamPack pack;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->sub_7100016284(*mWeaponIdx_s)) {
        sub_71005D7270(&pack, "TargetPos");
        // C++14 evaluation order: the original evaluates the destination first
        _f0.operator=(act::PlayerInfo::getSomeProcLink());
    } else if (_d0.hasProc()) {
        pack.addVec3(sead::DynamicCast<ksys::act::Actor>(_d0.getProc(nullptr, nullptr))
                         ->getMtx()
                         .getTranslation(),
                     "TargetPos", -1);
        _f0 = _d0;
    } else {
        sub_71005D7270(&pack, "TargetPos");
        _f0.operator=(act::PlayerInfo::getSomeProcLink());
    }

    if (enemy) {
        const s32 idx = *mWeaponIdx_s;
        enemy->_c38[idx].reset();
        enemy->_e80.resetBit(idx);
    }

    changeChild("怒り", &pack);
}

}  // namespace uking::ai
