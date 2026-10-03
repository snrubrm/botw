#include "Game/AI/AI/aiChemicalWeaponRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

namespace uking::ai {

ChemicalWeaponRoot::ChemicalWeaponRoot(const InitArg& arg) : WeaponRootAI(arg) {}

ChemicalWeaponRoot::~ChemicalWeaponRoot() = default;

void ChemicalWeaponRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
    _e8 = true;
    _ec = -1;
    m44();
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
