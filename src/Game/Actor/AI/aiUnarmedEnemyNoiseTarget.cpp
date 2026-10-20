#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007320F0.h"
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

// 0x71005d56b4: gathers nearby loose weapons which the enemy can reach and use.
bool UnarmedEnemyNoiseTarget::sub_71005D56B4() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness || !sead::IsDerivedFrom<act::Enemy>(actor))
        return false;
    Unk_7102451808 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (entry->_a8 > *mSearchWeaponDist_s)
            continue;
        auto* target = sead::DynamicCast<ksys::act::Actor>(entry->_0.mLink.getProc(nullptr, nullptr));
        auto* weapon = sead::DynamicCast<act::Weapon>(target);
        if (!weapon)
            continue;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            const sead::Vector3f target_pos = weapon->getMtx().getTranslation();
            const sead::Vector3f origin = mActor->getMtx().getTranslation();
            if (!enemy->sub_710001A204(target_pos, origin, *mTargetPos_d,
                                        *mSearchWeaponTargetDist_s))
                continue;
        }
        if (sub_71005DE53C(weapon, static_cast<act::Enemy*>(actor), entry->_a8,
                          sead::Mathf::pi(), true)) {
            _100.emplaceBack(*entry);
            if (_100.isFull())
                return true;
        }
    }
    return _100.size() != 0;
}

// 0x71005d5a58: gathers nearby enabled base weapons allowed by the enemy's weapon mask.
bool UnarmedEnemyNoiseTarget::sub_71005D5A58() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness || !sead::IsDerivedFrom<act::Enemy>(actor))
        return false;
    Unk_7102451808 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        auto* target = sead::DynamicCast<ksys::act::Actor>(entry->_0.mLink.getProc(nullptr, nullptr));
        auto* weapon = sead::DynamicCast<act::Weapon>(target);
        if (!weapon || !(weapon->_e50 & 1) || entry->_a8 > *mSearchBaseWeaponDist_s ||
            weapon->_cf0 == 4 || !static_cast<act::Enemy*>(actor)->_f54.isOnBit(weapon->_cf0) ||
            weapon->hasParentActor())
            continue;
        _100.emplaceBack(*entry);
        if (_100.isFull())
            return true;
    }
    return _100.size() != 0;
}

// NON_MATCHING: register allocation and traversal scheduling differ.
// 0x71005d4dd0: resets navigation and first tries the enemy's remembered weapon slot.
void UnarmedEnemyNoiseTarget::m37() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019D38(_d0);
    _d0.reset();
    _730.reset(*mRepathTime_s);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_c38[*mWeaponIdx_s].hasProc()) {
            auto* weapon = sead::DynamicCast<act::Weapon>(
                    enemy->_c38[*mWeaponIdx_s].getProc(nullptr, nullptr));
            if (weapon && weapon->_cf0 != 4 && enemy->_f54.isOnBit(weapon->_cf0)) {
                const sead::Vector3f target = weapon->getMtx().getTranslation();
                if (sub_710072E154(mActor, target, nullptr, -1)) {
                    if (auto* owner = sead::DynamicCast<act::Enemy>(mActor)) {
                        owner->sub_7100019D38(_d0);
                        owner->sub_71000198E4(weapon);
                    }
                    _d0.acquire(weapon, false);
                    startMoveToTargetMaybe(weapon->getMtx().getTranslation());
                    return;
                }
            }
            enemy->_c38[*mWeaponIdx_s].reset();
            enemy->_e80.resetBit(*mWeaponIdx_s);
        }
    }
    if (!sub_71005D40E8())
        changeChild("探す", nullptr);
}

