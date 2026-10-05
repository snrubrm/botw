#include "Game/AI/AI/aiPriestBossActorNormalRoot.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

PriestBossActorNormalRoot::PriestBossActorNormalRoot(const InitArg& arg)
    : PriestBossActorRoot(arg) {}

PriestBossActorNormalRoot::~PriestBossActorNormalRoot() = default;

bool PriestBossActorNormalRoot::init_(sead::Heap* heap) {
    if (!PriestBossActorRoot::init_(heap))
        return false;
    _80.makeAllZero();
    return true;
}

void PriestBossActorNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

// NON_MATCHING: temporary string storage and the sync-mode branch layout differ.
void PriestBossActorNormalRoot::calc_() {
    PriestBossActorRoot::calc_();
    if (!sub_7100505BE4()) {
        if (!isCurrentChild("通常モード")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "FromSyncMode", -1);
            changeChild("通常モード", &pack);
        }
        return;
    }
    if (m36())
        return;
    if (isCurrentChild("攻撃変更の間")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            sub_710050DC18(true);
        return;
    }
    if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) &&
        !isCurrentChild("シンクロモード")) {
        changeChild("攻撃変更の間");
        return;
    }
    if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_0) &&
        !isCurrentChild("通常モード"))
        changeChild("攻撃変更の間");
}

void PriestBossActorNormalRoot::leave_() {
    PriestBossActorRoot::leave_();
}

void PriestBossActorNormalRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
}

// NON_MATCHING: the return value of the last isFailed() test is folded into `!x` (mvn / and) where
// the original branches to the shared `return false` / `return true` blocks
bool PriestBossActorNormalRoot::m36() {
    if (isCurrentChild("バナナモード")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            return false;
        return true;
    }

    if (sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_10))
        return false;

    if (isChangeable() || isFinished() || isFailed()) {
        if (!sub_7100505BE4()->isFlagOn(Unk_7102450fa8::Flag::_7))
            return false;
        changeChild("バナナモード");
        return true;
    }
    return false;
}

}  // namespace uking::ai
