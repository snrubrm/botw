#include "Game/AI/AI/aiDeadlyBlowWeaponRoot.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/UI/uiManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::ai {

static const sead::SafeString sUnk_71023e0fe8 = "ChemCharge";
static const sead::SafeString sUnk_71023e0ff8 = "ChemChargeFromHalf";
static const sead::SafeString sUnk_71023e1008 = "ChemFull";
static const sead::SafeString sUnk_71023e1018 = "ChemFullFromHalf";
static const sead::SafeString sUnk_71023e1028 = "ChemHalf";

// inline-only in the original; name is a guess (repeated six times in sub_710035C57C): starts the animation `name`
// on the weapon's ASList if the weapon has that animation.
static void startAnimation(const sead::SafeString name, ksys::act::Actor* actor) {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(actor)) {
        if (auto* as_list = weapon->getASList()) {
            if (as_list->sub_710115AA68(name))
                as_list->startAnimationMaybe(-1.0f, -1.0f, name, 0, 1, true);
        }
    }
}

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

bool DeadlyBlowWeaponRoot::isWeaponM213() const {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    return weapon && weapon->m213();
}

// NON_MATCHING: the original branches directly on the cast / m213() results of the repeated
// `weapon && weapon->m213()` check; ours merges them into one bool (extra `eor`)
bool DeadlyBlowWeaponRoot::m41() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!isWeaponM213()) {
        if (weapon && !_e8 && !weapon->m153() && weapon->m214() &&
            (weapon->_c20._0 == 0 || weapon->_c20._0 == 2)) {
            return true;
        }
    }
    if (!isWeaponM213()) {
        if (weapon && !_e8 && (weapon->_e50 & 2) && weapon->m214())
            return true;
    }
    return false;
}

bool DeadlyBlowWeaponRoot::m42() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return false;
    if (!isWeaponM213()) {
        if (_e8 && !weapon->_d08 && !weapon->m183())
            return true;
    }
    if (!isWeaponM213()) {
        if (!weapon->_d08 && !weapon->m183() && _e8 && !(weapon->_e50 & 2))
            return true;
    }
    if (!isWeaponM213()) {
        if (_e8 && weapon->m183() && (weapon->_c20._14 & 8) && weapon->m232() && !weapon->m214())
            return true;
    }
    return false;
}

// NON_MATCHING: only the last store: the original branches on `enabled` and stores the constant 1 / 0 (`if (enabled)
// x = true; else x = false;`), ours stores the bool
void DeadlyBlowWeaponRoot::sub_710035C57C() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    auto* as_list = weapon->getASList();
    if (!as_list)
        return;

    if (auto* parent = weapon->getParentActor()) {
        if (auto* chemical = parent->getChemicalStuff(); chemical && chemical->_c0 == 1) {
            as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
            return;
        }
        if (ksys::act::isEnemyProfile(parent)) {
            auto* enemy = sead::DynamicCast<act::Enemy>(parent);
            if (enemy && enemy->_e84.isOnBit(16)) {
                if (_ec == 5)
                    return;
                as_list->sub_710115B01C(0, 1, true);
                _ec = 5;
                return;
            }
        }
    }

    as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (!ksys::StageInfo::sIsCDungeon && dlc::hasEscapedOneHitObliteratorQuest(false) && weapon->_d38)
        weapon->_d38->sub_71002EF850();
    if (!weapon->_d38)
        return;
    const s32 max_charge = static_cast<s32>(weapon->_d38->sub_71002EF74C());
    if (max_charge < 1)
        return;

    const f32 ratio = (weapon->_d38 ? weapon->_d38->_14 : 0.0f) / max_charge;
    if (ratio >= 1.0f) {
        switch (_ec) {
        case -1:
        case 2:
            startAnimation(sUnk_71023e1008, mActor);
            _ec = 4;
            break;
        case 4:
            break;
        case 3:
            startAnimation(sUnk_71023e1018, mActor);
            _ec = 4;
            break;
        default:
            _ec = 4;
            break;
        }
    } else if (weapon->m214()) {
        if (ratio == 0.5f) {
            if (_ec != 1) {
                startAnimation(sUnk_71023e1028, mActor);
                _ec = 1;
            }
        } else {
            if (_ec != 3) {
                startAnimation(sUnk_71023e0ff8, mActor);
                _ec = 3;
            }
            as_list->sub_710115F1D8(0, 1, (ratio - 0.5f) * 2.0f);
        }
    } else {
        if (_ec != 2) {
            startAnimation(sUnk_71023e0fe8, mActor);
            _ec = 2;
        }
        as_list->sub_710115F1D8(0, 1, ratio);
    }

    if (isWeaponM213() && !((uking::ui::Manager::instance()->_64c30_bytes[5] >> 6) & 1)) {
        startAnimation(sUnk_71023e0fe8, mActor);
        as_list->sub_710115F1D8(0, 1, 0.0f);
    }

    const bool enabled = weapon->m214() || _e8;
    sub_71012412E4(mActor, 27, ratio, false);
    xlinkEventOn(mActor, 28, enabled, false);
    if (!isWeaponM213())
        dmg::DamageInfoMgr::instance()->setOneHitObliteratorActive(enabled);
}

void DeadlyBlowWeaponRoot::sub_710035CE18() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon && weapon->_d38 && (weapon->_d38->_18 & 8)) {
        if (ksys::StageInfo::sIsCDungeon || !dlc::hasEscapedOneHitObliteratorQuest(false))
            flyingObjectEmitXlink(mActor, "ChemSwordChargeLoop", 1, nullptr);
    }
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
