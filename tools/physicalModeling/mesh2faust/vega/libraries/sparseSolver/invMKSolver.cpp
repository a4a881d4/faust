/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 3.1                               *
 *                                                                       *
 * Copyright (C) 2007 CMU, 2009 MIT, 2016 USC                            *
 *                                                                       *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
 * http://www.jernejbarbic.com/code                                      *
 *                                                                       *
 * Research: Jernej Barbic, Fun Shing Sin, Daniel Schroeder,             *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC                 *
 *                                                                       *
 * This utility is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This utility is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invMKSolver.h"

InvMKSolver::InvMKSolver(LinearSolver * invMSolver, SparseMatrix * K)
{
  this->invMSolver = invMSolver;
  this->K = K;

  buffer = (double*) malloc (sizeof(double) * K->Getn());
}

InvMKSolver::~InvMKSolver()
{
  free(buffer);
}

void InvMKSolver::ComputeInvMK(double * x, double * output)
{
  K->MultiplyVector(x, buffer);
  memcpy(x, buffer, sizeof(double) * K->Getn());
  invMSolver->SolveLinearSystem(output, buffer);
}
