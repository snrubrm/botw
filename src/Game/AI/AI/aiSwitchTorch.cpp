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

// NON_MATCHING: the "lit" flag is kept as a re-normalised value in the original (cset after the
// merge, orn for the オン待機 test); branch shapes and register allocation differ
void SwitchTorch::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    auto* chemical = actor->getChemicalStuff();
    bool lit = false;
    if (chemical) {
        if (chemical->mMaterial->attribute.ref() & 0x200000) {
            lit = chemical->_c0 == 2 && (chemical->_c & 0x100000);
            if (!lit && *mSwitchTorchSpType_m == 2)
                chemical->sub_7100D90858(true, 2, false, true, false);
        } else {
            lit = chemical->_c0 == 2;
            if (!lit && *mSwitchTorchSpType_m == 2)
                chemical->sub_7100D90858(false, 2, false, true, false);
        }

        if (*mSwitchTorchSpType_m == 3) {
            if (chemical->_c & 0x400000) {
                if (!actor->checkLinkGimmickSuccessSignal())
                    actor->emitGimmickSuccessSignal_1();
            } else {
                if (actor->checkLinkGimmickSuccessSignal())
                    actor->emitGimmickSuccessSignal_0();
            }
        }
    }

    if (isCurrentChild("オフ待機") && child->isChangeable() && lit)
        changeChild("オン");
    else if (isCurrentChild("オン待機") && child->isChangeable() && !lit)
        changeChild("オフ");
    else if (isCurrentChild("オフ") && child->isFinished())
        changeChild("オフ待機");
    else if (isCurrentChild("オン") && child->isFinished())
        changeChild("オン待機");
}

void SwitchTorch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTorch::loadParams_() {
    getMapUnitParam(&mSwitchTorchSpType_m, "SwitchTorchSpType");
}

}  // namespace uking::ai
