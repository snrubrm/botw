#include "Game/AI/AI/aiPriestBossGiantStageRotRoot.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

PriestBossGiantStageRotRoot::PriestBossGiantStageRotRoot(const InitArg& arg)
    : PriestBossMode(arg), _a8() {}

PriestBossGiantStageRotRoot::~PriestBossGiantStageRotRoot() = default;

bool PriestBossGiantStageRotRoot::init_(sead::Heap* heap) {
    if (!PriestBossMode::init_(heap))
        return false;
    for (auto& sender : _a8)
        sender._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossGiantStageRotRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
    _468 = (sead::GlobalRandom::instance()->getU32() & 1) == 0;
    _46c = 0;
    _464 = *mBallsReleaseIntervalFrames_s > 0.0f ? 0 : 8;
    *mIsActive_a = true;
    *mFacePos_a = sUnk_71025c8cf8;
    *mKeepDistFromGround_a = 3.5f;
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        changeChild("地形を戻す");
    else
        changeChild("ロール前", params);

    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (unit) {
        unit->_34c = 0;
        unit->_3c8 = 0;
    }
}

void PriestBossGiantStageRotRoot::calc_() {
    PriestBossMode::calc_();
    sub_710071EB3C(mActor);

    switch (_46c) {
    case 1:
        _458.update();
        if (_458.value <= sead::Mathf::epsilon())
            _46c = 2;
        else
            sub_710051D234();
        break;
    case 2:
        if (sub_710051D438())
            _46c = 3;
        break;
    }

    auto* child = getCurrentChild();
    if (!child)
        return;

    if (m34()) {
        if (!isCurrentChild("地形を戻す")) {
            changeChild("地形を戻す");
            return;
        }
        if (child->isFinished() || child->isFailed())
            setFinished();
        return;
    }

    if (isCurrentChild("ロール前")) {
        if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            sub_710051D12C();
        }
        if (child->isFinished() || child->isFailed())
            changeChild("地形をロール");
    } else if (isCurrentChild("地形をロール")) {
        if (child->isFinished() || child->isFailed()) {
            *mKeepDistFromGround_a = 7.0f;
            changeChild("地形を戻す");
        }
    } else if (isCurrentChild("地形を戻す")) {
        if (child->isFinished() || child->isFailed()) {
            *mKeepDistFromGround_a = -1.0f;
            setFinished();
        }
    }
}

void PriestBossGiantStageRotRoot::leave_() {
    PriestBossMode::leave_();
    *mIsActive_a = false;
}

// NON_MATCHING: same expression tree; instruction scheduling and register allocation differ
void PriestBossGiantStageRotRoot::m35(sead::Vector3f* out, s32 idx) {
    if (!sub_7100505BE4())
        return;

    const f32 radius = sUnk_7102450fa0 * *mPercentRadiusHeight_s;
    const f32 height = sUnk_7102450fa0 - radius;
    const f32 diameter = (radius + height) * 2.0f;
    const f32 width = sead::Mathf::sin(*mCentralAngle_s * 0.5f) * diameter;
    const f32 rate = idx / 7.0f;
    const f32 arc = *mArcPercent_s;
    const f32 u = arc + rate * ((1.0f - arc) - arc) - 0.5f;
    const f32 h = u * u * -4.0f + 1.0f;
    const f32 x = width * 0.5f - (0.0f + rate * width);
    const f32 y = *mIronBallHeightOffset_s * h;
    const f32 z = *mZOffset_s + *mZOffsetIndex_s * h;

    const auto& mtx = mActor->getMtx();
    *out = mtx.getTranslation() + mtx.getBase(2) * z + mtx.getBase(0) * x + mtx.getBase(1) * y;
}

void PriestBossGiantStageRotRoot::sub_710051D12C() {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 0; i < 8; ++i) {
        if (!unit->sub_71007194D4(i + 11, &accessor))
            continue;
        sead::Vector3f pos;
        m35(&pos, i);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx = mActor->getMtx();
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
        }
    }
    const f32 length = *mHoldBallsCounterLength_s;
    _458.value = length;
    _458.previous_value = length;
    _46c = 1;
}

// NON_MATCHING: the original keeps the null path of the Enemy cast (x1 = 0) and compares the start
// index with 7 (b.gt); otherwise the same, apart from register allocation
void PriestBossGiantStageRotRoot::sub_710051D234() {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = _464; i < 8; ++i) {
        if (!unit->sub_71007194D4(i + 11, &accessor))
            continue;
        sead::Vector3f pos;
        m35(&pos, i);
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        const sead::Vector3f enemy_pos = enemy->getMtx().getTranslation();
        auto& sender = _a8[i];
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
            sender._18._0.acquire(enemy, false);
            sender._18._10 = enemy->_c48._8;
            sender._18._44 = 0;
            sender._18._20 = enemy_pos;
            sender._18._2c = sead::Vector3f::zero;
            sender._18._48 = 0;
            sender._18._38 = pos;
            sender._18._4c = 0;
        }
        sender.sub_710070DD78(accessor, true);
    }
}

bool PriestBossGiantStageRotRoot::sub_710051D438() {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 0; i < _464; ++i) {
        s32 idx = i;
        if (_468)
            idx = 7 - i;
        if (unit->sub_71007194D4(idx + 11, &accessor))
            _428.sub_710070DD78(accessor, true);
    }
    bool finished = true;
    if (++_464 < 9) {
        _458.value += *mBallsReleaseIntervalFrames_s;
        _46c = 1;
        finished = false;
    }
    return finished;
}

void PriestBossGiantStageRotRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mCentralAngle_s, "CentralAngle");
    getStaticParam(&mPercentRadiusHeight_s, "PercentRadiusHeight");
    getStaticParam(&mIronBallHeightOffset_s, "IronBallHeightOffset");
    getStaticParam(&mArcPercent_s, "ArcPercent");
    getStaticParam(&mZOffset_s, "ZOffset");
    getStaticParam(&mZOffsetIndex_s, "ZOffsetIndex");
    getStaticParam(&mHoldBallsCounterLength_s, "HoldBallsCounterLength");
    getStaticParam(&mBallsReleaseIntervalFrames_s, "BallsReleaseIntervalFrames");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mFacePos_a, "FacePos");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
