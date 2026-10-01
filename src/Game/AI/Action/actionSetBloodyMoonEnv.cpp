#include "Game/AI/Action/actionSetBloodyMoonEnv.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

SetBloodyMoonEnv::SetBloodyMoonEnv(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetBloodyMoonEnv::~SetBloodyMoonEnv() = default;

bool SetBloodyMoonEnv::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetBloodyMoonEnv::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* wm = ksys::world::Manager::instance();
    ksys::world::TimeMgr* time_mgr;
    if (wm && (time_mgr = wm->getTimeMgr())) {
        time_mgr->setBloodMoonForceMode(ksys::world::TimeMgr::BloodMoonForceMode::Immediate);
        setFinished();
    } else {
        setFailed();
    }
    mFlags.set(Flag::Changeable);
}

void SetBloodyMoonEnv::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetBloodyMoonEnv::loadParams_() {}

void SetBloodyMoonEnv::calc_() {
    if (isFinished() || isFailed())
        return;
}

}  // namespace uking::action
