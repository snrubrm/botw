#include "Game/AI/Behavior/behaviorLowCeilingController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

LowCeilingController::LowCeilingController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
LowCeilingController::~LowCeilingController() {
    ;
}

void LowCeilingController::m8() {
    if (_4c < 0)
        return;
    if (auto* cc = mActor->getCharacterController()) {
        if (cc->_224 == _4c)
            cc->sub_7100F62BB8();
        _48 = 0;
    }
    _48 = 0;
    _50 = 0;
}

void LowCeilingController::m9() {
    if (_4c < 0)
        return;
    if (auto* cc = mActor->getCharacterController()) {
        if (cc->_224 == _4c)
            cc->sub_7100F62BB8();
        _48 = 0;
    }
    _48 = 0;
    _50 = 0;
}

void LowCeilingController::loadParams() {
    getStaticParam(&mChangeFrame_s, "ChangeFrame");
    getStaticParam(&mReverseFrame_s, "ReverseFrame");
    getStaticParam(&mShapeName_s, "ShapeName");
}

}  // namespace uking::behavior
