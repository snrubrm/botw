#include "Game/Actor/AI/aiNPCConfrontEnemy.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include <random/seadGlobalRandom.h>
#include <limits>

// Source namespace is unknown (same declaration as in aiNPCRunaway.cpp).
bool sub_710001A9A4(const ksys::act::ActorLinkConstDataAccess& accessor, ksys::act::BaseProc* proc);

namespace uking::ai {

NPCConfrontEnemy::NPCConfrontEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg), _98(), _e8() {}

NPCConfrontEnemy::~NPCConfrontEnemy() = default;

bool NPCConfrontEnemy::init_(sead::Heap* heap) {
    _88 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCConfrontEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_88) {
        setFailed();
        return;
    }
    mActor->getLodState()->mFlags8.set(0x40000);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);
    sub_71005D7518(mActor, false);
    sub_710071418C(mActor, &_188);
    sub_71004C69B0(&_d8);
    if (ksys::act::hasTag(mActor, 0x207cbce1))
        mActor->emitBasicSigOn();
    if (!*mIsReturnFromDemo_d) {
        if (*mTerrorLayer_d & 0x100)
            sub_7100711FAC(mActor, "TerrorAnimal");
        _94 = false;
        _90 = false;
        _91 = false;
        _92 = false;
        _93 = false;
        _88->_1048 = 4;
        sub_7100713564(mActor, 4);
        _88->_1038 = 0;
        for (auto& link : _e8)
            link.reset();
        sub_71004C6CC8();
        if (sub_71005DB7E4(mActor, 0)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("抜刀", &pack);
            return;
        }
        if (sub_71004C6F0C(nullptr)) {
            sub_71004C717C();
            return;
        }
    }
    sub_71004C6A5C(true);
}

void NPCConfrontEnemy::sub_71004C6A5C(bool reset_timers) {
    if (reset_timers) {
        _98[3] = ksys::Timer(600.0f, 600.0f);
        const f32 duration = sead::GlobalRandom::instance()->getF32Range(10.0f, 15.0f) * 30.0f;
        _98[4] = ksys::Timer(duration, duration);
    }
    sead::Vector3f target = *mTargetPos_d;
    ksys::act::ActorLinkConstDataAccess nearest;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    f32 min_distance = std::numeric_limits<f32>::max();
    bool found = false;
    for (s32 idx = 0; idx < 10; ++idx) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_e8[idx], &accessor)) {
            const f32 distance = (position - accessor.getActorMtx().getTranslation()).length();
            if (distance < min_distance) {
                nearest.acquireActor(accessor);
                found = true;
                min_distance = distance;
            }
        }
    }
    if (found)
        nearest.getActorMtx().getTranslation(target);
    ksys::act::x_6(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(target, "TargetPos", -1);
    changeChild("アラート", &pack);
}

// NON_MATCHING: free-slot loop counter lifetime and saved link pointer allocation.
void NPCConfrontEnemy::sub_71004C6CC8() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || !awareness->_260[2])
        return;
    const s32 count = awareness->_260[2]->_8.size();
    s32 slot = 0;
    for (s32 idx = 0; idx < count; ++idx) {
        auto* sensor = awareness->_260[2];
        if (!sensor || idx >= sensor->_8.size())
            continue;
        auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, idx);
        if (!entry || static_cast<s32>(entry->_a4) != 3)
            continue;
        const auto& target = entry->_0.mLink;
        bool found = false;
        for (const auto& link : _e8) {
            if (link == target) {
                found = true;
                break;
            }
        }
        if (found)
            continue;
        ksys::act::BaseProcLink* free_link;
        do {
            if (slot >= 10)
                return;
            free_link = &_e8[slot++];
        } while (free_link->hasProc());
        *free_link = target;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&target, &accessor);
        auto* info = ksys::act::InfoData::instance();
        const s32 rank = ksys::act::getEnemyRank(info, accessor.getName().cstr());
        if (s32(_88->_1038) < rank)
            _88->_1038 = rank;
        if (slot >= 10)
            return;
    }
}

