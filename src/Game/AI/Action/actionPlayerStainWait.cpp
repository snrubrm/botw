#include "Game/AI/Action/actionPlayerStainWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/System/SeadController.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

PlayerStainWait::PlayerStainWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerStainWait::~PlayerStainWait() = default;

bool PlayerStainWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerStainWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    if (mActor->getASList()->x_1(0, 0) != "DemoWait")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DemoWait", true, -1.0f);
    _78 = mActor->getMtx();
    _20 = -1;
}

void PlayerStainWait::leave_() {
    mActor->setMtx(_78, false, true);
    ksys::act::ActorConstDataAccess accessor;
    auto* armors = mActor->getArmors();
    for (int i = 0; i < 3; ++i) {
        ksys::act::acquireActor(&armors->getPartsLink(i), &accessor);
        _28.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000ba), nullptr, true);
    }
}

// NON_MATCHING: matrix multiplication schedules translation lanes in different registers.
void PlayerStainWait::calc_() {
    f32 angle = 0.0f;
    if (auto* controller = ksys::SeadController::getInstance())
        angle = controller->getRightStick().x * 0.15f;
    sead::Matrix34f rotation;
    rotation.makeR({0.0f, angle, 0.0f});
    sead::Matrix34f mtx;
    mtx.setMul(mActor->getMtx(), rotation);
    mActor->setMtx(mtx, false, false);
    const s32 material = ksys::gdt::getFlag_ColorChange_MaterialIndex(false);
    if (material > 0 && _20 != material) {
        ksys::act::ActorConstDataAccess accessor;
        auto* armors = mActor->getArmors();
        for (int i = 0; i < 3; ++i) {
            ksys::act::acquireActor(&armors->getPartsLink(i), &accessor);
            _28.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000b9),
                            nullptr, true);
        }
        _20 = material;
    }
    setFinished();
}

bool PlayerStainWait::isChangeable() const {
    return false;
}

}  // namespace uking::action
