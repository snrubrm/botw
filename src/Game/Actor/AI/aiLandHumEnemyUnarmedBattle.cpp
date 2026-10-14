#include "Game/Actor/AI/aiLandHumEnemyUnarmedBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

// NON_MATCHING: scheduling / register allocation of the inlined FixedObjList setup stores (same as
// UnarmedEnemyNoiseTarget's ctor)
LandHumEnemyUnarmedBattle::LandHumEnemyUnarmedBattle(const InitArg& arg)
    : NavMove(arg) {}

LandHumEnemyUnarmedBattle::~LandHumEnemyUnarmedBattle() = default;

void LandHumEnemyUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    _150.clear();
    _148 = -1;
    _798 = sub_7100726E54(mActor);
    _799 = true;
    NavMove::enter_(params);
}

void LandHumEnemyUnarmedBattle::changeToFindItem() {
    if (_118.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    mActor->m45()->sub_7100F7D350();
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(_118, "ShootItem", -1);
    pack.addVec3(sub_71005D98D8(mActor), "TargetPos", -1);
    changeChild("アイテム発見", &pack);
}

// NON_MATCHING: the link assignment remains a call before the return rather than a tail call;
// register allocation also differs.
void LandHumEnemyUnarmedBattle::sub_710046FC10() {
    const auto* link = sub_7100471E98();
    if (!link->hasProcInCalcState())
        return;
    switch (_148) {
    case 0:
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            enemy->sub_7100019D38(_108);
            enemy->sub_7100019A9C(*link);
        }
        _108 = *link;
        break;
    case 1:
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            enemy->sub_7100019D38(_118);
            enemy->sub_7100019A9C(*link);
        }
        _118 = *link;
        break;
    }
}

// NON_MATCHING: scheduling only (loop setup and the accessor's zero stores). The original adds 0.0 to the radius.
bool LandHumEnemyUnarmedBattle::sub_710046F0AC() {
    _150.clear();
    sub_71004717FC();
    if (_150.size() == 0)
        return false;
    for (auto& entry : _150) {
        auto& link = entry._0.mLink;
        sead::Vector3f pos;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
        auto* actor = mActor;
        auto* nav = actor->m45();
        if (sub_710072F944(actor, pos, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 0.0f, 5.0f)) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                enemy->sub_7100019D38(_108);
                enemy->sub_7100019A9C(link);
            }
            _108 = link;
            if (!isGoStraight())
                startMoveToTargetMaybe(pos);
            return true;
        }
    }
    return false;
}

// NON_MATCHING: scheduling only, as sub_710046F0AC
bool LandHumEnemyUnarmedBattle::sub_710046F2B0() {
    _150.clear();
    sub_7100471B68();
    if (_150.size() == 0)
        return false;
    for (auto& entry : _150) {
        auto& link = entry._0.mLink;
        sead::Vector3f pos;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.getActorMtx().getTranslation(pos);
        auto* character = mActor->m45();
        character->sub_7100F7D350();
        accessor.sub_7100D122EC(character);
        auto* actor = mActor;
        auto* nav = actor->m45();
        if (sub_710072F944(actor, pos, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 1.0f, 5.0f)) {
            if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                enemy->sub_7100019D38(_118);
                enemy->sub_7100019A9C(link);
            }
            _118 = link;
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c2), mActor);
            if (!isGoStraight())
                startMoveToTargetMaybe(pos);
            return true;
        }
    }
    return false;
}

// NON_MATCHING: scalar argument loads are scheduled differently before the explosive search.
bool LandHumEnemyUnarmedBattle::sub_710046F50C() {
    if (isCurrentChild("危険回避"))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
    if (!level || !(level->mIsEscapeBomb.ref() || level->mIsKickBomb.ref() ||
                    level->mIsAvoidDanger.ref()))
        return false;
    _138.reset();
    const auto& link = sub_71005DE7F4(mActor, *mParams.mExplosivesAvoidDist_s - 2.0f,
                                    *mParams.mExplosivesAvoidSpeed_s,
                                    *mParams.mExplosivesAvoidAng_s, true);
    if (!link.hasProcInCalcState())
        return false;
    _138 = link;
    changeToAvoidDanger();
    return true;
}

void LandHumEnemyUnarmedBattle::changeToAvoidDanger() {
    if (_138.hasProcInCalcState()) {
        ksys::act::ai::InlineParamPack pack;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_138, &accessor);
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        pack.addVec3(pos, "TargetPos", -1);
        pack.addActor(_138, "TargetActor", -1);
        changeChild("危険回避", &pack);
    }
}

void LandHumEnemyUnarmedBattle::leave_() {
    NavMove::leave_();
    sub_71005DB3EC(mActor);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->sub_7100019C58(sub_71005D83E8(enemy, *mParams.mEquipItemSearchIdx_s));
        enemy->sub_7100019D38(_118);
        enemy->sub_7100019D38(_108);
    }
    if (_118.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    _150.clear();
}

