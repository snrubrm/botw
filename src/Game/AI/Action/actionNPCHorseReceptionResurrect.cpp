#include "Game/AI/Action/actionNPCHorseReceptionResurrect.h"

namespace uking::action {

NPCHorseReceptionResurrect::NPCHorseReceptionResurrect(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCHorseReceptionResurrect::~NPCHorseReceptionResurrect() = default;

bool NPCHorseReceptionResurrect::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCHorseReceptionResurrect::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void NPCHorseReceptionResurrect::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCHorseReceptionResurrect::loadParams_() {}

void NPCHorseReceptionResurrect::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
