#include "Game/AI/AI/aiMagneGrabbedPartsRangeSelector.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

MagneGrabbedPartsRangeSelector::MagneGrabbedPartsRangeSelector(const InitArg& arg)
    : RangeSelect(arg) {}

MagneGrabbedPartsRangeSelector::~MagneGrabbedPartsRangeSelector() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(mPartsName_s);
}

bool MagneGrabbedPartsRangeSelector::init_(sead::Heap* heap) {
    if (!RangeSelect::init_(heap))
        return false;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    enemy->sub_7100D3CED8(mPartsName_s, heap);
    return true;
}

void MagneGrabbedPartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void MagneGrabbedPartsRangeSelector::calc_() {
    RangeSelect::calc_();
}

void MagneGrabbedPartsRangeSelector::leave_() {
    RangeSelect::leave_();
}

void MagneGrabbedPartsRangeSelector::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

// NON_MATCHING: the original keeps a cleanup flag for the accessor scope and loads the 9999 default
// into a separate register (same instructions otherwise)
f32 MagneGrabbedPartsRangeSelector::m38() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D13BB8()) {
                const sead::Vector3f partsPos = accessor.getActorMtx().getTranslation();
                return (mActor->getMtx().getTranslation() - partsPos).length();
            }
        }
    }
    return 9999.0f;
}

}  // namespace uking::ai
