#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/Actor/actEnemy.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"

namespace uking::ai {

EnemyNormal::EnemyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original keeps the sender base vptr stores (_130/_2e0) after the payload resets;
// our `= default` Unk_7102357d20 dtor is elided (same issue as every other sender owner's dtor)
EnemyNormal::~EnemyNormal() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

bool EnemyNormal::init_(sead::Heap* heap) {
    _3ac.reset(4);
    _3ac.set(2);
    return true;
}

void EnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        m41();
        awareness->enable();
    }
    _3b0 = *mTerritoryArea_m > 0.0f ? mTerritoryArea_m : mTerritoryArea_s;
    _364 = 0;
    _368 = 0;
    m34();
    _36c = 15.0f;

    auto* actor = mActor;
    _3ac.makeAllZero();
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        _3ac.set(1);
    _3ac.set(2);
    if (auto* lod = actor->getLodState())
        lod->mFlags14.set(0x2000000);

    const s32 min = sead::Mathi::min(*mNoActionReactTimeMin_s, *mNoActionReactTimeMax_s);
    const s32 max = sead::Mathi::max(*mNoActionReactTimeMin_s, *mNoActionReactTimeMax_s);
    _124 = min;
    _128 = max;
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;
    _290.x();
}

void EnemyNormal::calc_() {
    auto* child = getCurrentChild();
    m59();
    if (isCurrentChild("プレイヤー発見"))
        sub_710039F570(true);
    else if (isCurrentChild("不審者発見"))
        sub_710039F570(false);
    sub_710039EB7C();
    sub_710039EC4C();
    if (m55())
        sub_710039ED94();

    if (child->isFinished() || child->isFailed()) {
        if (sub_710039EF24(1))
            return;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->_e84.resetBit(1);
        sub_71005D8E9C(mActor);

        Unk3 result;
        result._0 = -1;
        result._4 = 0;
        m60(&result);
        if (m63(&result)) {
            m62(&result);
            return;
        }
        if (result._0 == 2) {
            m62(&result);
            m40();
        } else if (result._0 == 1) {
            m62(&result);
            m36();
        } else if (result._0 == 0) {
            m62(&result);
            m39();
        } else {
            m64();
            m37();
        }
    } else if (child->isChangeable()) {
        if (sub_710039EF24(0))
            return;

        Unk3 result;
        result._0 = -1;
        result._4 = 0;
        m61(&result);
        if (m63(&result)) {
            m62(&result);
            return;
        }
        if (result._0 == 2) {
            m62(&result);
            m40();
        } else if (result._0 == 1) {
            m62(&result);
            m36();
        } else if (result._0 == 0) {
            m62(&result);
            m39();
        }
    }
}

// NON_MATCHING: the original tests the damage type with a bitmap lookup ((0x13 >> (type - 1)) & 1);
// ours uses a bit test on type
void EnemyNormal::sub_710039EB7C() {
    sub_710039E76C();
    if (_368 >= 0.0f)
        ksys::Timer::update(&_368, -1.0f);

    if (auto* damage_mgr = mActor->getDamageMgr()) {
        const s32 type = damage_mgr->getField54();
        if (_12c) {
            ksys::Timer::update(&_120, -1.0f);
        } else {
            switch (type) {
            case 1:
            case 2:
            case 5:
                _12c = true;
                break;
            default:
                break;
            }
        }
    }

    if (_364 > 0.0f)
        ksys::Timer::update(&_364, -1.0f);
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        _3ac.set(1);
    else
        _3ac.reset(1);
}

// NON_MATCHING: stack layout (the MessageType temporary is at the bottom of the frame in the original)
void EnemyNormal::sub_710039EC4C() {
    const f32 speed = mActor->getVelocity().length();
    if (speed <= sead::Mathf::epsilon() && speed >= -sead::Mathf::epsilon())
        return;

    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    sead::Vector3f home;
    actor->getHomePos(&home);
    Unk_71024516a0 filter;
    ksys::act::ActorConstDataAccess accessor;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (entry->_a8 > *mPressBreakObject_s)
            break;
        ksys::act::acquireActor(&entry->mLink, &accessor);
        actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000be),
                           nullptr, true);
    }
}

void EnemyNormal::sub_710039ED94() {
    auto* actor = mActor;
    auto* chemical = actor->getChemicalStuff();
    if (!chemical || chemical->_c0 == 2 || !(chemical->_b8 & 4))
        return;
    if (*mLostExtinguishFireDist_s <= 0.0f)
        return;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    sead::Vector3f home;
    actor->getHomePos(&home);
    if (!((home - actor->getMtx().getTranslation()).length() < *mLostExtinguishFireDist_s))
        return;

    Unk_71024517e0 filter;
    ksys::act::acc::Weapon accessor;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (entry->_a8 > *mLostExtinguishFireDist_s)
            break;
        ksys::act::acquireActor(&entry->mLink, &accessor);
        if (!accessor.sub_71002EF980()) {
            actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800002c),
                               nullptr, true);
        }
    }
}

bool EnemyNormal::sub_710039EF24(s32 mode) {
    Unk2 target;
    bool found = false;
    const s32 count = m53();
    for (s32 i = 0; i < count; ++i) {
        Unk1 info;
        if (mode == 1)
            m50(&info, i);
        else if (mode == 0)
            m49(&info, i);

        if (info._0 == -1)
            continue;
        if (m56(&target, &info) || sub_71003A2BE0(&target, &info)) {
            const s32 type = info._0;
            m57(type, &target);
            sub_71003A3D0C(type, &target);
            if (type == 0) {
                if (auto* unk = sub_71005D9D68(mActor))
                    unk->sub_71002DCBDC(8);
            }
            found = true;
            break;
        }
    }

    if (_368 <= 0.0f) {
        _188.x();
        _290.x();
        _200.x();
    }
    return found;
}

