/**
 * @file particule.h
 * @author E.Dutruy 355726
 * @date 2023-03-10
 * @version 0.1
 * @brief particule module interface
 */

#ifndef PARTICULE_H
#define PARTICULE_H

#include <vector>
#include "shape.h"

class Particule
{
private:
    shape::square shape_;

public:
    Particule(double x, double y, double size);

    /**
     * @brief check if a particule is ok with the project directive
     * 
     * @param particule_list std::vector<Paricule>
     * @return true/false
     */
    bool is_ok(std::vector<Particule> particule_list);
    
};

#endif /* PARTICULE_H */
