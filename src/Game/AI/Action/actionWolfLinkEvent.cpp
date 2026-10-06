#include "Game/AI/Action/actionWolfLinkEvent.h"
#include "Game/gameWolfLinkMgr.h"

namespace uking::action {

WolfLinkEvent::WolfLinkEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkEvent::~WolfLinkEvent() = default;

bool WolfLinkEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WolfLinkEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* manager = WolfLinkMgr::instance()) {
        switch (*mAction_d) {
        case 1:
            if (!manager->sub_7100683088(true))
                return;
            setFinished();
            return;
        case 0:
            setFinished();
            return;
        case 2:
            setFinished();
            return;
        case 3:
            setFinished();
            return;
        }
    }
    setFailed();
}

void WolfLinkEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkEvent::loadParams_() {
    getDynamicParam(&mAction_d, "Action");
}

void WolfLinkEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
