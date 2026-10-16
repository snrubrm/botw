#include "Game/Actor/Behavior/behaviorOnChangeXLinkCreateTrgDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

OnChangeXLinkCreateTrgDrop::OnChangeXLinkCreateTrgDrop(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

OnChangeXLinkCreateTrgDrop::~OnChangeXLinkCreateTrgDrop() = default;

bool OnChangeXLinkCreateTrgDrop::init_(sead::Heap* heap) {
    return OnChangeXLinkCreate::init_(heap);
}

void OnChangeXLinkCreateTrgDrop::calc() {
    OnChangeXLinkCreate::calc();
}

void OnChangeXLinkCreateTrgDrop::enter() {
    OnChangeXLinkCreate::enter();
}

void OnChangeXLinkCreateTrgDrop::leave() {
    OnChangeXLinkCreate::leave();
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
