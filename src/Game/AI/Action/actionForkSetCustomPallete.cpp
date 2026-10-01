#include "Game/AI/Action/actionForkSetCustomPallete.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

ForkSetCustomPallete::ForkSetCustomPallete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetCustomPallete::~ForkSetCustomPallete() = default;

bool ForkSetCustomPallete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetCustomPallete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetCustomPallete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetCustomPallete::loadParams_() {
    getStaticParam(&mPalleteType_s, "PalleteType");
}

void ForkSetCustomPallete::calc_() {
    auto* wm = ksys::world::Manager::instance();
    if (!wm)
        return;
    if (auto* env_mgr = wm->getEnvMgr())
        env_mgr->setPaletteSet(*mPalleteType_s);
}

}  // namespace uking::action
