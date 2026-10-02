#include "Game/AI/Action/actionKokkoMove.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

KokkoMove::KokkoMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KokkoMove::~KokkoMove() = default;

bool KokkoMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KokkoMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KokkoMove::leave_() {
    auto* nav = mActor->m45();
    auto* controller = mActor->getCharacterController();
    if (!nav || !controller)
        return;
    if (!*mAvoidPlayer_s)
        nav->sub_7100F7D350();
    controller->sub_7100F5EDD8(1.0f);
    controller->sub_7100F5EDE0(0.0f);
    controller->sub_7100F5E7F0(0.0f);
}

void KokkoMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAngularSpeed_s, "AngularSpeed");
    getStaticParam(&mNavMeshGoalDistanceTolerance_s, "NavMeshGoalDistanceTolerance");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mAvoidPlayer_s, "AvoidPlayer");
    getStaticParam(&mUseLocalSteering_s, "UseLocalSteering");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void KokkoMove::calc_() {
    ksys::act::ai::Action::calc_();
}

bool KokkoMove::m32() {
    return false;
}

}  // namespace uking::action
