#include "Game/AI/Action/actionArrowShootMoveWithStickOffset.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

ArrowShootMoveWithStickOffset::ArrowShootMoveWithStickOffset(const InitArg& arg)
    : ArrowShootMove(arg) {}

ArrowShootMoveWithStickOffset::~ArrowShootMoveWithStickOffset() = default;

bool ArrowShootMoveWithStickOffset::init_(sead::Heap* heap) {
    return ArrowShootMove::init_(heap);
}

void ArrowShootMoveWithStickOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowShootMoveWithStickOffset::leave_() {
    ArrowShootMove::leave_();
}

void ArrowShootMoveWithStickOffset::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mStickOffset_s, "StickOffset");
}

void ArrowShootMoveWithStickOffset::calc_() {
    ArrowShootMove::calc_();
}

float ArrowShootMoveWithStickOffset::m32() {
    return *mStickOffset_s;
}

bool ArrowShootMoveWithStickOffset::m35(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.hasProc() && accessor.getName() == "GanonTornado";
}

void ArrowShootMoveWithStickOffset::m36(bool* out, const ksys::act::ActorConstDataAccess& accessor) {
    *out = false;
}

f32 ArrowShootMoveWithStickOffset::m41() {
    return 1.0f;
}

}  // namespace uking::action
