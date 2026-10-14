#include "Game/Actor/AI/aiSeqTwoLineReachableTarget.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SeqTwoLineReachableTarget::SeqTwoLineReachableTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SeqTwoLineReachableTarget::~SeqTwoLineReachableTarget() = default;

bool SeqTwoLineReachableTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqTwoLineReachableTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    m34(params);
}

// NON_MATCHING: 4 bytes bigger; the original has the child's vtable load hoisted into both condition blocks (SimplifyCFG
// hoisting of the load that starts the shared body and the next condition); the plain `||` form here keeps them in the
// blocks (the duplicated-body form hoists the whole isFailed() call instead)
void SeqTwoLineReachableTarget::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
        } else if (isCurrentChild("先行動")) {
            const int type = *mReachableCheckType1_s;
            if ((type == 0 || type == 2) && !sub_710072E154(mActor, *m36(), nullptr, -1))
                setFailed();
            else
                m35();
        } else {
            const int type = *mReachableCheckType2_s;
            if ((type == 0 || type == 2) && !sub_710072E154(mActor, *m36(), nullptr, -1))
                setFailed();
            else
                setFinished();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("先行動")) {
            if (*mReachableCheckType1_s != 0)
                return;
        } else {
            if (*mReachableCheckType2_s != 0)
                return;
        }
        if (!sub_710072E154(mActor, *m36(), nullptr, -1))
            setFailed();
    }
}

void SeqTwoLineReachableTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqTwoLineReachableTarget::loadParams_() {
    getStaticParam(&mReachableCheckType1_s, "ReachableCheckType1");
    getStaticParam(&mReachableCheckType2_s, "ReachableCheckType2");
}

void SeqTwoLineReachableTarget::m34(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動", params);
}

void SeqTwoLineReachableTarget::m35() {
    changeChild("後行動");
}

}  // namespace uking::ai
