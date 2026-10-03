#include "Game/AI/Action/actionBindActionForManyActor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BindActionForManyActor::BindActionForManyActor(const InitArg& arg) : BindAction(arg) {}

BindActionForManyActor::~BindActionForManyActor() = default;

bool BindActionForManyActor::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void BindActionForManyActor::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent())) {
        _e8.acquire(parent, false);
    } else if (!*mIsKeepParentActor_d || !_e8.hasProc()) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(
            sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr)));
        if (actor)
            _e8.acquire(actor, false);
        else
            setFailed();
    }
    BindAction::enter_(params);
    _f8 = true;
}

void BindActionForManyActor::leave_() {
    BindAction::leave_();
}

void BindActionForManyActor::loadParams_() {
    BindAction::loadParams_();
    getDynamicParam(&mIsKeepParentActor_d, "IsKeepParentActor");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

bool BindActionForManyActor::handleMessage_(const ksys::Message* message) {
    if (message && message->getBrokerId() == u32(-1) && message->getType() == 0x3000003) {
        m35();
        return true;
    }
    return false;
}

void BindActionForManyActor::calc_() {
    BindAction::calc_();

    if (_f8) {
        _f8 = false;
        return;
    }

    if (sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent()))
        mActor->resetConnectedCalcParent(false);

    if (!_e8.hasProc())
        setFailed();
}

void BindActionForManyActor::m32() {}

ksys::act::Actor* BindActionForManyActor::m33() {
    return sead::DynamicCast<ksys::act::Actor>(
        sead::DynamicCast<ksys::act::Actor>(_e8.getProc(nullptr, nullptr)));
}

}  // namespace uking::action
