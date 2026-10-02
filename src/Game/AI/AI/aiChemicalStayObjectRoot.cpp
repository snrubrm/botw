#include "Game/AI/AI/aiChemicalStayObjectRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

ChemicalStayObjectRoot::ChemicalStayObjectRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChemicalStayObjectRoot::~ChemicalStayObjectRoot() = default;

bool ChemicalStayObjectRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChemicalStayObjectRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("通常");
}

void ChemicalStayObjectRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChemicalStayObjectRoot::loadParams_() {
    getStaticParam(&mIsCheckDelete_s, "IsCheckDelete");
}

bool ChemicalStayObjectRoot::m34() {
    auto* chemical = mActor->getChemicalStuff();
    if (!chemical)
        return false;
    if (_40 & 1)
        return chemical->_b9[0] >> 1 & 1;
    if (_40 & 2)
        return chemical->_b8 >> 2 & 1;
    return false;
}

}  // namespace uking::ai
