#include "Game/AI/Behavior/behaviorNeckRotateToPlayerAndNPC.h"
#include <cmath>
#include <limits>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::behavior {

// NON_MATCHING: store scheduling (the 0x38 pair is stored first)
NeckRotateToPlayerAndNPC::NeckRotateToPlayerAndNPC(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

NeckRotateToPlayerAndNPC::~NeckRotateToPlayerAndNPC() = default;

bool NeckRotateToPlayerAndNPC::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: instruction scheduling only: the original stores the three bytes / pointers of the ActorConstDataAccess together
// before the acquireActor call, and loads `mLimitAngle_s` between the dot product's multiplies (we load it before them)
void NeckRotateToPlayerAndNPC::sub_710062D70C() {
    if (auto* awareness = mActor->getAwareness()) {
        const f32 limit_distance = *mLimitDistance_s;
        const int count = *mIsUseAwnSight_s && awareness->_260[0] ? awareness->_260[0]->_8.size() :
                                                                    awareness->_8.size();
        for (int i = 0; i < count; ++i) {
            ksys::act::Unk_7100d78e50* entry = nullptr;
            if (*mIsUseAwnSight_s && awareness->_260[0]) {
                auto& entries = awareness->_260[0]->_8;
                if (entries.size() > i)
                    entry = ksys::act::sub_7100D78E30(&entries, i);
            } else {
                auto& entries = awareness->_8;
                if (entries.size() > i)
                    entry = ksys::act::sub_7100D78E30(&entries, i);
            }
            if (!entry)
                continue;
            if (limit_distance >= 0 && entry->_a8 > limit_distance)
                break;

            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) &&
                (ksys::act::isPlayerProfile(accessor) || ksys::act::isNPCProfile(accessor))) {
                sead::Vector3f actor_pos;
                mActor->getMtx().getTranslation(actor_pos);
                sead::Vector3f target_pos;
                accessor.getActorMtx().getTranslation(target_pos);
                sead::Vector3f direction = target_pos - actor_pos;
                direction.normalize();
                const f32 dot = direction.dot(mActor->getMtx().getBase(2));
                if (dot >= std::cos(*mLimitAngle_s)) {
                    _48 = entry->_0.mLink;
                    return;
                }
            }
        }
    }
    _48.reset();
}

void NeckRotateToPlayerAndNPC::m7() {
    _58.update();
    if (_58.value <= std::numeric_limits<f32>::epsilon()) {
        sub_710062D70C();
        _58.reset(*mUpdateInterval_s);
    }

    if (_48.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_48, &accessor);
        sub_71005DB068(mActor, accessor.getPreviousPos2());
    } else {
        sub_71005DB3EC(mActor);
    }
}

void NeckRotateToPlayerAndNPC::m8() {
    sub_710062D70C();
    _58 = ksys::Timer(*mUpdateInterval_s, *mUpdateInterval_s);
}

void NeckRotateToPlayerAndNPC::m9() {
    sub_71005DB3EC(mActor);
}

void NeckRotateToPlayerAndNPC::loadParams() {
    getStaticParam(&mUpdateInterval_s, "UpdateInterval");
    getStaticParam(&mLimitDistance_s, "LimitDistance");
    getStaticParam(&mLimitAngle_s, "LimitAngle");
    getStaticParam(&mIsUseAwnSight_s, "IsUseAwnSight");
}

}  // namespace uking::behavior
