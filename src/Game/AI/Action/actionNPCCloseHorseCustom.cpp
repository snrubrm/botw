#include "Game/AI/Action/actionNPCCloseHorseCustom.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCCloseHorseCustom::NPCCloseHorseCustom(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCCloseHorseCustom::~NPCCloseHorseCustom() = default;

bool NPCCloseHorseCustom::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCCloseHorseCustom::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A99104();
}

void NPCCloseHorseCustom::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCCloseHorseCustom::loadParams_() {}

void NPCCloseHorseCustom::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (!ui::sub_7100A990BC())
        setFinished();
}

}  // namespace uking::action
