#include "Game/Actor/AI/aiEnemySearch.h"
#include <limits>
#include <cmath>
#include "Game/Actor/aiAwarenessFilters.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: fixed-list initialization and timer/parameter stores are scheduled differently.
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

// NON_MATCHING: repeated RTTI null selection and the equipment-reset branch are folded differently.
void EnemySearch::m37() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019D38(_68);
    _68.reset();
    const f32 repath_time = static_cast<f32>(*mRepathTime_s);
    _6a8 = ksys::Timer(repath_time, repath_time);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_c38[*mEquipItemSearchIdx_s].hasProcInCalcState()) {
            auto* weapon = sead::DynamicCast<act::Weapon>(
                enemy->_c38[*mEquipItemSearchIdx_s].getProc(nullptr, nullptr));
            if (weapon) {
                if (!sead::IsDerivedFrom<act::Weapon>(weapon) ||
                    (weapon->_cf0 != 4 && enemy->_f54.isOnBit(weapon->_cf0))) {
                    const sead::Vector3f target = weapon->getMtx().getTranslation();
                    auto* actor = mActor;
                    auto* nav = actor->m45();
                    const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
                    if (sub_710072F944(actor, target, nullptr, radius, 5.0f)) {
                        if (auto* current = sead::DynamicCast<act::Enemy>(mActor)) {
                            current->sub_7100019D38(_68);
                            current->sub_71000198E4(weapon);
                        }
                        _68.acquire(weapon, false);
                        startMoveToTargetMaybe(weapon->getMtx().getTranslation());
                        return;
                    }
                } else {
                    const s32 index = *mEquipItemSearchIdx_s;
                    enemy->_c38[index].reset();
                    enemy->_e80.resetBit(index);
                }
            }
        }
    }
    if (!sub_71003B6888())
        m44();
}

void EnemySearch::m38() {
    if (!_68.hasProcInCalcState()) {
        if (!sub_71003B6888())
            m44();
        return;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_68.getProc(nullptr, nullptr));
    if (!sead::IsDerivedFrom<act::Weapon>(actor)) {
        setFailed();
        return;
    }
    if (sub_71005DEC08(&_68, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        const sead::Vector3f target = actor->getMtx().getTranslation();
        auto* owner = mActor;
        auto* nav = owner->m45();
        const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
        if (sub_710072F944(owner, target, nullptr, radius, 5.0f)) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
                enemy->sub_7100019D38(_68);
            _68.reset();
            if (!sub_71003B6888())
                m44();
            return;
        }
    }
    if (sub_71003B8020(_68)) {
        ksys::act::ai::InlineParamPack params;
        params.addActor(_68, "TargetWeapon", -1);
        changeChild("武器拾い", &params);
    } else {
        getCurrentChild()->setDynamicParam(actor->getMtx().getTranslation(), "TargetPos");
        _6a8.update();
        if (_6a8.value <= sead::Mathf::epsilon()) {
            if (!sub_71003B80F8() && !sub_71003B6888())
                m44();
            const f32 repath_time = static_cast<f32>(*mRepathTime_s);
            _6a8 = ksys::Timer(repath_time, repath_time);
        }
    }
}

void EnemySearch::m39() {
    if (!_68.hasProcInCalcState()) {
        if (!sub_71003B6888())
            m44();
        return;
    }
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_68.getProc(nullptr, nullptr));
    if (!sead::IsDerivedFrom<act::Weapon>(actor)) {
        m44();
        return;
    }
    if (sub_71005DEC08(&_68, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        const sead::Vector3f target = actor->getMtx().getTranslation();
        auto* owner = mActor;
        auto* nav = owner->m45();
        const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
        if (sub_710072F944(owner, target, nullptr, radius, 5.0f)) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
                enemy->sub_7100019D38(_68);
            _68.reset();
            if (!sub_71003B6888())
                m44();
            return;
        }
    }
    if (sub_71003B8020(_68)) {
        ksys::act::ai::InlineParamPack params;
        params.addActor(_68, "TargetWeapon", -1);
        changeChild("武器拾い", &params);
    }
}

// NON_MATCHING: search-angle parameter and visibility flag loads are scheduled differently.
bool EnemySearch::sub_71003B8B64() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy)
        return false;
    Unk_7102451808 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (!m46(entry->_0.mLink) || entry->_a8 > *mSearchDist_s)
            continue;
        auto* target = sead::DynamicCast<ksys::act::Actor>(entry->_0.mLink.getProc(nullptr, nullptr));
        auto* weapon = sead::DynamicCast<act::Weapon>(target);
        if (sub_71005DE53C(weapon, enemy, entry->_a8, *mSearchAng_s, *mIsUseSight_s)) {
            _78.emplaceBack(*entry);
            if (_78.isFull())
                return true;
        }
    }
    return _78.size() != 0;
}

// NON_MATCHING: target vector component loads and subtraction scheduling differ.
bool EnemySearch::sub_71003B80F8() {
    _78.clear();
    // The original constructs this list and appends the current target, without reading it later.
    sead::FixedObjList<sead::Vector3f, 8> points;
    sub_71003B8B64();
    if (_68.hasProcInCalcState()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_68, &accessor);
        points.emplaceBack(accessor.getActorMtx().getTranslation());
    }
    if (_78.size() != 0) {
        for (auto& entry : _78) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry._0.mLink, &accessor);
            const sead::Vector3f target = accessor.getActorMtx().getTranslation();
            auto* actor = mActor;
            auto* nav = actor->m45();
            const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
            if (sub_710072F944(actor, target, nullptr, radius, 5.0f)) {
                const auto& mtx = mActor->getMtx();
                const f32 dx = target.x - mtx(0, 3);
                const f32 dz = target.z - mtx(2, 3);
                if (std::sqrt(dx * dx + dz * dz) <= *mLineReachableWeaponDist_s) {
                    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                        enemy->sub_7100019D38(_68);
                        enemy->sub_7100019A9C(entry._0.mLink);
                    }
                    _68 = entry._0.mLink;
                    if (!isGoStraight())
                        startMoveToTargetMaybe(target);
                    return true;
                }
            }
        }
    }
    return false;
}

bool EnemySearch::sub_71003B884C() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy)
        return false;
    Unk_7102451808 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        auto* target = sead::DynamicCast<ksys::act::Actor>(entry->_0.mLink.getProc(nullptr, nullptr));
        auto* weapon = sead::DynamicCast<act::Weapon>(target);
        if (!weapon || !(weapon->_e50 & 1) || !m46(entry->_0.mLink) ||
            entry->_a8 > *mSearchDist_s)
            continue;
        if (sub_71005DE53C(weapon, enemy, entry->_a8, sead::Mathf::pi(), false)) {
            _78.emplaceBack(*entry);
            if (_78.isFull())
                return true;
        }
    }
    return _78.size() != 0;
}

}  // namespace uking::ai
