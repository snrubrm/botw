#include "Game/AI/AI/aiBlownOff.h"
#include <math/seadBoundBox.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

BlownOff::BlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("ふっとび", params);
}

// NON_MATCHING: one degenerate branch on the inlined drowning test result (tbnz / tbz to the next instruction).
void BlownOff::calc_() {
    // Whether the actor is in water deeper than DrownDepth (or the downward ray finds no floor).
    const auto isDrowning = [this] {
        if (*mDrownDepth_s > 0.0f && mActor->get68f()) {
            const f32 current = mActor->getMtx()(1, 3);
            return mActor->get6f0() - current > *mDrownDepth_s || !sub_710032F364();
        }
        return false;
    };
    const auto changeToDrown = [this] {
        sub_710072BB28(mActor);
        changeChild("水死");
    };

    if (isCurrentChild("起き上がり")) {
        auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
        if (actor && actor->m151(3) && !isCurrentChild("凍結")) {
            changeChild("起き上がり凍結");
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("水死")) {
            callDeleteAndCreateDropAndEmit(mActor, 0);
            return;
        }
        if (isCurrentChild("起き上がり")) {
            setFinished();
            return;
        }
        if (isDrowning()) {
            changeToDrown();
            return;
        }
        if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
            if (*mDrownDepth_s >= 0.0f && (actor->m151(7) || actor->m151(8))) {
                changeToDrown();
                return;
            }
            if (actor->m151(3)) {
                changeChild("凍結");
                return;
            }
        }
        if (!*mIsForceGetUp_s) {
            const f32 angle = sead::Mathf::abs(
                std::asin(sead::Mathf::clamp(mActor->getMtx()(1, 2), -1.0f, 1.0f)));
            if (angle <= sead::Mathf::epsilon() && -sead::Mathf::epsilon() <= angle) {
                setFinished();
                return;
            }
        }
        m34(nullptr);
        return;
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if ((isCurrentChild("凍結") || isCurrentChild("起き上がり凍結")) && isDrowning()) {
        changeToDrown();
        return;
    }

    if (*mIsIceBreak_s && isCurrentChild("凍結")) {
        auto* manager = mActor->getDamageMgr();
        if (manager && manager->getField54() == 0x17) {
            changeChild("ふっとび");
            return;
        }
    }

    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    if (*mDrownDepth_s >= 0.0f && (actor->m151(7) || actor->m151(8)) && !isCurrentChild("水死")) {
        changeToDrown();
        return;
    }
    if (!actor->m151(3))
        return;
    if (isCurrentChild("凍結") || isCurrentChild("起き上がり凍結"))
        return;
    changeChild("凍結");
}

void BlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
    getStaticParam(&mIsIceBreak_s, "IsIceBreak");
}

bool BlownOff::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("起き上がり") && getCurrentChild()->isFinished());
}

void BlownOff::m34(ksys::act::ai::InlineParamPack* params) {
    changeChild("起き上がり", params);
}

// NON_MATCHING: same instructions, other scheduling / registers (the original keeps `pos` in memory across the
// AABB query and loads `pos.y` after it; the depth / reference swap s8 / s9)
bool BlownOff::sub_710032F364() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 y;
    if (auto* controller = mActor->getCharacterController()) {
        if (!controller->isBit6Of116())
            return true;
        const f32 depth = *mDrownDepth_s;
        const f32 reference = controller->get194();
        sead::BoundBox3f aabb;
        controller->sub_7100F61A34()->getAabbInWorld(&aabb);
        if (pos.y < aabb.getMin().y)
            return true;
        aabb.getCenter(&pos);
        y = reference - depth;
    } else {
        f32 offset = 0;
        if (mActor->get68f()) {
            const f32 current = mActor->getMtx().m[1][3];
            offset = mActor->get6f0() - current;
        }
        y = pos.y + offset - *mDrownDepth_s;
    }
    sead::Vector3f to = pos;
    to.y = y;
    return sub_710072E928(pos, to, nullptr, nullptr, nullptr, 0.0f);
}

}  // namespace uking::ai
