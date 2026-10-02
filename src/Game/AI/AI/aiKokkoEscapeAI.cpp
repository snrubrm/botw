#include "Game/AI/AI/aiKokkoEscapeAI.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

KokkoEscapeAI::KokkoEscapeAI(const InitArg& arg) : AnimalEscapeAI(arg) {}

KokkoEscapeAI::~KokkoEscapeAI() = default;

bool KokkoEscapeAI::init_(sead::Heap* heap) {
    return AnimalEscapeAI::init_(heap);
}

void KokkoEscapeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _151 = true;
    AnimalEscapeAI::enter_(params);
    _151 = false;
}

void KokkoEscapeAI::calc_() {
    AnimalEscapeAI::calc_();
}

void KokkoEscapeAI::leave_() {
    AnimalEscapeAI::leave_();
}

void KokkoEscapeAI::loadParams_() {
    AnimalEscapeAI::loadParams_();
}

void KokkoEscapeAI::m38(ksys::act::ai::InlineParamPack* params) {
    params->addBool(_151, "IsJump", -1);
}

}  // namespace uking::ai
