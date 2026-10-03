#include "Game/AI/AI/aiGetItemNormal.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GetItemNormal::GetItemNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool GetItemNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GetItemNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::enableAttClient(mActor, "NoticeDo");
    changeChild("待機");
    _38 = true;
}

void GetItemNormal::calc_() {
    if (isCurrentChild("ゲット"))
        return;
    auto* actor = mActor;
    if (!m34())
        return;
    if (triggereGetItemDemoMaybe(actor, m35(), _38)) {
        ksys::act::disableAttClient(actor, "NoticeDo");
        _38 = false;
    } else {
        ksys::act::disableAttClient(mActor, "NoticeDo");
        changeChild("ゲット");
    }
}

bool GetItemNormal::m34() {
    auto* actor = mActor;
    if (sub_7100738E70(actor))
        return true;
    return sub_7100738DF0(actor);
}

void GetItemNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GetItemNormal::loadParams_() {}

}  // namespace uking::ai
