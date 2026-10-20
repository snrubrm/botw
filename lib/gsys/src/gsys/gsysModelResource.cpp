#include <gsys/gsysModelResource.h>
#include <gsys/gsysG3dResAnimationEx.h>
#include <gsys/gsysG3dResModelEx.h>
#include <nn/g3d/ResFile.h>

namespace gsys {

void ModelResource::CreateArg::pushBack(ModelShaderArchive* archive) {
    shader_archives.pushBack(archive);
}
ModelResource::CreateArg::CreateArg(void* file)
    : file(file), _818(true), _81a(true), _81b(false), _81c(false), buffer_count(-1),
      callback(nullptr) {}

void ModelResource::sub_7100C0B764(ModelResource* resource) {
    delete resource;
}

size_t ModelResource::getResFileSize() const {
    return mResFile->GetFileSize();
}

G3dResModelEx* ModelResource::getResModelEx(s32 index) const {
    return &mResModelExs[index];
}

G3dResAnimationEx* ModelResource::getG3dResSkeletalAnmEx(s32 index) {
    return &mSkeletalAnms[index];
}

G3dResAnimationEx* ModelResource::getG3dResMaterialAnmEx(MaterialAnmType type, s32 index) {
    return &mMaterialAnms[static_cast<s32>(type)][index];
}

bool ModelResource::isValid() const {
    mCS.lock();
    const bool valid = (mFlags >> 5) & 1;
    mCS.unlock();
    return valid;
}

void ModelResource::countUpAnimationReferenceCounter() {
    mAnimationReferenceCounter.increment();
}

void ModelResource::countDownAnimationReferenceCounter() {
    mAnimationReferenceCounter.decrement();
}

s32 ModelResource::getAnimationReferenceCounter() const {
    return mAnimationReferenceCounter.load();
}
}  // namespace gsys
