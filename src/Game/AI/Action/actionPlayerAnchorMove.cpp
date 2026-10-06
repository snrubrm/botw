#include "Game/AI/Action/actionPlayerAnchorMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"

namespace ksys::act {
// 0x7100ee25f0 (declared only): findLinkReferenceObj for a link (acquires the actor first).
map::Object* findLinkReferenceObj(BaseProcLink* link, const sead::SafeString& unit_config_name,
                                  const sead::SafeString& a3, int* idx);
}  // namespace ksys::act

namespace uking::action {

PlayerAnchorMove::PlayerAnchorMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

PlayerAnchorMove::~PlayerAnchorMove() = default;

bool PlayerAnchorMove::init_(sead::Heap* heap) {
    return PlayerGuidedMove::init_(heap);
}

void PlayerAnchorMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGuidedMove::enter_(params);
}

void PlayerAnchorMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerAnchorMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void PlayerAnchorMove::calc_() {
    PlayerGuidedMove::calc_();
}

// NON_MATCHING: the original copies the object translation as one 8-byte plus one 4-byte move (matched by copying through
// a local, not applied) and sets up the findLinkReferenceObj arguments in the other order (x2 before x3).
bool PlayerAnchorMove::m33(sead::Vector3f* pos) {
    auto& link = ksys::evt::sub_7100DC85D4(mActor);
    if (auto* object = ksys::act::findLinkReferenceObj(&link, mAnchorName_d, mUniqueName_d, nullptr)) {
        *pos = object->getTranslate();
    } else {
        sead::FixedSafeString<128> name;
        if (!mUniqueName_d.isEmpty())
            name.appendWithFormat("(ユニーク名：%s)", mUniqueName_d.cstr());
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.getActorMtx().getTranslation(*pos);
    }
    return true;
}

}  // namespace uking::action
