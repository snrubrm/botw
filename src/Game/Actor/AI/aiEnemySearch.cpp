#include "Game/Actor/AI/aiEnemySearch.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

EnemySearch::EnemySearch(const InitArg& arg) : NavMove(arg) {}

EnemySearch::~EnemySearch() = default;

void EnemySearch::enter_(ksys::act::ai::InlineParamPack* params) {
    _78.clear();
    NavMove::enter_(params);
}

// NON_MATCHING: target argument materialization changes the stack frame and call scheduling.
void EnemySearch::calc_() {
    NavMove::calc_();
    if (isGoStraightOrMove()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (_68.hasProcInCalcState()) {
            ksys::act::acquireActor(&_68, &accessor);
            sub_71005DB068(mActor, accessor.getActorMtx().getTranslation());
        } else {
            sub_71005DB068(mActor, sub_71005D9330(mActor));
        }
    } else {
        sub_71005DB3EC(mActor);
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("武器拾い")) {
            if (getCurrentChild()->isFinished())
                m45();
            else if (!sub_71003B6888())
                m44();
        } else if (!isGoStraightOrMove()) {
            if (!getCurrentChild()->isFinished() || !sub_71003B6888())
                m44();
        }
    } else if (getCurrentChild()->isChangeable() && isCurrentChild("武器拾い待ち")) {
        if (!sub_71003B6888())
            m44();
    }
}

bool EnemySearch::m34() {
    if (!NavMove::m34())
        return false;
    _78.clear();
    return true;
}

void EnemySearch::m44() {
    setFailed();
}

void EnemySearch::m45() {
    setFinished();
}

void EnemySearch::m35(const sead::Vector3f& target) {
    sub_71003B8780();
    NavMove::m35(target);
}

void EnemySearch::leave_() {
    NavMove::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mEquipItemSearchIdx_s));
    _78.clear();
}

void EnemySearch::loadParams_() {
    NavMove::loadParams_();
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mSearchAng_s, "SearchAng");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getStaticParam(&mLineReachableWeaponDist_s, "LineReachableWeaponDist");
}

// 0x71003b8020
bool EnemySearch::sub_71003B8020(ksys::act::BaseProcLink& link) const {
    auto* actor = mActor;
    if (sub_7100739030(actor, link))
        return true;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    sead::Vector3f self;
    actor->getMtx().getTranslation(self);
    const f32 reach = getReachDistanceMaybe();
    return (pos - self).squaredLength() < reach * reach;
}

// NON_MATCHING: the final link assignment is emitted as a call instead of a tail call.
void EnemySearch::sub_71003B8780() {
    auto* target = sub_71003B8E70();
    if (target->hasProcInCalcState()) {
        if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
            enemy->sub_7100019D38(_68);
            enemy->sub_7100019A9C(*target);
        }
        _68 = *target;
    }
}

// NON_MATCHING: only instruction order differs (the fcsel of the distance is emitted before the csel of the link, two
// loop-invariant subs are swapped)
// 0x71003b8e70
ksys::act::BaseProcLink* EnemySearch::sub_71003B8E70() {
    ksys::act::BaseProcLink* nearest = nullptr;
    if (auto* nav = mActor->m45()) {
        const sead::Vector3f pos = nav->_194;
        f32 nearest_distance = std::numeric_limits<f32>::max();
        for (auto& entry : _78) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry._0.mLink, &accessor);
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            const sead::Vector3f target(mtx(0, 3), mtx(1, 3), mtx(2, 3));
            const f32 distance = (pos - target).length();
            if (distance <= nearest_distance) {
                nearest_distance = distance;
                nearest = &entry._0.mLink;
            }
        }
    }
    if (!nearest)
        nearest = &ksys::act::getDummyBaseProcLink();
    return nearest;
}

}  // namespace uking::ai
