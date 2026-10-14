#include "Game/Actor/AI/aiOutOfScreen.h"
#include <gsys/gsysModel.h>
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Camera/CameraMgr.h"

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

// A point TagetDistance away from the actor, beside the camera's view direction on the actor's front side.
void OutOfScreen::sub_71004F4270(sead::Vector3f* out) {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front = {mtx.m[0][2], 0.0f, mtx.m[2][2]};
    sead::Vector3f camera_pos;
    ksys::sub_7100D8C6AC(&camera_pos);
    sead::Vector3f camera_dir;
    ksys::sub_7100D8C7FC(&camera_dir);

    camera_dir.y = 0.0f;
    front.normalize();
    camera_dir.normalize();

    sead::Vector3f side;
    side.setCross(camera_dir, front);
    sead::Vector3f dir;
    dir.setCross(camera_dir, side);
    if (front.dot(dir) < 0.0f)
        dir = -dir;

    sead::Vector3f offset = {dir.x, 0.1f, dir.z};
    const f32 distance = *mTagetDistance_s;
    const f32 length = offset.length();
    if (length > 0.0f)
        offset *= distance / length;

    mActor->getMtx().getTranslation(*out);
    *out += offset;

    const int interval = *mUpdateInterval_s;
    _50.reset(interval < 0 ? 1.0f : static_cast<f32>(interval), interval < 0 ? 0.0f : -1.0f);
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
