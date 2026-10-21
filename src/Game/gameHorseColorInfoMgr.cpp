#include "Game/gameHorseColorInfoMgr.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"

SEAD_SINGLETON_DISPOSER_IMPL(HorseColorInfoMgr)

// NON_MATCHING: createInstance inlines this constructor; the original zeroes +0x28..+0x48 with three
// 8-byte stores and one 4-byte store (ours merges them into two 16-byte stores) and stores
// SingletonDisposer_::sStaticDisposer before the instance's vptr (ours after it).
HorseColorInfoMgr::HorseColorInfoMgr()
    : _28(0), _29(0), _2a{}, _2c(0), mHeap(nullptr), mModel(nullptr), mTextureModel(nullptr),
      mLoadTask(sead::IDisposer::HeapNullOption::DoNotAppendDisposerIfNoHeapSpecified) {
    mLoadDelegate.bind(this, &HorseColorInfoMgr::loadResources);
}

HorseColorInfoMgr::~HorseColorInfoMgr() {
    sub_710094C810();
}

// NON_MATCHING: same calls and constants; the original materialises 0x40060000 in two steps
// (mov/movk), keeps the resource in a callee-saved register and places the name SafeString temporary
// in a 0x10 larger frame (our temporary sits at the bottom of the frame).
bool HorseColorInfoMgr::createModels() {
    mHeap = sead::ExpHeap::tryCreate(0x40060000, "HorseColorInfoMgr", uking::ui::getHeap(), 8,
                                     sead::Heap::cHeapDirection_Reverse, false);
    if (!mHeap)
        return false;

    gsys::Model::CreateArg model_arg;
    model_arg._4 = 2;
    gsys::ModelAnimation::CreateArg anim_arg;
    anim_arg._4 = 4;

    if (auto* resource = mModelRes.sub_71011FC6AC()) {
        mModel = gsys::Model::create(resource, "HorseColorInfo_Body", model_arg, mHeap, nullptr);
        if (mModel)
            mModel->createAnimation(&resource, 1, anim_arg, mHeap);
    }

    if (auto* resource = mTextureRes.sub_71011FC6AC()) {
        mTextureModel =
            gsys::Model::create(resource, "HorseColorInfo_Mane", model_arg, mHeap, nullptr);
        if (mTextureModel) {
            if (auto* anim_resource = mAnimRes.sub_71011FC6AC())
                mTextureModel->createAnimation(&anim_resource, 1, anim_arg, mHeap);
        }
    }

    // The result is discarded in the original.
    mHeap->adjust();
    return mModel && mTextureModel;
}

void HorseColorInfoMgr::sub_710094C810() {
    _28 &= ~2;
    _29 = 0;
    mLoadTask.removeFromQueue();
    if (mModel) {
        gsys::Model::sub_7100BF69F8(mModel);
        mModel = nullptr;
    }
    if (mTextureModel) {
        gsys::Model::sub_7100BF69F8(mTextureModel);
        mTextureModel = nullptr;
    }
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    if (mModelRes.requestedLoad())
        mModelRes.requestUnload();
    if (mTextureRes.requestedLoad())
        mTextureRes.requestUnload();
    if (mAnimRes.requestedLoad())
        mAnimRes.requestUnload();
    _2c = 0;
}

void HorseColorInfoMgr::sub_710094C638() {
    _28 = 0;
}

// NON_MATCHING: the lane is a 4-byte SEAD_ENUM-like class, so converting it to int spills it to the
// stack; the original reuses the lane temporary's slot (sp+8) for the mask, ours gets a separate
// slot (sp+4). The rest of the body is instruction-identical.
namespace {
// 0x71025d6710: the horse model string table, filled in by sinitHorseModelStrings 0x710094d3c8. Only
// the three model paths used here are named (0x168 / 0x178 / 0x188); the prefix and the tail hold the
// colour values and further names the other two functions of the TU read. Placeholder name and layout.
struct HorseModelStrings {
    u8 _0[0x168];
    sead::SafeString model;      // 0x168
    sead::SafeString maneModel;  // 0x178
    sead::SafeString maneAnim;   // 0x188
};
HorseModelStrings sHorseModelStrings{
    {}, {"Model/Horse_Link.bfres"}, {"Model/Horse_Link_Mane.bfres"},
    {"Model/Horse_Link_Mane_Animation.bfres"}};
}  // namespace

bool HorseColorInfoMgr::loadResources(void* arg) {
    ksys::res::LoadRequest request;
    request.mRequester = "HorseColorInfoMgr";

    ksys::res::Handle::Status status = ksys::res::Handle::Status::_1;
    sead::Resource* model = mModelRes.load(sHorseModelStrings.model, &request, &status);
    status = ksys::res::Handle::Status::_1;
    sead::Resource* mane = mTextureRes.load(sHorseModelStrings.maneModel, &request, &status);
    status = ksys::res::Handle::Status::_1;
    sead::Resource* anim = mAnimRes.load(sHorseModelStrings.maneAnim, &request, &status);
    if (model && mane && anim && createModels())
        return true;

    if (mModelRes.requestedLoad())
        mModelRes.requestUnload();
    if (mTextureRes.requestedLoad())
        mTextureRes.requestUnload();
    if (mAnimRes.requestedLoad())
        mAnimRes.requestUnload();
    if (mModel) {
        gsys::Model::sub_7100BF69F8(mModel);
        mModel = nullptr;
    }
    if (mTextureModel) {
        gsys::Model::sub_7100BF69F8(mTextureModel);
        mTextureModel = nullptr;
    }
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    return false;
}

void HorseColorInfoMgr::sub_710094D018() {
    if (_2c != 0) {
        if (_28 & 1)
            _28 &= ~1;
        return;
    }
    _28 &= ~2;
    _29 = 0;
    ksys::LowPrioThreadMgr::Request request;
    request.delegate = &mLoadDelegate;
    request.name = "HorseColorInfoMgr";
    request.task = &mLoadTask;
    // The original reaches the lane through a SEAD_ENUM-like 4-byte class: the conversion to int
    // spills the value to the stack, and the mask is shifted through a second such value.
    const ksys::LowPrioThreadMgr::Lane lane = ksys::LowPrioThreadMgr::Lane::_2;
    const ksys::LowPrioThreadMgr::Lane mask = 1 << int(lane);
    request.flags.setDirect(int(mask));
    request.lane_id = lane;
    ksys::evt::submitLowPriorityRequest(request);
    _2c = 1;
}

void HorseColorInfoMgr::sub_710094D0F8() {
    if (_2c == 2)
        _28 |= 1;
}
