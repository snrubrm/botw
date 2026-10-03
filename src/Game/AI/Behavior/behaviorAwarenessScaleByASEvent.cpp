#include "Game/AI/Behavior/behaviorAwarenessScaleByASEvent.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include <prim/seadStringUtil.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AwarenessScaleByASEvent::AwarenessScaleByASEvent(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AwarenessScaleByASEvent::~AwarenessScaleByASEvent() = default;

bool AwarenessScaleByASEvent::m6(sead::Heap* heap) {
    return true;
}

void AwarenessScaleByASEvent::m7() {
    if (auto* rideable = mActor->m132())
        rideable->m9();
    if (auto* awareness = mActor->getAwareness()) {
        ksys::as::ASList::Unk4 query;
        f32 scale = 1.0f;
        const s32 count = mActor->getASList()->getSlot0BankCount();
        for (int i = 0; i < count; ++i) {
            if (mActor->getASList()->x_4(0, i))
                continue;
            if (mActor->getASList()->x(4, &query, 0, i, &ksys::as::ASList::Unk2::sub_71011638DC,
                                       true)) {
                if (!sead::StringUtil::tryParseF32(&scale, query.name))
                    scale = 1.0f;
            }
        }
        awareness->sub_7100D7EBE0(scale);
    }
}

void AwarenessScaleByASEvent::m8() {}

void AwarenessScaleByASEvent::loadParams() {

}

void AwarenessScaleByASEvent::m9() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7EBE0(1.0f);
}

}  // namespace uking::behavior
