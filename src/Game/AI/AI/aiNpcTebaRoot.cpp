#include "Game/AI/AI/aiNpcTebaRoot.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

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

// NON_MATCHING: the original null-checks the message reference (`cbz x1`; see lane2 log s16)
bool NpcTebaRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x800000e) {
        _50 = true;
        return true;
    }
    return false;
}

void NpcTebaRoot::loadParams_() {
    getStaticParam(&mShowMessageLockonMinInterval_s, "ShowMessageLockonMinInterval");
    getStaticParam(&mApproachPlayerHeight_s, "ApproachPlayerHeight");
    getStaticParam(&mShowMessageDoDist_s, "ShowMessageDoDist");
}

}  // namespace uking::ai
