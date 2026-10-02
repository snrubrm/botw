#include "Game/AI/AI/aiCreationNestOnTree.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CreationNestOnTree::CreationNestOnTree(const InitArg& arg) : ItemOnTree(arg) {}

CreationNestOnTree::~CreationNestOnTree() = default;

// NON_MATCHING: the original materializes the bool argument (cset) before the other arguments
bool CreationNestOnTree::init_(sead::Heap* heap) {
    if (!ItemOnTree::init_(heap))
        return false;
    return _d0.sub_7100711298(heap, sead::SafeString::cEmptyString,
                              mActor->getMapObject() != nullptr);
}

// NON_MATCHING: the original loads mActor before the helper call (see lane1 log, borderline)
void CreationNestOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemOnTree::enter_(params);
    _d0.sub_7100711450();
    _d0._8 = *mTargetEscapedRadius_s;
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
}

void CreationNestOnTree::calc_() {
    ItemOnTree::calc_();
    _d0.sub_71007114DC();
}

void CreationNestOnTree::leave_() {
    _d0.sub_7100711BDC();
    ItemOnTree::leave_();
}

void CreationNestOnTree::loadParams_() {
    ItemOnTree::loadParams_();
    getStaticParam(&mActorNum_s, "ActorNum");
    getStaticParam(&mTargetEscapedRadius_s, "TargetEscapedRadius");
    getStaticParam(&mIsRemainNum_s, "IsRemainNum");
}

}  // namespace uking::ai
