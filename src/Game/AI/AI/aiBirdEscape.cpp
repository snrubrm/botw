#include "Game/AI/AI/aiBirdEscape.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

BirdEscape::BirdEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdEscape::~BirdEscape() = default;

bool BirdEscape::init_(sead::Heap* heap) {
    auto* root = mActor->getRootAi();
    _74 = (root && root->getI() == 4) || *mIsLocatorCreate_m;
    return true;
}

void BirdEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool BirdEscape::isChangeable() const {
    return false;
}

void BirdEscape::calc_() {
    if (!(_68.value <= sead::Mathf::epsilon())) {
        _68.update();
        if (_68.value <= sead::Mathf::epsilon()) {
            if (mActor->m135())
                mActor->m135()->_4 = 0;
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("逃走前")) {
            if (!isCurrentChild("逃走") || !*mIsUseEscapeEnd_s) {
                setFinished();
                return;
            }
            changeChild("逃走終了");
        } else {
            changeChild("逃走");
        }
        return;
    }
    child->isChangeable();
}

void BirdEscape::leave_() {
    _60.resetMotionType(_60.sub_710072ACF8(mActor));
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    if (int(controller->sub_7100F5F0E4()) == 3)
        return;

    if (controller->sub_7100F5F14C())
        controller->sub_7100F5F458(ksys::act::MotionType(0));
    else
        controller->sub_7100F5F458(ksys::act::MotionType(1));
}

void BirdEscape::loadParams_() {
    getStaticParam(&mForceEndTimer_s, "ForceEndTimer");
    getStaticParam(&mIsUseEscapeBefore_s, "IsUseEscapeBefore");
    getStaticParam(&mIsUseEscapeEnd_s, "IsUseEscapeEnd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getMapUnitParam(&mIsLocatorCreate_m, "IsLocatorCreate");
}

}  // namespace uking::ai
