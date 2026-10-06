#include "Game/AI/Action/actionSiteBossShootIceSplinter.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: the original hoists the cNullChar load above the first entry (as for a plain Entry[9]), which
// would make the destructor mismatch instead.
SiteBossShootIceSplinter::Entries::Entries() = default;

SiteBossShootIceSplinter::SiteBossShootIceSplinter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShootIceSplinter::~SiteBossShootIceSplinter() = default;

bool SiteBossShootIceSplinter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShootIceSplinter::enter_(ksys::act::ai::InlineParamPack* params) {
    _60 = isFinishedAS(0, 0);
    _62 = true;
    _61 = false;
    _64 = 0;
    sub_710026354C(*mThrowIdxOffset_s);
    _64 += 1;
}

void SiteBossShootIceSplinter::leave_() {
    if (_62)
        return;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        for (u32 i = *mThrowIdxOffset_s; i < 9; ++i)
            boss->_1560.sub_710066CBF8(i);
    }
}

void SiteBossShootIceSplinter::loadParams_() {
    getStaticParam(&mThrowIdxOffset_s, "ThrowIdxOffset");
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mThrowASName_s, "ThrowASName");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SiteBossShootIceSplinter::calc_() {
    if (_60) {
        _61 = false;
        if (mActor->getASList()->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            sub_710026354C(*mThrowIdxOffset_s + _64);
            _64 += 1;
        }
        if (isFinishedAS(0, 0))
            setFinished();
    } else if (isFinishedAS(0, 0)) {
        _60 = true;
        _61 = true;
        playAS(mThrowASName_s.cstr(), true, 0, 0, -1.0f);
    }
}

bool SiteBossShootIceSplinter::isFinished() const {
    if (!_60)
        return false;
    if (_61)
        return false;
    return ksys::act::ai::Action::isFinished() || isFinishedAS(0, 0);
}

}  // namespace uking::action
