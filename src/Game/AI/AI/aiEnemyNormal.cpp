#include "Game/AI/AI/aiEnemyNormal.h"
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
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNormal::leave_() {
    ksys::act::ai::Ai::leave_();
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

bool EnemyNormal::m45(const sead::Vector3f& target_pos, const ksys::act::BaseProcLink& target,
                      bool skip_own_pos) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (!skip_own_pos && !m46(pos, target))
        return true;
    if (target.hasProcInCalcState() && !m46(target_pos, target))
        return true;
    return false;
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

void EnemyNormal::m43() {
    sub_71003A19AC();
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

// NON_MATCHING: the original updates out->_44 with branches (ours selects)
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
            if (nav->sub_7100F76078(nav_pos, pos, 15.0f).sub_7100F7EB40())
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