void EnemyNormal::sub_71003A3D0C(s32 type, Unk2* target) {
    m58(type, target);
    switch (type) {
    case 0:
    case 1:
        sub_71003A02E0(target);
        break;
    case 2:
        sub_71003A0FD8(target);
        break;
    case 3:
        sub_71003A1164(target);
        break;
    case 4:
        sub_71003A0E38(target);
        break;
    case 5:
        sub_71003A1298(target);
        break;
    case 6:
        sub_71003A13E4(target);
        break;
    case 7:
        sub_71003A157C(target);
        break;
    case 8:
        m69(target);
        break;
    default:
        break;
    }
}

void EnemyNormal::sub_71003A0FD8(Unk2* target) {
    _3ac.reset(8);
    if (!ksys::act::isPlayerProfile(target->_0)) {
        if (auto* unk = sub_71005D9D68(mActor))
            unk->sub_71002DC628(*target->_0, 4);
    }
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;
    _358 = ksys::Timer(*mSoundLostTimer_s, *mSoundLostTimer_s);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target->_38, "TargetPos", -1);
    params.addActor(*target->_0, "TargetActor", -1);
    changeChild("音気づき", &params);
    sub_710039FAA4(target->_38);
}

void EnemyNormal::sub_71003A1164(Unk2* target) {
    _3ac.reset(8);
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target->_38, "TargetPos", -1);
    _50.reset();
    changeChild("脅威感知", &params);
    sub_710039FAA4(target->_38);
}

void EnemyNormal::sub_71003A1298(Unk2* target) {
    _3ac.reset(8);
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target->_38, "TargetPos", -1);
    params.addActor(*target->_0, "TargetActor", -1);
    changeChild("気配気づき", &params);
    sub_710039FAA4(target->_38);
}

void EnemyNormal::sub_71003A13E4(Unk2* target) {
    _3ac.reset(8);
    _188.x();
    if (!_200._30 && _3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    m41();
    _50.reset();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target->_38, "TargetPos", -1);
    params.addActor(*target->_0, "TargetActor", -1);
    changeChild("行動中仲間発見", &params);
    sub_710039FAA4(target->_38);
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DC628(*target->_0, 0x20);
}

void EnemyNormal::sub_71003A157C(Unk2* target) {
    _3ac.reset(8);
    _188.x();
    if (!_200._30 && _3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    m41();
    _290.x();
    _50.reset();

    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    params.addVec3(target->_38, "TargetPos", -1);
    changeChild("不調仲間発見", &params);
    sub_710039FAA4(target->_38);
}

void EnemyNormal::m69(Unk2* target) {
    _3ac.reset(8);
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    auto* actor = mActor;
    _120 = time;
    _12c = false;
    _364 = 0;
    _50.reset();

    ksys::act::ai::InlineParamPack params;
    params.addVec3(target->_38, "TargetPos", -1);
    m42();
    if (auto* awareness = actor->getAwareness()) {
        if (auto* sensor = awareness->_260[0]) {
            if (auto* flags = sensor->m16())
                flags->set(1);
        }
    }
    _370 = 60.0f;
    changeChild("攻撃反応", &params);
    sub_710039FAA4(target->_38);
}

void EnemyNormal::m41() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EBE0(1.0f);
        if (auto* sensor = awareness->_260[0]) {
            if (auto* flags = sensor->m16())
                flags->reset(1);
        }
    }
}

void EnemyNormal::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
    if (_3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    _188.x();
}

void EnemyNormal::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSoundLostTimer_s, "SoundLostTimer");
    getStaticParam(&mNoActionReactTimeMin_s, "NoActionReactTimeMin");
    getStaticParam(&mNoActionReactTimeMax_s, "NoActionReactTimeMax");
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mNpcTerritoryArea_s, "NpcTerritoryArea");
    getStaticParam(&mNoPlayerTerritoryArea_s, "NoPlayerTerritoryArea");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mEnlargeAwnRatio_s, "EnlargeAwnRatio");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mSpeadDist2_s, "SpeadDist2");
    getStaticParam(&mHomePosRadius_s, "HomePosRadius");
    getStaticParam(&mSubsTerritoryArea_s, "SubsTerritoryArea");
    getStaticParam(&mLostExtinguishFireDist_s, "LostExtinguishFireDist");
    getStaticParam(&mShortRangeTerritoryArea_s, "ShortRangeTerritoryArea");
    getStaticParam(&mCloseRangeTerritoryArea_s, "CloseRangeTerritoryArea");
    getStaticParam(&mPressBreakObject_s, "PressBreakObject");
    getStaticParam(&mTerritoryHeight_s, "TerritoryHeight");
    getStaticParam(&mIsMindDoubtTarget_s, "IsMindDoubtTarget");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getAITreeVariable(&mPlayerSoundSealRefCount_a, "PlayerSoundSealRefCount");
    getAITreeVariable(&mSealNoPlayerAwnRequestCount_a, "SealNoPlayerAwnRequestCount");
}

void EnemyNormal::m35() {
    m64();
    m37();
}

void EnemyNormal::m36() {
    sead::Vector3f home_pos;
    m48(&home_pos);
    if ((home_pos - mActor->getMtx().getTranslation()).length() < *mHomePosRadius_s)
        m37();
    else
        m38();
}

void EnemyNormal::m42() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(*mEnlargeAwnRatio_s);
}

void EnemyNormal::m48(sead::Vector3f* pos) {
    mActor->getHomePos(pos);
}

s32 EnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    return sTable[idx];
}

void EnemyNormal::m64() {
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(8);
    sub_71005D8E9C(mActor);
}

bool EnemyNormal::m65(sead::Heap* heap) {
    _48 = new (heap) Unk_710039D8F0;
    return _48 != nullptr;
}

