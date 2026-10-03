#include "Game/AI/Action/actionNPCHorseReceptionRelease.h"
#include "KingSystem/GameData/gdtManager.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCHorseReceptionRelease::NPCHorseReceptionRelease(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCHorseReceptionRelease::~NPCHorseReceptionRelease() = default;

void NPCHorseReceptionRelease::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

// NON_MATCHING: scheduling (the original stores selected = false after loading the gdt::Manager instance and the
// SafeString vtable)
void NPCHorseReceptionRelease::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_1c) {
        bool selected = false;
        const bool success = ksys::gdt::Manager::instance()->getParamBypassPerm().get().getBool(&selected, "Horse_IsSelected");
        if (selected && success)
            setFinished();
        if (!ui::sub_7100A98FA8())
            setFinished();
    } else {
        ui::sub_7100A98D4C();
        _1c = true;
    }
}

}  // namespace uking::action
