#include "Game/AI/AI/aiGolemReaction.h"
#include "Game/AI/aiUnk_7102450410.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GolemReaction::GolemReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemReaction::~GolemReaction() = default;

bool GolemReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the two damage type compares (0x1b / 0x16) are emitted in the opposite order
void GolemReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    _120 = true;
    _128.mTimer = ksys::Timer(0, 0);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    if (*mGolemClimbedTime_a > 0.0f) {
        *mGolemClimbedTime_a = sead::Mathf::clampMin(
            *mGolemClimbedTime_a, f32(*mClimbLimitTime_s - *mClampRestClimbTime_s));
    }

    auto* actor = mActor;
    auto* life = actor->getLife();
    if (life && *life <= 0) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("死亡");
        return;
    }

    if (sub_71005DD798(mActor, 0x13, nullptr, 0, 0)) {
        sub_71003FE9C4();
        sub_7100708FF0(mActor, 30.0f);
        changeChild("起き上がる");
        return;
    }

    if (sead::DynamicCast<dmg::DamageManager>(actor->getDamageMgr())) {
        if (sub_71003FEAB0())
            return;

        auto* damage_mgr = mActor->getDamageMgr();
        if (damage_mgr && damage_mgr->getField54() <= 0x15 && *mGolemClimbedTime_a > 0.0f) {
            changeChild("小ダメージ");
            return;
        }

        damage_mgr = mActor->getDamageMgr();
        const s32 type = damage_mgr ? damage_mgr->getField54() : -1;
        if (type != 0x1b && type != 0x16 && !sub_71003FEC7C()) {
            changeChild("小ダメージ");
            return;
        }
    }

    auto* damage_mgr = mActor->getDamageMgr();
    if (damage_mgr && damage_mgr->getField50() == 4)
        _128.mTimer.reset(*mIgnoreBombTime_s);
    changeChild("ふっとび");
}

void GolemReaction::leave_() {
    sub_7100708FF0(mActor, 200.0f);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
}

void GolemReaction::loadParams_() {
    getStaticParam(&mClimbLimitTime_s, "ClimbLimitTime");
    getStaticParam(&mClampRestClimbTime_s, "ClampRestClimbTime");
    getStaticParam(&mIgnoreBombTime_s, "IgnoreBombTime");
    getStaticParam(&mRightArmTgtBodyName_s, "RightArmTgtBodyName");
    getStaticParam(&mLeftArmTgtBodyName_s, "LeftArmTgtBodyName");
    getStaticParam(&mBreakArmLXLinkKey_s, "BreakArmLXLinkKey");
    getStaticParam(&mBodyArmLName1_s, "BodyArmLName1");
    getStaticParam(&mBodyArmLName2_s, "BodyArmLName2");
    getStaticParam(&mChmArmLName_s, "ChmArmLName");
    getStaticParam(&mArmLMaterialName_s, "ArmLMaterialName");
    getStaticParam(&mBreakArmRXLinkKey_s, "BreakArmRXLinkKey");
    getStaticParam(&mBodyArmRName1_s, "BodyArmRName1");
    getStaticParam(&mBodyArmRName2_s, "BodyArmRName2");
    getStaticParam(&mChmArmRName_s, "ChmArmRName");
    getStaticParam(&mArmRMaterialName_s, "ArmRMaterialName");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool GolemReaction::sub_71003FEC7C() {
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (damage_mgr->getField54() == 21 || damage_mgr->checkDamageFlags(0))
            return true;
    }
    auto* controller = sead::DynamicCast<Unk_7102450410>(
        *static_cast<Unk_71025afb58**>(mGolemChemicalController_a));
    return sub_71007090F4(controller);
}

void GolemReaction::sub_71003FE9C4() {
    auto* damage = mActor->getDamageMgr();
    if (damage && damage->getField50() == 4) {
        bool right = false;
        bool left = false;
        sub_71003FF3F8(&right, &left);
        if (left) {
            sub_71003FF79C(mBodyArmLName1_s, mBodyArmLName2_s, "", mLeftArmTgtBodyName_s,
                           mChmArmLName_s, mArmLMaterialName_s, mBreakArmLXLinkKey_s);
        }
        if (right) {
            sub_71003FF79C(mBodyArmRName1_s, mBodyArmRName2_s, "", mRightArmTgtBodyName_s,
                           mChmArmRName_s, mArmRMaterialName_s, mBreakArmRXLinkKey_s);
        }
    }
}

}  // namespace uking::ai
