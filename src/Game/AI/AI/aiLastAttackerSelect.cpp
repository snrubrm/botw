#include "Game/AI/AI/aiLastAttackerSelect.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

void LastAttackerSelect::sub_7100474A28() {
    sead::Vector3f position;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(position);
    else
        position = getPlayerPosition();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("発見", &pack);
}

void LastAttackerSelect::sub_7100474B94() {
    sead::Vector3f position;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(position);
    else
        position = getPlayerPosition();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    changeChild("未発見", &pack);
}


LastAttackerSelect::LastAttackerSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastAttackerSelect::~LastAttackerSelect() = default;

bool LastAttackerSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LastAttackerSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool LastAttackerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastAttackerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* target = sub_71005D9050(mActor);
    if (target && target->hasProc()) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy && enemy->_e08._0 == *target) {
            sub_7100474A28();
            return;
        }
    }
    sub_7100474B94();
}

void LastAttackerSelect::calc_() {}

void LastAttackerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastAttackerSelect::loadParams_() {}

bool LastAttackerSelect::m34() {
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

}  // namespace uking::ai
