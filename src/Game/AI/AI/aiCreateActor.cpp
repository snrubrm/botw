#include "Game/AI/AI/aiCreateActor.h"

namespace uking::ai {

CreateActor::CreateActor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActor::~CreateActor() = default;

bool CreateActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActor::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003591E4(nullptr);
}

void CreateActor::leave_() {
    if (_58.isAllocatedOrFailed())
        _58.deleteProc();
}

void CreateActor::loadParams_() {
    getStaticParam(&mCreatePriorityState_s, "CreatePriorityState");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mActorName_s, "ActorName");
}

const sead::SafeString& CreateActor::m34() {
    return mActorName_s;
}

}  // namespace uking::ai
