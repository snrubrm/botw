#include "Game/AI/Action/actionCheckHorseCustomizeEdit.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

CheckHorseCustomizeEdit::CheckHorseCustomizeEdit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CheckHorseCustomizeEdit::~CheckHorseCustomizeEdit() = default;

bool CheckHorseCustomizeEdit::oneShot_() {
    ui::sub_7100A990EC();
    return ksys::act::ai::Action::oneShot_();
}

}  // namespace uking::action
