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
    * Call function ``InitFromScratch()``.

* ``If the simulation is a restart:``
    * Call function ``InitFromCheckpoint()``.
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
:math:`\Delta y = 0` if the dimension is two.
If the simulation coordinate is RZ cylindrical,

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
(5) Initialize Perfectly Matched Layers (PML) by calling ``InitPML()``.
(6) If electrostatic mode is turned on,
``getLevelMasks(masks)`` and ``getLevelMasks(gather_masks, n_buffer + 1)``
are called.

Allocate particle data ``AllocData()``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``AllocData()`` is defined in class ``MultiParticleContainer``
to loop over every species,
and call another ``AllocData()`` defined in class
``WarpXParticleContainer``
to call ``reserveData()`` and ``resizeData()``
which are AMReX functions to reserve and resize data on all levels.














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
