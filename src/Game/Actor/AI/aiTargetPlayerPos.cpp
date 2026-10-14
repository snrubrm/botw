#include "Game/Actor/AI/aiTargetPlayerPos.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

TargetPlayerPos::TargetPlayerPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetPlayerPos::~TargetPlayerPos() = default;

bool TargetPlayerPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetPlayerPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetPlayerPos::calc_() {
    TargetActorPos::calc_();
}

void TargetPlayerPos::leave_() {
    TargetActorPos::leave_();
}

void TargetPlayerPos::loadParams_() {
    TargetActorPos::loadParams_();
}

void TargetPlayerPos::m35(sead::Vector3f* pos) {
    *pos = getPlayerPosition();
}

}  // namespace uking::ai
