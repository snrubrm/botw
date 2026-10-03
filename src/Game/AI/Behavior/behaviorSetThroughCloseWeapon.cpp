#include "Game/AI/Behavior/behaviorSetThroughCloseWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::behavior {

SetThroughCloseWeapon::SetThroughCloseWeapon(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetThroughCloseWeapon::~SetThroughCloseWeapon() = default;

bool SetThroughCloseWeapon::m6(sead::Heap* heap) {
    return true;
}

void SetThroughCloseWeapon::m7() {}

void SetThroughCloseWeapon::m8() {
    sub_71007A439C(mActor, &_28);
}

void SetThroughCloseWeapon::m9() {
    sub_71007A4440(mActor, &_28);
}

bool SetThroughCloseWeapon::Listener::m0(void* a1, void* a2, void* a3, void* a4, void* a5, void* a6,
                                         const ksys::act::Struct8Base* info) {
    return (info->_18 & 7) != 0;
}

void SetThroughCloseWeapon::loadParams() {

}

}  // namespace uking::behavior
