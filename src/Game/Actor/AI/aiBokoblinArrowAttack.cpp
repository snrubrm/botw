#include "Game/Actor/AI/aiBokoblinArrowAttack.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

BokoblinArrowAttack::BokoblinArrowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: stack slots of the probe directions / positions and load scheduling (the flow and calls match).
void BokoblinArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    // Back away when the target is close and there is no cliff behind.
    const sead::Vector3f target_pos = *mTargetPos_d;
    if ((target_pos - mActor->getMtx().getTranslation()).length() <= *mBackWalkStartDist_s) {
        auto* actor = mActor;
        const sead::Vector3f& front = actor->getMtx().getBase(2);
        const sead::Vector3f back = -sead::Vector3f(front.x, 0.0f, front.z);
        if (!sub_710072FEC4(actor, back, 2.5f, nullptr, true, nullptr)) {
            const sead::Vector3f target = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("後ずさり", &pack);
            return;
        }
    }

    // Move forward to a ledge when the target is far above or below.
    bool check_forward = true;
    const sead::Vector3f& target = *mTargetPos_d;
    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    const f32 dy = sead::Mathf::abs(target.y - pos.y);
    if (!(dy <= 4.0f)) {
        const f32 horizontal = sead::Vector3f(target.x - pos.x, 0.0f, target.z - pos.z).length();
        if (std::atan2(dy, horizontal) >= 0.34906584f) {
            auto* actor = mActor;
            const f32 cliff_dist = *mCliffCheckDist_s;
            sead::Vector3f ahead;
            actor->getMtx().getTranslation(ahead);
            ahead += actor->getMtx().getBase(2) * cliff_dist;
            bool on_nav = false;
            if (auto* nav = actor->m45())
                on_nav = nav->sub_7100F76078(nullptr, ahead, 1.0f).sub_7100F7EB40();
            if (!on_nav) {
                auto* actor2 = mActor;
                const sead::Vector3f& front = actor2->getMtx().getBase(2);
                const sead::Vector3f dir(front.x, 0.0f, front.z);
                sead::Vector3f edge;
                if (sub_710072FEC4(actor2, dir, *mCliffCheckDist_s, &edge, true, nullptr)) {
                    const sead::Vector3f& p = mActor->getMtx().getTranslation();
                    if (sead::Vector2f(p.x - edge.x, p.z - edge.z).length() >= 0.5f) {
                        ksys::act::ai::InlineParamPack pack;
                        pack.addVec3(edge, "TargetPos", -1);
                        changeChild("前進", &pack);
                        return;
                    }
                }
            }
        }
    }

    if (sub_710072E1B4(mActor, false)) {
        auto* actor = mActor;
        const sead::Vector3f& front = actor->getMtx().getBase(2);
        const sead::Vector3f dir(front.x, 0.0f, front.z);
        if (!sub_710072FEC4(actor, dir, 0.5f, nullptr, true, nullptr) && sub_7100330328()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("前進", &pack);
            return;
        }
    }

    const sead::Vector3f stay_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(stay_pos, "TargetPos", -1);
    changeChild("静止", &pack);
}

bool BokoblinArrowAttack::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool BokoblinArrowAttack::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void BokoblinArrowAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBackWalkStartDist_s, "BackWalkStartDist");
    getStaticParam(&mBackWalkEndDist_s, "BackWalkEndDist");
    getStaticParam(&mCliffCheckDist_s, "CliffCheckDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
