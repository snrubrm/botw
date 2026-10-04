#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

EventFlagSelector::EventFlagSelector() {}

EventFlagSelector::~EventFlagSelector() {
    _18.freeBuffer();
}

// NON_MATCHING: the fallback result joins the loop-index return path rather than the epilogue.
int EventFlagSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    for (auto it = _18.begin(), end = _18.end(); it != end; ++it) {
        bool value = false;
        if (gdt::Manager::instance()->getBool(*it, &value, true) && value)
            return it.getIndex();
    }
    auto* parser = sead::DynamicCast<const res::ASStringArrayParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::StringArray));
    if (!parser)
        return -1;
    const s32 num_values = parser->getValues().size();
    return num_values == _18.size() ? -1 : num_values - 1;
}

const char* EventFlagSelector::m40(Context* ctx, const res::ASResource* resource) {
    return sub_710131D9F0(ctx, resource).cstr();
}

}  // namespace ksys::as
