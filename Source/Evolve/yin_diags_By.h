/// By

/// open files
std::ofstream ofs;
if ( ParallelDescriptor::IOProcessor() )
{
    ofs.open("By"+std::to_string(step+1)+".txt",
        std::ofstream::out | std::ofstream::app);
    ofs << std::fixed << std::setprecision(14) << std::scientific;
}

/// declare array for all data
Real arrall[nx][nz];
for (int i = 0; i < nx; ++i) {
for (int k = 0; k < nz; ++k) {
    arrall[i][k] = 0.0;
}
}

/// loop over boxes
for (MFIter mfi(By); mfi.isValid(); ++mfi)
{

    /// This is the valid Box of the current FArrayBox.
    /// By "valid", we mean the original ungrown Box in BoxArray.
    auto box = mfi.validbox();

    /// get indices
    auto lo = lbound(box);
    auto hi = ubound(box);

    /// Obtain Array4 from FArrayBox.
    auto arr = By.array(mfi);

    /// loops over indices
    int j = (hi.y-lo.y)/2;
    for (int i = lo.x; i <= hi.x; ++i) {
    for (int k = lo.z; k <= hi.z; ++k) {
        Real F = 0.5 * ( arr(i,j,k) + arr(i,j+1,k) );
        arrall[i][k] = F;
    }
    }

}

/// reduce sum
for (int i = 0; i < nx; ++i) {
for (int k = 0; k < nz; ++k) {
    Real buf = arrall[i][k];
    ParallelDescriptor::ReduceRealSum(buf);
    arrall[i][k] = buf;
}
}

/// write
if ( ParallelDescriptor::IOProcessor() )
{
    for (int i = 0; i < nx; ++i)
    {
        for (int k = 0; k < nz; ++k)
        {
            ofs << arrall[i][k] << " ";
        }
        ofs << std::endl;
    }
}

/// close file
if ( ParallelDescriptor::IOProcessor() )
{ ofs.close(); }
