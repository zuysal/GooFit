#pragma once

#include <goofit/FitControl.h>
#include <goofit/PDFs/MetricPointer.h>
#include <goofit/PDFs/MetricTaker.h>
#include <goofit/PDFs/detail/Globals.h>
#include <goofit/PdfBase.h>
#include <goofit/UnbinnedDataSet.h>
#include <goofit/Version.h>

#include <thrust/device_vector.h>

#ifdef ROOT_FOUND
class TH1D;
#endif

namespace GooFit {

// Forward declare
struct ParameterContainer;
__device__ fptype callFunction(fptype *eventAddress, ParameterContainer &pc);

class GooPdf : public PdfBase {
  public:
    using PdfBase::PdfBase;

    double calculateNLL() override;

    /// NB: This does not project correctly in multidimensional datasets, because all observables
    /// other than 'var' will have, for every event, whatever value they happened to get set to last
    /// time they were set. This is likely to be the value from the last event in whatever dataset
    /// you were fitting to, but at any rate you don't get the probability-weighted integral over
    /// the other observables.
    __host__ std::vector<fptype> evaluateAtPoints(Observable var);

    /// A normalize function. This fills in the host_normalize
    __host__ fptype normalize() override;

    /// Just in case you are British and the previous spelling is offensive
    __host__ fptype normalise() { return normalize(); }

    __host__ virtual fptype integrate(fptype lo, fptype hi) const;
    __host__ bool hasAnalyticIntegral() const override;
    __host__ fptype getValue(EvalFunc evalfunc = EvalFunc::Eval);

    /// Produce a list of probabilies at points
    __host__ std::vector<std::vector<fptype>> getCompProbsAtDataPoints();

    /// Set an equidistant grid based on the stored variable binning
    __host__ UnbinnedDataSet makeGrid();

    __host__ void initialize();
    __host__ void scan(Observable var, std::vector<fptype> &values);
    __host__ void setFitControl(std::shared_ptr<FitControl> fc) override;
    __host__ virtual void setMetrics();
    __host__ void setParameterConstantness(bool constant = true);

    static __host__ int findFunctionIdx(void *dev_functionPtr);
    __host__ void setDebugMask(int mask, bool setSpecific = true) const;

#ifdef ROOT_FOUND
    /// Plot a PDF to a ROOT histogram
    __host__ TH1D *plotToROOT(Observable var, double normFactor = 1, std::string name = "");
#endif

    __host__ void setIndices() override;

  protected:
    __host__ virtual double sumOfNll(int numVars) const;
    std::shared_ptr<MetricTaker> logger;
};

} // namespace GooFit
