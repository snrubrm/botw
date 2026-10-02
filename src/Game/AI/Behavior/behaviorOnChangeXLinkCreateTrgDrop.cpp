#include "Game/AI/Behavior/behaviorOnChangeXLinkCreateTrgDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

OnChangeXLinkCreateTrgDrop::OnChangeXLinkCreateTrgDrop(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

OnChangeXLinkCreateTrgDrop::~OnChangeXLinkCreateTrgDrop() = default;

bool OnChangeXLinkCreateTrgDrop::m6(sead::Heap* heap) {
    return OnChangeXLinkCreate::m6(heap);
}

void OnChangeXLinkCreateTrgDrop::m7() {
    OnChangeXLinkCreate::m7();
}

void OnChangeXLinkCreateTrgDrop::m8() {
    OnChangeXLinkCreate::m8();
}

void OnChangeXLinkCreateTrgDrop::m9() {
    OnChangeXLinkCreate::m9();
}

void OnChangeXLinkCreateTrgDrop::loadParams() {
    OnChangeXLinkCreate::loadParams();
    mActor->getRootAi()->getAITreeVariable2(&mIsDrop_a, "IsDrop");
}

void OnChangeXLinkCreateTrgDrop::m14() {
    if (*mIsDrop_a)
        xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, nullptr);
}

}  // namespace uking::behavior
