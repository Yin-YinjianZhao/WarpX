#! /usr/bin/env python

import sys
import yt
import numpy as np
import matplotlib.pyplot as plt
sys.path.insert(1, '../../../../warpx/Regression/Checksum/')
import checksumAPI

tolerance = sys.float_info.epsilon
print('tolerance = ', tolerance)

filename = 'restart_plt00010'
ds  = yt.load( filename )
ad  = ds.all_data()
xb  = ad['beam',     'particle_position_x'].to_ndarray()
xe  = ad['plasma_e', 'particle_position_x'].to_ndarray()
xp  = ad['plasma_p', 'particle_position_x'].to_ndarray()
zb  = ad['beam',     'particle_position_z'].to_ndarray()
ze  = ad['plasma_e', 'particle_position_z'].to_ndarray()
zp  = ad['plasma_p', 'particle_position_z'].to_ndarray()

filename = 'orig_restart_plt00010'
ds  = yt.load( filename )
ad  = ds.all_data()
xb0 = ad['beam',     'particle_position_x'].to_ndarray()
xe0 = ad['plasma_e', 'particle_position_x'].to_ndarray()
xp0 = ad['plasma_p', 'particle_position_x'].to_ndarray()
zb0 = ad['beam',     'particle_position_z'].to_ndarray()
ze0 = ad['plasma_e', 'particle_position_z'].to_ndarray()
zp0 = ad['plasma_p', 'particle_position_z'].to_ndarray()

num = 0
for i in range(len(xb)):
    for j in range(len(xb0)):
        if abs(xb[i]-xb0[j]) < tolerance:
            break
        else:
            num = num + 1
    if num == len(xb0):
        assert( num < len(xb0) )
        num = 0

filename = sys.argv[1]
test_name = filename[:-9] # Could also be os.path.split(os.getcwd())[1]
checksumAPI.evaluate_checksum(test_name, filename)
