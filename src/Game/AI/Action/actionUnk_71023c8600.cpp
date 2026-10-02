#include "Game/AI/Action/actionUnk_71023c8600.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

Unk_71023c8600::Unk_71023c8600(ksys::act::ai::ActionBase* owner) : Unk_71025afc58(owner) {}

Unk_71023c8600::~Unk_71023c8600() {
    if (_30.isEmpty())
        return;
    if (auto* parts = mOwner->getActor()->m101())
        parts->sub_7100D3CFEC(_30);
}

bool Unk_71023c8600::init_(sead::Heap* heap) {
    if (_30.isEmpty())
        return true;
    if (auto* parts = mOwner->getActor()->m101()) {
        if (!parts->sub_7100D3CED8(_30, heap))
            return false;
    }
    return true;
}

void Unk_71023c8600::sub_71002A7A38() {
    if (mState != 0)
        return;
    if (!(*mIgniteHandle_d)->isProcReady())
        return;
    mOwner->getActor()->setConnectedCalcChild((*mIgniteHandle_d)->getProc(), false);
    mState = 1;
}

void Unk_71023c8600::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mOwner->getActor()->getConnectedCalcChild()) {
        mFlags.set(Flag::Failed);
        mFlags.reset(Flag::Finished);
        return;
    }
    mState = 0;
}

void Unk_71023c8600::calc_() {
    if (isFinished() || isFailed())
        return;

    switch (mState) {
    case 0: {
        auto* as_list = mOwner->getActor()->getASList();
        if (!as_list)
            return;
        if (!as_list->x(0x45, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
            return;
        auto* proc = (*mIgniteHandle_d)->getProc();
        mOwner->getActor()->setConnectedCalcChild(proc, false);
        if (!_30.isEmpty()) {
            if (auto* parts = mOwner->getActor()->m101()) {
                if (sead::DynamicCast<ksys::act::Actor>(proc))
                    parts->sub_7100D3D108(_30, proc);
            }
        }
        mState = 1;
        break;
    }
    case 1:
        if (!mOwner->getActor()->getConnectedCalcChild()) {
            mState = 4;
            break;
        }
        if (auto* handle = *mIgniteHandle_d)
            sub_71005DC640(mOwner->getActor(), handle, *mGrabIdx_s);
        mState = 2;
        break;
    case 2:
        if (auto* child = mOwner->getActor()->getConnectedCalcChild()) {
            if (child->isCalc())
                mState = 3;
        } else {
            mState = 4;
        }
        break;
    }
}

void Unk_71023c8600::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}
