#include "Game/AI/Action/actionRegistedActorAllDeadCheckBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RegistedActorAllDeadCheckBase::RegistedActorAllDeadCheckBase(const InitArg& arg)
    : RegistedActorSetActionBase(arg) {}

RegistedActorAllDeadCheckBase::~RegistedActorAllDeadCheckBase() = default;

bool RegistedActorAllDeadCheckBase::init_(sead::Heap* heap) {
    if (!RegistedActorSetActionBase::init_(heap))
        return false;
    _408 = false;
    return true;
}

void RegistedActorAllDeadCheckBase::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorSetActionBase::enter_(params);
}

void RegistedActorAllDeadCheckBase::leave_() {
    RegistedActorSetActionBase::leave_();
}

void RegistedActorAllDeadCheckBase::loadParams_() {
    RegistedActorSetActionBase::loadParams_();
}

void RegistedActorAllDeadCheckBase::calc_() {
    RegistedActorSetActionBase::calc_();

    for (auto& entry : _20.mEntries) {
        if (entry.link.hasProc()) {
            _408 = true;
            if (m32(&entry.link)) {
                if (mActor->checkLinkBasicSig())
                    mActor->emitBasicSigOff();
                return;
            }
        }
    }

    if (_408 && !mActor->checkLinkBasicSig())
        mActor->emitBasicSigOn();
}

bool RegistedActorAllDeadCheckBase::m32(ksys::act::BaseProcLink* link) {
    return true;
}

}  // namespace uking::action
