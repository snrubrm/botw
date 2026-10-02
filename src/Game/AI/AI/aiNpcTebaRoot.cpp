#include "Game/AI/AI/aiNpcTebaRoot.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

NpcTebaRoot::NpcTebaRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NpcTebaRoot::~NpcTebaRoot() = default;

bool NpcTebaRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NpcTebaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NpcTebaRoot::leave_() {
    if (auto* client = mActor->getAttention()->getClientByName("Ride"))
        client->disable();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void NpcTebaRoot::loadParams_() {
    getStaticParam(&mShowMessageLockonMinInterval_s, "ShowMessageLockonMinInterval");
    getStaticParam(&mApproachPlayerHeight_s, "ApproachPlayerHeight");
    getStaticParam(&mShowMessageDoDist_s, "ShowMessageDoDist");
}

}  // namespace uking::ai