bool EnemyNormal::m45(const sead::Vector3f& target_pos, ksys::act::BaseProcLink& target,
                      bool skip_own_pos) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (!skip_own_pos && !m46(pos, target))
        return true;
    if (target.hasProcInCalcState() && !m46(target_pos, target))
        return true;
    return false;
}

// NON_MATCHING: register allocation (the address of _308's link is kept in a callee-saved register
// across the lock instead of being recomputed for sub_71002DC628)
bool EnemyNormal::handleMessage_(const ksys::Message& message) {
    if (_308.m2(message)) {
        if (auto* unk = sub_71005D9D68(mActor))
            unk->sub_71002DC628(_308._38.mLink, 0x40);
        _308.x();
        return true;
    }

    if (_188._30 || m73())
        return false;

    if (_188.m2(message)) {
        sead::Vector3f center;
        m48(&center);
        if (m45(_188._38.mData._28, _188._38.mData._0, false)) {
            _188.x();
            return false;
        }
        if (ksys::map::AutoPlacementMgr::instance() &&
            ksys::map::AutoPlacementMgr::instance()->isNonAutoPlacement(_188._38.mData._28, true)) {
            return false;
        }
        _290.x();
        if (!_200._30) {
            _368 = sead::GlobalRandom::instance()->getF32Range(8.0f, 20.0f);
            if (_3ac.isOn(2)) {
                _3ac.reset(2);
                if (auto* lod = mActor->getLodState())
                    lod->mFlags14.reset(0x2000000);
            }
        }
        return !(_188._38.mData._34 & 2);
    }

    if (!_200._30 && _200.m2(message)) {
        if (_188._30)
            return true;
        _368 = sead::GlobalRandom::instance()->getF32Range(8.0f, 20.0f);
        _290.x();
        if (_3ac.isOn(2)) {
            _3ac.reset(2);
            if (auto* lod = mActor->getLodState())
                lod->mFlags14.reset(0x2000000);
        }
        return true;
    }

    if (mActor->getParam()->getRes().mGParamList->getEnemy()->mIsMindFriend.ref() && !_290._30 &&
        _290.m2(message)) {
        if (_188._30)
            return true;
        if (_200._30)
            return true;
        _368 = sead::GlobalRandom::instance()->getF32Range(18.0f, 40.0f);
        if (_3ac.isOn(2)) {
            _3ac.reset(2);
            if (auto* lod = mActor->getLodState())
                lod->mFlags14.reset(0x2000000);
        }
        return true;
    }

    return false;
}

}  // namespace uking::ai

bool Unk_71023e9028::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000bf)
        return false;

    auto* payload = static_cast<Unk_71023e9028_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

bool Unk_71023e8ff8::m2(const ksys::Message& message) {
    if (message.getType().value != 0x80000b3)
        return false;

    auto* payload = static_cast<Unk_71023e8ff8_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

namespace uking::ai {

// NON_MATCHING: the original shares one "return false" block (ours duplicates it per early return)
bool EnemyNormal::m46(const sead::Vector3f& pos, ksys::act::BaseProcLink& target) {
    sead::Vector3f center;
    m48(&center);

    const f32 area = sub_71003A234C(&target);
    const bool has_target = target.hasProc();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target, &accessor);
    const auto& mtx = accessor.getActorMtx();
    const sead::Vector2f target_xz(mtx.m[0][3], mtx.m[2][3]);

    const f32 height = *mTerritoryHeight_s;
    if (height > 0.0f) {
        if (sead::Mathf::abs(center.y - pos.y) > height)
            return false;
        if (sead::Mathf::abs(center.y - mtx.m[1][3]) > height)
            return false;
    }

    const sead::Vector2f center_xz(center.x, center.z);
    const f32 area_sq = area * area;
    if (!((center_xz - sead::Vector2f(pos.x, pos.z)).squaredLength() < area_sq))
        return false;
    if (has_target && !((center_xz - target_xz).squaredLength() < area_sq))
        return false;

    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (!mgr)
        return true;
    sead::Vector3f own_pos;
    mActor->getMtx().getTranslation(own_pos);
    if (mgr->isNonAutoPlacement(own_pos, true))
        return false;
    return !mgr->isNonAutoPlacement(pos, true);
}

f32 EnemyNormal::sub_71003A234C(ksys::act::BaseProcLink* target) {
    if (!target || !target->hasProc())
        return *_3b0;
    if (ksys::act::isNPCProfile(target))
        return *mNpcTerritoryArea_s;
    if (ksys::act::isPlayerProfile(target) || ksys::act::isNotLivingCreature(target))
        return *_3b0 + _3b8;
    return *mNoPlayerTerritoryArea_s;
}

// NON_MATCHING: the three filter branches are tail-merged differently; the filter bits are stored
// once more in the original's "2" path layout
ksys::act::Unk_71024dc858* EnemyNormal::sub_71003A0114(bool a1, s32 type, s32 a3, u16* flags) {
    if (*flags & 0x30) {
        if (type != 2)
            return nullptr;
        Unk_7102451600 filter;
        filter._28 = *flags & 0x20;
        return sub_71003A04E0(a1, &filter, a3, *flags & 0x40);
    }

    auto* actor = mActor;
    if (isCurrentChild("攻撃反応")) {
        Unk_7102451498 filter(actor);
        return sub_71003A04E0(a1, &filter, a3, *flags & 0x40);
    }

    Unk_71024514c0 filter(actor);
    if (type == 1 || *mSealNoPlayerAwnRequestCount_a >= 1)
        filter._30 |= 2;
    filter._30 |= type == 2;
    auto* enemy = static_cast<act::Enemy*>(actor);
    if (type != 3 && !(*flags & 8) && *mIsMindDoubtTarget_s && !(enemy && enemy->_e84.isOnBit(1)))
        filter._30 |= 4;
    return sub_71003A04E0(a1, &filter, a3, *flags & 0x40);
}

// NON_MATCHING: the original selects the range member address per case (2 / 1) and shares the
// distance check; the final checks are laid out differently
ksys::act::Unk_71024dc858* EnemyNormal::sub_71003A04E0(bool a1, ksys::act::Unk_71024dccf8* filter,
                                                       s32 a3, bool a4) {
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (mgr->isNonAutoPlacement(pos, true))
            return nullptr;
    }

    auto* awareness = actor->getAwareness();
    if (!awareness)
        return nullptr;

    ksys::act::Unk_71024dc858* entry;
    if (a4) {
        do {
            entry = ksys::act::sub_7100D7EEE8(&awareness->_8, filter);
            if (!entry)
                return nullptr;
        } while (m45(entry->_88, entry->mLink, false));
    } else {
        if (awareness->_300 == 0)
            return nullptr;
        entry = m47(awareness, filter, a3);
        if (!entry)
            return nullptr;
    }

    auto* link = &entry->mLink;
    if (a3 == 2 || a3 == 1) {
        const f32 range = a3 == 2 ? *mShortRangeTerritoryArea_s : *mCloseRangeTerritoryArea_s;
        f32 dist;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            const auto& mtx = accessor.getActorMtx();
            const auto& own_mtx = mActor->getMtx();
            const f32 dx = mtx.m[0][3] - own_mtx.m[0][3];
            const f32 dz = mtx.m[2][3] - own_mtx.m[2][3];
            dist = std::sqrt(dx * dx + dz * dz);
        }
        if (!(dist < range))
            return nullptr;
    }

    sead::Vector3f center;
    m48(&center);
    if (entry->_a0 == 0)
        return nullptr;
    if (a1)
        return entry;
    if (m45(entry->_88, *link, false))
        return nullptr;
    return entry;
}

