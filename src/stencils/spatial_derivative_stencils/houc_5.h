/*****************************************************************************************
*                                                                                        *
* This file is part of ALPACA                                                            *
*                                                                                        *
******************************************************************************************
*                                                                                        *
*  \\                                                                                    *
*  l '>                                                                                  *
*  | |                                                                                   *
*  | |                                                                                   *
*  | alpaca~                                                                             *
*  ||    ||                                                                              *
*  ''    ''                                                                              *
*                                                                                        *
* ALPACA is a MPI-parallelized C++ code framework to simulate compressible multiphase    *
* flow physics. It allows for advanced high-resolution sharp-interface modeling          *
* empowered with efficient multiresolution compression. The modular code structure       *
* offers a broad flexibility to select among many most-recent numerical methods covering *
* WENO/T-ENO, Riemann solvers (complete/incomplete), strong-stability preserving Runge-  *
* Kutta time integration schemes, level set methods and many more.                       *
*                                                                                        *
* This code is developed by the 'Nanoshock group' at the Chair of Aerodynamics and       *
* Fluid Mechanics, Technical University of Munich.                                       *
*                                                                                        *
******************************************************************************************
*                                                                                        *
* LICENSE                                                                                *
*                                                                                        *
* ALPACA - Adaptive Level-set PArallel Code Alpaca                                       *
* Copyright (C) 2020 Nikolaus A. Adams and contributors (see AUTHORS list)               *
*                                                                                        *
* This program is free software: you can redistribute it and/or modify it under          *
* the terms of the GNU General Public License as published by the Free Software          *
* Foundation version 3.                                                                  *
*                                                                                        *
* This program is distributed in the hope that it will be useful, but WITHOUT ANY        *
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A        *
* PARTICULAR PURPOSE. See the GNU General Public License for more details.               *
*                                                                                        *
* You should have received a copy of the GNU General Public License along with           *
* this program (gpl-3.0.txt).  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>   *
*                                                                                        *
******************************************************************************************
*                                                                                        *
* THIRD-PARTY tools                                                                      *
*                                                                                        *
* Please note, several third-party tools are used by ALPACA. These tools are not shipped *
* with ALPACA but available as git submodule (directing to their own repositories).      *
* All used third-party tools are released under open-source licences, see their own      *
* license agreement in 3rdParty/ for further details.                                    *
*                                                                                        *
* 1. tiny_xml           : See LICENSE_TINY_XML.txt for more information.                 *
* 2. expression_toolkit : See LICENSE_EXPRESSION_TOOLKIT.txt for more information.       *
* 3. FakeIt             : See LICENSE_FAKEIT.txt for more information                    *
* 4. Catch2             : See LICENSE_CATCH2.txt for more information                    *
* 5. ApprovalTests.cpp  : See LICENSE_APPROVAL_TESTS.txt for more information            *
*                                                                                        *
******************************************************************************************
*                                                                                        *
* CONTACT                                                                                *
*                                                                                        *
* nanoshock@aer.mw.tum.de                                                                *
*                                                                                        *
******************************************************************************************
*                                                                                        *
* Munich, February 10th, 2021                                                            *
*                                                                                        *
*****************************************************************************************/
#ifndef HOUC_5_H
#define HOUC_5_H

#include "stencils/stencil.h"

/**
 * @brief Discretization of the SpatialDerivativeStencil class to evaluate the stencil with a 5th order HOUC stencil of \cite Nourgaliev2007.
 */
class HOUC5 : public Stencil<HOUC5> {

   friend Stencil;

   static constexpr StencilType stencil_type_ = StencilType::Derivative;

   static constexpr unsigned int stencil_size_            = 7;
   static constexpr unsigned int downstream_stencil_size_ = 3;

   static constexpr double one_sixtieth = 1.0 / 60.0;

   static constexpr double coefficient_0_ = -2.0;
   static constexpr double coefficient_1_ = +15.0;
   static constexpr double coefficient_2_ = -60.0;
   static constexpr double coefficient_3_ = +20.0;
   static constexpr double coefficient_4_ = +30.0;
   static constexpr double coefficient_5_ = -3.0;

   /**
    * @brief Implements the 5th order HOUC stencil. Also See base class.
    * @note Hotpath function.
    */
   constexpr double ApplyImplementation( std::array<double, stencil_size_> const& array, std::array<int const, 2> const evaluation_properties, double const ) const {
      // Assign values to v_i to make it easier to read
      double const v0 = array[downstream_stencil_size_ - 3 * evaluation_properties[1]];
      double const v1 = array[downstream_stencil_size_ - 2 * evaluation_properties[1]];
      double const v2 = array[downstream_stencil_size_ - 1 * evaluation_properties[1]];
      double const v3 = array[downstream_stencil_size_];
      double const v4 = array[downstream_stencil_size_ + 1 * evaluation_properties[1]];
      double const v5 = array[downstream_stencil_size_ + 2 * evaluation_properties[1]];

      double const result = coefficient_0_ * v0 + coefficient_1_ * v1 + coefficient_2_ * v2 + coefficient_3_ * v3 + coefficient_4_ * v4 + coefficient_5_ * v5;

      return result * one_sixtieth * evaluation_properties[1];
   }

public:
   explicit constexpr HOUC5() = default;
   ~HOUC5()                   = default;
   HOUC5( HOUC5 const& )      = delete;
   HOUC5& operator=( HOUC5 const& ) = delete;
   HOUC5( HOUC5&& )                 = delete;
   HOUC5& operator=( HOUC5&& ) = delete;
};

#endif//HOUC_5_H
