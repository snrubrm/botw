#include "Game/Actor/AI/aiEnemyRecognizeTarget.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyRecognizeTarget::EnemyRecognizeTarget(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyRecognizeTarget::~EnemyRecognizeTarget() = default;

// NON_MATCHING: register allocation and stack slots for the grass query and awareness filter differ.
bool EnemyRecognizeTarget::m34() {
    if (*mSummonNum_s > 0) {
        auto* actor = mActor;
        if (actor->checkFlag(ksys::act::Actor::ActorFlag::_29)) {
            float height = 0.0f;
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            if (sub_710072C1B8(&height, &position) != 1 && height < *mSummonGrassHeight_s)
                return false;
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
