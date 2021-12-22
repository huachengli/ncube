
char * help = "help";
#include "proc.h"
#include "linear_interpolate.h"
void IdFormatView(size_t n_,size_t *ins_,char * format_,size_t _pline)
{
    for(size_t i=0;i<n_;++i)
    {
        if(i%_pline == 0)
            fprintf(stdout,"\n");
        fprintf(stdout,format_,ins_[i]);

    }
    fprintf(stdout,"\n");
}

void IntFormatView(PetscInt n_,PetscInt *ins_,char * format_)
{
    for(PetscInt i=0;i<n_;++i)
    {
        if(i%16 == 0)
        {
            PetscPrintf(PETSC_COMM_WORLD,"\n Id(%6d-%6d)  ",i,i+15);
        }

        PetscPrintf(PETSC_COMM_WORLD,format_,ins_[i]);
    }
    PetscPrintf(PETSC_COMM_WORLD,"\n");
}


void ISCompareView(size_t n,ISLocalToGlobalMapping a,ISLocalToGlobalMapping b)
{
//    n /= 3;
    PetscInt * LocalId,*GlobalId1,*GlobalId2;
    PetscMalloc(n* sizeof(PetscInt),&LocalId);
    PetscMalloc(n* sizeof(PetscInt),&GlobalId1);
    PetscMalloc(n* sizeof(PetscInt),&GlobalId2);

    for(size_t k=0;k<n;k++)
    {
        LocalId[k] = (PetscInt) k;
        GlobalId1[k] = GlobalId2[k] = -1;
    }
    ISLocalToGlobalMappingApply(a,(PetscInt)n/3,LocalId,GlobalId1);
    ISLocalToGlobalMappingApply(b,(PetscInt)n,LocalId,GlobalId2);

    for(size_t k=0;k<n;k++)
    {
        if(k%8 ==0) fprintf(stdout,"\n");
        fprintf(stdout,"%5d->(%5d,%5d);",LocalId[k],GlobalId1[k],GlobalId2[k]);
    }
    fprintf(stdout,"\n");

    PetscFree(LocalId);
    PetscFree(GlobalId1);
    PetscFree(GlobalId2);
}

int main_sysK(int argc,char **argv)
{
    PetscInitialize(&argc,&argv,(char*)0,"test");
    ProcCtx _t;
    ProcCtx3dInit(&PETSC_COMM_WORLD,&_t,64,64,64);
    ProcCtxSetGloId(&_t,0,SIZE_MAX);
//    IdFormatView(_t.nGloId,_t.GloId,"%8d;",4);
//    ISLocalToGlobalMappingView(_t.map,PETSC_VIEWER_STDOUT_WORLD);
//    ISLocalToGlobalMappingView(_t.SysKMap,PETSC_VIEWER_STDOUT_WORLD);
//    ISCompareView(3*_t.nGloId,_t.map,_t.SysKMap);

    Mat SystemK;

    // 1st
//    MatCreateAIJ(PETSC_COMM_WORLD,(PetscInt)_t.nGloId*3,(PetscInt)_t.nGloId*3,PETSC_DETERMINE,PETSC_DETERMINE,60,NULL,30,NULL,&SystemK);
    // 2nd
    /*MatCreate(PETSC_COMM_WORLD,&SystemK);
    MatSetType(SystemK,MATMPIAIJ);
    MatSetOption(SystemK,MAT_SYMMETRIC,PETSC_TRUE);
    MatSetBlockSize(SystemK,3);
    MatSetSizes(SystemK,(PetscInt)_t.nGloId*3,(PetscInt)_t.nGloId*3,PETSC_DETERMINE,PETSC_DETERMINE);
    MatMPIAIJSetPreallocation(SystemK,81,NULL,10,NULL);*/
    // 3rd
    MatCreate(PETSC_COMM_WORLD,&SystemK);
    MatSetType(SystemK,MATMPISBAIJ);
    MatSetSizes(SystemK,(PetscInt)_t.nGloId*3,(PetscInt)_t.nGloId*3,PETSC_DETERMINE,PETSC_DETERMINE);
    MatMPISBAIJSetPreallocation(SystemK,3,27,NULL,0,NULL);
    MatSetOption(SystemK,MAT_GETROW_UPPERTRIANGULAR,PETSC_TRUE);
    MatSetFromOptions(SystemK);
    MatSetLocalToGlobalMapping(SystemK,_t.SysKMap,_t.SysKMap);
//    MatSetLocalToGlobalMapping(SystemK,_t.SysKMap_nb,_t.SysKMap_nb);
    MatSetUp(SystemK);

    SysKAssmble(SystemK,&_t);

#define CHECK_PATTERN 0
#if CHECK_PATTERN
    PetscInt * nzo,nrows, * nzo_bitmap;
    PetscMalloc(128* sizeof(PetscInt),&nzo_bitmap);
//    MatSeqAIJGetMaxRowNonzeros(SystemK,nzo);
    MatGetPattern(SystemK,&nrows,&nzo);
    for(size_t k=0;k<128;k++) nzo_bitmap[k] = 0;
    for(size_t k=0;k<nrows;k++)
    {
        if(nzo[k] > 128) continue;
        if(nzo[k] < 0) continue;
        nzo_bitmap[nzo[k]]++;
    }

//    IntFormatView(nrows,nzo,"%6d;");
    IntFormatView(128,nzo_bitmap,"%6d;");

    PetscFree(nzo);
    PetscFree(nzo_bitmap);
#endif

#define VIEW_SYSK 0
#if VIEW_SYSK
    PetscViewer _pdw;
    PetscViewerDrawOpen(PETSC_COMM_WORLD,NULL,"mat_system_k",PETSC_DECIDE,PETSC_DECIDE,600,600,&_pdw);
    PetscViewerDrawSetPause(_pdw,5.0);
    PetscViewerSetFromOptions(_pdw);
    MatView(SystemK,_pdw);
    PetscViewerDestroy(&_pdw);
#endif
//    sleep(5);
    MatDestroy(&SystemK);
    PetscFinalize();
    return 0;
}
int main()
{
    double tM[3][3] = {1,2,3,4,4,8,9,1,25};
    double tA[3][3],tB[3][3];
    double detM = Determinant(tM);
    MatrixInverse(tM,tA);
    double detC = MatrixTimeAB(tB,tM,tA);

    return 0;
}
