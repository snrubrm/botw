#include "Game/AI/Action/actionForceSetPlayerRestartPosAngle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"

// Declaration only: receiver/argument ABI is proved; source namespace remains unknown.
ksys::map::Object* sub_7100EE5240(ksys::act::Actor* actor, const sead::SafeString& anchor,
                               const sead::SafeString& unique);

namespace uking::action {

ForceSetPlayerRestartPosAngle::ForceSetPlayerRestartPosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceSetPlayerRestartPosAngle::~ForceSetPlayerRestartPosAngle() = default;

bool ForceSetPlayerRestartPosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ForceSetPlayerRestartPosAngle::oneShot_() {
    sub_7100138D68();
    return true;
}

// NON_MATCHING: the natural map/accessor branches and diagnostic string lifetime differ.
void ForceSetPlayerRestartPosAngle::sub_7100138D68() {
    auto& link = ksys::evt::sub_7100DC85D4(mActor);
    if (!link.hasProcInCalcState())
        return;
    auto* object = sub_7100EE5240(mActor, mAnchorName_d, mUniqueName_d);
    if (object) {
        auto* info = ksys::act::PlayerInfo::instance();
        if (!info)
            return;
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&info->getPlayerLink(), &player);
        const sead::Vector3f position = object->getTranslate();
        const f32 angle = object->getRotate().y * 57.295776f;
        player.setRestartBuf(position, angle);
    } else {
        sead::FixedSafeString<128> name;
        name.appendWithFormat("%s", mAnchorName_d.cstr());
        if (!mUniqueName_d.isEmpty())
            name.appendWithFormat("(ユニーク名：%s)", mUniqueName_d.cstr());
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
    }
}

void ForceSetPlayerRestartPosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

}  // namespace uking::action
