#include "Game/AI/Action/actionSandwichDetectionAreaTag.h"
#include <cstring>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::action {

SandwichDetectionAreaTag::SandwichDetectionAreaTag(const InitArg& arg) : AreaTagAction(arg) {
    std::memset(_48, 0xff, sizeof(_48));
    _148 = false;
    _149 = false;
}

SandwichDetectionAreaTag::~SandwichDetectionAreaTag() = default;

bool SandwichDetectionAreaTag::init_(sead::Heap* heap) {
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

void SandwichDetectionAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SandwichDetectionAreaTag::leave_() {
    AreaTagAction::leave_();
}

void SandwichDetectionAreaTag::loadParams_() {}

void SandwichDetectionAreaTag::calc_() {
    AreaTagAction::calc_();
}

bool SandwichDetectionAreaTag::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (_148)
        return true;

    _148 = accessor.hasProc();
    _148 &= !accessor.hasTag(ksys::act::tags::ExclusionFromSandwichDetection);
    _148 &= accessor.getName() != "GameROMPlayer";
    return _148;
}

void SandwichDetectionAreaTag::m2() {
    std::memset(_48, 0xff, sizeof(_48));
    _148 = false;
}

void SandwichDetectionAreaTag::m5() {
    if (mActor) {
        if (_148) {
            if (!_149)
                mActor->emitBasicSigOn();
        } else if (_149) {
            mActor->emitBasicSigOff();
        }
    }
    _149 = _148;
}

bool SandwichDetectionAreaTag::m13(const CollisionIterator& it, int area_idx) {
    return !ActorObserverBase::m13(it, area_idx);
}

bool SandwichDetectionAreaTag::m14(const ContactIterator& it, int area_idx) {
    return !ActorObserverBase::m14(it, area_idx);
}

}  // namespace uking::action
