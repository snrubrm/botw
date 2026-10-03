#include "Game/AI/AI/aiNPCSuspend.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

NPCSuspend::NPCSuspend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NPCSuspend::~NPCSuspend() {
    ;
}

bool NPCSuspend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSuspend::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = *mRetryCount_s;
    _6c = ksys::Timer(*mWaitTime_s, *mWaitTime_s);
    changeChild("停止");
}

// NON_MATCHING: the original compares the old retry count (`cmp w8, #2`) after storing the decrement while ours
// compares the decremented value, and its two Timer stores (`stp s0, s0` + rate) are paired; everything
// else matches
void NPCSuspend::calc_() {
    if (isFinished())
        return;

    if (isCurrentChild("停止")) {
        _6c.update();
        if (!(_6c.value <= sead::Mathf::epsilon()))
            return;

        if (auto* nav = mActor->m45()) {
            sead::Vector3f target;
            bool found;
            {
                ksys::phys::Unk_7100f7e9f0 result = nav->sub_7100F76078(
                    &target, mActor->getMtx().getTranslation(), *mSearchRadius_s);
                found = result.sub_7100F7EB40();
            }

            if (found) {
                if ((mActor->getMtx().getTranslation() - target).length() < 0.5f) {
                    setFinished();
                    return;
                }

                _78.reset(f32(*mEndMoveTime_s));
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target, "TargetPos", -1);
                pack.addString(mASName_d, "ASName", -1);
                changeChild("移動", &pack);
                return;
            }
        }

        _6c = ksys::Timer(f32(*mWaitTime_s), f32(*mWaitTime_s));
        changeChild("停止");
    } else if (isCurrentChild("移動")) {
        if (getCurrentChild()->isFinished()) {
            setFinished();
            return;
        }

        _78.update();
        if (!(_78.value <= sead::Mathf::epsilon()))
            return;

        if (_68-- < 2) {
            setFailed();
            return;
        }

        _6c = ksys::Timer(f32(*mWaitTime_s), f32(*mWaitTime_s));
        changeChild("停止");
    }
}

void NPCSuspend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSuspend::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mEndMoveTime_s, "EndMoveTime");
    getStaticParam(&mRetryCount_s, "RetryCount");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::ai
