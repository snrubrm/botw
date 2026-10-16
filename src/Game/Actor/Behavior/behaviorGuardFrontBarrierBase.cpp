#include "Game/Actor/Behavior/behaviorGuardFrontBarrierBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

GuardFrontBarrierBase::GuardFrontBarrierBase(const InitArg& arg) : OnStateXLinkCreate(arg) {}

GuardFrontBarrierBase::~GuardFrontBarrierBase() = default;

bool GuardFrontBarrierBase::init_(sead::Heap* heap) {
    return OnStateXLinkCreate::init_(heap);
}

void GuardFrontBarrierBase::calc() {
    OnStateXLinkCreate::calc();
    if (!m14()) {
        sub_7100631CAC();
        return;
    }
    if (_58.sub_7101241B6C())
        return;
    if (mKey_s.isEmpty())
        return;
    xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, &_58);
}

void GuardFrontBarrierBase::enter() {
    OnStateXLinkCreate::enter();
}

void GuardFrontBarrierBase::leave() {
    OnStateXLinkCreate::leave();
}

void GuardFrontBarrierBase::loadParams() {
    OnStateXLinkCreate::loadParams();
}

bool GuardFrontBarrierBase::m14() {
    return mActor->getASList()->x(14, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                  true);
}

}  // namespace uking::behavior
