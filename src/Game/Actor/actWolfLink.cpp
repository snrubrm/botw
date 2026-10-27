#include "Game/Actor/actWolfLink.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/gameStatisticsMgr.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <prim/seadScopedLock.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7100742478.h"

namespace uking::act {

// The "AtkBody" havok body name, shared with sub_71002F581C in the original.
static const sead::SafeString sAtkBody("AtkBody");

WolfLink::~WolfLink() = default;

bool Unk_71023d2f50::m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                        const ksys::act::Struct8Base* info, const ksys::act::PhysicsUserTag* tag) {
    return static_cast<ksys::phys::RigidBody*>(a5)->getContactLayer() ==
           ksys::phys::ContactLayer::SensorAttackPlayer;
}

// 0x71002f460c: looks up the WolfLink GParam object, resets the target table, the per-state timers
// and the home position, then enables the animal-support ray cast.
// NON_MATCHING: the entry-table loop's two constant stores are merged into one 64-bit store (the
// original keeps an stp), the timer index temporaries take separate stack slots, and the CalcArg /
// loop scheduling differs. Same instructions otherwise.
WolfLink::InitResult WolfLink::init_() {
    _1680 = getParam()->getRes().mGParamList->getWolfLink();
    if (!_1680)
        return InitResult::Failed;

    auto* sub1250 = _1250;
    if (auto* sub = sub1250->_18)
        sub->m0();
    if (auto* sub = sub1250->_10)
        sub->sub_71006F6518();

    auto* atk = getAtk();
    if (!sead::IsDerivedFrom<ksys::act::ActorAtk>(atk))
        return InitResult::Failed;
    static_cast<ksys::act::ActorAtk*>(atk)->sub_710079E344(&_15e0);

    _1650 = StatisticsMgr::instance()->getStatsPointer("player_safety_restart");

    for (auto& entry : _1608) {
        entry._8 = -1.0f;
        entry.mActorId = -1;
        entry._20 = State::_0;
        entry._24 = 0;
        entry._10.reset();
    }

    for (const auto idx : Idx14f8()) {
        _14f8[idx].rate = 0;
        sub_71002F2E78(idx);
    }

    getHomePos(&_1668);
    _1674.set(_1668);

    _14f8[Idx14f8::_9].rate = -1.0f;
    _14f8[Idx14f8::_10].value = 0.0f;
    _14f8[Idx14f8::_10].previous_value = 0.0f;
    _14f8[Idx14f8::_10].rate = -1.0f;
    _14f8[Idx14f8::_5].rate = -1.0f;

    _14c8.sub_710071EE1C();

    if (_1198) {
        Unk_7102357908::Unk50::CalcArg arg{
            sead::Vector3f(0, 0, -0.44f), 2.5f, sead::Vector3f(0, 0, 0), 2.0f, true};
        _1198->sub_71006F0800(arg);
    }

    return InitResult::Ok;
}

bool WolfLink::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!Enemy::prepareInit_(heap, arg))
        return false;

    Entry1608* entries = new (heap, 8, std::nothrow) Entry1608[16];
    if (!entries)
        return true;
    _1608 = sead::Buffer<Entry1608>(16, entries);
    return true;
}

void WolfLink::preDelete2_(const PreDeleteArg& arg) {
    Enemy::preDelete2_(arg);
    _1608.freeBuffer();
}

bool WolfLink::startPreparingForPreDelete_() {
    if (!Enemy::startPreparingForPreDelete_())
        return false;
    if (_c48._8.hasProc()) {
        _1638.sub_710070DCC0(&_c48._8, false);
        _c48._8.reset();
        _c48._7c = 0;
    }
    if (auto* manager = WolfLinkMgr::instance())
        manager->sub_7100682F80(this, true);
    return true;
}

// NON_MATCHING: comparator materialization and the final search result branch differ.
bool WolfLink::sub_71002F420C() {
    if (!_c48._8.hasProc())
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_c48._8, &accessor))
        return false;
    const u32 id = accessor.getId();
    return _1608.binarySearch(id, +[](const Entry1608& entry, const u32& id) -> s32 {
        if (entry.mActorId > id)
            return 1;
        if (entry.mActorId < id)
            return -1;
        return 0;
    }) != -1;
}

