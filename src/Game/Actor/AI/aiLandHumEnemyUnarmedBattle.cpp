#include "Game/Actor/AI/aiLandHumEnemyUnarmedBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
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

// NON_MATCHING: scheduling of the translation copies and of the pending entry counter.
bool LandHumEnemyUnarmedBattle::sub_710046E57C() {
    if (isGoStraightOrMove() && _118.hasProcInCalcState()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        if (accessor.isAttClientEnabled("Grab")) {
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            auto* character = mActor->m45();
            character->sub_7100F7D350();
            accessor.sub_7100D122EC(character);
            auto* actor = mActor;
            auto* nav = actor->m45();
            if (sub_710072F944(actor, pos, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 1.0f, 5.0f)) {
                if (isMove())
                    startMoveToTargetMaybe(pos);
                return true;
            }
        }
    }

    sead::FixedObjList<sead::Vector3f, 8> points;
    _150.clear();
    sub_7100471B68();
    auto* character = mActor->m45();
    character->sub_7100F7D350();

    if (_118.hasProcInCalcState()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_118, &accessor);
        accessor.sub_7100D122EC(character);
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        if (accessor.isAttClientEnabled("Grab")) {
            points.emplaceBack(pos);
            auto* actor = mActor;
            auto* nav = actor->m45();
            if (sub_710072F944(actor, pos, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 1.0f, 5.0f)) {
                if (!isGoStraight())
                    startMoveToTargetMaybe(pos);
                return true;
            }
        }
    }

    if (_150.size() != 0) {
        sead::SafeArray<ksys::act::Unk_7100d78e50*, 8> pending;
        s32 num_pending = 0;
        for (auto& entry : _150) {
            auto& link = entry._0.mLink;
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            auto* entry_character = mActor->m45();
            entry_character->sub_7100F7D350();
            accessor.sub_7100D122EC(entry_character);
            auto* actor = mActor;
            auto* nav = actor->m45();
            if (!sub_710072F944(actor, pos, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 1.0f, 5.0f)) {
                if (!points.isFull()) {
                    points.emplaceBack(pos);
                    pending[num_pending++] = &entry;
                }
                continue;
            }
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
        for (s32 i = 0; i < num_pending; ++i) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&pending[i]->_0.mLink, &accessor);
            accessor.sub_7100D122EC(character);
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c2), mActor);
        }
    }

    if (points.size() == 0)
        return false;
    if (!isGoStraightOrMove())
        changeToLookAround();
    m41(points);
    return true;
}

