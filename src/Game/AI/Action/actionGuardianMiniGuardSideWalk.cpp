#include "Game/AI/Action/actionGuardianMiniGuardSideWalk.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GuardianMiniGuardSideWalk::GuardianMiniGuardSideWalk(const InitArg& arg) : TargetCircleWalk(arg) {}

GuardianMiniGuardSideWalk::~GuardianMiniGuardSideWalk() = default;

void GuardianMiniGuardSideWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircleWalk::enter_(params);
    sub_7100196094();
}

void GuardianMiniGuardSideWalk::loadParams_() {
    TargetCircleWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardSideWalk::sub_7100196094() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    for (int i = 0; i < 3; ++i) {
        if (*mASSlot_s == i)
            list->sub_710115B140(sead::SafeString(mASName_s.cstr()), i, i, 0, 0);
        else
            playAS("SideWalk", true, i, 0, -1.0f);
    }
}

}  // namespace uking::action
