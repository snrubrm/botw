#include "Game/AI/AI/aiEnemyRecognizeTarget.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyRecognizeTarget::EnemyRecognizeTarget(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyRecognizeTarget::~EnemyRecognizeTarget() = default;

// NON_MATCHING: the original holds this in x19 and the actor in x20; ours swaps them.
bool EnemyRecognizeTarget::m34() {
    if (*mSummonNum_s > 0) {
        auto* actor = mActor;
        if (actor->checkFlag(ksys::act::Actor::ActorFlag::_29)) {
            {
                float height = 0.0f;
                const sead::Vector3f position = mActor->getMtx().getTranslation();
                if (sub_710072C1B8(&height, &position) != 1 && height < *mSummonGrassHeight_s)
                    return false;
            }
            if (auto* awareness = actor->getAwareness()) {
                Unk_7102451448 filter;
                return ksys::act::sub_7100D7EEE8(&awareness->_8, &filter) == nullptr;
            }
        }
    }
    return false;
}

void EnemyRecognizeTarget::loadParams_() {
    EnemyRecognizeTargetBase::loadParams_();
    getStaticParam(&mSummonNum_s, "SummonNum");
    getStaticParam(&mSummonGrassHeight_s, "SummonGrassHeight");
    getStaticParam(&mSummonCheckDist_s, "SummonCheckDist");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
}

}  // namespace uking::ai
