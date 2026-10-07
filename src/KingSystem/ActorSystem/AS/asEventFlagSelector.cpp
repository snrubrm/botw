#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

EventFlagSelector::EventFlagSelector(const CreateArg&, s32, const res::ASResource*) {}

EventFlagSelector::~EventFlagSelector() {
    _18.freeBuffer();
}

// NON_MATCHING: buffer-allocation branches and handle-loop register allocation differ.
bool EventFlagSelector::m8(const InitArg& arg) {
    if (!SelectorBase::m8(arg))
        return false;
    auto* parser = sead::DynamicCast<const res::ASStringArrayParser>(
        arg.resource->getExtensions().getParser(res::ASParamParser::Type::StringArray));
    if (!parser || parser->getValues().size() == 0)
        return true;
    int num_flags = parser->getValues().size();
    if (res::ASResource::getDefaultStr() == *parser->getValues()[num_flags - 1].value)
        --num_flags;
    if (num_flags == 0)
        return true;
    if (!_18.tryAllocBuffer(num_flags, arg.createArg->heap, 8))
        return false;
    _18.fill(gdt::InvalidHandle);
    for (int i = 0; i < num_flags; ++i)
        _18[i] = gdt::Manager::instance()->getBoolHandle(*parser->getValues()[i].value);
    return true;
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
