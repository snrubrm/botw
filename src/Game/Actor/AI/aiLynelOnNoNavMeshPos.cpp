#include "Game/Actor/AI/aiLynelOnNoNavMeshPos.h"
#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LynelOnNoNavMeshPos::LynelOnNoNavMeshPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelOnNoNavMeshPos::~LynelOnNoNavMeshPos() = default;

bool LynelOnNoNavMeshPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack slots of the ground normal and the nav position (the original shares them with the param pack).
void LynelOnNoNavMeshPos::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mJumpTimer_s;
    _60.mTimer = ksys::Timer(time, time);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const auto& target = sub_71005D9330(mActor);
    const f32 distance = sead::Vector2f(pos.x - target.x, pos.z - target.z).length();

    if (auto* controller = mActor->getCharacterController()) {
        const f32 min_up = std::cos(*mHeavySlopeAngle_s);
        sead::Vector3f normal;
        // On a heavy slope: the ground normal (or else the actor's up axis) is steeper than HeavySlopeAngle.
        if ((controller->sub_7100F5F234(&normal) && normal.y < min_up) ||
            mActor->getMtx()(1, 1) < min_up) {
            if (!(*mNoJumpDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) >= distance)) {
                if (!(*mHyperJumpDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) < distance)) {
                    const s32 state = sub_71005D9744(mActor);
                    if (state == 5 || state == 2) {
                        if (auto* nav = mActor->m45()) {
                            sead::Vector3f nav_pos;
                            if (nav->sub_7100F76078(&nav_pos, sub_71005D9330(mActor), 2.0f)
                                    .sub_7100F7EB40()) {
                                ksys::act::ai::InlineParamPack pack;
                                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                                changeChild("ジャンプ", &pack);
                                return;
                            }
                        }
                    }
                }
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("超ジャンプ", &pack);
                return;
            }
        }
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘", &pack);
}

// NON_MATCHING: stack slots of the ground normal / nav position, the reused child vtable load and one
// compare form (cset lt) in the jump check.
void LynelOnNoNavMeshPos::calc_() {
    _60.sub_7100D3BCE4();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (!isCurrentChild("戦闘")) {
            setFinished();
            return;
        }

        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const auto& target = sub_71005D9330(mActor);
        const f32 distance = sead::Vector2f(pos.x - target.x, pos.z - target.z).length();
        if (!(*mHyperJumpDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) < distance)) {
            const s32 state = sub_71005D9744(mActor);
            if (state == 5 || state == 2) {
                if (auto* nav = mActor->m45()) {
                    sead::Vector3f nav_pos;
                    if (nav->sub_7100F76078(&nav_pos, sub_71005D9330(mActor), 2.0f).sub_7100F7EB40()) {
                        ksys::act::ai::InlineParamPack pack;
                        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                        changeChild("ジャンプ", &pack);
                        return;
                    }
                }
            }
        }

        if (auto* controller = mActor->getCharacterController()) {
            const f32 min_up = std::cos(*mHeavySlopeAngle_s);
            sead::Vector3f normal;
            if ((controller->sub_7100F5F234(&normal) && normal.y < min_up) ||
                mActor->getMtx()(1, 1) < min_up) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("超ジャンプ", &pack);
                return;
            }
        }

        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("ジャンプ", &pack);
        return;
    }

    if (child->isChangeable() && isCurrentChild("戦闘")) {
        const f32 timer = _60.mTimer.value;
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const auto& target = sub_71005D9330(mActor);
        const f32 distance = sead::Vector2f(pos.x - target.x, pos.z - target.z).length();

        bool heavy_slope = false;
        if (auto* controller = mActor->getCharacterController()) {
            const f32 min_up = std::cos(*mHeavySlopeAngle_s);
            sead::Vector3f normal;
            if (controller->sub_7100F5F234(&normal) && normal.y < min_up)
                heavy_slope = true;
            else
                heavy_slope = mActor->getMtx()(1, 1) < min_up;
        }

        if (timer <= sead::Mathf::epsilon() ||
            *mNoJumpDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) < distance || heavy_slope) {
            bool jumped = false;
            if (!(*mHyperJumpDist_s + sub_71007320F0(mActor, *mWeaponIdx_s) < distance)) {
                const s32 state = sub_71005D9744(mActor);
                if (state == 5 || state == 2) {
                    if (auto* nav = mActor->m45()) {
                        sead::Vector3f nav_pos;
                        if (nav->sub_7100F76078(&nav_pos, sub_71005D9330(mActor), 2.0f)
                                .sub_7100F7EB40()) {
                            ksys::act::ai::InlineParamPack pack;
                            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                            changeChild("ジャンプ", &pack);
                            jumped = true;
                        }
                    }
                }
            }
            if (!jumped && heavy_slope) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("超ジャンプ", &pack);
            }
        }
    }

    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void LynelOnNoNavMeshPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelOnNoNavMeshPos::loadParams_() {
    getStaticParam(&mJumpTimer_s, "JumpTimer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mHeavySlopeAngle_s, "HeavySlopeAngle");
    getStaticParam(&mNoJumpDist_s, "NoJumpDist");
    getStaticParam(&mHyperJumpDist_s, "HyperJumpDist");
}

}  // namespace uking::ai
