#include "Game/AI/Action/actionHornUse.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

HornUse::HornUse(const InitArg& arg) : HornUseBase(arg) {}

HornUse::~HornUse() = default;

bool HornUse::init_(sead::Heap* heap) {
    if (!HornUseBase::init_(heap))
        return false;
    _f0.sub_7100D78564(heap);
    return true;
}

void HornUse::enter_(ksys::act::ai::InlineParamPack* params) {
    HornUseBase::enter_(params);
    _1a8 = f32(*mSpreadTime_s);
}

void HornUse::leave_() {
    HornUseBase::leave_();
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_f0);
}

// NON_MATCHING: the original keeps &mSpreadTime_s in a callee-saved register from the start
// (known unexplained loadParams_ shape)
void HornUse::loadParams_() {
    HornUseBase::loadParams_();
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mSpreadTime_s, "SpreadTime");
    getStaticParam(&mTerrorLevel_s, "TerrorLevel");
    getStaticParam(&mNoticeMaskState_s, "NoticeMaskState");
}

// NON_MATCHING: the original stores the AITerror::x index temporary after converting the level
void HornUse::calc_() {
    HornUseBase::calc_();

    if (!(_1a8 >= 0.0f))
        return;

    ksys::Timer::update(&_1a8, -1.0f);
    if (!(_1a8 < 0.0f))
        return;

    if (auto* owner = mActor->get548()) {
        _f0.setRadius(*mSpreadDist_s);
        _f0.x(2, 4, f32(*mTerrorLevel_s));
        owner->sub_7100D783E4(&_f0);
    }

    u8 mask;
    switch (*mNoticeMaskState_s) {
    case 0: {
        mask = 4;
        auto* actor = mActor;
        if (sead::IsDerivedFrom<act::Enemy>(actor) &&
            static_cast<act::Enemy*>(actor)->_e84.isOnBit(1)) {
            mask = 5;
        }
        break;
    }
    case 1:
        mask = 5;
        break;
    default:
        mask = 4;
        break;
    }

    auto* link = sub_71005D9050(mActor);
    auto* actor = mActor;
    const auto& pos = sub_71005D9330(actor);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_98._18.mLock);
        auto& data = _98._18.mData;
        if (link)
            data._0 = *link;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = pos;
        data._34 = mask;
    }

    if (auto* awareness = mActor->getAwareness()) {
        Unk_7102451448 filter;
        while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            if (entry->_a8 < *mSpreadDist_s) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&entry->_0.mLink, &accessor);
                _98.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        }
    }
}

}  // namespace uking::action
