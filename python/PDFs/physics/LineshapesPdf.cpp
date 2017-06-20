#include <pybind11/pybind11.h>

#include <goofit/Variable.h>
#include <goofit/PDFs/physics/LineshapesPdf.h>
#include <goofit/PDFs/physics/ResonancePdf.h>

using namespace GooFit;
namespace py = pybind11;

void init_LineshapesPdf(py::module &m) {
    py::class_<LineshapesPdf, GooPdf>(m, "LineshapesPdf")
        .def(py::init<std::string, Variable *, Variable *, unsigned int, unsigned int, *>())

        ;
}








