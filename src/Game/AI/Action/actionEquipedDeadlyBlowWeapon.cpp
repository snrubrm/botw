#include "Game/AI/Action/actionEquipedDeadlyBlowWeapon.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

EquipedDeadlyBlowWeapon::EquipedDeadlyBlowWeapon(const InitArg& arg) : EquipedAction(arg) {}

EquipedDeadlyBlowWeapon::~EquipedDeadlyBlowWeapon() = default;

bool EquipedDeadlyBlowWeapon::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedDeadlyBlowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    EquipedAction::enter_(params);
}

void EquipedDeadlyBlowWeapon::leave_() {
    EquipedAction::leave_();
}

void EquipedDeadlyBlowWeapon::loadParams_() {
    EquipedAction::loadParams_();
}

bool EquipedDeadlyBlowWeapon::handleMessage_(const ksys::Message* message) {
    if (message && message->getBrokerId() == u32(-1) && message->getType() == 0x80000e0) {
        if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor)) {
            if (weapon->_d38)
                weapon->_d38->sub_71002EF75C();
            return true;
        }
    }
    return false;
}

void EquipedDeadlyBlowWeapon::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
