#include <algorithm>
#include "Game/AI/Action/actionGuardianMoveTo.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"

void Unk_7100041da4::m0(Data* data, ksys::act::Actor* actor) {
    if (sub_710003955C(actor)->_70 == 2) {
        if (auto* rail = sub_7100EEF034(actor, 0)) {
            sead::Vector3f pos;
            actor->getMtx().getTranslation(pos);
            const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
            sead::Vector3f target;
            rail->calcTranslate(&target, progress);
            sead::Vector3f dir = target - pos;
            const f32 dist = sead::Mathf::clampMax(dir.normalize(), 6.0f);
            data->_0 = dir;
            data->_c = dir;
            data->_18 = dist;
            data->_34 = data->_b8;
            data->_40 = sead::Vector3f::ey;
            return;
        }
    }
    const f32 len = data->_28.length();
    if (len > 0.0f)
        data->_c.setScale(data->_28, 1.0f / len);
    data->_0 = data->_1c;
    data->_18 = 0.0f;
    data->_34 = data->_b8;
    data->_40 = sead::Vector3f::ey;
}

namespace uking::action {

GuardianMoveTo::GuardianMoveTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianMoveTo::~GuardianMoveTo() = default;

bool GuardianMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (auto* data = sub_71001928B0())
        data->_50 = static_cast<Unk_7100041da4*>(this);
}

void GuardianMoveTo::leave_() {
    ksys::act::ai::Action::leave_();
    if (auto* data = sub_71001928B0())
        data->_50 = nullptr;
}

void GuardianMoveTo::loadParams_() {}

void GuardianMoveTo::calc_() {
    ksys::act::ai::Action::calc_();
}

uking::act::Guardian* GuardianMoveTo::sub_7100192798() {
    return sead::DynamicCast<uking::act::Guardian>(mActor);
}

uking::act::Guardian* GuardianMoveTo::sub_7100192824() {
    return sead::DynamicCast<uking::act::Guardian>(mActor);
}

uking::act::Guardian::Unk1* GuardianMoveTo::sub_7100192770() {
    return sub_71001928B0();
}

uking::act::Guardian::Unk1* GuardianMoveTo::sub_71001928B0() {
    auto* actor = mActor;
    if (!actor)
        return nullptr;
    if (auto* guardian = sead::DynamicCast<uking::act::Guardian>(actor))
        return guardian->_15b0;
    if (auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()))
        if (auto* guardian = sead::DynamicCast<uking::act::Guardian>(parent))
            return guardian->_15b0;
    return nullptr;
}

}  // namespace uking::action
