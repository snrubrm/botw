#include "Game/Actor/AI/aiPriestBossMakeClone.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

PriestBossMakeClone::PriestBossMakeClone(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMakeClone::~PriestBossMakeClone() = default;

bool PriestBossMakeClone::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMakeClone::enter_(ksys::act::ai::InlineParamPack* params) {
    mCloneRecords.clear();
    _54 = sUnk_71025c8cf8;
    _60 = sead::Vector3f::zero;
    _6c = sead::Vector3f::zero;
    mRespawnStarted = false;
    mRespawnTimer = 0.0f;
    mState = 0;
    sub_7100524660(1);
}

void PriestBossMakeClone::calc_() {
    if (mRespawnStarted) {
        ksys::Timer::update(&mRespawnTimer, 1.0f);
        if (mRespawnTimer > *mRespawnFrame_s) {
            sub_7100525270(1);
            sub_7100525270(2);
            sub_7100525270(5);
            mRespawnStarted = false;
        }
    }
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;
    switch (mState) {
    case 1:
        sub_7100524660(2);
        break;
    case 2:
    case 3:
        sub_7100524660(4);
        break;
    case 4:
        sub_7100524660(5);
        break;
    case 5:
        if (!mRespawnStarted) {
            auto* unit = sead::DynamicCast<Unk_7102450fa8>(
                *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
            if (!unit->isFlagOn(Unk_7102450fa8::Flag::_4))
                setFinished();
        }
        break;
    default:
        break;
    }
}

// NON_MATCHING: actor loads around allocation and payload lock, plus register allocation.
void PriestBossMakeClone::sub_7100525270(s32 value) {
    if (!sead::DynamicCast<Unk_7102450fa8>(
            *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a)))
        return;
    ksys::act::ActorLinkConstDataAccess accessor;
    auto* unit = sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit->sub_71007194CC(&accessor) || mCloneRecords.isFull())
        return;
    auto* record = mCloneRecords.emplaceBack(mActor, 0x80000d5);
    if (record) {
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&record->_18.mLock);
            record->_18._0 = value;
            record->_18._18 = false;
            record->_18.mLink.acquire(mActor, false);
        }
        record->sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
    }
}

void PriestBossMakeClone::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMakeClone::loadParams_() {
    getStaticParam(&mRespawnFrame_s, "RespawnFrame");
    getStaticParam(&mBackStepDistance_s, "BackStepDistance");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
