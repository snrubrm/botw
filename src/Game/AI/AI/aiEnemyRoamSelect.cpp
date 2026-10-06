#include "Game/AI/AI/aiEnemyRoamSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

bool sub_710072C9FC(ksys::act::Actor* actor, f32 distance);

namespace uking::ai {

EnemyRoamSelect::EnemyRoamSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoamSelect::~EnemyRoamSelect() = default;

bool EnemyRoamSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyRoamSelect::sub_71003B3720() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (sub_71005D9F04(mActor)) {
        if (isRootAiParamINot5())
            return false;
        return !sub_710072C9FC(mActor, 2.0f);
    }
    if (enemy && enemy->_e84.isOnBit(23))
        return false;
    return (mActor->getMtx().getTranslation() - *mCentralPos_d).length() > *mNotReturnDist_s;
}

bool EnemyRoamSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyRoamSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnemyRoamSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRoamSelect::leave_() {
    _78 = false;
}

void EnemyRoamSelect::loadParams_() {
    getStaticParam(&mHideGrassHeight_s, "HideGrassHeight");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getStaticParam(&mNotReturnDist_s, "NotReturnDist");
}

}  // namespace uking::ai
