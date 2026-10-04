#include "Game/AI/AI/aiChemicalWeaponRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

ChemicalWeaponRoot::ChemicalWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

ChemicalWeaponRoot::~ChemicalWeaponRoot() = default;

void ChemicalWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    _e8 = true;
    _ec = -1;
    m44();
}

void ChemicalWeaponRoot::sub_7100348B18() {
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
                if (_ec == 2)
                    return;
                as_list->sub_710115B01C(0, 1, true);
                _ec = 2;
                return;
            }
        }
    }

    as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (!weapon->_d38)
        return;
    const s32 max_charge = static_cast<s32>(weapon->_d38->sub_71002EF74C());
    if (max_charge < 1)
        return;

    const f32 ratio = (weapon->_d38 ? weapon->_d38->_14 : 0.0f) / max_charge;
    if (ratio >= 1.0f) {
        if (_ec != 1) {
            if (as_list->sub_710115AA68("ChemFull"))
                as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemFull", 0, 1, true);
            _ec = 1;
        }
    } else {
        if (_ec != 0) {
            if (as_list->sub_710115AA68("ChemCharge"))
                as_list->startAnimationMaybe(-1.0f, -1.0f, "ChemCharge", 0, 1, true);
            _ec = 0;
        }
        as_list->sub_710115F1D8(0, 1, ratio);
    }

    const s32 enabled = weapon->m214() ? 1 : _e8;
    sub_71012412E4(mActor, 27, ratio, false);
    xlinkEventOn(mActor, 28, enabled, false);
}

void ChemicalWeaponRoot::calc_() {
    WeaponRootAI::calc_();
    sub_7100348B18();

    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon && weapon->_d38 && (weapon->_d38->_18 & 8))
        flyingObjectEmitXlink(mActor, "ChemSwordChargeLoop", 1, nullptr);

    weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (weapon) {
        const bool flag = weapon->m214() || _e8;
        if (auto* chemical = mActor->sub_71011D8A44(0)) {
            if (flag)
                chemical->_bf &= ~2;
            else
                chemical->_bf |= 2;
        }
    }
}

bool ChemicalWeaponRoot::isWeaponM213() const {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    return weapon && weapon->m213();
}

// NON_MATCHING: the repeated `weapon && weapon->m213()` check: the original branches on the cast / m213() results
// separately, ours merges the two paths into one bool (an extra `eor`); same as DeadlyBlowWeaponRoot::m41
bool ChemicalWeaponRoot::m41() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!isWeaponM213() && weapon && !_e8 && !weapon->m153() && weapon->m214() &&
        (weapon->_c20._0 == 0 || weapon->_c20._0 == 2)) {
        return true;
    }
    if (!isWeaponM213() && weapon && !_e8 && (weapon->_e50 & 2) && weapon->m214())
        return true;
    return false;
}

bool ChemicalWeaponRoot::m42() {
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

void ChemicalWeaponRoot::m43() {
    _e8 = true;
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->sub_7100D90AF4(true);
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->_bf &= ~2;
    if (auto* chemicals = mActor->getChemicalContainer()) {
        if (chemicals->sub_7100E3718C(0)) {
            if (auto* chemical = mActor->sub_71011D8A44(0)) {
                if ((chemical->mMaterial->attribute.ref() & 1) && !(chemical->_be & 1))
                    chemical->sub_7100D90858(false, 2, false, true, false);
            }
        }
    }
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->sub_7100D91098(true);
}

void ChemicalWeaponRoot::m44() {
    _e8 = false;
    auto* first = mActor->sub_71011D8A44(0);
    if (first) {
        first->sub_7100D91098(false);
        if (auto* chemical = mActor->sub_71011D8A44(0))
            chemical->sub_7100D90AF4(false);
    }
    if (auto* chemicals = mActor->getChemicalContainer()) {
        if (auto* element = chemicals->sub_7100E3718C(0)) {
            element->_30 |= 0x200;
            if (first && (first->mMaterial->attribute.ref() & 1) && !(first->_be & 1)) {
                if (auto* chemical = mActor->sub_71011D8A44(0))
                    chemical->sub_7100D8EEE0();
            }
        }
    }
}

}  // namespace uking::ai