bool EnemyNormal::m70() {
    if (sub_7100736D98(mActor) || testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        return true;
    }
    return m45(sub_71005D9330(mActor), sub_71005D94AC(mActor), false);
}

bool EnemyNormal::m73() {
    return isCurrentChild("プレイヤー発見") || isCurrentChild("諦め");
}

bool EnemyNormal::m43() {
    return sub_71003A19AC();
}

bool EnemyNormal::sub_71003A19AC() {
    Unk2 target;
    Unk1 info;
    info._8 |= 0x800;
    if (!m66(&target, &info))
        return false;

    target._8.getTranslation(_60);
    _50 = *target._0;
    if (!ksys::act::isPlayerProfile(&_50)) {
        if (auto* unk = sub_71005D9D68(mActor))
            unk->sub_71002DC628(_50, 4);
    }

    auto* link = target._0;
    auto* actor = mActor;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_130._18.mLock);
        auto& data = _130._18.mData;
        if (link)
            data._0 = *link;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 1;
        data._24 = 1;
        data._28 = target._38;
        data._34 = 0;
    }
    sub_710039F938(true);
    return true;
}

void EnemyNormal::sub_710039F938(bool a1) {
    const f32 dist = a1 ? *mSpreadDist_s : *mSpeadDist2_s;
    if (auto* awareness = mActor->getAwareness()) {
        Unk_7102451448 filter;
        while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            if (entry->_a8 < dist) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&entry->mLink, &accessor);
                _130.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        }
    }

    if (!a1)
        return;

    sead::Vector3f home;
    mActor->getHomePos(&home);
    const sead::Vector3f diff = home - mActor->getMtx().getTranslation();
    if (std::sqrt(diff.x * diff.x + diff.z * diff.z) < dist)
        sub_71005E1884(mActor, &_130, mFortressTag_s.cstr());
}

bool EnemyNormal::m51() {
    return isCurrentChild("諦め") || isCurrentChild("音気づき") ||
           isCurrentChild("行動中仲間発見") || isCurrentChild("不調仲間発見") ||
           isCurrentChild("脅威感知");
}

bool EnemyNormal::m54() {
    return isCurrentChild("待機");
}

bool EnemyNormal::m55() {
    return isCurrentChild("諦め") || isCurrentChild("見失い");
}

void EnemyNormal::sub_710039FAA4(const sead::Vector3f& pos) {
    sead::Vector3f home;
    mActor->getHomePos(&home);
    const sead::Vector3f diff = home - mActor->getMtx().getTranslation();
    if (std::sqrt(diff.x * diff.x + diff.z * diff.z) < *mHomePosRadius_s) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_2e0._18.mLock);
            _2e0._18._0 = pos;
        }
        sub_71005E1884(mActor, &_2e0, mFortressTag_s.cstr());
    }
}

// NON_MATCHING: the filter address of the link branch is materialised after the link copy, not before
ksys::act::Unk_71024dc858* EnemyNormal::sub_710039FE20(ksys::act::BaseProcLink* link) {
    Unk_7102451560 member_filter;
    Unk_7102451740 link_filter;
    link_filter._28.reset();

    ksys::act::Unk_71024dccf8* filter;
    if (link) {
        link_filter._28 = *link;
        filter = &link_filter;
    } else {
        member_filter._28 = sub_71005D9E64(mActor);
        filter = &member_filter;
    }

    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return nullptr;

    if (auto* sensor = awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, filter);
        if (entry && !m45(entry->_88, entry->mLink, false))
            return entry;
    }

    filter->_8 = -1;
    if (auto* sensor = awareness->_260[1]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, filter);
        if (entry && entry->_a8 < 5.0f && !m45(entry->_88, entry->mLink, false))
            return entry;
    }
    return nullptr;
}

