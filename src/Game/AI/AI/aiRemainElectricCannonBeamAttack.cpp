#include "Game/AI/AI/aiRemainElectricCannonBeamAttack.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

RemainElectricCannonBeamAttack::RemainElectricCannonBeamAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainElectricCannonBeamAttack::~RemainElectricCannonBeamAttack() {
    if (_38.hasProc())
        _38.reset();
    if (_48.hasProc())
        _48.reset();
}

bool RemainElectricCannonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack slot of the MessageType temporary (sp+4 in the original; same known issue as
// OctarockEscape / AreaActorObserve)
void RemainElectricCannonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710053E864();
    if (_38.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        _58.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000085), nullptr,
                        true);
    }
    changeChild("溜め");
    mFlags.set(Flag::Changeable);
}

void RemainElectricCannonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonBeamAttack::loadParams_() {}

}  // namespace uking::ai
