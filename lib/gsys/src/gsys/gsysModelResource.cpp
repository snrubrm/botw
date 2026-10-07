#include <gsys/gsysModelResource.h>
#include <nn/g3d/ResFile.h>

namespace gsys {
ModelResource::CreateArg::CreateArg(void* file)
    : file(file), _818(true), _81a(true), _81b(false), _81c(false), buffer_count(-1),
      callback(nullptr) {}

void ModelResource::sub_7100C0B764(ModelResource* resource) {
    delete resource;
}

size_t ModelResource::getResFileSize() const {
    return mResFile->GetFileSize();
}
}  // namespace gsys
