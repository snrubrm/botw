#include "Game/AI/Action/actionNPCHorseReception.h"

namespace uking::action {

NPCHorseReception::NPCHorseReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCHorseReception::~NPCHorseReception() = default;

void NPCHorseReception::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void NPCHorseReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
