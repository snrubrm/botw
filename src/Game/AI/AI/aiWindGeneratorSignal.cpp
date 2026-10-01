#include "Game/AI/AI/aiWindGeneratorSignal.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WindGeneratorSignal::WindGeneratorSignal(const InitArg& arg) : WindGenerator(arg) {}

WindGeneratorSignal::~WindGeneratorSignal() = default;

bool WindGeneratorSignal::init_(sead::Heap* heap) {
    return WindGenerator::init_(heap);
}

void WindGeneratorSignal::enter_(ksys::act::ai::InlineParamPack* params) {
    WindGenerator::enter_(params);
}

void WindGeneratorSignal::calc_() {
    WindGenerator::calc_();
}

void WindGeneratorSignal::leave_() {
    WindGenerator::leave_();
}

void WindGeneratorSignal::loadParams_() {
    WindGenerator::loadParams_();
}

void WindGeneratorSignal::m34() {
    WindGenerator::m34();
    mActor->emitBasicSigOff();
}

void WindGeneratorSignal::m35() {
    WindGenerator::m35();
    auto* actor = mActor;
    if (!actor->hasPlacementLinkForBasicSig() || actor->checkBasicSig())
        actor->emitBasicSigOn();
}

}  // namespace uking::ai
