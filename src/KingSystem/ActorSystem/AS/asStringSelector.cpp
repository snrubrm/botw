#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"

namespace ksys::as {

StringSelector::StringSelector() {}

const char* StringSelector::m40(Context* ctx, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    return list->sub_710115ECF4(sub_7101165408(resource), 0);
}

int StringSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    return resource->findStringIndex(m40(ctx, resource));
}

const sead::SafeString& StringSelector::sub_710131D9F0(Context* ctx,
                                                       const res::ASResource* resource) {
    const s8 index = ctx->sub_7101258CD4(sub_71011653E8(resource))->_0;
    auto* parser = sead::DynamicCast<const res::ASStringArrayParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::StringArray));
    if (index >= 0 && parser)
        return *parser->getValues()[index].value;
    return sead::SafeString::cEmptyString;
}

}  // namespace ksys::as