// NON_MATCHING: the original updates out->_44 with branches (ours selects)
bool EnemyNormal::m72(Unk2* out, Unk1* info) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    if (enemy->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
        sub_710039E1D0(out, 1, info)) {
        out->_44 |= 1;
        return true;
    }

    if (!sub_7100736D98(mActor) && !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        return false;
    }

    if (auto* entry = sub_71003A0114(m51(), 1, info->_4, &info->_8)) {
        out->sub_71003A02A4(entry);
        out->_44 |= 1;
        return true;
    }

    auto* link = &enemy->_e08._0;
    if (!ksys::act::isPlayerProfile(link) && !ksys::act::isNotLivingCreature(link) &&
        link->hasProc()) {
        return false;
    }

    auto* unk = sub_71005D9D68(mActor);
    auto& player = ksys::act::PlayerInfo::getSomeProcLink();
    if (!unk || !unk->sub_71002DC9E8(player, 8, false))
        return false;

    out->sub_710039E308(&player);
    out->_44 |= 1;
    return true;
}

bool EnemyNormal::sub_710039E1D0(Unk2* out, s32 type, Unk1* info) {
    if (!sub_71005D8F28(mActor))
        return false;
    if (m45(sub_71005D9330(mActor), sub_71005D94AC(mActor), false))
        return false;
    auto* target = sub_71005D9050(mActor);
    if (!sub_71003A33C0(type, target, &info->_8))
        return false;
    out->sub_710039E308(target);
    if (info->_8 & 4)
        out->_44 |= 1;
    else
        out->_44 &= ~1;
    return true;
}

// NON_MATCHING: the original updates out->_44 with branches (ours selects)
// NON_MATCHING: the original keeps a separate `return true` block per case; ours shares one
bool EnemyNormal::sub_71003A2BE0(Unk2* out, Unk1* info) {
    switch (info->_0) {
    case 0:
        if (m67(out, info))
            return true;
        break;
    case 1:
        if (sub_71003A361C(out, 2, info))
            return true;
        break;
    case 2:
        if (sub_71003A2E20(out, info))
            return true;
        break;
    case 3:
        if (m68(out, info))
            return true;
        break;
    case 4:
        if (sub_71003A361C(out, 3, info))
            return true;
        break;
    case 5:
        if (auto* awareness = mActor->getAwareness()) {
            Unk_71024514c0 filter(mActor);
            auto* sensor = awareness->_260[3];
            if (sensor) {
                auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
                if (entry && !m45(entry->_88, entry->mLink, false)) {
                    out->sub_71003A02A4(entry);
                    return true;
                }
            }
        }
        break;
    case 6:
        if (auto* entry = sub_710039FE20(nullptr)) {
            out->sub_71003A02A4(entry);
            return true;
        }
        break;
    case 7:
        if (sub_71003A2F18(out))
            return true;
        break;
    case 8:
        if (sub_71003A31C0(out))
            return true;
        break;
    default:
        break;
    }
    return false;
}

bool EnemyNormal::sub_71003A2E20(Unk2* out, Unk1* info) {
    if (m66(out, info))
        return true;

    auto& data = _188._38.mData;
    if (_368 > 0.0f || !_188._30 || data._20 != 1)
        return false;
    auto* unk = sub_71005D9D68(mActor);
    auto* link = &data._0;
    if (unk && unk->sub_71002DC9E8(*link, 4, false))
        return false;
    out->_0 = link;
    out->_38 = data._28;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    out->_8 = accessor.getActorMtx();
    return true;
}

// NON_MATCHING: register allocation (the filter address is kept in a callee-saved register for its dtor)
bool EnemyNormal::sub_71003A2F18(Unk2* out) {
    if (mActor->getParam()->getRes().mGParamList->getEnemy()->mIsMindFriend.ref()) {
        if (auto* unk = sub_71005D9D68(mActor)) {
            auto* link = unk->sub_71002DCEDC(0x100, mActor->getMtx().getTranslation());
            if (link->hasProcInCalcState()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(link, &accessor);
                if (accessor.sub_7100D10FB8()) {
                    sead::Vector3f target_pos;
                    accessor.getActorMtx().getTranslation(target_pos);
                    if (!m45(target_pos, *link, false)) {
                        out->sub_710039E308(link);
                        return true;
                    }
                }
            }
        }

        if (auto* awareness = mActor->getAwareness()) {
            Unk_7102451358 filter;
            if (auto* sensor = awareness->_260[0]) {
                auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
                if (entry && !m45(entry->_88, entry->mLink, false)) {
                    out->sub_71003A02A4(entry);
                    return true;
                }
            }
        }
    }

    if (_368 > 0.0f || !_290._30)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_290._38.mLink, &accessor);
    out->_0 = &_290._38.mLink;
    accessor.getActorMtx().getTranslation(out->_38);
    out->_8 = accessor.getActorMtx();
    return true;
}

bool EnemyNormal::sub_71003A33C0(s32 type, ksys::act::BaseProcLink* target, u16* flags) {
    if (!target)
        return false;

    if (type == 1) {
        if (!ksys::act::isPlayerProfile(target))
            return false;
        if (*flags & 8)
            return true;
        return !enemyTeamStuff(mActor, target);
    }

    if (type == 2) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(target, &accessor);
        if ((*flags & 0x10) && !accessor.sub_7100022ED8())
            return false;
        if ((*flags & 0x20) && (!accessor.isNPCProfile() || accessor.sub_7100022FD0()))
            return false;
        return !ksys::act::isPlayerProfile(target);
    }

    if (type == 3)
        return enemyTeamStuff(mActor, target);

    return false;
}