// NON_MATCHING: position load scheduling, register allocation and return block layout.
bool NPCConfrontEnemy::sub_71004C6F0C(ksys::act::BaseProcLink* link) {
    auto* awareness = mActor->getAwareness();
    if (!awareness || !awareness->_260[2])
        return false;
    const s32 count = awareness->_260[2]->_8.size();
    f32 min_distance = std::numeric_limits<f32>::max();
    bool found = false;
    for (s32 idx = 0; idx < count; ++idx) {
        auto* sensor = awareness->_260[2];
        const auto* entry = sensor && idx < sensor->_8.size() ?
                                ksys::act::sub_7100D78E30(&sensor->_8, idx) : nullptr;
        ksys::act::ActorLinkConstDataAccess accessor;
        if (entry && ksys::act::acquireActor(&entry->_0.mLink, &accessor)) {
            const auto& mtx = accessor.getActorMtx();
            const f32 distance = (mActor->getMtx().getTranslation() - mtx.getTranslation()).length();
            if (sub_710001A9A4(accessor, mActor) && distance < min_distance) {
                if (link)
                    *link = entry->_0.mLink;
                found = true;
                min_distance = distance;
            }
        }
    }
    return found;
}

void NPCConfrontEnemy::sub_71004C717C() {
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addFloat(static_cast<f32>(*mTerrorLevel_d), "TerrorLevel", -1);
    pack.addBool(_92, "IsBattleStart", -1);
    pack.addActor(_e8[0], "EnemyLink", -1);
    changeChild("戦闘", &pack);
}

void NPCConfrontEnemy::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCConfrontEnemy::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mRewardDistance_s, "RewardDistance");
    getStaticParam(&mTerrorDistAfterPlayerRescue_s, "TerrorDistAfterPlayerRescue");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

// 0x71004c83dc
bool NPCConfrontEnemy::sub_71004C83DC() {
    for (s32 i = 0; i < 10; ++i) {
        if (!_e8[i].hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_e8[i], &accessor);
        const sead::Vector3f other_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - other_pos;
        const f32 distance = diff.length();
        if (distance < *mReleaseDistance_s)
            return false;
    }
    return true;
}

// 0x71004c82d0
void NPCConfrontEnemy::sub_71004C82D0() {
    ksys::act::x_6(mActor);
    _98[0] = ksys::Timer(5.0f, 5.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("お礼", &pack);
}

// 0x71004c8ddc
void NPCConfrontEnemy::sub_71004C8DDC(const sead::Vector3f& pos) {
    _98[1] = ksys::Timer(600.0f, 600.0f);
    sub_71005D76E0(mActor, true);
    ksys::act::setEnabledTalkAndLockOn(mActor, false);
    _88->_1048 = 2;
    sub_7100713564(mActor, 2);
    _88->_1038 = 0;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("気絶前振り向き", &pack);
}

// 0x71004c84c8
void NPCConfrontEnemy::sub_71004C84C8() {
    ksys::act::x_6(mActor);
    if (!_90 && !_91) {
        if (_93) {
            _88->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _88->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    if (sub_71005DB7E4(mActor, 0) && !_90 && !_91) {
        sub_71004C82D0();
        return;
    }
    if (sub_71005DB7E4(mActor, 0))
        setFinished();
    else
        changeChild("納刀", nullptr);
}

// 0x71004c69b0
// NON_MATCHING: the original loads the object array pointer once before the loop but re-reads the size every
// iteration (`i != size`); ours re-loads both (a local copy of the array hoists both)
bool NPCConfrontEnemy::sub_71004C69B0(ksys::act::BaseProcLink* link) {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* link_data = obj->getLinkData()) {
            for (s32 i = 0; i != link_data->mObjects.size(); ++i) {
                ksys::act::ActorLinkConstDataAccess accessor;
                link_data->mObjects(i)->getActorWithAccessor(accessor);
                if (accessor.isNPCProfile()) {
                    accessor.linkAcquire(link);
                    return true;
                }
            }
        }
    }
    return false;
}

}  // namespace uking::ai
