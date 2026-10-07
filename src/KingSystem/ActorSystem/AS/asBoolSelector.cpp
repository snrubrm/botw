#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::as {

BoolSelector::BoolSelector(const CreateArg&, s32, const res::ASResource*) {}

int BoolSelector::m39(Context* ctx, u32 a2, const res::ASResource* resource) {
    ASList* list = ctx->mList;
    auto* parser = sead::DynamicCast<const res::ASBitIndexParser>(
        resource->getExtensions().getParser(res::ASParamParser::Type::BitIndex));
    return list->sub_710115EE14(parser ? parser->getBitIndex() : -1);
}

}  // namespace ksys::as
