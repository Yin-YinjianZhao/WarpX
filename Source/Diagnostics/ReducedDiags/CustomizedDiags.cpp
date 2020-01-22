#include "CustomizedDiags.H"
#include "WarpX.H"
#include "WarpXConst.H"
#include "AMReX_REAL.H"
#include "AMReX_ParticleReduce.H"
#include <iostream>
#include <cmath>

using namespace amrex;

/// constructor
CustomizedDiags::CustomizedDiags (std::string rd_name)
: ReducedDiags{rd_name}
{

    if (ParallelDescriptor::IOProcessor())
    {
        if ( m_IsNotRestart )
        {
            /// open file
            std::ofstream ofs;
            ofs.open(m_path + m_rd_name + ".txt",
                std::ofstream::out | std::ofstream::app);

            #include "HeaderRow.h"

            /// close file
            ofs.close();
        }
    }

}
///< end constructor

/// customized function
void CustomizedDiags::ComputeDiags (int step)
{

    #include "ComputeDiags.h"

}
///< end void CustomizedDiags::ComputeDiags
