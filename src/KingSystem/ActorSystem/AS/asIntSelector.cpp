#include "KingSystem/ActorSystem/AS/asElement.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/System/StageInfo.h"

namespace ksys::as {

IntSelector::IntSelector(const CreateArg& arg, s32 value, const res::ASResource* resource)
    : _18(-1) {
    if (const auto* children = sead::DynamicCast<const res::ASResourceWithChildren>(resource))
        _18 = getValue(arg.actor, children);
}

// NON_MATCHING: signed length tests and the common integer-lookup tail have different scheduling.
s32 IntSelector::getValue(act::Actor* actor, const res::ASResource* resource) {
    mii::UMii* umii = actor->getUMii();
    switch (resource->getTypeIndex()) {
    case 19: {
        const sead::SafeString prefix = "Dungeon";
        const s32 prefix_length = prefix.calcLength();
        const auto& map_name = StageInfo::getCurrentMapName();
        const s32 length = map_name.calcLength() - prefix_length;
        if (length < 0 || map_name.comparen(prefix, prefix_length) != 0)
            return resource->findIntIndex(-1);
        const auto number = map_name.getPart(prefix_length);
        s32 value = -1;
        if (length > 0) {
            value = 0;
            for (s32 i = 0; i < length; ++i)
                value = value * 10 + sead::Mathi::clamp(number[i] - '0', 0, 9);
        }
        return resource->findIntIndex(value);
    }
    case 22:
        return resource->findIntIndex(actor->sub_71011CA00C());
    case 23:
        return resource->findIntIndex(actor->_838);
    case 32:
        return resource->findIntIndex(umii ? umii->getAge() : std::numeric_limits<s32>::min());
    case 40:
        return resource->findIntIndex(actor->_834);
    case 45: {
        sead::SafeString value;
        value = umii ? *umii->getPersonal().personality : res::ASResource::getDefaultStr();
        return resource->findStringIndex(value);
    }
    case 59:
        return resource->findIntIndex(umii ? *umii->getBody().height : std::numeric_limits<s32>::min());
    case 60:
        return resource->findIntIndex(umii ? *umii->getBody().weight : std::numeric_limits<s32>::min());
    default:
        return -1;
    }
}

void IntSelector::m12(Context* ctx, State* state, const res::ASResource* resource) {
    s32 index;
    if (!sub_71013031B4(&index, ctx, resource))
        return;
    Element* child = mChildren[index];
    const res::ASResource* child_resource = sub_71013031FC(resource, index);
    child->m12(ctx, state, child_resource);
}

int IntSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return _18;
}

}  // namespace ksys::as