void LandHumEnemyUnarmedBattle::sub_71004703E8() {
    if (_118.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019D38(_118);
    _118.reset();
}

// NON_MATCHING: same operations; the scheduling of the offset products / the matrix product loads differs (the original
// loads the offset vector pair first and adds the translation after all three dot products)
bool LandHumEnemyUnarmedBattle::sub_7100470D54(ksys::act::BaseProcLink* link, bool a2) {
    auto* actor = mActor;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (!accessor.isAttClientEnabled("Grab"))
        return false;
    ksys::res::AttCheck_Unk1 arg;
    arg._0 = actor->getMtx();
    const auto& base_offset = *mParams.mAttOffset_s;
    const auto& scale = actor->getScale();
    const sead::Vector3f offset(base_offset.x * scale.x, base_offset.y * scale.y,
                                base_offset.z * scale.z);
    sead::Vector3f position;
    position.setMul(actor->getMtx(), offset);
    arg._0.setTranslation(position);
    arg._36 = a2;
    arg._35 = true;
    arg._34 = *mParams.mCanGrabHeavy_s;
    arg._30 = *mParams.mGrabCheckRadius_s;
    return accessor.sub_7100D13AE4("Grab", actor, &arg, false);
}

bool LandHumEnemyUnarmedBattle::sub_7100470ED4(ksys::act::BaseProcLink& link) const {
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

void LandHumEnemyUnarmedBattle::loadParams_() {
    NavMove::loadParams_();
    getStaticParam(&mParams.mLostTimer_s, "LostTimer");
    getStaticParam(&mParams.mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mParams.mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mParams.mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mParams.mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getStaticParam(&mParams.mSearchBowTargetDist_s, "SearchBowTargetDist");
    getStaticParam(&mParams.mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mParams.mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mParams.mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mParams.mAttOffset_s, "AttOffset");
    getStaticParam(&mParams.mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mParams.mRepathTime_s, "RepathTime");
    getStaticParam(&mParams.mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mParams.mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mParams.mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mLostVMin_s, "LostVMin");
    getStaticParam(&mParams.mLostVMax_s, "LostVMax");
    getStaticParam(&mParams.mLostRange_s, "LostRange");
    getStaticParam(&mParams.mOnCoHitAllowGrabAngle_s, "OnCoHitAllowGrabAngle");
}

void LandHumEnemyUnarmedBattle::m35(const sead::Vector3f& target) {
    sub_710046FC10();
    NavMove::m35(target);
}

void LandHumEnemyUnarmedBattle::m42() {
    _799 = false;
    changeToBattle();
}

void LandHumEnemyUnarmedBattle::changeToBattle() {
    if (_118.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c3), mActor);
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D98D8(mActor), "TargetPos", -1);
    changeChild("戦闘", &pack);
}

// The getName() call and the profile comparison results are unused in the original (their use was
// compiled out); the calls remain.
// NON_MATCHING: the copy into _150. The original copy-constructs Unk_7100d78e50 as: entry ctor, matrix / field
// copies, then the entry's virtual m14(&other entry) (no such copy constructor declared yet); ours memcpys it.
bool LandHumEnemyUnarmedBattle::sub_7100471B68() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || !_798)
        return false;

    Unk_71024516c8 filter;
    filter._28 = mActor;
    filter._30 = *mParams.mCanGrabHeavy_s;
    while (auto* sensor = awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
            if (level &&
                (level->mIsEscapeBomb.ref() || level->mIsKickBomb.ref() || level->mIsAvoidDanger.ref()) &&
                ksys::act::hasTag(&entry->_0.mLink, 0xf3a5f416))
                continue;
        }
        if (entry->_a8 > *mParams.mSearchObjectDist_s)
            continue;
        if (entry->_94.length() > *mParams.mItemChaseableSpd_s)
            continue;

        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&entry->_0.mLink, &accessor);
        if (accessor.sub_7100D10E6C(30))
            continue;
        if (!accessor.isAttClientEnabled("Grab") || accessor.sub_7100D12E64())
            continue;
        if (!sub_7100472020(&entry->_0.mLink))
            continue;
        _150.emplaceBack(*entry);
        if (_150.isFull())
            return true;
    }
    return _150.size() != 0;
}

// NON_MATCHING: scheduling only (loop setup order and the fcsel of min_dist).
const ksys::act::BaseProcLink* LandHumEnemyUnarmedBattle::sub_7100471E98() {
    const ksys::act::BaseProcLink* nearest = nullptr;
    if (auto* nav = mActor->m45()) {
        const sead::Vector3f nav_pos = nav->_194;
        f32 min_dist = sead::Mathf::maxNumber();
        for (auto& entry : _150) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&entry._0.mLink, &accessor);
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            accessor.getName();
            const f32 dist = (nav_pos - pos).length();
            if (dist <= min_dist) {
                nearest = &entry._0.mLink;
                min_dist = dist;
            }
            const bool is_shield = accessor.getProfile() == "WeaponShield";
            static_cast<void>(is_shield);
        }
    }
    if (!nearest)
        nearest = &ksys::act::getDummyBaseProcLink();
    return nearest;
}

bool LandHumEnemyUnarmedBattle::sub_7100472020(const ksys::act::BaseProcLink* link) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return true;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f target;
    accessor.getActorMtx().getTranslation(target);
    const sead::Vector3f self = enemy->getMtx().getTranslation();
    return enemy->sub_710001A204(target, self, sub_71005D9330(mActor),
                                 *mParams.mSearchWeaponTargetDist_s);
}

}  // namespace uking::ai
