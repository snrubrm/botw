#include "Game/AI/Action/actionLargeDamage.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

LargeDamage::LargeDamage(const InitArg& arg) : ActionEx(arg) {}

LargeDamage::~LargeDamage() = default;

void LargeDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("LargeDamage", false, 0, 0, -1.0f);
    auto* mgr = sub_710072BA90(mActor);
    sub_71005E242C(&_40, mActor, mgr);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EF08(true);
    _34.value = 0.5f;
    _34.prev_value = 0.5f;
    _28.reset(*mActionTime_s);
    _4c = 0;
}

void LargeDamage::leave_() {
    ActionEx::leave_();
}

void LargeDamage::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
}

void LargeDamage::calc_() {
    switch (_4c) {
    case 0: {
        auto* controller = mActor->getCharacterController();
        if (!controller)
            return;

        _28.update();
        if (_28.value <= sead::Mathf::epsilon()) {
            _34 *= 0.0f;
            _34.updateStats();
            playAS("GetUp", false, 0, 0, -1.0f);
            controller->sub_7100F5EF08(true);
            sub_7100738660(controller, 0.0f);
            ++_4c;
        } else {
            sub_7100738660(controller, 0.85f);
            _34 *= 0.9f;
            _34.updateStats();
        }
        sub_710072C1B4(controller, _40);
        controller->sub_7100F5E7F0(_34.value * 30.0f);
        break;
    }
    case 1:
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
}

bool LargeDamage::isChangeable() const {
    return _4c == 1;
}

}  // namespace uking::action
