/// particle
/// loop over species
for (int i_s = 0; i_s < species_number; ++i_s)
{

    /// get mpi rank
    int myproc = ParallelDescriptor::MyProc();

    /// get WarpXParticleContainer class object
    auto & myspc = mypc.GetParticleContainer(i_s);

    /// get mass (amrex:Real)
    auto m = myspc.getMass();

    /// loop over refinement levels
    for (int lev = 0; lev <= level_number; ++lev)
    {

        /// position arrays
        amrex::Gpu::ManagedDeviceVector<ParticleReal> x, y, z;

        /// Loop over boxes
        for (WarpXParIter pti(myspc, lev); pti.isValid(); ++pti)
        {

            /// open file
            std::ofstream ofs;
            ofs.open(species_names[i_s]+std::to_string(step+1)+"_"+
                std::to_string(myproc)+".txt",
                std::ofstream::out | std::ofstream::app);
            ofs << std::fixed << std::setprecision(14)
                << std::scientific;

            /// get particlu arrays
            pti.GetPosition(x, y, z);
            auto & w  = pti.GetAttribs(PIdx::w);
            auto & ux = pti.GetAttribs(PIdx::ux);
            auto & uy = pti.GetAttribs(PIdx::uy);
            auto & uz = pti.GetAttribs(PIdx::uz);

            /// loop over particles
            for (long i = 0; i < ux.size(); i++)
            {
                ofs << x[i];  ofs << " ";
                ofs << y[i];  ofs << " ";
                ofs << z[i];  ofs << " ";
                ofs << ux[i]; ofs << " ";
                ofs << uy[i]; ofs << " ";
                ofs << uz[i]; ofs << " ";
                ofs << w[i];  ofs << std::endl;
            }
            ///< end loop over particles

            /// close file
            ofs.close();

        }
        ///< end loop over boxes
    }
    ///< end loop over refinement levels
}
///< end loop over species