bool EnemyNormal::sub_71003A34D0(Unk2* out, s32 type, Unk1* info) {
    auto& data = _188._38.mData;
    if (data._20 != 0 || data._24 != 2 || _368 > 0.0f)
        return false;

    auto* link = &data._0;
    switch (type) {
    case 1:
        if (!ksys::act::isPlayerProfile(link))
            return false;
        if (!(data._34 & 1) && enemyTeamStuff(mActor, link))
            return false;
        break;
    case 2:
        if (ksys::act::isPlayerProfile(link))
            return false;
        break;
    case 3:
        if (data._34 & 1)
            return false;
        if (!enemyTeamStuff(mActor, link))
            return false;
        break;
    default:
        return false;
    }

    out->_0 = link;
    out->_38 = data._28;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        out->_8 = accessor.getActorMtx();
    }
    if (info->_8 & 5)
        out->_44 |= 1;
    else
        out->_44 &= ~1;
    return true;
}

bool EnemyNormal::sub_71003A361C(Unk2* out, s32 type, Unk1* info) {
    if (sub_710039E1D0(out, type, info))
        return true;
    if (info->_8 & 2)
        return false;
    auto* entry = sub_71003A0114(m51(), type, info->_4, &info->_8);
    if (!entry)
        return sub_71003A34D0(out, type, info);
    out->sub_71003A02A4(entry);
    if (info->_8 & 4)
        out->_44 |= 1;
    else
        out->_44 &= ~1;
    return true;
}

bool EnemyNormal::sub_710039DB34(bool a1) {
    return m45(sub_71005D9330(mActor), sub_71005D94AC(mActor), a1);
}

// NON_MATCHING: info._8 (0 or 8) is computed with branches in the original (cset + lsl here)
void EnemyNormal::m34() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    sub_710039E76C();

    Unk2 target;
    Unk1 info;
    info._8 = enemy->_e84.isOnBit(1) || !*mIsMindDoubtTarget_s ? 8 : 0;

    if (m72(&target, &info)) {
        m57(0, &target);
        m58(0, &target);
        sub_71003A02E0(&target);
        if (auto* unk = sub_71005D9D68(mActor))
            unk->sub_71002DCBDC(8);
        return;
    }

    {
        auto* actor = sead::DynamicCast<act::Enemy>(mActor);
        if (actor && actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000) &&
            sub_710039E1D0(&target, 2, &info) && *target._0 == actor->_e08._0) {
            target._44 |= 1;
            m57(1, &target);
            m58(1, &target);
            sub_71003A02E0(&target);
            return;
        }
    }

    if (*mIsMindDoubtTarget_s) {
        auto* actor = sead::DynamicCast<act::Enemy>(mActor);
        if (actor && sub_710039E1D0(&target, 3, &info)) {
            target._44 |= 1;
            m57(4, &target);
            m58(4, &target);
            sub_71003A0E38(&target);
            return;
        }
    }

    if (m71(&target, &info)) {
        m57(8, &target);
        m58(8, &target);
        m69(&target);
        return;
    }

    if (m70()) {
        Unk3 result;
        result._4 = 0;
        result._0 = 1;
        m62(&result);
        m38();
    } else {
        m35();
    }
}

void EnemyNormal::sub_710039E76C() {
    if (_3ac.isOff(4))
        return;

    auto* player_info = ksys::act::PlayerInfo::instance();
    if (!player_info) {
        _3b8 = 0;
        _3ac.reset(4);
        return;
    }

    auto* link = &player_info->getPlayerLink();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (!m46(pos, *link))
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    sead::Vector3f player_pos;
    accessor.getActorMtx().getTranslation(player_pos);
    if (m46(player_pos, *link)) {
        _3b8 = 0;
        _3ac.reset(4);
    }
}

void EnemyNormal::sub_71003A02E0(Unk2* target) {
    if (isCurrentChild("プレイヤー発見") && *target->_0 == sub_71005D94AC(mActor))
        return;

    _3ac.reset(8);
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(4);
    _3ac.reset(4);
    _3b8 = 0;
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;
    _50.reset();
    _364 = 0;
    m41();
    _36c = 10.0f;

    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    params.addVec3(target->_38, "TargetPos", -1);
    params.addBool(target->_44 & 1, "ForceNotice", -1);
    changeChild("プレイヤー発見", &params);
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        sub_710039FAA4(target->_38);
}

void EnemyNormal::sub_71003A0E38(Unk2* target) {
    _3ac.reset(8);
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;
    _50.reset();
    _364 = 0;
    m41();
    _36c = 10.0f;

    ksys::act::ai::InlineParamPack params;
    params.addActor(*target->_0, "TargetActor", -1);
    params.addVec3(target->_38, "TargetPos", -1);
    params.addBool(target->_44 & 1, "ForceNotice", -1);
    changeChild("不審者発見", &params);
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        sub_710039FAA4(target->_38);
}

void EnemyNormal::m37() {
    _3ac.reset(0xc);
    _3b8 = 0;
    m41();
    _50.reset();
    _364 = 0;

    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m48(&pos);
    params.addVec3(pos, "CentralPos", -1);
    changeChild("待機", &params);
}

void EnemyNormal::m38() {
    if (isCurrentChild("プレイヤー発見"))
        _3ac.set(8);
    _188.x();
    if (!_200._30 && _3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    _50.reset();
    m41();
    _364 = 0;

    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m48(&pos);
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(26)) {
        if (auto* nav = mActor->m45()) {
            sead::Vector3f nav_pos;
            if (nav->sub_7100F76078(&nav_pos, pos, 15.0f).sub_7100F7EB40())
                pos = nav_pos;
        }
    }
    params.addVec3(pos, "TargetPos", -1);
    changeChild("諦め", &params);
}

