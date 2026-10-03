#include "Game/AI/AI/aiClusterRenderCheckTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::ai {

ClusterRenderCheckTag::ClusterRenderCheckTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ClusterRenderCheckTag::~ClusterRenderCheckTag() = default;

bool ClusterRenderCheckTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ClusterRenderCheckTag::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("オフ");
    _58 = false;
    _38.bind(this, &ClusterRenderCheckTag::sub_710035404C);
    mFlags.set(Flag::Changeable);
}

bool ClusterRenderCheckTag::sub_710035404C(ksys::map::Unk_71012497f8Entry* entry) {
    if (entry->_80)
        return !_58;
    _58 = true;
    return false;
}

void ClusterRenderCheckTag::calc_() {
    auto* actor = mActor;
    const f32 radius = actor->getScale().x;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    if (auto* mgr = ksys::map::PlacementMgr::instance())
        mgr->sub_71011EB40C(&pos, radius, &_38);
    if (!_58)
        actor->m107();
    if (_58 && !isCurrentChild("オン"))
        changeChild("オン");
}

void ClusterRenderCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ClusterRenderCheckTag::loadParams_() {}

}  // namespace uking::ai
