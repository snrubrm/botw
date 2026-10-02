#include "Game/AI/AI/aiGuardFrequencySelect.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"

namespace uking::ai {

GuardFrequencySelect::GuardFrequencySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardFrequencySelect::~GuardFrequencySelect() = default;

void GuardFrequencySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710040CA40())
        changeChild("ガード", params);
    else
        changeChild("通常", params);
}

void GuardFrequencySelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else
        setFailed();
}

void GuardFrequencySelect::loadParams_() {}

bool GuardFrequencySelect::sub_710040CA40() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || enemy->_e84.isOnBit(0))
        return false;
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1))
        return true;

    const auto* level = enemy->getParam()->getRes().mGParamList->getEnemyLevel();
    const s32 guard_per = level ? level->mGuardPer.ref() : 0;
    return s32(sead::GlobalRandom::instance()->getU32(100)) < guard_per;
}

}  // namespace uking::ai