// 0x71002f430c: same search as sub_71002F420C, returns the entry's value at +0x20.
WolfLink::State WolfLink::sub_71002F430C(const ksys::act::BaseProcLink* link) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return State();
    const u32 id = accessor.getId();
    const s32 index = _1608.binarySearch(id, +[](const Entry1608& entry, const u32& id) -> s32 {
        if (entry.mActorId < id)
            return -1;
        if (entry.mActorId > id)
            return 1;
        return 0;
    });
    if (index == -1)
        return State();
    return State(_1608[index]._20);
}

WolfLink::State WolfLink::sub_71002F440C() {
    return sub_71002F430C(&_c48._8);
}

// 0x71002f612c: ascending comparator of two _1608 entries by actor id.
s32 sub_71002F612C(const WolfLink::Entry1608* a, const WolfLink::Entry1608* b) {
    if (a->mActorId < b->mActorId)
        return -1;
    return b->mActorId < a->mActorId;
}

// 0x71002f4008: adds the actor behind `link` to the _1608 target table unless it is already
// listed. `state` selects the restricted-target time stored in the entry.
// NON_MATCHING: clang hoists the 90.0f arm's constant load into the jump-table dispatch (the arm
// block disappears), two instructions shorter than the original.
void WolfLink::sub_71002F4008(ksys::act::BaseProcLink* link, State state) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return;

    f32 time;
    switch (state) {
    case State::_0:
        time = _1680->mRestrictedTargetTimeNormal.ref();
        break;
    case State::_1:
        time = 90.0f;
        break;
    case State::_2:
        time = _1680->mRestrictedTargetTimeNormal.ref();
        break;
    case State::_3:
        time = 90.0f;
        break;
    case State::_4:
        time = _1680->mRestrictedTargetTimeSpecial.ref();
        break;
    case State::_5:
        time = 90.0f;
        break;
    case State::_6:
        time = _1680->mRestrictedTargetTimeSpecial.ref();
        break;
    case State::_7:
        time = 90.0f;
        break;
    default:
        time = 0.0f;
        break;
    }

    const u32 id = accessor.getId();
    if (_1608.binarySearch(id, +[](const Entry1608& entry, const u32& id) -> s32 {
            if (entry.mActorId < id)
                return -1;
            if (entry.mActorId > id)
                return 1;
            return 0;
        }) != -1)
        return;

    const s32 index = sead::Mathi::clampMax(_1694, 15);
    Entry1608* entry = _1608.get(index);
    if (!entry || entry->mActorId != -1)
        return;

    entry->_24 = 1;
    entry->mActorId = accessor.getId();
    entry->_0 = time;
    entry->_4 = time;
    entry->_8 = -1.0f;
    entry->_20 = state;
    entry->_10 = *link;

    _1694 = sead::Mathi::clamp(_1694 + 1, 0, 15);
    sub_71002F5DA8(&_1608, sub_71002F612C, 0, sead::Mathi::min(_1694, 15));
}

void WolfLink::sub_71002F3148(u32 a1, bool flag) {
    if (_1698 & 4)
        return;
    if (flag) {
        const Idx14f8 idx = Idx14f8::_8;
        _14f8[idx].rate = -1;
    }
    getDamageMgr()->mField_34 = true;
    _1698 |= 4;
}

void WolfLink::sub_71002F31BC() {
    if (!(_1698 & 4))
        return;
    const Idx14f8 idx = Idx14f8::_8;
    _14f8[idx].rate = 0;
    sub_71002F2E78(Idx14f8::_8);
    getDamageMgr()->mField_34 = false;
    _1698 &= ~4;
}

