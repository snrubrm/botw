#include "Game/AI/AI/aiChemicalEnemyRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

ChemicalEnemyRoot::ChemicalEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
ChemicalEnemyRoot::~ChemicalEnemyRoot() {
    ;
}

void ChemicalEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
    if (*mIsElementNoHit_s) {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D90FF0(true);
    } else {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D90FF0(false);
    }
    _1f9 = false;
    _1f8 = !mColorASName_s.isEmpty();
    if (auto* as_list = mActor->getASList()) {
        as_list->sub_710115C11C();
        as_list->sub_710115BED4(true);
    }
}

void ChemicalEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mIsElementNoHit_s, "IsElementNoHit");
    getStaticParam(&mIsElectricWater_s, "IsElectricWater");
    getStaticParam(&mColorASName_s, "ColorASName");
}

// NON_MATCHING: the two epsilon range compares (-eps <= diff, diff <= eps) are emitted in the opposite
// order (and with swapped branch conditions); the rest of the function matches
void ChemicalEnemyRoot::sub_710034790C() {
    if (!_1f8)
        return;

    if (_1f9) {
        auto* chemical = mActor ? mActor->getChemicalStuff() : nullptr;
        if (chemical && (chemical->mMaterial->attribute.ref() & 0x108) == 0x108 &&
            !(chemical->_be & 4) && sead::Mathf::equalsEpsilon(0.0f, chemical->_1b8)) {
            if (auto* as_list = mActor->getASList()) {
                as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
                as_list->x_3(0, 1, &ksys::as::ASList::Unk2::sub_7101163100, 0.0f);
            }
            _1f9 = false;
            return;
        }
        if (_1f9)
            return;
    }

    auto* chemical = mActor ? mActor->getChemicalStuff() : nullptr;
    if (!chemical || (chemical->mMaterial->attribute.ref() & 0x108) != 0x108 ||
        (chemical->_be & 4) || !sead::Mathf::equalsEpsilon(0.0f, chemical->_1b8)) {
        if (auto* as_list = mActor->getASList())
            as_list->startAnimationMaybe(-1.0f, -1.0f, mColorASName_s.cstr(), 0, 1, true);
        _1f9 = true;
    }
}

void ChemicalEnemyRoot::calc_() {
    EnemyRoot::calc_();
    sub_710034790C();
    if (!*mIsElementNoHit_s || !*mIsElectricWater_s)
        return;

    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return;

    if (chemical->_c0 == 1) {
        if (!(chemical->_bf & 1))
            chemical->sub_7100D90AF4(false);
    } else if (chemical->_bf & 1) {
        chemical->sub_7100D90AF4(true);
    }

    if (!(chemical->_c & 0x1000000) && chemical->_190 > 0.0f)
        chemical->sub_7100D90FF0(false);
    else
        chemical->sub_7100D90FF0(true);
}

}  // namespace uking::ai
