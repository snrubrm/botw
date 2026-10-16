#include "Game/Actor/Action/actionChangePostureWithAS.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ChangePostureWithAS::ChangePostureWithAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePostureWithAS::~ChangePostureWithAS() = default;

bool ChangePostureWithAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps the "" literal in a callee-saved register for the final call and places the
// AS name loads in the branch blocks.
void ChangePostureWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::SafeString current(mActor->getASList()->sub_710115ECF4(59, 1));
    const char* as_name;
    if (current == "") {
        if (mPosture_d == "Crouch")
            as_name = "Stand_To_Crouch";
        else if (mPosture_d == "SitOnObject")
            as_name = "Stand_To_Sit";
        else if (mPosture_d == "Sit")
            as_name = "Stand_To_Rest";
        else {
            setFailed();
            return;
        }
    } else if (current == "Crouch") {
        if (!(mPosture_d == "Stand")) {
            setFailed();
            return;
        }
        as_name = "Crouch_To_Stand";
    } else if (current == "SitOnObject") {
        if (!(mPosture_d == "Stand")) {
            setFailed();
            return;
        }
        as_name = "Sit_To_Stand";
    } else if (current == "Sit") {
        if (!(mPosture_d == "Stand")) {
            setFailed();
            return;
        }
        as_name = "Rest_To_Stand";
    } else {
        setFailed();
        return;
    }
    playAS(as_name, false, 0, 0, -1.0f);
    mActor->getASList()->goLimpFromHeadShotMaybe(
        59, sead::SafeString(mPosture_d == "Stand" ? "" : mPosture_d.cstr()), true);
}

void ChangePostureWithAS::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangePostureWithAS::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

void ChangePostureWithAS::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
