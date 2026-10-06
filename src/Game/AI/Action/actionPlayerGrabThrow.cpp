#include "Game/AI/Action/actionPlayerGrabThrow.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayerGrabThrow::PlayerGrabThrow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(5);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(30);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GrabThrow", true, -1.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_1800 = player->_20bc.value * 30.0f;
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        sub_71005DC3F4(child);
}

void PlayerGrabThrow::leave_() {
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100887AC4())
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x100);
}

void PlayerGrabThrow::loadParams_() {
    getStaticParam(&mOverThrowSpeedYB_s, "OverThrowSpeedYB");
    getStaticParam(&mOverThrowSpeedFB_s, "OverThrowSpeedFB");
    getStaticParam(&mOverThrowSpeedYL_s, "OverThrowSpeedYL");
    getStaticParam(&mOverThrowSpeedFL_s, "OverThrowSpeedFL");
    getStaticParam(&mOverThrowInertiaRate_s, "OverThrowInertiaRate");
}

void PlayerGrabThrow::sub_71007F00D0() {
    sead::Vector3f position = sead::Vector3f::zero;
    sead::Vector3f direction;
    static_cast<ksys::act::Player*>(mActor)->_1b18.getBase(direction, 2);
    direction.normalize();
    const f32 speed = *mOverThrowSpeedFB_s + static_cast<ksys::act::Player*>(mActor)->_1800 * *mOverThrowInertiaRate_s;
    position += direction * speed;
    position.y += *mOverThrowSpeedYB_s;
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        sub_71005DC30C(child, position);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_d11 = 0;
    static_cast<ksys::act::Player*>(mActor)->_20f8 = 0;
    const auto& name = static_cast<ksys::act::Player*>(mActor)->getEquipmentTypeName(0);
    static_cast<ksys::act::Player*>(mActor)->_d30.copy(name);
    static_cast<ksys::act::Player*>(mActor)->m228(false);
}

void PlayerGrabThrow::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 zero = 0.0f;
    player->_20bc.chase(zero, 0.03f);
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        sub_71007F00D0();
        static_cast<ksys::act::Player*>(mActor)->_cec.reset(0x20);
    }
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerGrabThrow::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
