#include <gsys/gsysModelOcclusionQuery.h>

namespace gsys {

void ModelOcclusionQuery::destroy(ModelOcclusionQuery* query) {
    if (query)
        delete query;
}

}  // namespace gsys
