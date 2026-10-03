#include "Game/AI/AI/aiKokkoAngryTargetSelect.h"
#include "Game/AI/AI/aiKokkoAngry.h"
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

// NON_MATCHING: see getKokkoTargetLink (entry-0 address computed as enemy + 0xd78)
void KokkoAngryTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::act::isEnemyProfile(getKokkoTargetLink(mActor)))
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
