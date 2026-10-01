#include "Game/AI/Action/actionGuardWithAS.h"

namespace uking::action {

GuardWithAS::GuardWithAS(const InitArg& arg) : Guard(arg) {}

GuardWithAS::~GuardWithAS() = default;

void GuardWithAS::loadParams_() {
    Guard::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardWithAS::m38() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (*mASSlot_s != 0)
        playAS(mASName_s.cstr(), false, *mASSlot_s, 0, -1.0f);
}

}  // namespace uking::action