// 0x71002f2e78: sets timer `idx` of _14f8 to its configured length plus a random part of the
// configured random range (length + random(length, length + rand)); the two "look at" cases pick the
// Wait parameters when the current AS animation is "Wait" and the Run ones otherwise.
// NON_MATCHING: in the two "look at" cases the original folds the value offset into the selected
// pointer for both members; ours folds it into the add for the length and into the load for the
// random value (two instructions differ).
void WolfLink::sub_71002F2E78(Idx14f8 idx) {
    if (!mActorParam)
        return;
    if (!mActorParam->getRes().mGParamList)
        return;
    f32 length = 0.0f;
    f32 rand = 0.0f;
    switch (idx) {
    case Idx14f8::_0:
        length = _1680->mHowlCooldownCounterLength.ref();
        rand = _1680->mHowlCooldownCounterRand.ref();
        break;
    case Idx14f8::_1:
        length = _1680->mHealCooldownCounterLength.ref();
        rand = _1680->mHealCooldownCounterRand.ref();
        break;
    case Idx14f8::_2:
        length = _1680->mFailPathCooldownCounterLength.ref();
        rand = _1680->mFailPathCooldownCounterRand.ref();
        break;
    case Idx14f8::_3: {
        if (!mASList)
            return;
        const f32* p_length;
        const f32* p_rand;
        if (mASList->x_1(0, 0) == "Wait") {
            p_length = &_1680->mLookAtCooldownWait.ref();
            p_rand = &_1680->mLookAtCooldownWaitRand.ref();
        } else {
            p_length = &_1680->mLookAtCooldownRun.ref();
            p_rand = &_1680->mLookAtCooldownRunRand.ref();
        }
        length = *p_length;
        rand = *p_rand;
        break;
    }
    case Idx14f8::_4: {
        if (!mASList)
            return;
        const f32* p_length;
        const f32* p_rand;
        if (mASList->x_1(0, 0) == "Wait") {
            p_length = &_1680->mLookAtCounterWait.ref();
            p_rand = &_1680->mLookAtCounterWaitRand.ref();
        } else {
            p_length = &_1680->mLookAtCounterRun.ref();
            p_rand = &_1680->mLookAtCounterRunRand.ref();
        }
        length = *p_length;
        rand = *p_rand;
        break;
    }
    case Idx14f8::_5:
        length = _1680->mRetargetCooldownCounterLength.ref();
        rand = _1680->mRetargetCooldownCounterRand.ref();
        break;
    case Idx14f8::_6:
        length = rand = _1680->mAfterTargetDeathCounterRand.ref();
        break;
    case Idx14f8::_7:
        length = _1680->mLostTargetCounterLength.ref();
        rand = _1680->mLostTargetCounterRand.ref();
        break;
    case Idx14f8::_8:
        length = _1680->mInvinceableCounterLength.ref();
        rand = _1680->mInvinceableCounterRand.ref();
        break;
    case Idx14f8::_9:
        length = 30.0f;
        break;
    case Idx14f8::_10:
        length = _1680->mSafePosFailCounter.ref();
        break;
    case Idx14f8::_11:
    case Idx14f8::_12:
        break;
    case Idx14f8::_13:
        length = _1680->mGiveUpShiekSensorLength.ref();
        break;
    case Idx14f8::_14:
        length = _1680->mRetryShiekSensorLength.ref();
        break;
    case Idx14f8::_15:
        length = _1680->mBattleWallHitLength.ref();
        break;
    case Idx14f8::_16:
        length = _1680->mFollowRetryLength.ref();
        break;
    case Idx14f8::_17:
        length = _1680->mPowerUpFoodLength.ref();
        break;
    case Idx14f8::_18:
        length = 300.0f;
        break;
    }
    ksys::Timer& timer = _14f8[idx];
    const f32 value = sead::GlobalRandom::instance()->getF32Range(length, length + rand);
    timer.value = value;
    timer.previous_value = value;
}

void WolfLink::sub_71002F493C() {
    if (_c48._8.hasProc()) {
        _1638.sub_710070DCC0(&_c48._8, false);
        _c48._8.reset();
        _c48._7c = 0;
    }
}

// NON_MATCHING: regalloc (ours keeps the accessor address in a callee-saved register).
sead::Vector3f WolfLink::sub_71002F4988() {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_c48._8, &accessor))
        return _c48._18;
    sead::Vector3f out;
    sub_7100742C7C(&out, accessor.getActorMtx(), accessor.sub_7100D0FD54(), getMtx().getTranslation());
    return out;
}

bool WolfLink::shouldUnload(s32* a1) {
    s32 reason = 0;
    const bool unload = Enemy::shouldUnload(&reason);
    if (unload)
        uking::ui::showInfoOverlay(0x28);
    *a1 = reason;
    return unload;
}

