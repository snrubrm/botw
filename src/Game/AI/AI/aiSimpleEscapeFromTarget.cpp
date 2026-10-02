#include "Game/AI/AI/aiSimpleEscapeFromTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

SimpleEscapeFromTarget::SimpleEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleEscapeFromTarget::~SimpleEscapeFromTarget() = default;

bool SimpleEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = _60 = *mKeepTime_s;
    sub_710056CF84();
}

void SimpleEscapeFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleEscapeFromTarget::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SimpleEscapeFromTarget::m34() {
    setFailed();
    return false;
}

void SimpleEscapeFromTarget::m35(bool finished) {
    if (finished)
        setFinished();
    else
        setFailed();
}

void SimpleEscapeFromTarget::m36(sead::Vector3f* dir) {
    dir->set(*mTargetPos_d);
    *dir -= mActor->getMtx().getTranslation();
    dir->y = 0.0f;
    dir->normalize();
}

void SimpleEscapeFromTarget::m37() {
    sead::Vector3f pos;
    if (sub_710056D354(&pos)) {
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        return;
    }
    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17)
        m34();
}

bool SimpleEscapeFromTarget::sub_710056D354(sead::Vector3f* out) {
    sead::Vector3f dir;
    m36(&dir);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f d;
    d = dir;
    if (!m39(d)) {
        m38(&d, 1);
        if (!m39(d)) {
            m38(&d, 2);
            if (!m39(d)) {
                m38(&d, 3);
                if (!m39(d))
                    return false;
            }
        }
    }
    d *= *mSpaceDist_s;
    d += pos;
    *out = d;
    return true;
}

void SimpleEscapeFromTarget::sub_710056CF84() {
    auto* nav = mActor->m45();
    sead::Vector3f pos;
    if ((nav && (nav->_2a4 & 0xffff) == 0x17) || !sub_710056D354(&pos)) {
        m34();
        return;
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("後退移動", &params);
}

}  // namespace uking::ai
