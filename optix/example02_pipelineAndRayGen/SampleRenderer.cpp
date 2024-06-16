#include "SampleRenderer.h"
#include <optix_function_table_definition.h>

namespace osc
{
    extern "C" char embedded_ptx_code[];

    /*! SBT record for a raygen program */
    struct __align__(OPTIX_SBT_RECORD_ALIGNMENT) RaygenRecord
    {
        __align__(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
        // just a dummy value - later examples will use more interesting
        // data here
        void *data;
    };

    /*! SBT record for a miss program */
    struct __align__(OPTIX_SBT_RECORD_ALIGNMENT) MissRecord
    {
        __align__(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
        // just a dummy value - later examples will use more interesting
        // data here
        void *data;
    };

    /*! SBT record for a hitgroup program */
    struct __align__(OPTIX_SBT_RECORD_ALIGNMENT) HitgroupRecord
    {
        __align__(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
        // just a dummy value - later examples will use more interesting
        // data here
        int objectID;
    };

    /*! constructor - performs all setup, including initializing
        optix, creates module, pipeline, programs, SBT, etc. */
    SampleRenderer::SampleRenderer()
    {
        initOptix();

        std::cout << "#osc: creating optix context ..." << std::endl;
        createContext();

        std::cout << "#osc: setting up module ..." << std::endl;
        createModule();

        std::cout << "#osc: creating raygen programs ..." << std::endl;
        createRaygenPrograms();
        std::cout << "#osc: creating miss programs ..." << std::endl;
        createMissPrograms();
        std::cout << "#osc: creating hitgroup programs ..." << std::endl;
        createHitgroupPrograms();

        std::cout << "#osc: setting up optix pipeline ..." << std::endl;
        createPipeline();

        std::cout << "#osc: building SBT ..." << std::endl;
        buildSBT();

        launchParamsBuffer.alloc(sizeof(launchParams));
        std::cout << "#osc: context, module, pipeline, etc, all set up ..." << std::endl;

        std::cout << GDT_TERMINAL_GREEN;
        std::cout << "#osc: Optix 7 Sample fully set up" << std::endl;
        std::cout << GDT_TERMINAL_DEFAULT;
    }

    void SampleRenderer::initOptix()
    {
        std::cout << "#osc: initializing optix..." << std::endl;

        // -------------------------------------------------------
        // check for available optix7 capable devices
        // -------------------------------------------------------
        cudaFree(0);
        int numDevices;
        cudaGetDeviceCount(&numDevices);
        if (numDevices == 0)
            throw std::runtime_error("#osc: no CUDA capable devices found!");
        std::cout << "#osc: found " << numDevices << " CUDA devices" << std::endl;

        // -------------------------------------------------------
        // initialize optix
        // -------------------------------------------------------
        OPTIX_CHECK(optixInit());
        std::cout << GDT_TERMINAL_GREEN
                  << "#osc: successfully initialized optix... yay!"
                  << GDT_TERMINAL_DEFAULT << std::endl;
    }
}