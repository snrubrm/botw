#include "Game/AI/Action/actionSimpleUniqueTalk.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/Event/evtEventSystem.h"

namespace uking::action {

SimpleUniqueTalk::SimpleUniqueTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleUniqueTalk::~SimpleUniqueTalk() = default;

bool SimpleUniqueTalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleUniqueTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::evt::EventSystem::instance()->setSpeaker(mActor);
    if (auto* ui = ui::UI::instance()) {
        if (ui->sub_71010A5A54())
            ui->x_0(false);
    }
}

void SimpleUniqueTalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleUniqueTalk::loadParams_() {
    getDynamicParam(&mMstxtName_d, "MstxtName");
}

void SimpleUniqueTalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
