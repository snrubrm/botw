#include "Game/AI/AI/aiDeadlyBlowWeaponRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::ai {

static const sead::SafeString sUnk_71023e1008 = "ChemFull";

DeadlyBlowWeaponRoot::DeadlyBlowWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

DeadlyBlowWeaponRoot::~DeadlyBlowWeaponRoot() = default;

bool DeadlyBlowWeaponRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void DeadlyBlowWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);

    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        auto* as_list = weapon->getASList();
        if (!as_list)
            return;
        _ec = as_list->x_1(0, 1) == sUnk_71023e1008 ? 4 : -1;
    }
    _e8 = false;

    auto* evt_mgr = ksys::evt::Manager::instance();
    if (!evt_mgr)
        return;
    auto* flow_mgr = evt_mgr->getEventFlowMgr();
    if (!flow_mgr)
        return;
    if (!_f8)
        _f8 = flow_mgr->loadSimple("Demo605_0", "Demo605_0");
    if (!_100)
        _100 = flow_mgr->loadSimple("Demo605_0", "Demo605_1");
}

void DeadlyBlowWeaponRoot::calc_() {
    WeaponRootAI::calc_();
    sub_710035C57C();
    sub_710035CE18();
}

void DeadlyBlowWeaponRoot::leave_() {
    WeaponRootAI::leave_();

    if (_f8) {
        if (auto* evt_mgr = ksys::evt::Manager::instance()) {
            if (auto* flow_mgr = evt_mgr->getEventFlowMgr()) {
                flow_mgr->unload(_f8);
                _f8 = nullptr;
            }
        }
    }
    if (_100) {
        if (auto* evt_mgr = ksys::evt::Manager::instance()) {
            if (auto* flow_mgr = evt_mgr->getEventFlowMgr()) {
                flow_mgr->unload(_100);
                _100 = nullptr;
            }
        }
    }
}

void DeadlyBlowWeaponRoot::loadParams_() {
    WeaponRootAI::loadParams_();
}

}  // namespace uking::ai
