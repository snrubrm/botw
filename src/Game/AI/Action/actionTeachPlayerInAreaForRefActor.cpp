#include "Game/AI/Action/actionTeachPlayerInAreaForRefActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

TeachPlayerInAreaForRefActor::TeachPlayerInAreaForRefActor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TeachPlayerInAreaForRefActor::~TeachPlayerInAreaForRefActor() = default;

bool TeachPlayerInAreaForRefActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeachPlayerInAreaForRefActor::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = mActor->checkBasicSig();
    if (_28) {
        auto* actor = mActor;
        const bool sig = actor->checkBasicSig();
        sub_710029450C();
        _28 = sig;
        if (sig)
            actor->m107();
    }
}

void TeachPlayerInAreaForRefActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void TeachPlayerInAreaForRefActor::loadParams_() {
    getStaticParam(&mNextTimer_s, "NextTimer");
}

void TeachPlayerInAreaForRefActor::calc_() {
    auto* actor = mActor;
    const bool sig = actor->checkBasicSig();
    if (sig) {
        if (!_28) {
            sub_710029450C();
        } else {
            _30.sub_7100D3BCE4();
            if (_30.mTimer.value <= sead::Mathf::epsilon())
                sub_710029450C();
        }
        _28 = sig;
        actor->m107();
    } else {
        _28 = sig;
    }
}

// NON_MATCHING: the original frame is 0x10 larger (an unused 8-byte slot below the accessor) and its loop guard is
// `cmp w21, #1; b.lt` instead of `cbz`
void TeachPlayerInAreaForRefActor::sub_710029450C() {
    {
        const auto& link = ksys::act::PlayerInfo::getSomeProcLink();
        sead::ScopedLock<sead::JobQueueLock> lock(&_48._18.mLock);
        _48._18.mLink = link;
    }
    if (auto* obj = mActor->getMapObject()) {
        if (auto* link_data = obj->getLinkData()) {
            for (auto* object : link_data->mObjects) {
                ksys::act::ActorLinkConstDataAccess accessor;
                object->getActorWithAccessor(accessor);
                if (accessor.hasProc())
                    _48.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        }
    }
    const f32 time = *mNextTimer_s;
    _30.mTimer = ksys::Timer(time, time, -1.0f);
}

}  // namespace uking::action
