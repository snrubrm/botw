#include "Game/AI/Action/actionHopFlyByTriggers.h"
#include <prim/seadStringUtil.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

// Source owner and namespace are unknown (defined in aiUnk_71006F55D8.cpp).
void sub_71006F5538(ksys::phys::CharacterController* controller);

namespace uking::action {

HopFlyByTriggers::HopFlyByTriggers(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HopFlyByTriggers::~HopFlyByTriggers() = default;

bool HopFlyByTriggers::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HopFlyByTriggers::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HopFlyByTriggers::leave_() {
    _40.resetMotionType(mActor->getCharacterController());
}

void HopFlyByTriggers::loadParams_() {
    getStaticParam(&mXZSpeedMax_s, "XZSpeedMax");
    getStaticParam(&mHopAccRatio_s, "HopAccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void HopFlyByTriggers::calc_() {
    if (auto* as_list = mActor->getASList()) {
        ksys::as::ASList::Unk4 query;
        if (as_list->x(68, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            f32 height = 0.0f;
            sead::StringUtil::tryParseF32(&height, query.name);
            sub_710019DF74(height);
        }
    } else {
        setFailed();
    }
    sub_7100738AA8(mActor, 0.45f);
    if (isFinishedAS(0, 0))
        setFinished();
}

void HopFlyByTriggers::sub_710019DF74(f32 height) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sub_71006F5538(controller);
    const sead::Vector3f gravity = getGravity(actor) * (1.0f / 900.0f);

    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    sead::Vector3f dir = -front;
    ksys::util::sub_71011EFA00(&dir, dir, gravity);
    dir.normalize();

    const f32 jump_speed = sub_710072D068(&gravity, height);
    const sead::Vector3f& velocity = actor->getVelocity();
    const f32 xz_speed = sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    const f32 accel = *mHopAccRatio_s * (*mXZSpeedMax_s - xz_speed);
    const f32 speed = xz_speed + accel;

    sead::Vector3f up = -gravity;
    up.normalize();
    sub_7100737710(controller, dir * speed + up * jump_speed);
}

}  // namespace uking::action
