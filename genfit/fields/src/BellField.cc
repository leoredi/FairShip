/* Copyright 2008-2010, Technische Universitaet Muenchen,
   Authors: Christian Hoeppner & Sebastian Neubert & Johannes Rauch

   This file is part of GENFIT.

   GENFIT is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GENFIT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with GENFIT.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "BellField.h"
#include "math.h"
Double_t kilogauss = 1.;
Double_t tesla     = 10*kilogauss;

// implementation of Bellshape field for Ship
namespace genfit {

  BellField::BellField()
    : AbsBField(),
      fMiddle(0),fPeak(0)
  { ; }
  BellField::BellField(double Peak, double Middle,int orientation)
    : AbsBField(),
      fMiddle(Middle),fPeak(Peak),fOrient(orientation)
  { ; }

TVector3 BellField::get(const TVector3& pos) const {
  Double_t zlocal=(pos.z()-fMiddle)/100.;
  TVector3 field_(0.,fPeak/(1.+pow(fabs(zlocal)/2.1,6.)),0.);
  return field_;
}

void BellField::get(const double& x, const double& y, const double& z, double& Bx, double& By, double& Bz) const {
  Double_t zlocal=fabs((z-fMiddle)/100.);
  Bz = 0.;
  By = 0.;
  Bx = 0.;
  if (fOrient==1){
  By = fPeak/(1.+pow(fabs(zlocal)/2.1,6.));
  }
  if (fOrient==2){
   //new field based on simulation of Davide Tommasini (22/1/2015)
    Bx = 0;
    if (zlocal<3.8) {
      Bx=0.14361*exp( -0.5 * pow((zlocal-0.45479E-01)/2.5046,2.));
    }else if (zlocal<11.9) {
      Bx=0.19532-0.61512E-01*zlocal+0.68447E-02*pow(zlocal,2.)-0.25672E-03*pow(zlocal,3.);
    }
    Bx=fPeak/0.14361*Bx*tesla;
  }
}

} /* End of namespace genfit */
