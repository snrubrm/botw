#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

UnarmedEnemySearchWeapon::UnarmedEnemySearchWeapon(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemySearchWeapon::~UnarmedEnemySearchWeapon() = default;

void UnarmedEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    _78.clear();
    UnarmedEnemySearch::enter_(params);
}

// NON_MATCHING: target argument materialization changes the stack frame and call scheduling.
void UnarmedEnemySearchWeapon::calc_() {
    UnarmedEnemySearch::calc_();
    if (isGoStraightOrMove()) {
        ksys::act::ActorConstDataAccess accessor;
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

bool UnarmedEnemySearchWeapon::m34() {
    if (!UnarmedEnemySearch::m34())
        return false;
    _78.clear();
    return true;
}

void UnarmedEnemySearchWeapon::m44() {
    setFailed();
}

void UnarmedEnemySearchWeapon::m45() {
    setFinished();
}

void UnarmedEnemySearchWeapon::m35(const sead::Vector3f& target) {
    sub_71003B8780();
    UnarmedEnemySearch::m35(target);
}

void UnarmedEnemySearchWeapon::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mEquipItemSearchIdx_s));
    _78.clear();
}

void UnarmedEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mSearchAng_s, "SearchAng");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getStaticParam(&mLineReachableWeaponDist_s, "LineReachableWeaponDist");
}

// 0x71003b8020
bool UnarmedEnemySearchWeapon::sub_71003B8020(ksys::act::BaseProcLink& link) const {
    auto* actor = mActor;
    if (sub_7100739030(actor, link))
        return true;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    sead::Vector3f self;
    actor->getMtx().getTranslation(self);
    const f32 reach = getReachDistanceMaybe();
    return (pos - self).squaredLength() < reach * reach;
}

}  // namespace uking::ai
