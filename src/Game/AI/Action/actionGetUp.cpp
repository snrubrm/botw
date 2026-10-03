#include "Game/AI/Action/actionGetUp.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GetUp::GetUp(const InitArg& arg) : GetUpBase(arg) {}

GetUp::~GetUp() = default;

bool GetUp::init_(sead::Heap* heap) {
    return GetUpBase::init_(heap);
}

void GetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpBase::enter_(params);
    _150.value = _150.prev_value = 0;
}

void GetUp::leave_() {
    GetUpBase::leave_();
}

void GetUp::loadParams_() {
    GetUpBase::loadParams_();
    getStaticParam(&mRotRatio_s, "RotRatio");
}

void GetUp::calc_() {
    GetUpBase::calc_();
}

bool GetUp::m34() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return true;
    if (_68.value <= sead::Mathf::epsilon()) {
        sub_71007419B4(&_44, getUpDir(controller->get70()));
        sub_71007419F4(_44, controller);
        return true;
    }
    _150.lerp(sead::Mathf::pi() / 2, 0.05f);
    _150.updateStats();
    sub_7100741628(&_44, getUpDir(controller->get70()), *mRotRatio_s, _150.value, 0.0f);
    _68.update();
    sub_71007419F4(_44, controller);
    return false;
}

f32 GetUp::m35() {
    return *mRotRatio_s;
}

}  // namespace uking::action
