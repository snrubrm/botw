#include "Game/Actor/AI/aiBokoblinArrowAttack.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

BokoblinArrowAttack::BokoblinArrowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

inline void BokoblinArrowAttack::changeToStay() {
    const sead::Vector3f target = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("静止", &pack);
}

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

    changeToStay();
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

// NON_MATCHING: stack slots of the probe direction and the target copies (shared with the param pack in the original).
void BokoblinArrowAttack::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!(isCurrentChild("後ずさり") || isCurrentChild("前進")) || !getCurrentChild()->isFailed()) {
            setFinished();
            return;
        }
        changeToStay();
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("静止")) {
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
            }
        }
    } else if (isCurrentChild("後ずさり")) {
        const sead::Vector3f target = *mTargetPos_d;
        const sead::Vector3f& pos = mActor->getMtx().getTranslation();
        if (sead::Vector2f(target.x - pos.x, target.z - pos.z).length() >= *mBackWalkEndDist_s)
            changeToStay();
    } else if (isCurrentChild("前進")) {
        auto* actor = mActor;
        const sead::Vector3f& front = actor->getMtx().getBase(2);
        const sead::Vector3f dir(front.x, 0.0f, front.z);
        if (sub_710072FEC4(actor, dir, 0.5f, nullptr, true, nullptr) || !sub_7100330328() ||
            !sub_710072E1B4(mActor, false)) {
            changeToStay();
        }
    }
}

// NON_MATCHING: the weapon position is kept in integer registers and stored to the stack late in the original (stack
// layout of the ray end points).
// Whether the line from the equipped weapon towards the target (at most 25) hits the ground.
bool BokoblinArrowAttack::sub_7100330328() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    const s32 idx = *mWeaponIdx_s;
    auto* weapon = sead::DynamicCast<ksys::act::Actor>(enemy->getWeapons()->getEquippedWeapon(idx));
    if (!weapon)
        return false;

    const sead::Vector3f start = weapon->getMtx().getTranslation();
    sead::Vector3f dir = *mTargetPos_d - start;
    const f32 length = dir.normalize();
    const sead::Vector3f end = start + dir * sead::Mathf::min(length, 25.0f);
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::Arrow);
    query.setStartAndEnd(start, end);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.worldRayCast(ksys::phys::ContactLayerType::Entity);
    return query.hasHit();
}

}  // namespace uking::ai
