#include "Game/Actor/AI/aiNPCRunaway.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

// Source namespace is unknown (same declaration as in actionForkDynActorNoTargetSelf.cpp).
bool sub_710001A9A4(const ksys::act::ActorLinkConstDataAccess& accessor, ksys::act::BaseProc* proc);

namespace uking::ai {

NPCRunaway::NPCRunaway(const InitArg& arg) : ksys::act::ai::Ai(arg), _90(), _e8() {}

NPCRunaway::~NPCRunaway() = default;

bool NPCRunaway::init_(sead::Heap* heap) {
    _80 = sead::DynamicCast<act::NPC>(mActor);
    _88 = mActor->getParam()->getRes().mGParamList->getNpc()->mTolerantTime.ref();
    return true;
}

void NPCRunaway::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005D7518(mActor, false);
    mActor->getLodState()->mFlags8.set(0x40000);
    sub_710071418C(mActor, &_188);
    sub_71004DD654(&_d8);
    if (ksys::act::hasTag(mActor, 0x207cbce1))
        mActor->emitBasicSigOn();
    if (*mIsReturnFromDemo_d) {
        sub_71004DD700();
        return;
    }
    if (*mTerrorLayer_d & 0x100)
        sub_7100711FAC(mActor, "TerrorAnimal");
    _8d = false;
    if (_80) {
        _80->_1048 = 4;
        sub_7100713564(mActor, 4);
        _80->_1038 = 0;
    }
    for (auto& link : _e8)
        link.reset();
    sub_71004DD80C();
    sub_71007130BC(mActor, false);
    changeChild("驚く", nullptr);
}

void NPCRunaway::leave_() {
    mActor->getLodState()->mFlags8.reset(0x40000);
    sub_71005D7518(mActor, true);
}

void NPCRunaway::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mCorneredDistance_s, "CorneredDistance");
    getStaticParam(&mStandRateTime_s, "StandRateTime");
    getStaticParam(&mStandingTime_s, "StandingTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
}

// 0x71004dd700
void NPCRunaway::sub_71004DD700() {
    _90[1] = ksys::Timer(300.0f, 300.0f);
    sub_71007130BC(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("待機", &pack);
}

// 0x71004dea74
void NPCRunaway::sub_71004DEA74() {
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);
    sub_71007130BC(mActor, false);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addVec3(*mTargetVel_d, "TargetVel", -1);
    changeChild("逃走", &pack);
}

// 0x71004dec8c
void NPCRunaway::sub_71004DEC8C() {
    if (_80) {
        if (_8c) {
            _80->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _80->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    _90[2] = ksys::Timer(5.0f, 5.0f);
    sub_71007130BC(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(false, "TerrorOccurring", -1);
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("お礼", &pack);
}

// 0x71004df0b0
void NPCRunaway::sub_71004DF0B0(const sead::Vector3f& pos) {
    if (_80) {
        _80->_1048 = 2;
        sub_7100713564(mActor, 2);
    }
    _90[5] = ksys::Timer(600.0f, 600.0f);
    sub_71005D7644(mActor, false);
    sub_71005D76E0(mActor, true);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("気絶前振り向き", &pack);
}

// 0x71004df1d0
void NPCRunaway::sub_71004DF1D0() {
    if (_80) {
        if (_8c) {
            _80->_1048 = 0;
            sub_7100713564(mActor, 0);
        } else {
            _80->_1048 = 1;
            sub_7100713564(mActor, 1);
        }
    }
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, "", 0);
    sub_71007130BC(mActor, true);
    sub_71005D7644(mActor, false);
    _90[4] = ksys::Timer(*mStandingTime_s * 30.0f, *mStandingTime_s * 30.0f);
    changeChild("立ち上がる", nullptr);
}

// 0x71004deba0
bool NPCRunaway::sub_71004DEBA0() {
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

// NON_MATCHING: free-slot loop counter lifetime and saved link pointer allocation.
void NPCRunaway::sub_71004DD80C() {
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
        if (_80) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&target, &accessor);
            auto* info = ksys::act::InfoData::instance();
            const s32 rank = ksys::act::getEnemyRank(info, accessor.getName().cstr());
            if (s32(_80->_1038) < rank)
                _80->_1038 = rank;
        }
        if (slot >= 10)
            return;
    }
}

// 0x71004dd654
// NON_MATCHING: the original loads the object array pointer once before the loop but re-reads the size every
// iteration (`i != size`); ours re-loads both (a local copy of the array hoists both)
bool NPCRunaway::sub_71004DD654(ksys::act::BaseProcLink* link) {
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

// 0x71004de978
// NON_MATCHING: the original keeps the loop counter as `i + 1` in a register (index = counter - 1); ours counts from 0 and allocates the callee-saved registers in a different order
bool NPCRunaway::sub_71004DE978(ksys::act::BaseProcLink* link) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    if (!awareness->_260[2])
        return false;
    const int count = awareness->_260[2]->_8.size();
    for (int i = 0; i < count; ++i) {
        ksys::act::Unk_7100d78e50* entry = nullptr;
        if (awareness->_260[2]) {
            auto& entries = awareness->_260[2]->_8;
            if (entries.size() > i)
                entry = ksys::act::sub_7100D78E30(&entries, i);
        }
        ksys::act::ActorLinkConstDataAccess accessor;
        if (entry && ksys::act::acquireActor(&entry->_0.mLink, &accessor) &&
            sub_710001A9A4(accessor, mActor)) {
            if (link)
                *link = entry->_0.mLink;
            return true;
        }
    }
    return false;
}

}  // namespace uking::ai
