#include "Game/Actor/AI/aiBirdEscape.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::ai {

BirdEscape::BirdEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdEscape::~BirdEscape() = default;

bool BirdEscape::init_(sead::Heap* heap) {
    auto* root = mActor->getRootAi();
    _74 = (root && root->getI() == 4) || *mIsLocatorCreate_m;
    return true;
}

// NON_MATCHING: the original reuses the position slot for the ray start and the param pack (scoped locals) and keeps
// the direction in float registers.
void BirdEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* cc = mActor->getCharacterController();
    if (!cc) {
        setFailed();
        return;
    }
    _60.changeMotionType(cc, ksys::act::MotionType::Hover);

    sead::Vector3f normal;
    sead::Vector3f pos;
    cc->sub_7100F5F6E0(&pos);

    // Escape direction: away from the target, or the actor's front if that is not usable.
    sead::Vector3f dir = pos - *mTargetPos_d;
    dir.y = 0.0f;
    dir.normalize();
    if (dir.isNan() || (dir.x <= 0.1f && dir.x >= -0.1f && dir.y <= 0.1f && dir.y >= -0.1f &&
                        dir.z <= 0.1f && dir.z >= -0.1f)) {
        dir = mActor->getMtx().getBase(2);
    }

    const sead::Vector3f from = pos - dir * 0.5f;
    const sead::Vector3f to = pos + dir * 7.0f;
    if (sub_710072E500(from, to, nullptr, &normal, nullptr, 1.0f)) {
        normal.y = 0.0f;
        dir = -dir;
        if (normal.normalize() > 0.0f && normal.dot(dir) < 0.76604444f)
            dir = normal;
    }

    mActor->getLodState()->mFlags10.set(0x40);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);

    const s32 time = *mForceEndTimer_s;
    _68 = time < 0 ? ksys::Timer(-1.0f, -1.0f, 0.0f) : ksys::Timer(time, time);

    if (!*mIsUseEscapeBefore_s || _74) {
        changeChild("逃走");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos + dir * 5.0f, "TargetPos", -1);
        changeChild("逃走前", &pack);
    }
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
