#include <gsys/gsysModelResource.h>

namespace gsys {
ModelResource::CreateArg::CreateArg(void* file)
    : file(file), _818(true), _81a(true), _81b(false), _81c(false), buffer_count(-1),
      callback(nullptr) {}

void ModelResource::sub_7100C0B764(ModelResource* resource) {
    delete resource;
}
}  // namespace gsys
