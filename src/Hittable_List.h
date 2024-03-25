#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "Hittable.h"
#include "Interval.h"

class Hittable_List : Hittable 
{
    public:
    
        std::vector< std::shared_ptr<Hittable> > objcts;

        Hittable_List() {};
        Hittable_List(const std::shared_ptr<Hittable> objct) { add(objct); }

        void clear() { objcts.clear(); }

        void add(const std::shared_ptr<Hittable> objct) { objcts.push_back(objct); }

        bool hit(const Ray&r, const Interval& ray_t, Hit_Record& rec) const override 
        {
            Hit_Record temp_recrd;
            bool hit_anything = false;
            double closest = ray_t.max;

            for (const auto& objct : objcts)
            {
                if (objct->hit(r, Interval(ray_t.min, closest), temp_recrd))
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