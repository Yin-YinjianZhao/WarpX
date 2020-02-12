int output_freq = 0;
int output_Ex   = 0;
int output_Ey   = 0;
int output_Ez   = 0;
int output_Bx   = 0;
int output_By   = 0;
int output_Bz   = 0;
int output_P    = 0;
ParmParse pp("yin");
pp.query("output_freq", output_freq);
pp.query("output_Ex",   output_Ex);
pp.query("output_Ey",   output_Ey);
pp.query("output_Ez",   output_Ez);
pp.query("output_Bx",   output_Bx);
pp.query("output_By",   output_By);
pp.query("output_Bz",   output_Bz);
pp.query("output_P",    output_P);

int step = -1;

if ( output_freq > 0 )
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
    if (output_Ex)
    {
        #include "yin_diags_Ex.h"
    }
    if (output_Ey)
    {
        #include "yin_diags_Ey.h"
    }
    if (output_Ez)
    {
        #include "yin_diags_Ez.h"
    }
    if (output_Bx)
    {
        #include "yin_diags_Bx.h"
    }
    if (output_By)
    {
        #include "yin_diags_By.h"
    }
    if (output_Bz)
    {
        #include "yin_diags_Bz.h"
    }

    /// output particle data
    if (output_P)
    {
        #include "yin_diags_P.h"
    }
}
