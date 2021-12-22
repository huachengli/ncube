//
// Created by huacheng on 12/14/21.
//

#include "proc.h"
#include "shape.h"

PetscErrorCode SysKAssmble_1(Mat _sysK,size_t _i,size_t _j, size_t _k,size_t _n0,size_t _n1,size_t _n2)
{
    PetscInt _nlocal_indices = 8;
    PetscInt _blk = (PetscInt) Ids2l(_i,_j,_k,_n0,_n1,_n2);
    PetscInt _local_indices[8] = {
            (PetscInt) (_blk + 1 + _n0), (PetscInt)(_blk + _n0),
            (PetscInt) (_blk), (PetscInt)(_blk + 1),
            (PetscInt) (_blk + 1 + _n0 + _n0*_n1), (PetscInt)(_blk + _n0 + _n0*_n1),
            (PetscInt) (_blk + _n0*_n1), (PetscInt)(_blk + 1 + _n0*_n1)};

    PetscScalar _local_mat[8*3][8*3] = {0.0};
    for(size_t _a=0;_a<8;++_a)
    {
        for(size_t _b=0;_b<8;++_b)
        {
            for(size_t _m=0;_m<3;++_m)
            {
                for(size_t _n=0;_n<3;++_n)
                {
                    _local_mat[_a * 3 + _m][_b * 3 + _n] = (PetscScalar) *DefaultLinearCuboidNaNb(_a, _b, _m, _n);
                }
                _local_mat[_a * 3 + _m][_b * 3 + _m] += (PetscScalar) 2.0* *DefaultLinearCuboidNaNb(_a, _b, _m, _m);
            }
        }
    }

//    MatSetValuesLocal(_sysK,_nlocal_indices,_local_indices,_nlocal_indices,_local_indices,_local_mat,ADD_VALUES);
    // Block Version
//    MatSetValuesBlockedLocal(_sysK,_nlocal_indices,_local_indices,_nlocal_indices,_local_indices,&_local_mat[0][0],ADD_VALUES);

    // Without Block
    PetscInt _local_indices_nb[8*3],_nlocal_indices_nb=8*3;
    for(size_t _a=0;_a<8;++_a)
    {
        for(size_t _m=0;_m<3;++_m)
        {
            _local_indices_nb[_m + 3*_a] = (PetscInt) (_m +  3*_local_indices[_a]);
        }
    }
    PetscErrorCode ierr = MatSetValuesLocal(_sysK,_nlocal_indices_nb,_local_indices_nb,
                      _nlocal_indices_nb,_local_indices_nb,&_local_mat[0][0],ADD_VALUES);
    CHKERRQ(ierr);

}

void SysKAssmble(Mat _sysK,ProcCtx * _procCtx)
{
    size_t _n0 = _procCtx->Nps[0], _n1 = _procCtx->Nps[1], _n2=_procCtx->Nps[2];

    {
        for (size_t _k = 0; _k < _n2 - 1; _k++)
            for (size_t _j = 0; _j < _n1 - 1; _j++)
                for (size_t _i = 0; _i < _n0 - 1; _i++)
                    SysKAssmble_1(_sysK, _i, _j, _k, _n0, _n1, _n2);
    }

    MatAssemblyBegin(_sysK,MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(_sysK,MAT_FINAL_ASSEMBLY);
}

PetscErrorCode MatGetPattern(Mat _kmat,PetscInt * _rows, PetscInt ** _nnz)
{
    PetscInt m,n,*nzo,tmp_nzo;
    MatGetSize(_kmat,&m,&n);
    PetscMalloc(m* sizeof(PetscInt),&nzo);
    for(size_t k=0;k<m;++k)
    {
        nzo[k] = -SIZE_MAX/64;
        MatGetRow(_kmat,(PetscInt)k,&tmp_nzo,NULL,NULL);
        nzo[k] = tmp_nzo;
        MatRestoreRow(_kmat,(PetscInt)k,&tmp_nzo,NULL,NULL);
    }
    *_nnz = nzo;
    *_rows = m;
    return 0;
}

