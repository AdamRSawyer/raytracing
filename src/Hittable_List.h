#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "Hittable.h"

class Hittable_List : Hittable 
{
    public:
    
        std::vector< std::shared_ptr<Hittable> > objcts;

        Hittable_List() {};
        Hittable_List(const std::shared_ptr<Hittable> objct) { add(objct); }

        void clear() { objcts.clear(); }

        void add(const std::shared_ptr<Hittable> objct) { objcts.push_back(objct); }

        bool hit(const Ray&r, double ray_tmin, double ray_tmax, Hit_Record& rec) const override 
        {
            Hit_Record temp_recrd;
            bool hit_anything = false;
            double closest = ray_tmax;

            for (const auto& objct : objcts)
            {
                if (objct->hit(r, ray_tmin, closest, temp_recrd))
                {
                    hit_anything = true;
                    closest = temp_recrd.t;
                    rec = temp_recrd;
                }
            }

            return hit_anything;
        }
    
};

#endif