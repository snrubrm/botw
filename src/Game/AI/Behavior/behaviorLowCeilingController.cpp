#include "Game/AI/Behavior/behaviorLowCeilingController.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

LowCeilingController::LowCeilingController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
LowCeilingController::~LowCeilingController() {
    ;
}

bool LowCeilingController::m6(sead::Heap* heap) {
    _4c = -1;
    _50 = 0;
    if (auto* physics = mActor->getPhysics())
        _4c = physics->sub_7100FBE7F0(mShapeName_s);
    return true;
}

// NON_MATCHING: the original tests `moving` with cbnz where ours uses tbnz #0 (bool / int / u32 and
// ternary forms tried) and merges the final `_50 = 0` of both branches
void LowCeilingController::m7() {
    if (_4c < 0)
        return;
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    const u32 state = _48;
    int moving = 0;
    if (auto* nav = mActor->m45()) {
        if ((nav->_2a4 & 0xffff) != 0x17)
            moving = (nav->_2a4 & 0xffff) == 5;
    }
    const f32 timer = _50;
    if (state) {
        if (!moving) {
            _50 = delta + timer;
            if (!(_50 >= *mReverseFrame_s))
                return;
            if (_4c < 0)
                return;
            if (auto* cc = mActor->getCharacterController()) {
                if (cc->_224 == _4c)
                    cc->sub_7100F62BB8();
                _48 = 0;
            }
            _48 = 0;
            _50 = 0;
            return;
        }
    } else if (moving) {
        _50 = delta + timer;
        if (!(_50 >= *mChangeFrame_s))
            return;
        const s32 idx = _4c;
        _50 = 0;
        if (idx < 0)
            return;
        if (auto* cc = mActor->getCharacterController()) {
            cc->sub_7100F5F270(_4c);
            _48 = 1;
        }
        _48 = 1;
        _50 = 0;
        return;
    }
    _50 = sead::Mathf::clampMin(timer - delta, 0.0f);
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
