#include "Game/AI/AI/aiChemicalExplode.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ChemicalExplode::ChemicalExplode(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChemicalExplode::~ChemicalExplode() = default;

bool ChemicalExplode::isChangeable() const {
    return false;
}

bool ChemicalExplode::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChemicalExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical || chemical->_c0 == 4) {
        changeChild("爆破");
        return;
    }
    chemical->sub_7100D909A4();
    changeChild("爆破予約");
}

void ChemicalExplode::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChemicalExplode::loadParams_() {}

}  // namespace uking::ai