void WolfLink::m156() {
    const s32 life_value = _168c;
    if (life_value < 0) {
        DynamicActor::m156();
        return;
    }
    if (s32* life = getLife())
        *life = life_value;
    _168c = -1;
}

s32 WolfLink::getBaseAtkPower() {
    auto* param = _1680;
    const f32 base = param->mAttackBase.ref();
    const f32 heart_mod = param->mAttackHeartMod.ref();
    const u16 flags = _1698;
    s32 power = base + heart_mod * (getMaxLife() / 4);
    if (flags & 0x1000)
        power *= _1680->mPowerUpFoodAttackMod.ref();
    return power;
}

s32 WolfLink::sub_71002F4428() {
    auto* param = _1680;
    const f32 base = param->mDefenseBase.ref();
    const f32 heart_mod = param->mDefenseHeartMod.ref();
    return base + heart_mod * (getMaxLife() / 4);
}

void WolfLink::sub_71002F4A40(const sead::Vector3f* pos, f32 a, f32 b) {
    const f32 dist_sq = (getMtx().getTranslation() - *pos).squaredLength();
    if (dist_sq > 1600.0f) {
        if (auto* bone_control = mBoneControl) {
            if (auto* controller = bone_control->_0) {
                controller->_8 = controller->_c;
                controller->_10._9c = controller->_10._98;
                controller->sub_7100D85774();
                _1698 &= ~8;
            }
        }
    } else {
        if (auto* bone_control = mBoneControl) {
            if (auto* controller = bone_control->_0) {
                if (b > 0.0f)
                    controller->_10.sub_7100D8A9D0(b);
                if (a > 0.0f)
                    controller->sub_7100D85600(a);
                controller->sub_7100D8571C(*pos);
                controller->sub_7100D85750();
                _1698 |= 8;
            }
        }
    }
}

void WolfLink::calcMaybe() {
    Enemy::calcMaybe();

    if (_1250) {
        if (auto* cloth = _1250->_18) {
            auto* controller = getCharacterController();
            if (controller && controller->sub_7100F5F14C()) {
                if (!cloth->_30)
                    cloth->m0();
            } else {
                if (cloth->_30)
                    cloth->m1();
            }
        }
    }

    const f32 scale = _598 ? _598->_40 : 0.0f;
    for (auto it = WolfLink::Idx14f8::begin(); it != WolfLink::Idx14f8::end(); ++it) {
        const Idx14f8 idx = *it;
        const s32 i = idx.getRelativeIndex();
        if (!(_14f8[i].value <= sead::Mathf::epsilon())) {
            _14f8[i].value += scale * _14f8[i].rate;
            _14f8[i].update();
        }
    }

    sub_71002F4D54();
    sub_71002F50C4();

    if (auto* controller = getCharacterController()) {
        const f32 speed = controller->sub_7100F5EF00() / 11.0f;
        sub_71005D8D4C(this, speed * 2.0f + 0.0f, 1, false);
    }

    sub_71002F5408();

    if (auto* nav = m45()) {
        if (auto* controller = getCharacterController()) {
            const f32 speed = controller->sub_7100F5EF00() / 11.0f * 1.25f + 0.0f;
            if (!sead::Mathf::isNan(speed)) {
                auto lock = sead::makeScopedLock(nav->_1e0);
                nav->_284.x = 0.0f;
                nav->_284.y = 0.0f;
                nav->_284.z = speed;
            }
        }
    }

    sub_71002F5618();
    sub_71002F56D8();
}

void WolfLink::sub_71002F5618() {
    if (!_c48._8.hasProc()) {
        _1698 &= ~0x2000;
        return;
    }

    const sead::Vector3f pos = sub_71002F4988();
    if (pos.isNan()) {
        _1698 &= ~0x2000;
        return;
    }

    if (!sub_7100742588(nullptr, m45(), &pos, 10.0f)) {
        _1698 &= ~0x2000;
        return;
    }

    _1698 |= 0x2000;
}

