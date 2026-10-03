#include "Game/AI/Action/actionNPCHorseReceptionResurrect.h"
#include "KingSystem/GameData/gdtManager.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCHorseReceptionResurrect::NPCHorseReceptionResurrect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCHorseReceptionResurrect::~NPCHorseReceptionResurrect() = default;

bool NPCHorseReceptionResurrect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseReceptionResurrect::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void NPCHorseReceptionResurrect::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCHorseReceptionResurrect::loadParams_() {}

// NON_MATCHING: scheduling (the original stores selected = false after loading the gdt::Manager instance and the
// SafeString vtable)
void NPCHorseReceptionResurrect::calc_() {
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
        ui::sub_7100A98E18();
        _1c = true;
    }
}

}  // namespace uking::action
