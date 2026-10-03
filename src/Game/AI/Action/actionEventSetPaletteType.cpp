#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "Game/AI/Action/actionEventSetPaletteType.h"

namespace uking::action {

EventSetPaletteType::EventSetPaletteType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetPaletteType::~EventSetPaletteType() = default;

bool EventSetPaletteType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetPaletteType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetPaletteType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetPaletteType::loadParams_() {
    getDynamicParam(&mPaletteType_d, "PaletteType");
    getDynamicParam(&mChangeFrame_d, "ChangeFrame");
    getDynamicParam(&mEndFrame_d, "EndFrame");
    getDynamicParam(&mSpeed_d, "Speed");
}

void EventSetPaletteType::calc_() {
    // NON_MATCHING: the original writes the EnvMgr fields without the PtrArray bounds check that
    // getXMgr() keeps (reads like an inline member function of the manager; not repeated elsewhere)
    if (isFailed())
        return;
    if (auto* wm = ksys::world::Manager::instance()) {
        auto* env = wm->getEnvMgr();
        env->mPaletteSetOverride = *mPaletteType_d;
        env->mPaletteSetOverrideTimer = 4;
        env->_6b5c8 = *mChangeFrame_d;
        env->_6b5cc = *mEndFrame_d;
        env->_6b550 = *mSpeed_d;
        env->mBlockPaletteSetOverride = true;
        return;
    }
    setFailed();
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
