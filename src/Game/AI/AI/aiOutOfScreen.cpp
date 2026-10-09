#include "Game/AI/AI/aiOutOfScreen.h"
#include <gsys/gsysModel.h>
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

OutOfScreen::OutOfScreen(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OutOfScreen::~OutOfScreen() = default;

bool OutOfScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OutOfScreen::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F4054();
    mActor->getLodState()->mFlags10.set(0x40);
}

// 0x71004f4128
void OutOfScreen::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        sub_71004F4054();
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return;
    sead::BoundSphere3f bounds;
    actor->getModel()->getBounding(&bounds);
    if (!sub_7100D8C5E8(bounds.getCenter(), bounds.getRadius(), 0.01f, *mDeleteDistance_s) ||
        controller->sub_7100F5F264()) {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
        return;
    }
    _50.update();
    if (_50.value <= sead::Mathf::epsilon()) {
        sead::Vector3f position;
        sub_71004F4270(&position);
        child->setDynamicParam(position, "TargetPos");
    }
}

void OutOfScreen::sub_71004F4054() {
    sead::Vector3f pos;
    sub_71004F4270(&pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void OutOfScreen::leave_() {
    mActor->getLodState()->mFlags10.reset(0x40);
}

void OutOfScreen::loadParams_() {
    getStaticParam(&mUpdateInterval_s, "UpdateInterval");
    getStaticParam(&mTagetDistance_s, "TagetDistance");
    getStaticParam(&mDeleteDistance_s, "DeleteDistance");
}

}  // namespace uking::ai
