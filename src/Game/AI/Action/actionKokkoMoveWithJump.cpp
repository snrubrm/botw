#include "Game/AI/Action/actionKokkoMoveWithJump.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

KokkoMoveWithJump::KokkoMoveWithJump(const InitArg& arg) : KokkoMove(arg) {}

KokkoMoveWithJump::~KokkoMoveWithJump() = default;

bool KokkoMoveWithJump::init_(sead::Heap* heap) {
    return KokkoMove::init_(heap);
}

void KokkoMoveWithJump::enter_(ksys::act::ai::InlineParamPack* params) {
    KokkoMove::enter_(params);
    auto* controller = mActor->getCharacterController();
    if (!controller || !mActor->m45()) {
        setFailed();
        return;
    }
    if (*mIsJump_d && controller->sub_7100F5F0E4() == ksys::act::MotionType::_0) {
        controller->sub_7100F60398(*mJumpDir_s * (*mJumpSpeed_s * controller->sub_7100F60370()));
    }
}

void KokkoMoveWithJump::leave_() {
    KokkoMove::leave_();
}

void KokkoMoveWithJump::loadParams_() {
    KokkoMove::loadParams_();
    getStaticParam(&mJumpSpeed_s, "JumpSpeed");
    getStaticParam(&mJumpDir_s, "JumpDir");
    getDynamicParam(&mIsJump_d, "IsJump");
}

void KokkoMoveWithJump::calc_() {
    KokkoMove::calc_();
}

bool KokkoMoveWithJump::m32() {
    return *mIsJump_d;
}

}  // namespace uking::action
