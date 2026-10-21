#include "Game/Actor/aiUnk_710244ECF0.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

Unk_710244ecf0::Unk_710244ecf0() = default;

// NON_MATCHING: ours shares one return path (and keeps the result in a callee-saved register) between the two
// branches; the original keeps the accessor destructor call and the return per branch.
bool Unk_710244ecf0::m4(ksys::act::BaseProc* proc) {
    auto* actor = static_cast<ksys::act::Actor*>(proc);

    if (_58.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_58, &accessor);
        sead::Matrix34f mtx;
        const bool found =
            _68.isEmpty() ? accessor.sub_7100D11860(&mtx) : accessor.sub_7100D119A8(&mtx, _68);
        if (!found)
            return false;
        mtx.setMul(mtx, _28);
        actor->mMtx = mtx;
        actor->nullsub_4648();
        if (_18)
            ksys::act::sub_7100EE58C0(actor, mtx);
        return true;
    }

    auto* model = sub_7100D3C770(proc);
    if (!model)
        return false;
    sead::Matrix34f mtx;
    mtx.setMul(model->getMatrix(), _28);
    actor->mMtx = mtx;
    actor->nullsub_4648();
    if (_18)
        ksys::act::sub_7100EE58C0(actor, mtx);
    return true;
}

bool Unk_710244ecf0::m5(ksys::act::BaseProc*) {
    return false;
}
