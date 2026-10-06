#include "Game/AI/AI/aiNavViewMove.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
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

// NON_MATCHING: the same register allocation / scheduling of the target computations as sub_71004BAE20, and the
// original stores the Timer's value / previous value as one `stp` (ours two `str`)
void NavViewMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinishedOrFailed()) {
        if (isCurrentChild("移動")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (isCurrentChild("回転")) {
            _5c = false;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("移動", &pack);
            return;
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("移動") && _5c && _50.value <= sead::Mathf::epsilon()) {
            sub_71004BAE20();
            return;
        }
    }

    if (isCurrentChild("移動")) {
        if (!*mCheckOnce_s) {
            if (sub_71004BABDC()) {
                _5c = false;
            } else if (_5c) {
                _50.update();
            } else {
                _5c = true;
                const f32 time = sead::GlobalRandom::instance()->getS32Range(4, 7);
                _50 = ksys::Timer(time, time);
            }
        }
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    } else {
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
        getCurrentChild()->setDynamicParam(target, "TargetPos");
    }
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
