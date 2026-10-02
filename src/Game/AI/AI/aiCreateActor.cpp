#include "Game/AI/AI/aiCreateActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

CreateActor::CreateActor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActor::~CreateActor() = default;

bool CreateActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActor::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003591E4(nullptr);
}

void CreateActor::leave_() {
    if (_58.isAllocatedOrFailed())
        _58.deleteProc();
}

void CreateActor::loadParams_() {
    getStaticParam(&mCreatePriorityState_s, "CreatePriorityState");
    getStaticParam(&mScale_s, "Scale");
    getStaticParam(&mActorName_s, "ActorName");
}

void CreateActor::sub_71003591E4(ksys::act::ai::InlineParamPack* params) {
    if (_58.isAllocatedOrFailed())
        _58.deleteProc();

    ksys::act::InstParamPack pack;
    pack->addMatrix(mActor->getMtx());
    ksys::act::ActorCreator::addScale(pack, *mScale_s);
    if (*mCreatePriorityState_s == 2)
        ksys::act::ActorCreator::setCreatePriorityState2(pack, mActor);
    else if (*mCreatePriorityState_s == 1)
        ksys::act::ActorCreator::setCreatePriorityState1(pack, mActor);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        m34().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_58, &pack, nullptr,
        1);
    changeChild("生成中", params);
}

const sead::SafeString& CreateActor::m34() {
    return mActorName_s;
}

}  // namespace uking::ai
