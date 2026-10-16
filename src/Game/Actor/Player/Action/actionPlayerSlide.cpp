#include "Game/Actor/Player/Action/actionPlayerSlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerSlide::PlayerSlide(const InitArg& arg) : PlayerAction(arg) {}

PlayerSlide::~PlayerSlide() = default;

// NON_MATCHING: block placement of the LandDamage early return (the original keeps it inline after the life check).
void PlayerSlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x80);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);

    auto* life = mActor->getLife();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (life && *life <= 0) {
        player->switchToAnimSequenceMaybe("LandDamage", true, -1.0f);
        return;
    }

    const auto angle = player->x_5();
    if (ksys::util::sub_71011EE4C0(s64(player->_1c8c) - s64(angle.value)) <= 0x37ffffff) {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Slide", true, -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_20c8 = *mFrontSlideMaxSpeedF_s;
    } else {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Slide", true, -1.0f);
        static_cast<ksys::act::Player*>(mActor)->_20c8 = *mBackSlideMaxSpeedF_s;
    }

    // C++14 evaluation order: the original evaluates the destination first
    static_cast<ksys::act::Player*>(mActor)->_1844.operator=(
        ksys::Timer(*mEffectContTime_s, *mEffectContTime_s));
    // C++14 evaluation order: the original evaluates the destination first
    static_cast<ksys::act::Player*>(mActor)->_1850.operator=(
        ksys::Timer(*mUpKeyInvalidTime_s, *mUpKeyInvalidTime_s));
    static_cast<ksys::act::Player*>(mActor)->_185c = ksys::Timer(5.0f, 5.0f);
    static_cast<ksys::act::Player*>(mActor)->_1810 = {0, 0, 0};
    static_cast<ksys::act::Player*>(mActor)->_20bc.value = 0;
    static_cast<ksys::act::Player*>(mActor)->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->_1c68.value = static_cast<ksys::act::Player*>(mActor)->_1c8c;
    static_cast<ksys::act::Player*>(mActor)->_20e4 = 0.0f;
    static_cast<ksys::act::Player*>(mActor)->_17f1 = false;

    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E754(true);
        controller->sub_7100F60E80(true);
        controller->_48->_8c = 1;
        f32* slip = controller->_48->sub_7100F68F40();
        slip[2] = *mMaxSlipSpeed_s;
        slip[3] = *mSlipSpeedAdd_s;
        slip[0] = *mLimitAngleDegStart_s;
    }
}

void PlayerSlide::leave_() {
    _60.fade();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60E80(false);
        controller->_48->_8c = 0;
        if (!static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround()) {
            sead::Vector3f velocity;
            controller->sub_7100F5F598(&velocity);
            auto* player = static_cast<ksys::act::Player*>(mActor);
            const f32 speed =
                sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z) / 30.0f;
            player->_20bc.value = speed;
            player->_20bc.prev_value = speed;
            static_cast<ksys::act::Player*>(mActor)->_1c68 =
                ksys::util::Unk_7101EC6BAC(sead::Mathf::atan2Idx(velocity.x, velocity.z));
        }
    }
}

bool PlayerSlide::isChangeable() const {
    if (_1c)
        return true;
    return static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(2);
}

void PlayerSlide::loadParams_() {
    getStaticParam(&mUpKeyInvalidTime_s, "UpKeyInvalidTime");
    getStaticParam(&mFrontSlideMaxSpeedF_s, "FrontSlideMaxSpeedF");
    getStaticParam(&mBackSlideMaxSpeedF_s, "BackSlideMaxSpeedF");
    getStaticParam(&mLimitAngleDegStart_s, "LimitAngleDegStart");
    getStaticParam(&mMaxSlipSpeed_s, "MaxSlipSpeed");
    getStaticParam(&mSlipSpeedAdd_s, "SlipSpeedAdd");
    getStaticParam(&mSlipSpeedDec_s, "SlipSpeedDec");
    getStaticParam(&mEffectContTime_s, "EffectContTime");
}

void PlayerSlide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
