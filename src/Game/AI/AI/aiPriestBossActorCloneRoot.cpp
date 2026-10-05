#include "Game/AI/AI/aiPriestBossActorCloneRoot.h"
#include "Game/AI/aiUnk_7102450fa8.h"

// Source namespace and helper ownership are unknown; declaration only.
void sub_710071EBA4(ksys::act::Actor* actor);

namespace uking::ai {

PriestBossActorCloneRoot::PriestBossActorCloneRoot(const InitArg& arg)
    : PriestBossActorNormalRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PriestBossActorCloneRoot::~PriestBossActorCloneRoot() {
    ;
}

bool PriestBossActorCloneRoot::init_(sead::Heap* heap) {
    return PriestBossActorNormalRoot::init_(heap);
}

void PriestBossActorCloneRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorNormalRoot::enter_(params);
}

void PriestBossActorCloneRoot::calc_() {
    PriestBossActorNormalRoot::calc_();
    if (sub_7100505BE4() && sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_1))
        sub_710071EBA4(mActor);
}

void PriestBossActorCloneRoot::leave_() {
    PriestBossActorNormalRoot::leave_();
}

void PriestBossActorCloneRoot::loadParams_() {
    PriestBossActorNormalRoot::loadParams_();
    getStaticParam(&mDisappearXLinkEventKey_s, "DisappearXLinkEventKey");
}

// NON_MATCHING: the return value of the last isFailed() test is folded into `!x` (mvn / and) where
// the original branches to the shared `return false` / `return true` blocks
bool PriestBossActorCloneRoot::m36() {
    if (isCurrentChild("バナナモード")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return false;
        return true;
    }

    if (isChangeable() || isFinished() || isFailed()) {
        if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_8))
            return false;
        changeChild("バナナモード");
        return true;
    }
    return false;
}

}  // namespace uking::ai