// NON_MATCHING: register allocation and traversal scheduling differ.
// 0x71005d516c: follows the selected weapon and periodically refreshes the navigation target.
void UnarmedEnemyNoiseTarget::m38() {
    if (!_d0.hasProc()) {
        setFailed();
        return;
    }
    auto* target = sead::DynamicCast<ksys::act::Actor>(_d0.getProc(nullptr, nullptr));
    if (!sead::IsDerivedFrom<act::Weapon>(target)) {
        setFailed();
        return;
    }
    if (sub_71005DEC08(&_d0, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        const sead::Vector3f position = target->getMtx().getTranslation();
        if (sub_710072E154(mActor, position, nullptr, -1)) {
            sub_71005D46FC();
            return;
        }
    }
    auto* actor = mActor;
    if (actor) {
        bool close = sub_7100739030(actor, _d0);
        if (!close) {
            sead::Vector3f difference;
            {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_d0, &accessor);
                difference = accessor.getActorMtx().getTranslation() - actor->getMtx().getTranslation();
            }
            close = difference.squaredLength() < 2.0f;
        }
        if (close) {
            sub_71005D4AB0();
            return;
        }
    }
    getCurrentChild()->setDynamicParam(target->getMtx().getTranslation(), "TargetPos");
    _730.update();
    if (_730.value <= sead::Mathf::epsilon()) {
        if (!sub_71005D40E8())
            changeChild("探す", nullptr);
        _730.reset(*mRepathTime_s);
    }
    const s32 state = getStateMaybe();
    if (state == 2) {
        resetStateMaybe();
        changeChild("探す", nullptr);
    } else if (state == 1) {
        resetStateMaybe();
        sub_71005D4C28();
    }
}

// NON_MATCHING: register allocation and traversal scheduling differ.
// 0x71005d394c: tracks the last noise target and dispatches the search / alarm children.
void UnarmedEnemyNoiseTarget::calc_() {
    bool refresh_position;
    if (*mLostTime_s < 0) {
        refresh_position = sub_71005D8F28(mActor);
    } else {
        const s32 state = sub_71005D9744(mActor);
        refresh_position = sub_71005D8F28(mActor) && (state == 2 || state == 5);
    }
    if (refresh_position) {
        _c8 = *mLostTime_s;
        _e0 = sub_71005D9330(mActor);
    } else {
        ksys::Timer::update(&_c8, -1.0f);
    }
    NavMove::calc_();
    if (isGoStraightOrMove()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        sead::Vector3f position;
        if (_d0.hasProc()) {
            ksys::act::acquireActor(&_d0, &accessor);
            accessor.getActorMtx().getTranslation(position);
        } else {
            position = sub_71005D9330(mActor);
        }
        sub_71005DB068(mActor, position);
    } else {
        sub_71005DB3EC(mActor);
    }
    auto* child = getCurrentChild();
    if (child->isFinishedOrFailed()) {
        if (_c8 <= 0) {
            setFailed();
            return;
        }
        if (isCurrentChild("後退")) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(_e0, "TargetPos", -1);
            changeChild("騒ぐ", &params);
            return;
        }
        if (isCurrentChild("探す") || isCurrentChild("怒り")) {
            if (sub_71005D40E8())
                return;
            const sead::Vector3f difference = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
            const f32 distance = *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
            ksys::act::ai::InlineParamPack params;
            params.addVec3(_e0, "TargetPos", -1);
            if (difference.squaredLength() < distance * distance)
                changeChild("後退", &params);
            else
                changeChild("騒ぐ", &params);
            return;
        }
        if (isCurrentChild("武器発見")) {
            if (!child->isFinished())
                sub_71005D46FC();
            else
                changeChild("待機", nullptr);
            return;
        }
        if (isGoStraightOrMove())
            return;
        if (getCurrentChild()->isFinished()) {
            if (!sub_71005D40E8())
                changeChild("探す", nullptr);
            return;
        }
        setFailed();
        return;
    }
    if (!child->isChangeable())
        return;
    if (isCurrentChild("探す")) {
        sub_71005D40E8();
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    } else if (isCurrentChild("騒ぐ")) {
        if (!sub_71005D40E8()) {
            if (_c8 <= 0) {
                setFailed();
            } else {
                const sead::Vector3f difference = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
                const f32 distance = *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
                if (difference.squaredLength() < distance * distance) {
                    ksys::act::ai::InlineParamPack params;
                    params.addVec3(_e0, "TargetPos", -1);
                    changeChild("後退", &params);
                }
            }
        }
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    } else if (isCurrentChild("後退")) {
        if (!sub_71005D40E8() && _c8 <= 0)
            setFailed();
    } else if (isCurrentChild("怒り") && _f0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_f0, &accessor);
        sead::Vector3f position;
        accessor.getActorMtx().getTranslation(position);
        getCurrentChild()->setDynamicParam(position, "TargetPos");
    }
}

}  // namespace uking::ai
