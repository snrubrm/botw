#include "Game/AI/Behavior/behaviorCharacterControllerFormChange.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::behavior {

CharacterControllerFormChange::CharacterControllerFormChange(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

CharacterControllerFormChange::~CharacterControllerFormChange() = default;

void CharacterControllerFormChange::m7() {}

void CharacterControllerFormChange::m8() {
    auto* cc = mActor->getCharacterController();
    _38 = -1;
    if (!cc)
        return;
    _38 = cc->_224;
    if (_3c < 0 || _38 == _3c)
        return;
    cc->sub_7100F5F270(_3c);
}

void CharacterControllerFormChange::m9() {
    if (!*mIsRestoreWhenLeave_s)
        return;
    auto* cc = mActor->getCharacterController();
    if (!cc)
        return;
    if (cc->_224 != _38)
        cc->sub_7100F5F270(_38);
}

void CharacterControllerFormChange::loadParams() {
    getStaticParam(&mEnterState_s, "EnterState");
    getStaticParam(&mIsRestoreWhenLeave_s, "IsRestoreWhenLeave");
}

}  // namespace uking::behavior
