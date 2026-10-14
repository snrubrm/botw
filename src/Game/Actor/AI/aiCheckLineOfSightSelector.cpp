#include "Game/Actor/AI/aiCheckLineOfSightSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include <math/seadVector.h>

namespace uking::ai {

CheckLineOfSightSelector::CheckLineOfSightSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CheckLineOfSightSelector::~CheckLineOfSightSelector() = default;

bool CheckLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: backend store pairing only — the original stores the negated x/y
// with separate str (with the z load interleaved); ours pairs them into stp.
void CheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    auto* controller = mActor->getCharacterController();
    if (!nav) {
        changeChild("全方向失敗", params);
        return;
    }
    if (!controller) {
        changeChild("全方向失敗", params);
        return;
    }
    sead::Vector3f vec = controller->get64();
    m34(&vec);
    if (vec.dot(controller->get64()) >= 0.0f) {
        sead::Vector3f dir = controller->get64();
        if (sub_7100346AA4(nav, &dir)) {
            changeChild("前方成功", params);
        } else {
            dir.x = -dir.x;
            dir.y = -dir.y;
            dir.z = -dir.z;
            if (sub_7100346AA4(nav, &dir)) {
                changeChild("後方成功", params);
            } else {
                changeChild("全方向失敗", params);
            }
        }
    } else {
        sead::Vector3f dir = controller->get64();
        const f32 x = dir.x;
        const f32 y = dir.y;
        const f32 z = dir.z;
        dir.x = -x;
        dir.y = -y;
        dir.z = -z;
        if (sub_7100346AA4(nav, &dir)) {
            changeChild("後方成功", params);
        } else {
            dir.x = x;
            dir.y = y;
            dir.z = z;
            if (sub_7100346AA4(nav, &dir)) {
                changeChild("前方成功", params);
            } else {
                changeChild("全方向失敗", params);
            }
        }
    }
}

void CheckLineOfSightSelector::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void CheckLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CheckLineOfSightSelector::loadParams_() {
    getStaticParam(&mDirectionNum_s, "DirectionNum");
    getStaticParam(&mDirectionAngle_s, "DirectionAngle");
    getStaticParam(&mDistance_s, "Distance");
    getStaticParam(&mRadiusScale_s, "RadiusScale");
}

bool CheckLineOfSightSelector::isFinished() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFinished())
        return true;
    return child && child->isFinished();
}

bool CheckLineOfSightSelector::isFailed() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFailed())
        return true;
    return child && child->isFailed();
}

void CheckLineOfSightSelector::m34(sead::Vector3f* out) {}

}  // namespace uking::ai
