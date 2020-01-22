#ifndef WARPX_DIAGNOSTICS_REDUCEDDIAGS_CUSTOMIZEDDIAGS_H_
#define WARPX_DIAGNOSTICS_REDUCEDDIAGS_CUSTOMIZEDDIAGS_H_

#include "ReducedDiags.H"
#include <fstream>

/**
 *  This class contains a customized function.
*/
class CustomizedDiags : public ReducedDiags
{
public:

    /** constructor
     *  @param[in] rd_name reduced diags names */
    CustomizedDiags(std::string rd_name);

    virtual void ComputeDiags(int step) override final;

};
///< end class CustomizedDiags

#endif // WARPX_DIAGNOSTICS_REDUCEDDIAGS_CUSTOMIZEDDIAGS_H_
