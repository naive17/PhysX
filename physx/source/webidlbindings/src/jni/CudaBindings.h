#ifndef CUDA_BINDINGS_H
#define CUDA_BINDINGS_H

#if !(defined(__EMSCRIPTEN__) || defined(__APPLE__))

#include "cudamanager/PxCudaContext.h"
#include "extensions/PxParticleExt.h"
#include "PxPhysicsAPI.h"
#include "PxParticleGpu.h"
#include "PxAttachment.h"

typedef physx::PxCudaInteropMode::Enum PxCudaInteropModeEnum;

struct PxCudaTopLevelFunctions {

    static int GetSuggestedCudaDeviceOrdinal(physx::PxFoundation& foundation) {
        return PxGetSuggestedCudaDeviceOrdinal(foundation.getErrorCallback());
    }

    static physx::PxCudaContextManager* CreateCudaContextManager(physx::PxFoundation& foundation, const physx::PxCudaContextManagerDesc& desc) {
        return PxCreateCudaContextManager(foundation, desc);
    }

    static physx::PxParticleClothPreProcessor* CreateParticleClothPreProcessor(physx::PxCudaContextManager* cudaContextManager) {
        return PxCreateParticleClothPreProcessor(cudaContextManager);
    }

    static physx::ExtGpu::PxParticleClothBufferHelper* CreateParticleClothBufferHelper(const physx::PxU32 maxCloths, const physx::PxU32 maxTriangles, const physx::PxU32 maxSprings, const physx::PxU32 maxParticles, physx::PxCudaContextManager *cudaContextManager) {
        return physx::ExtGpu::PxCreateParticleClothBufferHelper(maxCloths, maxTriangles, maxSprings, maxParticles, cudaContextManager);
    }

    static physx::PxParticleClothBuffer* CreateAndPopulateParticleClothBuffer(const physx::ExtGpu::PxParticleBufferDesc &desc, const physx::PxParticleClothDesc &clothDesc, physx::PxPartitionedParticleCloth &output, physx::PxCudaContextManager *cudaContextManager) {
        return physx::ExtGpu::PxCreateAndPopulateParticleClothBuffer(desc, clothDesc, output, cudaContextManager);
    }

    static physx::PxU32* allocPinnedHostBufferPxU32(physx::PxCudaContextManager *cudaContextManager, physx::PxU32 numElements) {
        return cudaContextManager->allocPinnedHostBuffer<physx::PxU32>(numElements);
    }

    static physx::PxVec4* allocPinnedHostBufferPxVec4(physx::PxCudaContextManager *cudaContextManager, physx::PxU32 numElements) {
        return cudaContextManager->allocPinnedHostBuffer<physx::PxVec4>(numElements);
    }

    static void freePinnedHostBufferPxU32(physx::PxCudaContextManager* cudaContextManager, physx::PxU32* buffer) {
        cudaContextManager->freePinnedHostBuffer(buffer);
    }

    static void freePinnedHostBufferPxVec4(physx::PxCudaContextManager* cudaContextManager, physx::PxVec4* buffer) {
        cudaContextManager->freePinnedHostBuffer(buffer);
    }
    
    static physx::PxU64 pxU32deviceptr(void* pxU32data) { return CUdeviceptr(pxU32data); }

    static physx::PxU64 pxVec4deviceptr(physx::PxVec4* pxVec4data) { return CUdeviceptr(pxVec4data); }
};

typedef physx::PxParticleBufferFlag::Enum PxParticleBufferFlagEnum;
typedef physx::PxParticleFlag::Enum PxParticleFlagEnum;
typedef physx::PxParticlePhaseFlag::Enum PxParticlePhaseFlagEnum;
typedef physx::PxParticleSolverType::Enum PxParticleSolverTypeEnum;

typedef physx::PxGpuMirroredPointer<physx::PxGpuParticleSystem> PxGpuMirroredGpuParticleSystemPointer;

typedef std::vector<physx::PxParticleRigidFilterPair> Vector_PxParticleRigidFilterPair;
typedef std::vector<physx::PxParticleSpring> Vector_PxParticleSpring;

#endif

#endif