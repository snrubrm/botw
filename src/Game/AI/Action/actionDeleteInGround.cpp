#include "Game/AI/Action/actionDeleteInGround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

DeleteInGround::DeleteInGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DeleteInGround::~DeleteInGround() = default;

bool DeleteInGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeleteInGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DeleteInGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void DeleteInGround::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: scheduling of the scaled gravity store
void DeleteInGround::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* actor = mActor;
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    gravity = gravity * (1.0f / 900.0f);
    sub_7100738488(actor, 0.0f, gravity);
    sub_7100738AA8(actor, 0.0f);
    if (isFinishedAS(0, 0)) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFinished();
    }
}

}  // namespace uking::action
