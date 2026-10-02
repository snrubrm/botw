#include "Game/AI/AI/aiKorokPinWheelRoot.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

KorokPinWheelRoot::KorokPinWheelRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (trivial members only);
// written as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
KorokPinWheelRoot::~KorokPinWheelRoot() { ; }

bool KorokPinWheelRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokPinWheelRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _48.value = *mRotSpd_s;
    _48.prev_value = *mRotSpd_s;
    sub_710073FA90(&_54, mActor);
}

void KorokPinWheelRoot::calc_() {
    _48.updateStats();
    const sead::Vector3f& player_pos = getPlayerPosition();
    sead::Vector3f dir = player_pos - mActor->getMtx().getTranslation();
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    if (dir.x * dir.x + dir.z * dir.z > *mLength_s * *mLength_s) {
        sead::Vector3f up;
        body->getTransform().getBase(up, 1);
        sub_710073FA94(&_54, mActor);
        dir.normalize();
        sub_710074006C(&_54, dir, up, true, 0.16f, _48.value, _48.value / 10.0f);
        sub_7100740E8C(_54, body);
    } else {
        body->setAngularVelocity(sead::Vector3f::zero);
    }
}

void KorokPinWheelRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokPinWheelRoot::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mLength_s, "Length");
}

}  // namespace uking::ai
