#include "Game/AI/AI/aiNPCTravelerRoot.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

NPCTravelerRoot::NPCTravelerRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCTravelerRoot::~NPCTravelerRoot() = default;

bool NPCTravelerRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _248 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCTravelerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

// NON_MATCHING: the original tests the Message reference for null before reading its type (cbz x1); a
// reference cannot be tested without `&message`, which clang drops (same for the other handleMessage_ with
// that test)
bool NPCTravelerRoot::handleMessage_(const ksys::Message* message) {
    if (NPCRoot::handleMessage_(message))
        return true;
    if (message->getType() == 0x8000077) {
        if (auto* value = static_cast<const f32*>(message->getUserData())) {
            _2a8 = ksys::Timer(*value, *value, -1.0f);
            return true;
        }
    }
    return false;
}

void NPCTravelerRoot::leave_() {
    NPCRoot::leave_();
}

void NPCTravelerRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mIsRiderChangableAction_s, "IsRiderChangableAction");
}

}  // namespace uking::ai
