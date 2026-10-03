#include "Game/AI/AI/aiAssassinBossFirstRangeKeepMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapObject.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

AssassinBossFirstRangeKeepMove::AssassinBossFirstRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
AssassinBossFirstRangeKeepMove::~AssassinBossFirstRangeKeepMove() {
    ;
}

bool AssassinBossFirstRangeKeepMove::init_(sead::Heap* heap) {
    if (!EnemyRangeKeepMove::init_(heap))
        return false;
    sub_7100317AB8();
    return true;
}

void AssassinBossFirstRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f target_pos = sub_71005D9330(mActor);
    const sead::Vector3f diff = target_pos - _128;
    if (sqrtf(diff.x * diff.x + diff.z * diff.z) > *mNoMoveAnchorDist_s) {
        EnemyRangeKeepMove::enter_(params);
        return;
    }
    if (sub_71003AD298() && !sub_71003AD058())
        changeToBattleBackAway();
    else
        changeToBattleWait();
}

void AssassinBossFirstRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void AssassinBossFirstRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mNoMoveAnchorDist_s, "NoMoveAnchorDist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

void AssassinBossFirstRangeKeepMove::calc_() {
    const sead::Vector3f target_pos = sub_71005D9330(mActor);
    const sead::Vector3f diff = target_pos - _128;
    if (!(sqrtf(diff.x * diff.x + diff.z * diff.z) > *mNoMoveAnchorDist_s)) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            changeToBattleWait();
            return;
        }
        if (isCurrentChild("戦闘待機")) {
            getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
            return;
        }
    }
    EnemyRangeKeepMove::calc_();
}

// NON_MATCHING: the original loop compares the index with a signed `<` and copies the position as
// 8 + 4 bytes (see AssassinBossEscapeFromTarget::sub_7100315244; the index-loop form gets inlined
// into init_)
void AssassinBossFirstRangeKeepMove::sub_7100317AB8() {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* links = obj->getLinkData()) {
            auto& objects = links->mObjects;
            for (auto it = objects.begin(), end = objects.end(); it != end; ++it) {
                if (sead::SafeString((*it)->getUnitConfigName()) == mAnchorName_s) {
                    _128 = (*it)->getTranslate();
                    return;
                }
            }
        }
    }
    mActor->getHomePos(&_128);
}

}  // namespace uking::ai
