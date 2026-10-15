#include "Game/Actor/Behavior/behaviorTargetFindSpreadToTag.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::behavior {

TargetFindSpreadToTag::TargetFindSpreadToTag(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

TargetFindSpreadToTag::~TargetFindSpreadToTag() = default;

bool TargetFindSpreadToTag::m6(sead::Heap* heap) {
    return true;
}

void TargetFindSpreadToTag::m7() {}

void TargetFindSpreadToTag::m8() {
    auto* target = sub_71005D9050(mActor);
    auto* actor = mActor;
    const auto& position = sub_71005D9330(actor);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_38._18.mLock);
        auto& data = _38._18.mData;
        if (target)
            data._0 = *target;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = position;
        data._34 = 0;
    }
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    const auto& objects = object->getLinkData()->mObjects;
    const s32 count = objects.size();
    auto* const* linked_objects = objects.getBufferPtr();
    for (s32 i = 0; i < count; ++i) {
        auto* linked_object = linked_objects[i];
        if (!linked_object)
            continue;
        const char* name = linked_object->getUnitConfigName();
        if (mTagName_s.isEmpty() || sead::SafeString(name) == mTagName_s) {
            ksys::act::ActorLinkConstDataAccess accessor;
            linked_objects[i]->getActorWithAccessor(accessor);
            if (accessor.hasProc())
                _38.sub_710070DD78(accessor, true);
        }
    }
}

void TargetFindSpreadToTag::m9() {}

void TargetFindSpreadToTag::loadParams() {
    getStaticParam(&mTagName_s, "TagName");
}

}  // namespace uking::behavior
