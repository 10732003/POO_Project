/**
 * @file constantes.h
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief all global constants
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "shape.h"

namespace cst
{
    // --------------- given ---------------
    enum Etat_neutraliseur {EN_PANNE, EN_MARCHE} ;
    constexpr short unsigned maxF(25) ;
    constexpr double dmax(128.);
    constexpr double delta_t(0.125); // seconde
    constexpr double r_spatial(16.);
    constexpr double r_reparateur(2.);
    constexpr double r_neutraliseur(4.);
    constexpr double vtran_max(4.); // par seconde
    constexpr double vrot_max(0.125); // rd/s env. 7°/s
    constexpr double epsil_alignement(0.01); // rd env. 0.6°
    constexpr double desintegration_rate(0.0002); 
    constexpr double risk_factor(3.); 
    constexpr double d_particule_min(8*shape ::epsil_zero); 
    constexpr unsigned max_update(600);
    constexpr unsigned modulo_update(100);

    // --------------- our constants ---------------
    constexpr double PI(3.14159265358979323846);
} // namespace cst


#endif /* CONSTANTES_H */
