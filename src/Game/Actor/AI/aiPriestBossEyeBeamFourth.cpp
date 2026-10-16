#include "Game/Actor/AI/aiPriestBossEyeBeamFourth.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossEyeBeamFourth::PriestBossEyeBeamFourth(const InitArg& arg) : PriestBossEyeBeam(arg) {}

PriestBossEyeBeamFourth::~PriestBossEyeBeamFourth() = default;

bool PriestBossEyeBeamFourth::init_(sead::Heap* heap) {
    return PriestBossEyeBeam::init_(heap);
}

void PriestBossEyeBeamFourth::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossEyeBeam::enter_(params);
    _120 = false;
    _121 = false;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void PriestBossEyeBeamFourth::leave_() {
    PriestBossEyeBeam::leave_();
}

void PriestBossEyeBeamFourth::loadParams_() {
    PriestBossEyeBeam::loadParams_();
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mSearchEndAngle_s, "SearchEndAngle");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossEyeBeamFourth::m34() {
    m47(getPlayerPosition());
}

sead::SafeString PriestBossEyeBeamFourth::m46() {
    return "FourthBeam";
}

void PriestBossEyeBeamFourth::m47(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "AimTargetPos", -1);
    params.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("索敵", &params);
}

void PriestBossEyeBeamFourth::m48(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("速攻照準", &params);
}

// 0x7100515a24
// NON_MATCHING: stack slots only (the original puts `pos` at sp + 0 and the SafeString temporaries above it)
void PriestBossEyeBeamFourth::calc_() {
    if (m35())
        return;
    *mDestinationPos_a = mActor->getMtx().getTranslation();
    sead::Vector3f pos;
    m36(&pos);
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("索敵")) {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5F6FC(sead::Vector3f::zero);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
            }
            if (!_120) {
                sead::Matrix34f mtx = sead::Matrix34f::ident;
                mActor->sub_71011D57F8(&mtx, "Spine_1");
                if (m40(mtx, getPlayerPosition(), static_cast<f32>(*mSearchEndAngle_s), 180.0f)) {
                    m42(pos);
                    return;
                }
                setFinished();
                return;
            }
            if (!_121) {
                auto* meta = sead::DynamicCast<Unk_7102450fa8>(
                    *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
                if (meta)
                    meta->_444 = true;
            }
            setFinished();
        } else if (isCurrentChild("照準")) {
            if (!_120) {
                m43();
                return;
            }
            if (!_121) {
                auto* meta = sead::DynamicCast<Unk_7102450fa8>(
                    *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
                if (meta)
                    meta->_444 = true;
            }
            setFinished();
        } else if (isCurrentChild("速攻照準") || isCurrentChild("チャージ")) {
            m44(pos);
        } else if (isCurrentChild("発射")) {
            m38(pos);
            m45();
        } else if (isCurrentChild("待機")) {
            m41();
            setFinished();
        }
        return;
    }

    if (isCurrentChild("索敵")) {
        if (sub_710051600C()) {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            if (player.x_12())
                _121 = true;
            _120 = true;
        }
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        mActor->sub_71011D57F8(&mtx, "Spine_1");
        if (m40(mtx, getPlayerPosition(), static_cast<f32>(*mSearchEndAngle_s), 180.0f) &&
            !sub_710051600C()) {
            if (auto* controller = mActor->getCharacterController()) {
                controller->sub_7100F5F6FC(sead::Vector3f::zero);
                controller->sub_7100F5FB24(sead::Vector3f::zero);
            }
            m42(pos);
        }
    } else if (isCurrentChild("照準") && sub_710051600C()) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (player.x_12())
            _121 = true;
        _120 = true;
    }

    const bool is_aiming = isCurrentChild("索敵") || isCurrentChild("照準");
    child = getCurrentChild();
    if (is_aiming) {
        child->setDynamicParam(pos, "AimTargetPos");
        getCurrentChild()->setDynamicParam(getPlayerPosition(), "TargetPos");
    } else {
        child->setDynamicParam(pos, "TargetPos");
    }
}

// NON_MATCHING: the final compare branches to the `true` block at the end (the original falls through to it).
// 0x710051600c (placeholder name): the StandEyeBeamFoot animation is playing and not at its last frame yet
bool PriestBossEyeBeamFourth::sub_710051600C() {
    auto* list = mActor->getASList();
    if (list && list->x_1(0, 0) == "StandEyeBeamFoot") {
        const f32 frame = list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
        if (frame < list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C))
            return true;
    }
    return false;
}

}  // namespace uking::ai
