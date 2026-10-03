#include "Game/AI/AI/aiGolemPartRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

GolemPartRoot::GolemPartRoot(const InitArg& arg) : ReuseBulletPartsRoot(arg) {}

GolemPartRoot::~GolemPartRoot() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_c8, &accessor);
    if (accessor.hasProc() && accessor.isStateSleep())
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool GolemPartRoot::init_(sead::Heap* heap) {
    return ReuseBulletPartsRoot::init_(heap);
}

// NON_MATCHING: register allocation of the loop count / the two flags (the logic is complete)
void GolemPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ReuseBulletPartsRoot::enter_(params);
    bool has_ice = false;
    bool has_burn = false;
    if (auto* chemicals = mActor->getChemicalContainer()) {
        const s32 count = chemicals->_58.size() + chemicals->_80;
        for (s32 i = 0; i < count; ++i) {
            auto* chemical = chemicals->sub_7100E37788(i);
            if (!chemical)
                continue;
            if (*mGolemPartInitialBurn_a) {
                if (chemical->_c0 == 2) {
                    has_burn = true;
                } else {
                    chemical->sub_7100D90858(false, 2, false, true, false);
                    has_burn = true;
                }
            } else if (chemical->_c0 == 2) {
                chemical->sub_7100D90B78();
            }
            if (chemical->mMaterial->attribute.ref() & 0x8000) {
                if (*mGolemPartInitialIceMagic_a) {
                    chemical->_bf &= ~2;
                    has_ice = true;
                } else {
                    chemical->_bf |= 2;
                }
            }
        }
    }

    if (!has_ice && !has_burn) {
        if (!mNormalAS_s.isEmpty())
            changeAS(mNormalAS_s.cstr(), false, 0, 0);
        xlinkEventOn(mActor, 26, 0, false);
    } else {
        if (!mActiveAS_s.isEmpty())
            changeAS(mActiveAS_s.cstr(), false, 0, 0);
        xlinkEventOn(mActor, 26, 1, false);
    }
}

void GolemPartRoot::calc_() {
    ReuseBulletPartsRoot::calc_();
}

void GolemPartRoot::leave_() {
    ReuseBulletPartsRoot::leave_();
}

void GolemPartRoot::loadParams_() {
    ReuseBulletPartsRoot::loadParams_();
    getStaticParam(&mChemFieldScale_s, "ChemFieldScale");
    getStaticParam(&mNormalAS_s, "NormalAS");
    getStaticParam(&mActiveAS_s, "ActiveAS");
    getAITreeVariable(&mGolemPartInitialIceMagic_a, "GolemPartInitialIceMagic");
    getAITreeVariable(&mGolemPartInitialBurn_a, "GolemPartInitialBurn");
}

}  // namespace uking::ai
