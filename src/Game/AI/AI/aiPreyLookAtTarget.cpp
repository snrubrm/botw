#include "Game/AI/AI/aiPreyLookAtTarget.h"
#include <algorithm>
#include <cmath>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PreyLookAtTarget::PreyLookAtTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyLookAtTarget::~PreyLookAtTarget() = default;

bool PreyLookAtTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: regalloc / spill order of the saved position; `hearing` is tested with tbz in the
// original (cbz here)
void PreyLookAtTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _50 = *mTargetPos_d;

    const bool hearing = mActor->getASList()->x_1(0, 0).startsWith("Hearing");
    if (!hearing) {
        const auto& mtx = mActor->getMtx();
        sead::Vector3f dir = _50 - mtx.getTranslation();
        dir.y = 0.0f;
        sead::Vector3f front;
        mtx.getBase(front, 2);
        const f32 dist = dir.normalize();
        const f32 limit = *mLimitAngle_s;
        if (front.dot(dir) < std::cos(limit)) {
            const f32 angle = limit * (front.cross(dir).y >= 0.0f ? 1.0f : -1.0f);
            sead::Matrix34f rot;
            rot.makeR({0.0f, angle, 0.0f});
            sead::Vector3f rotated;
            rotated.setRotated(rot, front);
            const f32 len = rotated.length();
            if (len > 0.0f)
                rotated *= dist / len;
            _50 = pos + rotated;
        }
    }

    if (_50.y < mActor->getPreviousPos2().y)
        _50.y += std::min(mActor->getPreviousPos2().y - _50.y, 1.0f);

    sub_71005DB068(mActor, _50);
    _5c = false;
    if (auto* awareness = mActor->getAwareness())
        _5c = awareness->_334 & 2;

    if (hearing) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_50, "TargetPos", -1);
        changeChild("連続ふり向き", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_50, "TargetPos", -1);
        changeChild("ふり向き", &pack);
    }
}

void PreyLookAtTarget::calc_() {
    if (*mIsUpdateViewPos_s)
        getCurrentChild()->setDynamicParam(_50, "TargetPos");

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ふり向き") || isCurrentChild("連続ふり向き")) {
            if (auto* awareness = mActor->getAwareness()) {
                if (_5c)
                    awareness->_334 &= ~2;
            }
            ksys::act::ai::InlineParamPack params;
            params.addVec3(_50, "TargetPos", -1);
            changeChild("警戒", &params);
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else {
        child->isChangeable();
    }
}

void PreyLookAtTarget::leave_() {
    sub_71005DB3EC(mActor);
    if (auto* awareness = mActor->getAwareness()) {
        if (_5c)
            awareness->_334 |= 2;
    }
}

void PreyLookAtTarget::loadParams_() {
    getStaticParam(&mLimitAngle_s, "LimitAngle");
    getStaticParam(&mIsUpdateViewPos_s, "IsUpdateViewPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
