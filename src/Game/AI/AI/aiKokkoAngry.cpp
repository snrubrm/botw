#include "Game/AI/AI/aiKokkoAngry.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KokkoAngry::KokkoAngry(const InitArg& arg) : CreateActorWithTarget(arg) {}

KokkoAngry::~KokkoAngry() = default;

bool KokkoAngry::init_(sead::Heap* heap) {
    return CreateActorWithTarget::init_(heap);
}

void KokkoAngry::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActorWithTarget::enter_(params);
}

void KokkoAngry::leave_() {
    CreateActorWithTarget::leave_();
}

void KokkoAngry::loadParams_() {
    CreateActorWithTarget::loadParams_();
}

bool KokkoAngry::m36() {
    if (CreateActorWithTarget::m36() &&
        mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8)) {
        return true;
    }
    return false;
}

}  // namespace uking::ai
