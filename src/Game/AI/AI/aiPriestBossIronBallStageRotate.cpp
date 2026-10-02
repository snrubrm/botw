#include "Game/AI/AI/aiPriestBossIronBallStageRotate.h"
#include <cmath>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossIronBallStageRotate::PriestBossIronBallStageRotate(const InitArg& arg)
    : PriestBossIronBall(arg) {}

PriestBossIronBallStageRotate::~PriestBossIronBallStageRotate() = default;

bool PriestBossIronBallStageRotate::init_(sead::Heap* heap) {
    return PriestBossIronBall::init_(heap);
}

void PriestBossIronBallStageRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossIronBall::enter_(params);
    *mIsActive_a = true;
}

void PriestBossIronBallStageRotate::calc_() {
    PriestBossIronBall::calc_();
}

void PriestBossIronBallStageRotate::leave_() {
    PriestBossIronBall::leave_();
    *mIsActive_a = false;
}

void PriestBossIronBallStageRotate::loadParams_() {
    PriestBossIronBall::loadParams_();
    getStaticParam(&mIronBallSummonRadius_s, "IronBallSummonRadius");
    getStaticParam(&mIronBallSummonArchAngle_s, "IronBallSummonArchAngle");
    getStaticParam(&mIronBallSummonOffsetY_s, "IronBallSummonOffsetY");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

// NON_MATCHING: the original keeps the null path of the Enemy cast (x1 = 0); see
// PriestBossGiantStageRotRoot::sub_710051D234
void PriestBossIronBallStageRotate::m34() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 0; i < 8; ++i) {
        if (unit->sub_71007194D4(i + 11, &accessor)) {
            auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
            const sead::Vector3f enemy_pos = enemy->getMtx().getTranslation();
            auto& sender = _a0[i];
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
                sender._18._0.acquire(enemy, false);
                sender._18._10 = enemy->_c48._8;
                sender._18._44 = 0;
                sender._18._20 = enemy_pos;
                sender._18._2c = sead::Vector3f::zero;
                sender._18._48 = 3;
                sender._18._38 = enemy_pos;
                sender._18._4c = 0;
            }
            sender.sub_710070DD78(accessor, true);
        }
        ++_650;
    }
}

// NON_MATCHING: the original reads the parameters before storing the translation (see log)
void PriestBossIronBallStageRotate::m35(sead::Vector3f* out, s32 idx) {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    const auto& mtx = mActor->getMtx();
    *out = mtx.getTranslation();
    const sead::Vector3f side = mtx.getBase(0);
    const f32 angle = idx * (*mIronBallSummonArchAngle_s * (1.0f / 7.0f));
    const f32 dist = std::cos(angle) * *mIronBallSummonRadius_s;
    const f32 offset_y = *mIronBallSummonOffsetY_s;
    const f32 height = std::sin(angle) * *mIronBallSummonRadius_s;
    out->x += side.x * dist;
    out->y += offset_y + height;
    out->z += side.z * dist;
}

}  // namespace uking::ai
