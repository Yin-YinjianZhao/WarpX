/// output frequency
int output_freq = 0;

/// judge if do diags
/// step+1 is the current time step
if ( output_freq > 0 && (step+1) % output_freq == 0 )
{

    /// get WarpX class object
    auto & warpx = WarpX::GetInstance();

    /// get MultiParticleContainer class object
    auto & mypc = warpx.GetPartContainer();

    /// get number of particle species (int)
    auto species_number = mypc.nSpecies();

    /// get species names (std::vector<std::string>)
    auto species_names = mypc.GetSpeciesNames();

    /// get number of level (int)
    auto level_number = warpx.finestLevel();

    /// get MultiFab data at level 0
    auto & Ex = warpx.getEfield(0,0);
    auto & Ey = warpx.getEfield(0,1);
    auto & Ez = warpx.getEfield(0,2);
    auto & Bx = warpx.getBfield(0,0);
    auto & By = warpx.getBfield(0,1);
    auto & Bz = warpx.getBfield(0,2);

    /// get number of cells
    Vector<int> n_cell;
    ParmParse pc("amr");
    pc.getarr("n_cell", n_cell);
    int nx = n_cell[0];
    int ny = n_cell[1];
    int nz = n_cell[2];

    /// output field slice
    {
        #include "yin_diags_Ex.h"
    }
    {
        #include "yin_diags_Ey.h"
    }
    {
        #include "yin_diags_Ez.h"
    }
    {
        #include "yin_diags_Bx.h"
    }
    {
        #include "yin_diags_By.h"
    }
    {
        #include "yin_diags_Bz.h"
    }

    /// output particle data
    {
        #include "yin_diags_P.h"
    }

}
///< end judge if do diags
