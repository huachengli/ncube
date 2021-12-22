//
// Created by huacheng on 12/13/21.
//

#ifndef NCUBE_PROC_H
#define NCUBE_PROC_H

#include "mpi.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <petsc.h>
#define MaxDim 3
#define X 0
#define Y 1
#define Z 2


typedef struct _ProcCtx
{
    MPI_Comm * ProcComm;
    size_t Nps[MaxDim];
    size_t * GloId;
    size_t * GhtId;
    size_t nGloId;
    size_t nGhtId;
    ISLocalToGlobalMapping map;
    ISLocalToGlobalMapping SysKMap;
    ISLocalToGlobalMapping SysKMap_nb;

} ProcCtx;

size_t Ids2l(size_t _i,size_t _j,size_t _k,size_t _n0,size_t _n1,size_t _n2);
void SetGloIdStripe(size_t * _gloId, size_t _first, size_t _stripe,
                    size_t _nps0st, size_t _nps1st, size_t _nps2st,
                    size_t _nps0, size_t _nps1, size_t _nps2,
                    size_t _n0,size_t _n1,size_t _n2);
void ProcCtxSetGloId(ProcCtx * _procCtx, size_t _first, size_t _stripe);
void ProcCtx3dInit(MPI_Comm * _procComm, ProcCtx * _procCtx, size_t _nps0, size_t _nps1, size_t _nps2);
void ProcCtxSetISMap(ProcCtx * _procCtx);

void SysKAssmble(Mat _sysK,ProcCtx * _procCtx);
PetscErrorCode MatGetPattern(Mat _kmat,PetscInt * _rows, PetscInt ** _nnz);
#endif //NCUBE_PROC_H
