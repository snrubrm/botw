#include "Game/AI/Action/actionGanonThrowMultiTornado.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

GanonThrowMultiTornado::GanonThrowMultiTornado(const InitArg& arg) : GanonThrowTornado(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GanonThrowMultiTornado::~GanonThrowMultiTornado() {
    ;
}

bool GanonThrowMultiTornado::init_(sead::Heap* heap) {
    return GanonThrowTornado::init_(heap);
}

void GanonThrowMultiTornado::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowTornado::enter_(params);
}

void GanonThrowMultiTornado::leave_() {
    GanonThrowTornado::leave_();
}

void GanonThrowMultiTornado::loadParams_() {
    GanonThrowTornado::loadParams_();
    getStaticParam(&mAppearOffset1_s, "AppearOffset1");
    getDynamicParam(&mThrowPartsName1_d, "ThrowPartsName1");
}

void GanonThrowMultiTornado::calc_() {
    GanonThrowTornado::calc_();
}

// NON_MATCHING: same as GanonThrowTornado::m32 (inlined dummy link getter).
ksys::act::BaseProcLink& GanonThrowMultiTornado::m32(int idx) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        if (idx == 0)
            return GanonThrowTornado::m32(0);
        return enemy->getActorPartsActor(mThrowPartsName1_d);
    }
    return ksys::act::getDummyBaseProcLink();
}

const sead::Vector3f* GanonThrowMultiTornado::m33(int idx) {
    if (idx == 0)
        return GanonThrowTornado::m33(0);
    return mAppearOffset1_s;
}

}  // namespace uking::action
