#include "Game/AI/Action/actionNPCHorseReception.h"
#include "KingSystem/GameData/gdtManager.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCHorseReception::NPCHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseReception::~NPCHorseReception() = default;

void NPCHorseReception::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void NPCHorseReception::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (_1c) {
        auto* gdm = ksys::gdt::Manager::instance();
        bool selected = false;
        const bool success = gdm->getParamBypassPerm().get().getBool(&selected, "Horse_IsSelected");
        if (selected && success)
            setFinished();
        if (!ui::sub_7100A98FA8())
            setFinished();
    } else {
        ui::sub_7100A98C80();
        _1c = true;
    }
}

}  // namespace uking::action
