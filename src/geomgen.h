#ifndef GEOM_GEN_H
#define GEOM_GEN_H

class HitObject;

HitObject* book1_cover(bool with_bvh=false, bool with_checkers_ground=false);
HitObject* two_spheres_turbulence();

#endif // GEOM_GEN_H
