#include "Game/Actor/AI/aiCheckLineOfSightSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <math/seadVector.h>

namespace uking::ai {

CheckLineOfSightSelector::CheckLineOfSightSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CheckLineOfSightSelector::~CheckLineOfSightSelector() = default;

bool CheckLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: backend store pairing only — the original stores the negated x/y
// with separate str (with the z load interleaved); ours pairs them into stp.
void CheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* nav = mActor->m45();
    auto* controller = mActor->getCharacterController();
    if (!nav) {
        changeChild("全方向失敗", params);
        return;
    }
    if (!controller) {
        changeChild("全方向失敗", params);
        return;
    }
    sead::Vector3f vec = controller->get64();
    m34(&vec);
    if (vec.dot(controller->get64()) >= 0.0f) {
        sead::Vector3f dir = controller->get64();
        if (sub_7100346AA4(nav, &dir)) {
            changeChild("前方成功", params);
        } else {
            dir.x = -dir.x;
            dir.y = -dir.y;
            dir.z = -dir.z;
            if (sub_7100346AA4(nav, &dir)) {
                changeChild("後方成功", params);
            } else {
                changeChild("全方向失敗", params);
            }
        }
    } else {
        sead::Vector3f dir = controller->get64();
        const f32 x = dir.x;
        const f32 y = dir.y;
        const f32 z = dir.z;
        dir.x = -x;
        dir.y = -y;
        dir.z = -z;
        if (sub_7100346AA4(nav, &dir)) {
            changeChild("後方成功", params);
        } else {
            dir.x = x;
            dir.y = y;
            dir.z = z;
            if (sub_7100346AA4(nav, &dir)) {
                changeChild("前方成功", params);
            } else {
                changeChild("全方向失敗", params);
            }
        }
    }
}

void CheckLineOfSightSelector::calc_() {
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void CheckLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CheckLineOfSightSelector::loadParams_() {
    getStaticParam(&mDirectionNum_s, "DirectionNum");
    getStaticParam(&mDirectionAngle_s, "DirectionAngle");
    getStaticParam(&mDistance_s, "Distance");
    getStaticParam(&mRadiusScale_s, "RadiusScale");
}

bool CheckLineOfSightSelector::isFinished() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFinished())
        return true;
    return child && child->isFinished();
}

bool CheckLineOfSightSelector::isFailed() const {
    auto* child = getCurrentChild();
    if (ActionBase::isFailed())
        return true;
    return child && child->isFailed();
}

void CheckLineOfSightSelector::m34(sead::Vector3f* out) {}

}  // namespace uking::ai

namespace uking::ai {

// NON_MATCHING: one register choice in the tolerance product.
bool CheckLineOfSightSelector::sub_7100346AA4(ksys::phys::NavMeshCharacter* nav, sead::Vector3f* dir) {
    ksys::phys::HavokAI::Unk2 query;
    query._30 = 0xff;
    query.distance = *mDistance_s;
    query.tolerance = nav->getRadiusMaybe() * *mRadiusScale_s;
    query.dir = *dir;
    auto* havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
    if (havok->sub_7100F86324(nav, query, nullptr))
        return true;

    const u32 idx = sead::Mathf::rad2idx(*mDirectionAngle_s);
    f32 s, c;
    sead::Mathf::sinCosIdx(&s, &c, idx);
    sead::Vector3f left = *dir;
    sead::Vector3f right = *dir;
    for (s32 i = 0; i < *mDirectionNum_s; ++i) {
        left.set(c * left.x - s * left.z, 0.0f, c * left.z + s * left.x);
        query.dir = left;
        havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
        if (havok->sub_7100F86324(nav, query, nullptr))
            return true;

        right.set(s * right.z + c * right.x, 0.0f, c * right.z - s * right.x);
        query.dir = right;
        havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
        if (havok->sub_7100F86324(nav, query, nullptr))
            return true;
    }
    return false;
}

}  // namespace uking::ai
