#include "Game/AI/AI/aiGuardFlagSelect.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

GuardFlagSelect::GuardFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardFlagSelect::~GuardFlagSelect() = default;

void GuardFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy) {
        const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
        if (level && level->mIsGuardArrow.ref()) {
            changeChild("盾構え", params);
            return;
        }
    }
    changeChild("通常", params);
}

void GuardFlagSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (getCurrentChild()->isFinished())
            setFinished();
        else
            setFailed();
    }
}

void GuardFlagSelect::loadParams_() {}

}  // namespace uking::ai
