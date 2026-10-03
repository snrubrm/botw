#include "Game/AI/AI/aiTargetOnMovableNavmeshSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100D123A0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetOnMovableNavmeshSelect::TargetOnMovableNavmeshSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TargetOnMovableNavmeshSelect::~TargetOnMovableNavmeshSelect() = default;

bool TargetOnMovableNavmeshSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetOnMovableNavmeshSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::acc::Actor accessor;
    ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor);
    if (accessor.navmeshStuff(*mCheckDist_s, *mOnStopCheckDist_s, mActor))
        changeChild("ナビメッシュ内", params);
    else
        changeChild("ナビメッシュ外", params);
}

void TargetOnMovableNavmeshSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("ナビメッシュ外")) {
        ksys::act::acc::Actor accessor;
        ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor);
        if (accessor.navmeshStuff(*mCheckDist_s, *mOnStopCheckDist_s, mActor))
            changeChild("ナビメッシュ内");
    } else {
        ksys::act::acc::Actor accessor;
        ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor);
        if (!accessor.navmeshStuff(*mCheckDist_s, *mOnStopCheckDist_s, mActor))
            changeChild("ナビメッシュ外");
    }
}

void TargetOnMovableNavmeshSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetOnMovableNavmeshSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mOnStopCheckDist_s, "OnStopCheckDist");
}

}  // namespace uking::ai
