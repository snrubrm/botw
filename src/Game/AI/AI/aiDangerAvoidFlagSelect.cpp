#include "Game/AI/AI/aiDangerAvoidFlagSelect.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

DangerAvoidFlagSelect::DangerAvoidFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DangerAvoidFlagSelect::~DangerAvoidFlagSelect() = default;

void DangerAvoidFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy) {
        const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
        if (level && level->mIsAvoidDanger.ref()) {
            changeChild("避ける", params);
            return;
        }
    }
    changeChild("通常", params);
}

bool DangerAvoidFlagSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void DangerAvoidFlagSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void DangerAvoidFlagSelect::loadParams_() {}

}  // namespace uking::ai
