#include "Game/AI/Action/actionPlayASForDemoPreMove.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

PlayASForDemoPreMove::PlayASForDemoPreMove(const InitArg& arg) : PlayASForDemo(arg) {}

PlayASForDemoPreMove::~PlayASForDemoPreMove() = default;

bool PlayASForDemoPreMove::init_(sead::Heap* heap) {
    return PlayASForDemo::init_(heap);
}

// NON_MATCHING: register allocation only (the original loads the home translation z, y, x into s9, s10, s11 before the
// first root motion query; here x, y, z).
void PlayASForDemoPreMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForDemo::enter_(params);
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    auto* model = actor->getModel();
    auto* body = actor->getMainBody();
    sead::Matrix34f mtx;
    actor->getHomeMtx(&mtx);
    if (as_list && model) {
        sead::Vector3f pos;
        pos.set(mtx.getTranslation());
        sead::Matrix34f root;
        as_list->sub_710115D4A4(0.0f, &root, true);
        const sead::Vector3f start = root.getTranslation();
        as_list->sub_710115D4A4(as_list->x_5(sub_710021BDC4(), sub_710021BA28(),
                                             &ksys::as::ASList::Unk2::sub_710116323C),
                                &root, true);
        as_list->sub_710115F1D8(0, 0, 0.0f);
        pos -= root.getTranslation() - start;
        mtx.setTranslation(pos);
    }
    if (body) {
        if (body->isAddedToWorld()) {
            actor->setMtx(mtx, false, true);
        } else {
            actor->setMtx(mtx, true, true);
            actor->nullsub_4648();
            body->setTransform(mtx);
        }
    }
    setFinished();
}

bool PlayASForDemoPreMove::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    return true;
}

void PlayASForDemoPreMove::leave_() {
    PlayASForDemo::leave_();
}

void PlayASForDemoPreMove::loadParams_() {
    PlayASForDemo::loadParams_();
}

void PlayASForDemoPreMove::calc_() {}

}  // namespace uking::action