void EnemyNormal::m40() {
    _3ac.reset(8);
    const s32 time = _124 == _128 ? _124 : sead::GlobalRandom::instance()->getS32Range(_124, _128);
    _120 = time;
    _12c = false;
    _188.x();
    if (!_200._30 && _3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    _50.reset();
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("怒り", &params);
}

void EnemyNormal::m39() {
    if (isCurrentChild("プレイヤー発見"))
        _3ac.set(8);
    _188.x();
    if (!_200._30 && _3ac.isOff(2)) {
        _3ac.set(2);
        if (auto* lod = mActor->getLodState())
            lod->mFlags14.set(0x2000000);
    }
    m41();
    _50.reset();
    _364 = 50.0f;
    changeChild("見失い");
}

ksys::act::Unk_71024dc858* EnemyNormal::m47(ksys::act::AwarenessInstance* awareness,
                                            ksys::act::Unk_71024dccf8* filter, s32 a3) {
    while (awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, filter);
        if (!entry)
            break;
        if (!m45(entry->_88, entry->mLink, false))
            return entry;
    }
    return nullptr;
}

// NON_MATCHING: switch lowering order in the 諦め case, the type-1 result stores (merged into one
// 8-byte constant store here) and some scheduling
void EnemyNormal::m49(Unk1* out, s32 idx) {
    if (*mSealNoPlayerAwnRequestCount_a > 0)
        out->_8 |= 0x1000;

    const s32 type = m52(idx);
    if (type == 4) {
        if (!*mIsMindDoubtTarget_s) {
            out->_0 = -1;
            return;
        }
    } else if ((type == 6 || type == 7) && _368 > 0.0f) {
        out->_0 = -1;
        return;
    }

    if (isCurrentChild("プレイヤー発見")) {
        auto& target = sub_71005D94AC(mActor);
        if (ksys::act::isPlayerProfile(&target)) {
            out->_0 = -1;
            return;
        }
        switch (type) {
        case 1: {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&target, &accessor);
            if (accessor.hasProc() && accessor.sub_7100022FD0()) {
                out->_8 |= 0x4f0;
                out->_0 = type;
                out->_4 = 1;
                return;
            }
            break;
        }
        case 0:
        case 2:
            out->_8 |= 0x684;
            out->_0 = type;
            out->_4 = 2;
            return;
        default:
            break;
        }
        out->_0 = -1;
        return;
    }

    if (isCurrentChild("不審者発見")) {
        switch (type) {
        case 4:
        case 5:
        case 6:
        case 7:
            out->_0 = -1;
            return;
        default:
            out->_0 = type;
            out->_4 = 2;
            out->_8 |= 0x384;
            return;
        }
    }

    if (isCurrentChild("怒り")) {
        switch (type) {
        case 0:
        case 1:
        case 4:
            out->_0 = type;
            out->_8 |= 3;
            return;
        default:
            out->_0 = -1;
            return;
        }
    }

    if (isCurrentChild("見失い")) {
        out->_0 = type;
        out->_8 |= 0x1003;
        return;
    }

    if (isCurrentChild("諦め")) {
        switch (type) {
        case 0:
        case 1:
        case 4:
            break;
        case 2:
            out->_0 = -1;
            return;
        default:
            out->_0 = type;
            out->_8 |= 0x1000;
            return;
        }
    } else if (isCurrentChild("音気づき")) {
        if (type == 2) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("行動中仲間発見")) {
        switch (type) {
        case 2:
        case 6:
        case 7:
            out->_0 = -1;
            return;
        default:
            break;
        }
    } else if (isCurrentChild("不調仲間発見")) {
        if (type == 7 || type == 2) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("攻撃反応")) {
        switch (type) {
        case 0:
        case 1:
        case 4:
            out->_0 = type;
            out->_8 |= 1;
            if (_370 > 0.0f)
                out->_8 |= 8;
            return;
        case 3:
        case 8:
            out->_0 = type;
            return;
        default:
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("脅威感知")) {
        if (!(type == 0 || type == 1)) {
            out->_0 = -1;
            return;
        }
    } else if (isCurrentChild("気配気づき")) {
        if (type == 5) {
            out->_0 = -1;
            return;
        }
    }

    out->_0 = type;
    out->_8 |= 1;
}

void EnemyNormal::m50(Unk1* out, s32 idx) {
    const s32 type = m52(idx);
    if (type == 4) {
        if (!*mIsMindDoubtTarget_s || isCurrentChild("不審者発見")) {
            out->_0 = -1;
            return;
        }
    } else if ((type == 6 || type == 7) && _368 > 0.0f) {
        out->_0 = -1;
        return;
    }

    if (isCurrentChild("プレイヤー発見") || isCurrentChild("怒り") || isCurrentChild("見失い") ||
        isCurrentChild("気配気づき") || isCurrentChild("攻撃反応") ||
        isCurrentChild("行動中仲間発見") || isCurrentChild("不調仲間発見") ||
        isCurrentChild("脅威感知")) {
        out->_0 = -1;
        return;
    }

    if (isCurrentChild("音気づき")) {
        switch (type) {
        case 0:
        case 1:
        case 4:
            break;
        default:
            out->_0 = -1;
            return;
        }
    }

    out->_0 = type;
    out->_8 |= 1;
}

void EnemyNormal::m59() {
    auto* child = getCurrentChild();
    if (isCurrentChild("音気づき")) {
        if (m43()) {
            child->setDynamicParam(_60, "TargetPos");
            child->setDynamicParamImpl(_50, "TargetActor", &ksys::act::ai::ParamPack::setActor);
            _358 = ksys::Timer(*mSoundLostTimer_s, *mSoundLostTimer_s);
        } else if (!(_358.value <= sead::Mathf::epsilon())) {
            _358.update();
        }
    } else if (isCurrentChild("行動中仲間発見")) {
        if (auto* entry = sub_710039FE20(&_390)) {
            _390 = entry->mLink;
            _3a0 = entry->_88;
            child->setDynamicParam(_3a0, "TargetPos");
            child->setDynamicParamImpl(_390, "TargetActor", &ksys::act::ai::ParamPack::setActor);
        }
    } else if (isCurrentChild("プレイヤー発見") || isCurrentChild("不審者発見")) {
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    } else if (isCurrentChild("攻撃反応")) {
        if (_370 > 0.0f)
            ksys::Timer::update(&_370, -1.0f);
    }
}