// 0x71002f56d8: attack-body state of the AS event: while the attack event plays and the actor has
// attack info, sets _1698 bit 1 and makes the "AtkBody" rigid body dynamic; clears bit 1 when the
// event or the whole attack sequence ends.
// NON_MATCHING: the two flag tests of the "not latched" path are if-converted into one
// `bit1 | playing` value (two instructions more); the rest matches.
void WolfLink::sub_71002F56D8() {
    auto* as_list = getASList();
    if (!as_list)
        return;

    ksys::as::ASList::Unk4 query;
    const bool playing =
        as_list->sub_710115FBC8(3, &query, &ksys::as::ASList::Unk2::sub_71011638DC, true);
    if (!(_1698 & 1)) {
        if (!(_1698 & 2)) {
            if (!playing)
                sub_71002F581C();
        }
    } else {
        if (!(_1698 & 2)) {
            bool start_attack = true;
            if (playing) {
                if (hasAttackInfo(this))
                    _1698 |= 2;
                else
                    start_attack = false;
            }
            if (start_attack) {
                auto* body_set = getPhysics()->findBodyByName(*sub_71007A24BC());
                if (body_set) {
                    if (auto* body = body_set->findBodyByHavokName(sAtkBody)) {
                        sub_71007A3258(body, nullptr);
                        if (auto* controller = getCharacterController()) {
                            controller->sub_7100F62DD0(1.0f);
                            _1698 &= ~1;
                        }
                    }
                }
            }
        }
    }

    if (as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101163940) || as_list->x_4(0, 0))
        _1698 &= ~2;
}

void WolfLink::sub_71002F4B3C() {
    if (auto* bone_control = mBoneControl) {
        if (auto* controller = bone_control->_0) {
            controller->_8 = controller->_c;
            controller->_10._9c = controller->_10._98;
            controller->sub_7100D85774();
            _1698 &= ~8;
        }
    }
}

// 0x71002f581c: starts the WolfLink's attack sensor while the attack event is not latched. The
// attack type is 0x100 for an Enemy while the Stalfos-critical flag is set, 2 when the tagged
// target's critical chance passes, and 1 otherwise.
// NON_MATCHING: the critical-hit block is laid out out of line; the original falls into it and
// shares one `type = 1` block between the two hasTag exits (5 instructions more).
void WolfLink::sub_71002F581C() {
    auto* body_set = getPhysics()->findBodyByName(*sub_71007A24BC());
    if (!body_set)
        return;
    auto* body = body_set->findBodyByHavokName(sAtkBody);
    if (!body)
        return;

    const auto* attack = getParam()->getRes().mGParamList->getAttack();
    const s32 impulse = attack->mImpulse.ref();

    u32 type = 1;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (ksys::act::acquireActor(&_c48._8, &accessor)) {
        if ((_1698 >> 9 & 1) && accessor.getProfile() == "Enemy") {
            type = 0x100;
        } else if (accessor.hasTag(0xA4C7BA34u) && !accessor.hasTag(0x35B5AFC9u)) {
            const s32 chance =
                sead::Mathi::max(s32(_1680->mVSStalfosCritChance.ref()) - s32(_169a), 0);
            if (sead::GlobalRandom::instance()->getU32(u32(chance)) == 0) {
                _169a = 0;
                type = 2;
            } else {
                ++_169a;
            }
        }
    }

    auto* sensor = getActorAttackSensor(this);
    sensor->activateAttackSensor(0x2000, type, getBaseAtkPower(), impulse, 0.0f, 0,
                                 attack->mGuardBreakPower.ref(), -1, false, 1, -1);

    if (!body->isAddedToWorld()) {
        body->setTransform(getMtx(), ksys::phys::PropagateToLinkedMotions{true});
        sub_71007A2B64(body, nullptr);
    }
    if (auto* controller = getCharacterController()) {
        controller->sub_7100F62DD0(0.2f);
        sub_71007A2EB0(body, this, nullptr);
        _1698 |= 1;
    }
}

bool WolfLink::m81(const ksys::Message* message) {
    if (Enemy::m81(message))
        return true;
    if (message->getType() == 0x80000a7) {
        if (auto* mtx = static_cast<const sead::Matrix34f*>(message->getUserData())) {
            setMtx(*mtx, true, true);
            nullsub_4648();
        }
        return true;
    }
    if (message->getType() == 0x3000010) {
        mActorFlags2.set(ActorFlag2::_20);
        return true;
    }
    return false;
}

}  // namespace uking::act

void* Unk_71023d2f68::m2() {
    return nullptr;
}

void* Unk_71023d2f90::m2() {
    return nullptr;
}
