#include "Game/AI/Action/actionStartupTelescope.h"
#include "Game/gameRuneMgr.h"

namespace uking::action {

StartupTelescope::StartupTelescope(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartupTelescope::~StartupTelescope() = default;

bool StartupTelescope::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartupTelescope::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* rune_mgr = RuneMgr::instance())
        rune_mgr->sub_71006758B0();
}

void StartupTelescope::loadParams_() {}

void StartupTelescope::calc_() {
    setFinished();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
