#include "Game/Actor/AI/aiKorokGoalTimerRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

// NON_MATCHING: the initial word and byte flag stores are scheduled in a different order.
KorokGoalTimerRootAI::KorokGoalTimerRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokGoalTimerRootAI::~KorokGoalTimerRootAI() = default;

bool KorokGoalTimerRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: store scheduling of the reset fields and the distance registers.
void KorokGoalTimerRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _230 = mActor->getMtx().getTranslation();

    // The starting block: the linked actor if it is loaded, else its placement object.
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, "FldObj_KorokStartingBlock_A_01");
    auto* block = ksys::act::findLinkReferenceObj(mActor, "FldObj_KorokStartingBlock_A_01", "", nullptr);
    if (accessor.hasProc())
        accessor.getActorMtx().getTranslation(_240);
    else if (block)
        _240 = block->getTranslate();

    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    const sead::Vector3f start(pos.x, pos.y + 1.9f, pos.z);
    const f32 distance = (start - _240).length();
    const f32 speed = (distance + -16.0f) * 0.11013216f + 10.0f;
    _264 = distance;
    _24c = start;
    _23c = 0;
    _224 = false;
    _220 = 0;
    _225 = true;
    _226 = false;
    _22c = 0;
    _26c = false;
    _228 = (*mGoalCountLimit_m - speed) + -15.0f;
    _268 = distance / speed;

    if (auto* korok = ksys::act::findLinkReferenceObj(mActor, "Npc_HiddenKorokGround", "", nullptr)) {
        _258 = korok->getTranslate();
    } else if (auto* korok_fly =
                   ksys::act::findLinkReferenceObj(mActor, "Npc_HiddenKorokFly", "", nullptr)) {
        _258 = korok_fly->getTranslate();
        _258.y += -1.5f;
    }
}

void KorokGoalTimerRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokGoalTimerRootAI::loadParams_() {
    getMapUnitParam(&mGoalCountLimit_m, "GoalCountLimit");
}

}  // namespace uking::ai
