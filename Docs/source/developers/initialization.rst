.. _developers-initialization:

Initialization
==============

The initialization of WarpX is done in the function call
``warpx.InitData()`` in ``Source/main.cpp``,
where ``warpx`` is a variable of the ``WarpX`` class.
``WarpX::InitData()`` is defined in
``Source/Initialization/WarpXInitData.cpp``.
The structure of the function ``WarpX::InitData()``
is as follows.

* ``If the simulation is a new run:``
    * Compute time step length by calling function ``ComputeDt()``.
    * Call function ``InitFromScratch()``,
      where particle data will be allocated and initialized,
      initial space-charge field will be computed, and
      Perfectly Matched Layers (PML) will be initialized.

* ``If the simulation is a restart:``
    * Call function ``InitFromCheckpoint()`` to initialize the simulation from a Checkpoint.
    * If ``is_synchronized``, call ``ComputeDt()``.
    * Call function ``PostRestart()``.

Compute time step length ``WarpX::ComputeDt()``
-----------------------------------------------

``WarpX::ComputeDt()`` is defined in
``Source/Evolve/WarpXEvolve.cpp``,
which computes the simulation time step length :math:`\Delta t`.

If the ``yee`` solver is used, :math:`\Delta t` will be determined as follows.
If the simulation coordinate is Cartesian,
according to the Courant-Friedrichs-Lewy (CFL) limit,

.. math::
    \Delta t  = \dfrac{ c f_{CFL} }
    { [(\Delta x)^{-2} + (\Delta y)^{-2} + (\Delta z)^{-2}]^{1/2} },

where :math:`f_{CFL}` denotes the input parameter ``warpx.cfl``,
the :math:`\Delta y` term is discarded if the dimension is 2-D X-Z.
If the simulation coordinate is 2-D R-Z cylindrical,

.. math::
    \Delta t  = \dfrac{ c f_{CFL} }
    { [\alpha (\Delta r)^{-2} + (\Delta z)^{-2}]^{1/2} },

where :math:`\alpha` is a special coefficient.

If the ``ckc`` solver is used, :math:`\Delta t` will be determined as,

.. math::
    \Delta t  = \dfrac{ f_{CFL} \Delta d_{min} }{ c },

where :math:`\Delta d_{min}` denotes the minimum value among
:math:`\Delta x`,
:math:`\Delta y`,
:math:`\Delta z`,
and
:math:`\Delta r`.

The above computation is for the finest level,
for all coarser levels,
:math:`\Delta t` will be multiplied by a factor.

Initialize from scratch ``WarpX::InitFromScratch()``
----------------------------------------------------

(1) New grids are made by calling ``AmrCore::InitFromScratch(time)``,
where ``time = 0.0``.
(2) Particle data is allocated by calling ``mypc->AllocData()``,
where ``mypc`` is a unique pointer of class ``MultiParticleContainer``.
(3) Initialize particle data by calling ``mypc->InitData()``.
(4) Compute initial space-charge fields by calling ``ComputeSpaceChargeField(reset_fields)``.
(5) Initialize PML by calling ``InitPML()``.

Allocate particle data ``AllocData()``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``AllocData()`` is defined in class ``MultiParticleContainer``
to loop over every species,
and call another ``AllocData()`` defined in class
``WarpXParticleContainer``
to call ``reserveData()`` and ``resizeData()``
which are AMReX functions to reserve and resize data on all levels.

Initialize particle data ``InitData()``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``InitData()`` is defined in class ``MultiParticleContainer``
to loop over every species,
and call another ``InitData()`` defined in class
``PhysicalParticleContainer``, which is inherited from class
``WarpXParticleContainer``.
In function ``PhysicalParticleContainer::InitData()``
in the file ``PhysicalParticleContainer.cpp``,
if ``<species>.do_field_ionization`` equals 1,
function ``InitIonizationModule()``
will be called to initialize the ionization module.
Then, ``AddParticles(0)`` is called to add particles on level 0,
in which functions ``AddNParticles``, ``AddGaussianBeam``,
and ``AddPlasma`` could be called
based on user's input parameters.
Then, ``Redistribute()`` is called to redistribute particles.

Initialize from Checkpoint ``WarpX::InitFromCheckpoint``
--------------------------------------------------------

Function ``WarpX::InitFromCheckpoint()`` is
defined in ``Source/Diagnostics/WarpXIO.cpp``.
(1) Read information from the header file ``WarpXHeader``:
number of levels; current time step and physical time;
time step length; if moving window is used;
coordinates of the lower and upper corners;
read and set boxes; masses and charges of species.
(2) Read all field data on all levels.
(3) Initialize PML if it is used.
(4) Allocate particle data.










General simulation initialization
---------------------------------

Regular simulation
~~~~~~~~~~~~~~~~~~

Running in a boosted frame
~~~~~~~~~~~~~~~~~~~~~~~~~~

Field initialization
--------------------

Particle initialization
-----------------------
