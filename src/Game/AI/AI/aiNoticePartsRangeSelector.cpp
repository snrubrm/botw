#include "Game/AI/AI/aiNoticePartsRangeSelector.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

NoticePartsRangeSelector::NoticePartsRangeSelector(const InitArg& arg) : RangeSelect(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NoticePartsRangeSelector::~NoticePartsRangeSelector() {
    ;
}

bool NoticePartsRangeSelector::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void NoticePartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void NoticePartsRangeSelector::calc_() {
    RangeSelect::calc_();
}

void NoticePartsRangeSelector::leave_() {
    RangeSelect::leave_();
}

// NON_MATCHING: the original loads the 10000.0 default into a separate register up front and keeps an
// accessor-scope cleanup flag (same family as MagneGrabbedPartsRangeSelector::m38)
f32 NoticePartsRangeSelector::m38() {
    f32 result = 10000.0f;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mPartsName_s);
        if (link.hasProcInCalcState()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            if (accessor.sub_7100D10E6C(25)) {
                const sead::Vector3f partsPos = accessor.getActorMtx().getTranslation();
                result = (mActor->getMtx().getTranslation() - partsPos).length();
            }
        }
    }
    return result;
}

void NoticePartsRangeSelector::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
