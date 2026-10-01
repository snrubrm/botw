#include "Game/AI/AI/aiEscapeFromTargetFrontRandomDir.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

EscapeFromTargetFrontRandomDir::EscapeFromTargetFrontRandomDir(const InitArg& arg)
    : EscapeFromTargetFront(arg) {}

EscapeFromTargetFrontRandomDir::~EscapeFromTargetFrontRandomDir() = default;

bool EscapeFromTargetFrontRandomDir::init_(sead::Heap* heap) {
    return EscapeFromTargetFront::init_(heap);
}

void EscapeFromTargetFrontRandomDir::enter_(ksys::act::ai::InlineParamPack* params) {
    EscapeFromTargetFront::enter_(params);
}

void EscapeFromTargetFrontRandomDir::calc_() {
    EscapeFromTargetFront::calc_();
}

void EscapeFromTargetFrontRandomDir::leave_() {
    EscapeFromTargetFront::leave_();
}

void EscapeFromTargetFrontRandomDir::loadParams_() {
    EscapeFromTargetFront::loadParams_();
    getStaticParam(&mInverseDirRatio_s, "InverseDirRatio");
}

int EscapeFromTargetFrontRandomDir::m34() {
    const int dir = EscapeFromTargetFront::m34();
    if (sead::GlobalRandom::instance()->getS32Range(0, 100) < *mInverseDirRatio_s)
        return -dir;
    return dir;
}

}  // namespace uking::ai
