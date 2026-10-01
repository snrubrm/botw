#include "Game/AI/Action/actionNPCNameHorse.h"

namespace uking::action {

NPCNameHorse::NPCNameHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCNameHorse::~NPCNameHorse() = default;

void NPCNameHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
    _1d = false;
    _20 = -1;
}

void NPCNameHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