// NON_MATCHING: block layout and register allocation (same structure as the original).
void LandHumEnemyUnarmedBattle::m38() {
    auto* actor = mActor;
    if (sub_71007A4178(actor, false)) {
        const s32 num = sub_71007A425C(actor);
        if (num > 0) {
            const auto& mtx = actor->getMtx();
            const sead::Vector3f front(mtx(0, 2), mtx(1, 2), mtx(2, 2));
            sead::Vector3f pos = mtx.getTranslation();
            for (s32 i = 0; i < num; ++i) {
                auto& link = sub_71007A40D0(actor, i)->_50;
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                const sead::Vector3f dir = accessor.getActorMtx().getTranslation() - pos;
                pos.normalize();
                if (sub_7100470D54(&link, front.dot(dir) >=
                                              sead::Mathf::cos(*mParams.mOnCoHitAllowGrabAngle_s))) {
                    _148 = 1;
                    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
                        enemy->sub_7100019D38(_118);
                        enemy->sub_7100019A9C(link);
                    }
                    _118 = link;
                    changeToFindItem();
                    return;
                }
            }
        }
    }

    switch (_148) {
    case 0: {
            if (!_108.hasProcInCalcState()) {
                auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
                if (enemy && enemy->_e80.isOnBit(*mParams.mEquipItemSearchIdx_s)) {
                    sub_710046ED70();
                    return;
                }
                if (sub_710046D718()) {
                    _148 = 0;
                    return;
                }
                if (sub_710046E57C()) {
                    _148 = 1;
                    return;
                }
                changeToBattle();
                return;
            }
            auto* weapon =
                sead::DynamicCast<act::Weapon>(sead::DynamicCast<ksys::act::Actor>(_108.getProc(nullptr, nullptr)));
            if (!weapon) {
                setFailed();
                return;
            }
            if (sub_71005DEC08(&_108, mActor, 1000.0f, 1000.0f, sead::Mathf::pi())) {
                const sead::Vector3f target = weapon->getMtx().getTranslation();
                auto* self = mActor;
                auto* nav = self->m45();
                if (sub_710072F944(self, target, nullptr, (nav ? nav->getRadiusMaybe() : 0.0f) + 0.0f, 5.0f)) {
                    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
                    if (enemy && enemy->_e80.isOnBit(*mParams.mEquipItemSearchIdx_s)) {
                        sub_710046ED70();
                        return;
                    }
                    if (auto* enemy2 = sead::DynamicCast<act::Enemy>(mActor))
                        enemy2->sub_7100019D38(_108);
                    _108.reset();
                    if (sub_710046D718()) {
                        _148 = 0;
                        return;
                    }
                    if (sub_710046E57C()) {
                        _148 = 1;
                        return;
                    }
                    changeToBattle();
                    return;
                }
            }
            if (sub_7100470ED4(_108)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addActor(_108, "TargetWeapon", -1);
                changeChild("武器発見", &pack);
                return;
            }
            getCurrentChild()->setDynamicParam(weapon->getMtx().getTranslation(), "TargetPos");
        break;
    }
    case 1: {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_118, &accessor);
            if (accessor.sub_7100D10E6C(30)) {
                _118.hasProcInCalcState();
                sub_71004703E8();
                changeToBattle();
                return;
            }
            const bool grab = accessor.isAttClientEnabled("Grab");
            const bool in_calc = _118.hasProcInCalcState();
            if (!grab || !in_calc ||
                sub_71005DEC08(&_118, mActor, *mParams.mSearchObjectDist_s + 0.2f,
                               *mParams.mItemChaseableSpd_s + 0.1f, sead::Mathf::piHalf())) {
                sub_71004703E8();
                changeToBattle();
                return;
            }
            getCurrentChild()->setDynamicParam(accessor.getActorMtx().getTranslation(), "TargetPos");
            if (sub_7100470D54(&_118, false)) {
                changeToFindItem();
                return;
            }
        break;
    }
    }

    _780.update();
    if (_780.value <= sead::Mathf::epsilon()) {
        if (!sub_710046F0AC() && !sub_710046D718()) {
            if (sub_710046E57C())
                _148 = 1;
            else
                changeToBattle();
        } else {
            _148 = 0;
        }
        _780.reset(*mParams.mRepathTime_s);
    }
}

// NON_MATCHING: the weapon cast result is kept with a csel in the original; slot-reset block placement and
// matrix load order differ.
void LandHumEnemyUnarmedBattle::m37() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100019D38(_108);
    _108.reset();
    sub_71004703E8();
    _780.reset(*mParams.mRepathTime_s);

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_c38[*mParams.mEquipItemSearchIdx_s].hasProcInCalcState()) {
        auto* weapon = sead::DynamicCast<act::Weapon>(
            enemy->_c38[*mParams.mEquipItemSearchIdx_s].getProc(nullptr, nullptr));
        if (weapon) {
            bool skip = false;
            if (sead::IsDerivedFrom<act::Weapon>(weapon)) {
                const s32 type = weapon->_cf0;
                if (type == 4 || !enemy->_f54.isOnBit(type)) {
                    const s32 idx = *mParams.mEquipItemSearchIdx_s;
                    enemy->_c38[idx].reset();
                    enemy->_e80.resetBit(idx);
                    skip = true;
                } else if (type == 3) {
                    const auto& target_pos = sub_71005D9330(mActor);
                    const sead::Vector2f distance(target_pos.x - mActor->getMtx()(0, 3),
                                                  target_pos.z - mActor->getMtx()(2, 3));
                    if (!(distance.length() >= *mParams.mSearchBowTargetDist_s))
                        skip = true;
                }
            }
            if (!skip) {
                auto* actor = mActor;
                auto* nav = actor->m45();
                if (sub_710072F944(actor, weapon->getMtx().getTranslation(), nullptr,
                                   (nav ? nav->getRadiusMaybe() : 0.0f) + 0.0f, 5.0f)) {
                    const sead::Vector2f distance(
                        weapon->getMtx()(0, 3) - enemy->getMtx()(0, 3),
                        weapon->getMtx()(2, 3) - enemy->getMtx()(2, 3));
                    if (distance.length() <= *mParams.mSearchWeaponDist_s) {
                        if (auto* enemy2 = sead::DynamicCast<act::Enemy>(mActor)) {
                            enemy2->sub_7100019D38(_108);
                            enemy2->sub_71000198E4(weapon);
                        }
                        _108.acquire(weapon, false);
                        _148 = 0;
                        startMoveToTargetMaybe(weapon->getMtx().getTranslation());
                        return;
                    }
                }
            }
        }
    } else {
        auto* enemy2 = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy2 && enemy2->_e80.isOnBit(*mParams.mEquipItemSearchIdx_s)) {
            sub_710046ED70();
            return;
        }
    }

    if (sub_710046D718())
        _148 = 0;
    else if (sub_710046E57C())
        _148 = 1;
    else
        changeToBattle();
}

