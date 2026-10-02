#include "Game/AI/AI/aiTargetPlayerPos.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

TargetPlayerPos::TargetPlayerPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetPlayerPos::~TargetPlayerPos() = default;

bool TargetPlayerPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPlayerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPlayerPos::calc_() {
    TargetPosAI::calc_();
}

void TargetPlayerPos::leave_() {
    TargetPosAI::leave_();
}

void TargetPlayerPos::loadParams_() {
    TargetPosAI::loadParams_();
}

void TargetPlayerPos::m35(sead::Vector3f* pos) {
    *pos = getPlayerPosition();
}

}  // namespace uking::ai
