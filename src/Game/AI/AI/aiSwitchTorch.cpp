#include "Game/AI/AI/aiSwitchTorch.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"

namespace uking::ai {

SwitchTorch::SwitchTorch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTorch::~SwitchTorch() = default;

bool SwitchTorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTorch::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* chemical = actor->getChemicalStuff();
    if (*mSwitchTorchSpType_m == 1) {
        if (chemical)
            chemical->sub_7100D90B78();
    } else if (actor->checkLinkBasicSig() || actor->isWaitRevivalForUsed()) {
        if (chemical) {
            chemical->sub_7100D90858(chemical->mMaterial->attribute.ref() & 0x200000, 2, false,
                                     true, false);
        }
        changeChild("オン");
        return;
    }
    changeChild("オフ");
}

void SwitchTorch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTorch::loadParams_() {
    getMapUnitParam(&mSwitchTorchSpType_m, "SwitchTorchSpType");
}

}  // namespace uking::ai
