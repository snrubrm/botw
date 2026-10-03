#include "Game/AI/AI/aiNavViewMove.h"
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

NavViewMove::NavViewMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavViewMove::~NavViewMove() = default;

bool NavViewMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavViewMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_71004BABDC()) {
        sub_71004BAE20();
        return;
    }

    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: the original copies nav->_248 under the lock as one 12-byte block (ldr x + ldr w), ours
// member-wise (sead::Vector3f::operator=); everything else is instruction-identical
bool NavViewMove::sub_71004BABDC() {
    auto* nav = mActor->m45();
    if (!nav)
        return true;

    const sead::Vector3f up = getUpDir(mActor);

    sead::Vector3f nav_dir;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        nav_dir = nav->_248;
    }
    ksys::util::sub_71011EFA00(&nav_dir, nav_dir, up);
    nav_dir.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    return front.dot(nav_dir) >= std::cos(*mSubsAngle_s);
}

// NON_MATCHING: register allocation / scheduling of the two target computations only
void NavViewMove::sub_71004BAE20() {
    _5c = false;
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f target;
    if (auto* nav = mActor->m45()) {
        sead::Vector3f dir;
        {
            auto lock = sead::makeScopedLock(nav->_1e0);
            dir = nav->_248;
        }
        target = dir * 5.0f + mActor->getMtx().getTranslation();
    } else {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        front.normalize();
        target = front + mActor->getMtx().getTranslation();
    }
    pack.addVec3(target, "TargetPos", -1);
    changeChild("回転", &pack);
}

void NavViewMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavViewMove::loadParams_() {
    getStaticParam(&mSubsAngle_s, "SubsAngle");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
