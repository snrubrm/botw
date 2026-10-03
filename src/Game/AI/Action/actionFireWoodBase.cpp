#include "Game/AI/Action/actionFireWoodBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::action {

FireWoodBase::FireWoodBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FireWoodBase::~FireWoodBase() = default;

bool FireWoodBase::init_(sead::Heap* heap) {
    if (*mInitBurnState_m) {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D90858(false, 2, false, true, false);
    }
    return true;
}

// NON_MATCHING: the original loads the m32 vtable slot before calling getChemicalStuff (spilled to the stack)
void FireWoodBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mChemicalRigidOn_s)
        ksys::act::sub_7100EE5330(mActor, ksys::act::getStr_Chemical());
    auto* chemical = mActor->getChemicalStuff();
    m32(chemical && chemical->_c0 == 2);
}

// NON_MATCHING: the original loads the m32 vtable slot before calling getChemicalStuff (spilled to the stack)
void FireWoodBase::leave_() {
    auto* chemical = mActor->getChemicalStuff();
    m32(chemical && chemical->_c0 == 2);
}

void FireWoodBase::loadParams_() {
    getStaticParam(&mChemicalRigidOn_s, "ChemicalRigidOn");
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
}

void FireWoodBase::m32(bool burning) {
    _30 = burning;
}

// NON_MATCHING: the original loads the m32 vtable slot before calling getChemicalStuff (spilled to the stack)
void FireWoodBase::calc_() {
    auto* chemical = mActor->getChemicalStuff();
    const bool burning = chemical && chemical->_c0 == 2;
    if (burning != _30)
        m32(burning);
}

}  // namespace uking::action
