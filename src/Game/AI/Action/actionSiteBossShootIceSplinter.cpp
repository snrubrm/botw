#include "Game/AI/Action/actionSiteBossShootIceSplinter.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

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

// NON_MATCHING: Position stores and message-type construction are scheduled differently.
void SiteBossShootIceSplinter::sub_710026354C(int idx) {
    const auto target = *mTargetPos_d;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        auto& link = boss->_1560._1e0[idx];
        if (!link.hasProc())
            return;
        auto& entry = _68[idx];
        entry._0 = target;
        entry._0.y += 1.0f;
        entry._18 = *mTargetActor_d;
        entry._28 = *mInitVelocity_s;
        entry.mNodeName.clear();
        ksys::act::ActorConstDataAccess actor;
        ksys::act::acquireActor(&link, &actor);
        mActor->sendMessage(*actor.getMessageTransceiverId(), ksys::MessageType(0x800003a),
                            &entry, true);
    }
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
