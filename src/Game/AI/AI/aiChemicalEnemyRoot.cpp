#include "Game/AI/AI/aiChemicalEnemyRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

ChemicalEnemyRoot::ChemicalEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

// The SafeString member makes the original keep the vtable store (see AssassinCallSelect).
ChemicalEnemyRoot::~ChemicalEnemyRoot() { ; }

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
