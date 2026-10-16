#include "Game/Actor/Behavior/behaviorOnTrgGuardOffTargetXLinkCreateBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

OnTrgGuardOffTargetXLinkCreateBase::OnTrgGuardOffTargetXLinkCreateBase(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnTrgGuardOffTargetXLinkCreateBase::~OnTrgGuardOffTargetXLinkCreateBase() {
    ;
}

bool OnTrgGuardOffTargetXLinkCreateBase::init_(sead::Heap* heap) {
    return true;
}

void OnTrgGuardOffTargetXLinkCreateBase::calc() {
    if (mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_710116388C,
                               true)) {
        Unk_71012419b4 handle{};
        xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, &handle);
        m14(&handle);
    }
}

void OnTrgGuardOffTargetXLinkCreateBase::enter() {}

void OnTrgGuardOffTargetXLinkCreateBase::leave() {}

void OnTrgGuardOffTargetXLinkCreateBase::loadParams() {
    getStaticParam(&mKey_s, "Key");
}

}  // namespace uking::behavior
