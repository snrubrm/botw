#include "Game/AI/Action/actionItemConductorDemoBind.h"

namespace uking::action {

ItemConductorDemoBind::ItemConductorDemoBind(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ItemConductorDemoBind::~ItemConductorDemoBind() = default;

void ItemConductorDemoBind::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71001C20C0()) {
        sub_71001C256C();
        _80 = 0;
    } else if (sub_71001C21C0()) {
        sub_71001C2A08();
        _80 = 2;
    } else {
        sub_71001C27A8();
        _80 = 1;
    }
    setFinished();
}

void ItemConductorDemoBind::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemConductorDemoBind::loadParams_() {
    getDynamicParam(&mRotOffsetX_d, "RotOffsetX");
    getDynamicParam(&mRotOffsetY_d, "RotOffsetY");
    getDynamicParam(&mRotOffsetZ_d, "RotOffsetZ");
    getDynamicParam(&mTransOffsetX_d, "TransOffsetX");
    getDynamicParam(&mTransOffsetY_d, "TransOffsetY");
    getDynamicParam(&mTransOffsetZ_d, "TransOffsetZ");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mNodeName_d, "NodeName");
}

void ItemConductorDemoBind::calc_() {
    switch (_80) {
    case 0:
        if (sub_71001C20C0())
            break;
        // Fall through.
    case 1:
        if (sub_71001C21C0()) {
            sub_71001C2A08();
            _80 = 2;
        }
        break;
    case 2:
        if (sub_71001C20C0()) {
            sub_71001C256C();
            _80 = 0;
        } else if (!sub_71001C21C0()) {
            sub_71001C27A8();
            _80 = 1;
        }
        break;
    }
}

}  // namespace uking::action
