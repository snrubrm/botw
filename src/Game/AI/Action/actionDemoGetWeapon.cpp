#include "Game/AI/Action/actionDemoGetWeapon.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

DemoGetWeapon::DemoGetWeapon(const InitArg& arg) : DemoGetItem(arg) {}

DemoGetWeapon::~DemoGetWeapon() = default;

bool DemoGetWeapon::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetWeapon::loadParams_() {
    DemoGetItem::loadParams_();
}

bool DemoGetWeapon::oneShot_() {
    if (!DemoGetItem::oneShot_())
        return false;
    auto* actor = mActor;
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor)) {
        weapon->m202(true);
        weapon->m182();
        weapon->sub_71002EE8B0();
    }
    actor->getPhysics()->sub_7100FBD324(false, false);
    actor = mActor;
    if (auto* body = sub_7100EE5FE4(actor))
        body->setTransform(actor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
    return true;
}

}  // namespace uking::action
