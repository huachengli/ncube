//
// Created by huacheng on 12/13/21.
//
#include "proc.h"

void ProcCtx3dInit(MPI_Comm * _procComm, ProcCtx * _procCtx, size_t _nps0, size_t _nps1, size_t _nps2)
{
    _procCtx->ProcComm = _procComm;
    _procCtx->Nps[X] = _nps0;
    _procCtx->Nps[Y] = _nps1;
    _procCtx->Nps[Z] = _nps2;
    _procCtx->nGloId = _nps0*_nps1*_nps2;
}


void ProcCtxSetGloId(ProcCtx * _procCtx, size_t _first, size_t _stripe)
{
    _procCtx->GloId = (size_t *) malloc(sizeof(size_t)*_procCtx->nGloId);

//    assert(_procCtx->nGloId > _stripe);

    SetGloIdStripe(_procCtx->GloId,_first,_stripe,0,0,0,
                   _procCtx->Nps[X],_procCtx->Nps[Y],_procCtx->Nps[Z],
                   _procCtx->Nps[X],_procCtx->Nps[Y],_procCtx->Nps[Z]);

    ProcCtxSetISMap(_procCtx);
}

void SetGloIdStripe(size_t * _gloId, size_t _first, size_t _stripe,
                    size_t _nps0st, size_t _nps1st, size_t _nps2st,
                    size_t _nps0, size_t _nps1, size_t _nps2,
                    size_t _n0,size_t _n1,size_t _n2)
{
    size_t _localId = 0;
    if(_stripe >= _nps0*_nps1*_nps2)
    {

        for(size_t _k=_nps2st;_k<_nps2st+_nps2;_k++)
        {
            for(size_t _j=_nps1st;_j<_nps1st+_nps1;_j++)
            {
                for(size_t _i=_nps0st;_i<_nps0st+_nps0;_i++)
                {
                    _gloId[_localId++] = _first + Ids2l(_i,_j,_k,_n0,_n1,_n2);
                }
            }
        }

    }
    else if(_nps0 > _nps1 && _nps0 > _nps2)
    {
        SetGloIdStripe(_gloId,_first,_stripe,
                       _nps0st,_nps1st,_nps2st,
                       _nps0/2,_nps1,_nps2,
                       _n0,_n1,_n2);
        SetGloIdStripe(_gloId + _nps0*_nps1*_nps2/2,_first,_stripe,
                       _nps0st+_nps0/2,_nps1st,_nps2st,
                       _nps0/2,_nps1,_nps2,
                       _n0,_n1,_n2);
    }
    else if(_nps1 > _nps2)
    {
        SetGloIdStripe(_gloId,_first,_stripe,
                       _nps0st,_nps1st,_nps2st,
                       _nps0,_nps1/2,_nps2,
                       _n0,_n1,_n2);
        SetGloIdStripe(_gloId + _nps0*_nps1*_nps2/2,_first,_stripe,
                       _nps0st,_nps1st+_nps1/2,_nps2st,
                       _nps0,_nps1/2,_nps2,
                       _n0,_n1,_n2);
    } else
    {
        SetGloIdStripe(_gloId,_first,_stripe,
                       _nps0st,_nps1st,_nps2st,
                       _nps0,_nps1,_nps2/2,
                       _n0,_n1,_n2);
        SetGloIdStripe(_gloId + _nps0*_nps1*_nps2/2,_first,_stripe,
                       _nps0st,_nps1st,_nps2st+_nps2/2,
                       _nps0,_nps1,_nps2/2,
                       _n0,_n1,_n2);
    }
}

size_t Ids2l(size_t _i,size_t _j,size_t _k,size_t _n0,size_t _n1,size_t _n2)
{
    return _i + _n0*(_j + _n1*_k);
}

void ProcCtxSetISMap(ProcCtx * _procCtx)
{

    PetscInt _ngloId_tmp = (PetscInt) _procCtx->nGloId;
    PetscInt *_gloId_tmp,*_gloId_tmp_nb;

    PetscMalloc(_ngloId_tmp* sizeof(PetscInt),&_gloId_tmp);
    PetscMalloc(3*_ngloId_tmp* sizeof(PetscInt),&_gloId_tmp_nb);
    for(size_t k=0;k<_ngloId_tmp;++k)
    {
        _gloId_tmp[k] = (PetscInt) _procCtx->GloId[k];
        for(size_t j=0;j<3;++j)
            _gloId_tmp_nb[3*k+j] = (PetscInt) (_procCtx->GloId[k] + j*_ngloId_tmp);

    }

    ISLocalToGlobalMappingCreate(*_procCtx->ProcComm,1,_ngloId_tmp,_gloId_tmp,PETSC_COPY_VALUES,&_procCtx->map);
    ISLocalToGlobalMappingCreate(*_procCtx->ProcComm,3,_ngloId_tmp,_gloId_tmp,PETSC_COPY_VALUES,&_procCtx->SysKMap);
    ISLocalToGlobalMappingCreate(*_procCtx->ProcComm,1,_ngloId_tmp*3,_gloId_tmp_nb,PETSC_COPY_VALUES,&_procCtx->SysKMap_nb);

    ISLocalToGlobalMappingSetType(_procCtx->map,ISLOCALTOGLOBALMAPPINGBASIC);
    ISLocalToGlobalMappingSetType(_procCtx->SysKMap,ISLOCALTOGLOBALMAPPINGBASIC);
    ISLocalToGlobalMappingSetType(_procCtx->SysKMap_nb,ISLOCALTOGLOBALMAPPINGBASIC);

    PetscFree(_gloId_tmp);
    PetscFree(_gloId_tmp_nb);
}