void EnemyNormal::m60(Unk3* out) {
    if (isCurrentChild("プレイヤー発見") || isCurrentChild("不審者発見")) {
        auto* target = sub_71005D9050(mActor);
        if (target && target->hasProc() && sub_71005D777C(target))
            out->_0 = 1;
        else
            out->_0 = getCurrentChild()->isFinished();
        out->_4 |= 2;
    } else if (isCurrentChild("音気づき")) {
        out->_0 = 0;
    } else if (isCurrentChild("行動中仲間発見")) {
        out->_0 = 0;
    } else if (isCurrentChild("諦め")) {
        out->_0 = -1;
    } else if (!m54()) {
        out->_0 = 1;
    }
}

void EnemyNormal::m61(Unk3* out) {
    if (isCurrentChild("プレイヤー発見") || isCurrentChild("不審者発見")) {
        if (m45(sub_71005D9330(mActor), sub_71005D94AC(mActor), true)) {
            auto* target = sub_71005D9050(mActor);
            if (target && ksys::act::isPlayerProfile(target))
                out->_4 |= 2;
            out->_0 = 2;
        }
    } else if (isCurrentChild("音気づき")) {
        if (*mSoundLostTimer_s >= 0 && _358.value <= sead::Mathf::epsilon())
            out->_0 = 0;
    }
}

void EnemyNormal::m62(Unk3* result) {
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(8);

    if (result->_4 & 1) {
        _3ac.set(4);
        const f32 value = *_3b0;
        const f32 sub_area = *mSubsTerritoryArea_s;
        _3b8 = value > sub_area + sub_area ? -sub_area : value * -0.5f;
    }

    if (result->_4 & 2) {
        _188.x();
        if (!_200._30 && _3ac.isOff(2)) {
            _3ac.set(2);
            if (auto* lod = mActor->getLodState())
                lod->mFlags14.set(0x2000000);
        }
    }
}

// NON_MATCHING: the seal flag is computed with branches in the original; `or` operand order; order
// of the m5 / Unk_71002dccbc null tests
bool EnemyNormal::m66(Unk2* out, Unk1* info) {
    auto* awareness = mActor->getAwareness();
    if (awareness && awareness->_260[1] && awareness->_260[1]->_8.size() != 0) {
        auto* sensor = awareness->_260[1];
        Unk_71024514e8 filter(mActor, &_50);
        u8 flags = *mPlayerSoundSealRefCount_a > 0 || _364 > 0.0f;
        if (info->_8 & 0x80)
            flags |= 8;
        if (info->_8 & 0x100)
            flags |= 0x20;
        if (info->_8 & 0x200)
            flags |= 4;
        if (info->_8 & 0x400)
            flags |= 0x10;
        filter._30 = flags;

        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (entry) {
            auto* target = sub_71005D9050(mActor);
            if (!target || !target->hasProc() || !(*target == entry->mLink)) {
                if (!m45(entry->_88, entry->mLink, false) && m44(entry->_88)) {
                    auto* unk = sub_71005D9D68(mActor);
                    if (entry->m5(1) || !unk || (info->_8 & 0x800) ||
                        !unk->sub_71002DC9E8(entry->mLink, 4, false)) {
                        out->sub_71003A02A4(entry);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool EnemyNormal::m67(Unk2* out, Unk1* info) {
    if (sub_71003A361C(out, 1, info))
        return true;

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e84.isOnBit(15)) {
        auto& player = ksys::act::PlayerInfo::getSomeProcLink();
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&player, &accessor);
        sead::Vector3f pos;
        accessor.getActorMtx().getTranslation(pos);
        if (!m45(pos, player, false)) {
            out->sub_710039E308(&ksys::act::PlayerInfo::getSomeProcLink());
            out->_44 |= 1;
            return true;
        }
    }

    if (info->_8 & 8) {
        auto* unk = sub_71005D9D68(mActor);
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        auto* link = unk->sub_71002DCEDC(8, pos);
        if (link->hasProcInCalcState() && !m45(pos, *link, false)) {
            out->sub_710039E308(link);
            out->_44 |= 1;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: register allocation (&filter kept in a callee-saved register)
bool EnemyNormal::m68(Unk2* out, Unk1* info) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    ksys::act::Unk_71024dc858* entry;
    if (info->_8 & 0x1000) {
        Unk_71023e8fa8 filter;
        auto* sensor = awareness->_260[2];
        entry = sensor ? ksys::act::sub_7100D7EEE8(&sensor->_8, &filter) : nullptr;
    } else {
        auto* sensor = awareness->_260[2];
        if (!sensor || sensor->_8.size() < 1)
            return false;
        entry = ksys::act::sub_7100D78E30(&sensor->_8, 0);
    }

    if (!entry || !(*mNoticeTerrorLevel_s <= entry->_a4))
        return false;
    out->sub_71003A02A4(entry);
    return true;
}

bool Unk_71023e8fa8::m2(ksys::act::Unk_71024dc978* entry) {
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return true;
    return !(target->_3c & 0x40);
}

void EnemyNormal::Unk2::sub_710039E308(ksys::act::BaseProcLink* link) {
    _0 = link;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    accessor.getActorMtx().getTranslation(_38);
    _8 = accessor.getActorMtx();
}

void EnemyNormal::Unk2::sub_71003A02A4(ksys::act::Unk_71024dc858* entry) {
    _0 = &entry->mLink;
    _38 = entry->_88;
    _8 = entry->_58;
}

}  // namespace uking::ai
