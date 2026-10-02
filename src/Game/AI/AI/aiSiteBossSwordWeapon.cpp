#include "Game/AI/AI/aiSiteBossSwordWeapon.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SiteBossSwordWeapon::SiteBossSwordWeapon(const InitArg& arg) : ChemicalWeaponRoot(arg) {}

SiteBossSwordWeapon::~SiteBossSwordWeapon() = default;

bool SiteBossSwordWeapon::init_(sead::Heap* heap) {
    return ChemicalWeaponRoot::init_(heap);
}

void SiteBossSwordWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalWeaponRoot::enter_(params);
    _f0 = false;
}

void SiteBossSwordWeapon::calc_() {
    ChemicalWeaponRoot::calc_();
}

void SiteBossSwordWeapon::leave_() {
    ChemicalWeaponRoot::leave_();
}

void SiteBossSwordWeapon::loadParams_() {
    WeaponRootAI::loadParams_();
}

// NON_MATCHING: the original null-checks the message reference (`cbz x1`; see lane2 log s17)
bool SiteBossSwordWeapon::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x8000059) {
        _f0 = true;
        return true;
    }
    if (message.getType() == 0x800005a) {
        _f0 = false;
        return true;
    }
    return ChemicalWeaponRoot::handleMessage_(message);
}

bool SiteBossSwordWeapon::m41() {
    return _f0 && ChemicalWeaponRoot::m41();
}

bool SiteBossSwordWeapon::m42() {
    return _f0 && ChemicalWeaponRoot::m42();
}

}  // namespace uking::ai
