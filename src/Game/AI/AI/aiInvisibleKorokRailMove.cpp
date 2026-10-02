#include "Game/AI/AI/aiInvisibleKorokRailMove.h"

namespace uking::ai {

InvisibleKorokRailMove::InvisibleKorokRailMove(const InitArg& arg) : KorokRailMove(arg) {}

InvisibleKorokRailMove::~InvisibleKorokRailMove() = default;

bool InvisibleKorokRailMove::init_(sead::Heap* heap) {
    return KorokRailMove::init_(heap);
}

void InvisibleKorokRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    KorokRailMove::enter_(params);
    xlinkSearchAndEmit(mActor, "InvisibleMove_Sign", 2, &_c0);
}

void InvisibleKorokRailMove::calc_() {
    KorokRailMove::calc_();
    _c0.sub_71012419B4(mActor->getMtx().getTranslation());
}

void InvisibleKorokRailMove::leave_() {
    KorokRailMove::leave_();
    _c0.fadeXLink();
}

void InvisibleKorokRailMove::m38(sead::Vector3f* diff, sead::Vector3f* pos) {
    pos->y = mActor->getMtx()(1, 3);
    KorokRailMove::m38(diff, pos);
}

void InvisibleKorokRailMove::loadParams_() {
    KorokRailMove::loadParams_();
}

}  // namespace uking::ai
