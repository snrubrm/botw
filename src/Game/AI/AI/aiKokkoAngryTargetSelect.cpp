#include "Game/AI/AI/aiKokkoAngryTargetSelect.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

KokkoAngryTargetSelect::KokkoAngryTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KokkoAngryTargetSelect::~KokkoAngryTargetSelect() = default;

bool KokkoAngryTargetSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool KokkoAngryTargetSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool KokkoAngryTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original derives the entry link address from &_d70 (+8) kept in x21 (same as
// KokkoAngry::calc_ / m35)
void KokkoAngryTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::BaseProcLink* target = &ksys::act::sUnk_71026505e0;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& targets = enemy->_d70;
        if (!targets.sub_71002DCCBC(-1))
            target = &targets.mEntries[0].link;
    }
    if (ksys::act::isEnemyProfile(target))
        changeChild("敵", params);
    else
        changeChild("プレイヤー", params);
}

void KokkoAngryTargetSelect::calc_() {}

void KokkoAngryTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KokkoAngryTargetSelect::loadParams_() {}

}  // namespace uking::ai
