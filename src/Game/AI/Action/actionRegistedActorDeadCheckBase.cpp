#include "Game/AI/Action/actionRegistedActorDeadCheckBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RegistedActorDeadCheckBase::RegistedActorDeadCheckBase(const InitArg& arg)
    : RegistedActorActionBase(arg) {}

RegistedActorDeadCheckBase::~RegistedActorDeadCheckBase() = default;

bool RegistedActorDeadCheckBase::init_(sead::Heap* heap) {
    if (!RegistedActorActionBase::init_(heap))
        return false;
    _408 = false;
    return true;
}

void RegistedActorDeadCheckBase::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorActionBase::enter_(params);
}

void RegistedActorDeadCheckBase::leave_() {
    RegistedActorActionBase::leave_();
}

void RegistedActorDeadCheckBase::loadParams_() {
    RegistedActorActionBase::loadParams_();
}

void RegistedActorDeadCheckBase::calc_() {
    RegistedActorActionBase::calc_();

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

bool RegistedActorDeadCheckBase::m32(ksys::act::BaseProcLink* link) {
    return true;
}

}  // namespace uking::action
