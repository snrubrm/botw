#include "Game/AI/AI/aiHorseReins.h"

namespace uking::ai {

HorseReins::HorseReins(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void HorseReins::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("再生");
}

void HorseReins::calc_() {}

void HorseReins::loadParams_() {}

}  // namespace uking::ai
