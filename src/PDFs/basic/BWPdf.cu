#include <goofit/PDFs/basic/BWPdf.h>
#include <goofit/PDFs/ParameterContainer.h>

namespace GooFit {

__device__ fptype device_BW(fptype *evt, ParameterContainer &pc) {
    int id = pc.getObservable(0);

    fptype x      = evt[id];
    fptype mean   = pc.getParameter(0);
    fptype gamma  = pc.getParameter(1);
    fptype rootPi = -2. * atan2(-1.0, 0.0);
    fptype ret    = (gamma / ((x - mean) * (x - mean) + gamma * gamma / 4)) / (2 * rootPi);

    pc.incrementIndex(1, 2, 0, 1, 1);

    return ret;
}

__device__ device_function_ptr ptr_to_BW = device_BW;

__host__ BWPdf::BWPdf(std::string n, Observable _x, Variable mean, Variable width)
    : GooPdf(n, _x) {
    registerParameter(mean);
    registerParameter(width);

    initialize();
}

__host__ void BWPdf::recursiveSetIndices() {
    GOOFIT_TRACE("host_function_table[{}] = {}({})", num_device_functions, getName(), "ptr_to_BW");
    GET_FUNCTION_ADDR(ptr_to_BW);

    host_function_table[num_device_functions] = host_fcn_ptr;
    functionIdx                               = num_device_functions++;

    populateArrays();
}

} // namespace GooFit
