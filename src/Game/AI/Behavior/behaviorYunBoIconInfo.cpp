#include "Game/AI/Behavior/behaviorYunBoIconInfo.h"
#include "Game/AI/AI/aiGoronHeroDescendentRoot.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {
void sub_7100A9A694(const UiSubsys1PinArg* arg);
}

namespace uking::behavior {

YunBoIconInfo::YunBoIconInfo(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

YunBoIconInfo::~YunBoIconInfo() = default;

bool YunBoIconInfo::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: actor access is scheduled after pin initialization.
void YunBoIconInfo::m7() {
    ui::UiSubsys1PinArg arg{};
    mActor->getMtx().getTranslation(arg.pos);
    switch (*mType_s) {
    case 0:
        arg.index = 1;
        break;
    case 1:
        arg.index = 0;
        break;
    }
    ui::sub_7100A9A694(&arg);
    ai::sub_7100A9A6AC(*mVisible_s);
}

void YunBoIconInfo::m8() {}

void YunBoIconInfo::m9() {}

void YunBoIconInfo::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mVisible_s, "Visible");
}

}  // namespace uking::behavior
