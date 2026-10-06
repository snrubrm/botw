#include "Game/AI/Action/actionWolfLinkAmiiboRegister.h"
#include "Game/gameWolfLinkMgr.h"

namespace uking::action {

WolfLinkAmiiboRegister::WolfLinkAmiiboRegister(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkAmiiboRegister::~WolfLinkAmiiboRegister() = default;

bool WolfLinkAmiiboRegister::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original reads the SpawnFlags param with a byte load (`ldrb`); an `int*` param is read with `ldr`
void WolfLinkAmiiboRegister::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* manager = WolfLinkMgr::instance())
        manager->sub_7100682CE8(mTargetPos_d, *mSpawnFlags_d);
    else
        setFailed();
}

void WolfLinkAmiiboRegister::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkAmiiboRegister::loadParams_() {
    getDynamicParam(&mSpawnFlags_d, "SpawnFlags");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void WolfLinkAmiiboRegister::calc_() {
    if (isFinished() || isFailed())
        return;
    if (auto* manager = WolfLinkMgr::instance()) {
        if (manager->sub_710068367C()) {
            setFinished();
            return;
        }
        if (!manager->sub_7100683698())
            return;
    }
    setFailed();
}

}  // namespace uking::action
