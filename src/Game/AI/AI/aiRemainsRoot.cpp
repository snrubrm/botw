#include "Game/AI/AI/aiRemainsRoot.h"
#include "Game/AI/aiUnk_71002CA6AC.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

RemainsRoot::RemainsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsRoot::~RemainsRoot() = default;

bool RemainsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool RemainsRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;
    auto* root = sead::DynamicCast<RemainsRoot>(other);
    if (!root)
        return false;
    ui::sub_7100A9A644(mActor);
    _48 = root->_48;
    _49 = mActor->getName().findIndex("_Far") != -1;
    return true;
}

void RemainsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _49 = actor->getName().findIndex("_Far") != -1;
    ui::sub_7100A9A644(actor);
    _48 = GameScene::getCurrentMapType() == "MainField";
    m34();
    m35(true);
}

void RemainsRoot::calc_() {
    if (_48) {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sub_71002CA6AC(*mRemainsTypeID_s, pos);
    }
}

void RemainsRoot::m34() {
    auto* actor = mActor;
    if (auto* rail = sub_7100EEF034(actor, 0)) {
        if (_48)
            sub_71002CA954(actor, *mRemainsTypeID_s, rail, *mIsAllowRotAxisX_s);
    }
}

void RemainsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsRoot::loadParams_() {
    getStaticParam(&mRemainsTypeID_s, "RemainsTypeID");
    getStaticParam(&mIsAllowRotAxisX_s, "IsAllowRotAxisX");
}

void RemainsRoot::m35(bool x) {
    m36();
}

void RemainsRoot::m36() {
    if (auto* body = mActor->getMainBody())
        body->setContactNone();
    changeChild("通常行動");
}

}  // namespace uking::ai
