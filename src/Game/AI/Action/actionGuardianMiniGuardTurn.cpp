#include "Game/AI/Action/actionGuardianMiniGuardTurn.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GuardianMiniGuardTurn::GuardianMiniGuardTurn(const InitArg& arg) : Turn(arg) {}

GuardianMiniGuardTurn::~GuardianMiniGuardTurn() = default;

void GuardianMiniGuardTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    Turn::enter_(params);
    sub_71001966C4();
}

void GuardianMiniGuardTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardTurn::sub_71001966C4() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    for (int i = 0; i < 3; ++i) {
        if (*mASSlot_s == i)
            list->sub_710115B140(sead::SafeString(mASName_s.cstr()), i, i, 0, 0);
        else
            playAS("Turn", true, i, 0, -1.0f);
    }
}

}  // namespace uking::action
