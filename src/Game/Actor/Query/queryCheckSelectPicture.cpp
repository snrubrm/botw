#include "Game/Actor/Query/queryCheckSelectPicture.h"
#include <evfl/Query.h>

// Native 0x7100a9e9ec takes a SafeString and checks saved album actor names.
// Free-function spelling is inferred; only the declaration is recovered here.
bool sub_7100A9E9EC(const sead::SafeString& actor_name);

namespace uking::query {

CheckSelectPicture::CheckSelectPicture(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSelectPicture::~CheckSelectPicture() = default;

int CheckSelectPicture::doQuery() {
    if (!mActor)
        return 0;
    return sub_7100A9E9EC(mActorName);
}

void CheckSelectPicture::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActorName");
}

void CheckSelectPicture::loadParams() {
    getDynamicParam(&mActorName, "ActorName");
}

}  // namespace uking::query
