#include "Game/AI/AI/aiPriestBossBlowoffReadyReaction.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossBlowoffReadyReaction::PriestBossBlowoffReadyReaction(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossBlowoffReadyReaction::~PriestBossBlowoffReadyReaction() = default;

bool PriestBossBlowoffReadyReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossBlowoffReadyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100510E80();
}

void PriestBossBlowoffReadyReaction::sub_7100510E80() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    unit->_34c = 0;
    for (s32 i = 0; i < 8; ++i) {
        ksys::act::ActorConstDataAccess accessor;
        if (unit->sub_71007194D4(i + 11, &accessor)) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
                _40._18._0 = 1;
                _40._18._4 = sead::Vector3f::zero;
            }
            _40.sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
        }
    }
}

void PriestBossBlowoffReadyReaction::calc_() {
    setFinished();
}

void PriestBossBlowoffReadyReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossBlowoffReadyReaction::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
