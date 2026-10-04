#include "Game/AI/Action/actionAirOctaReactionKorog.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

AirOctaReactionKorog::AirOctaReactionKorog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaReactionKorog::~AirOctaReactionKorog() = default;

bool AirOctaReactionKorog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaReactionKorog::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_4c, mActor);
    playAS(mAS_s.cstr(), false, 0, 0, -1.0f);
    if (auto* damage_mgr = sub_710072BA90(mActor))
        damage_mgr->m30(&_40);
    else
        _40.set(sead::Vector3f::ez);
    _40 = -_40;
}

void AirOctaReactionKorog::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaReactionKorog::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAS_s, "AS");
}

void AirOctaReactionKorog::calc_() {
    sub_710089A78();
    auto* chemical = mActor->sub_71011D8A44(0);
    if (!chemical || !(chemical->_bc & 0x4000))
        setFinished();
    if (isFinishedAS(0, 0)) {
        switch (*mEndState_s) {
        case 2:
            mFlags.set(Flag::Changeable);
            break;
        case 1:
            setFinished();
            break;
        }
    }
}

void AirOctaReactionKorog::sub_710089A78() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Vector3f impulse = -_40;
    impulse.normalize();
    impulse *= body->getMass();
    impulse *= *mSpeed_s;
    body->applyLinearImpulse(impulse);
}

}  // namespace uking::action
