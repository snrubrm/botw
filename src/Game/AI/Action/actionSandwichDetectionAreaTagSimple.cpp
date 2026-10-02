#include "Game/AI/Action/actionSandwichDetectionAreaTagSimple.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::action {

SandwichDetectionAreaTagSimple::SandwichDetectionAreaTagSimple(const InitArg& arg)
    : AreaTagAction(arg) {}

SandwichDetectionAreaTagSimple::~SandwichDetectionAreaTagSimple() = default;

bool SandwichDetectionAreaTagSimple::init_(sead::Heap* heap) {
    const ksys::phys::ContactLayer layers[] = {
        ksys::phys::ContactLayer::SensorObject,  ksys::phys::ContactLayer::SensorSmallObject,
        ksys::phys::ContactLayer::SensorEnemy,   ksys::phys::ContactLayer::SensorChemical,
        ksys::phys::ContactLayer::SensorQueryOnly,
    };
    _38.tryAllocBuffer(5, heap);
    if (!_38.isBufferReady())
        return false;
    for (int i = 0; i < 5; ++i)
        _38[i]._0 = layers[i];
    return true;
}

void SandwichDetectionAreaTagSimple::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SandwichDetectionAreaTagSimple::leave_() {
    AreaTagAction::leave_();
}

void SandwichDetectionAreaTagSimple::loadParams_() {}

void SandwichDetectionAreaTagSimple::calc_() {
    AreaTagAction::calc_();
}

bool SandwichDetectionAreaTagSimple::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (_48)
        return true;

    _48 = accessor.hasProc();
    _48 &= !accessor.hasTag(ksys::act::tags::ExclusionFromSandwichDetection);
    _48 &= accessor.getName() != "GameROMPlayer";
    return _48;
}

void SandwichDetectionAreaTagSimple::m5() {
    if (mActor) {
        if (_48) {
            if (!_49)
                mActor->emitBasicSigOn();
        } else if (_49) {
            mActor->emitBasicSigOff();
        }
    }
    _49 = _48;
}

}  // namespace uking::action