// NON_MATCHING: the original keeps a second copy of the sub_710046D718 test after _108.reset() (ours is
// tail-merged with the first one).
void LandHumEnemyUnarmedBattle::m39() {
    switch (_148) {
    case 0: {
        if (!_108.hasProcInCalcState()) {
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (enemy && enemy->_e80.isOnBit(*mParams.mEquipItemSearchIdx_s)) {
                sub_710046ED70();
                return;
            }
            if (sub_710046D718()) {
                _148 = 0;
                return;
            }
        } else {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(_108.getProc(nullptr, nullptr));
            if (!sead::DynamicCast<act::Weapon>(actor)) {
                setFailed();
                return;
            }
            if (!sub_71005DEC08(&_108, mActor, 1000.0f, 1000.0f, sead::Mathf::pi())) {
                if (sub_7100470ED4(_108)) {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addActor(_108, "TargetWeapon", -1);
                    changeChild("武器発見", &pack);
                    return;
                }
                changeToBattle();
                return;
            }
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            if (enemy && enemy->_e80.isOnBit(*mParams.mEquipItemSearchIdx_s)) {
                sub_710046ED70();
                return;
            }
            if (auto* enemy2 = sead::DynamicCast<act::Enemy>(mActor))
                enemy2->sub_7100019D38(_108);
            _108.reset();
            if (sub_710046D718()) {
                _148 = 0;
                return;
            }
        }
        if (!sub_710046E57C()) {
            changeToBattle();
            return;
        }
        _148 = 1;
        break;
    }
    case 1:
        if (sub_7100470D54(&_118, false)) {
            changeToFindItem();
            return;
        }
        changeToBattle();
        break;
    }
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

// NON_MATCHING: filter setup, vector load order and loop register allocation differ.
void LandHumEnemyUnarmedBattle::sub_710046ED70() {
    ksys::act::ai::InlineParamPack pack;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    auto* actor = sead::DynamicCast<ksys::act::Actor>(_108.getProc(nullptr, nullptr));
    auto* weapon = sead::DynamicCast<act::Weapon>(actor);
    if (!weapon || weapon->isParentPlayer()) {
        sub_71005D7270(&pack, "TargetPos");
        // C++14 evaluation order: the original evaluates the destination first
        _128.operator=(act::PlayerInfo::getSomeProcLink());
    } else {
        pack.addVec3(weapon->getMtx().getTranslation(), "TargetPos", -1);
        _128 = _108;
    }
    if (enemy) {
        const s32 idx = *mParams.mEquipItemSearchIdx_s;
        enemy->_c38[idx].reset();
        enemy->_e80.resetBit(idx);
        if (auto* enemy2 = sead::DynamicCast<act::Enemy>(mActor))
            enemy2->sub_7100019D38(_108);
        _108.reset();
    }
    changeChild("怒り", &pack);
}

bool LandHumEnemyUnarmedBattle::sub_71004717FC() {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy)
        return false;
    Unk_7102451808 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (!(entry->_a8 <= *mParams.mSearchWeaponDist_s))
            continue;
        auto* target = sead::DynamicCast<ksys::act::Actor>(entry->_0.mLink.getProc(nullptr, nullptr));
        auto* weapon = sead::DynamicCast<act::Weapon>(target);
        if (!weapon)
            continue;
        if (weapon->_cf0 == 3) {
            const auto& target_pos = sub_71005D9330(mActor);
            const sead::Vector2f distance(target_pos.x - mActor->getMtx()(0, 3),
                                          target_pos.z - mActor->getMtx()(2, 3));
            if (!(distance.length() >= *mParams.mSearchBowTargetDist_s))
                continue;
        }
        if (!sub_7100472020(&entry->_0.mLink) ||
            !sub_71005DE53C(weapon, enemy, entry->_a8, sead::Mathf::pi(), true))
            continue;
        _150.emplaceBack(*entry);
        if (_150.isFull())
            return true;
    }
    return _150.size() != 0;
}

// NON_MATCHING: filter setup, SafeString temporary spills and accessor / list cleanup scheduling differ.
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
