#include "Game/AI/Action/actionGuardianMiniGuardNavMeshWalk.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GuardianMiniGuardNavMeshWalk::GuardianMiniGuardNavMeshWalk(const InitArg& arg) : NavMeshWalk(arg) {}

GuardianMiniGuardNavMeshWalk::~GuardianMiniGuardNavMeshWalk() = default;

void GuardianMiniGuardNavMeshWalk::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardNavMeshWalk::m34() {
    NavMeshWalk::m34();
    auto* list = mActor->getASList();
    if (!list)
        return;
    for (int i = 0; i < 3; ++i) {
        if (*mASSlot_s == i)
            list->sub_710115B140(sead::SafeString(mASName_s.cstr()), i, i, 0, 0);
        else
            playAS("Walk", true, i, 0, -1.0f);
    }
}

}  // namespace uking::action
