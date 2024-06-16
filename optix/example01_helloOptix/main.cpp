#include "gdt/gdt.h"
#include "optix8.h"

namespace osc
{

    void initOptix()
    {
        cudaFree(0);
        int numDevices;
        if (numDevices == 0)
        {
            throw std::runtime_error("#osc: no CUDA available!");
        }

        OPTIX_CHECK(optixInit());
    }

    extern "C" int main(int ac, char **av)
    {
        try
        {
            std::cout << "#osc: initializing optix..." << std::endl;

            initOptix();

            std::cout << GDT_TERMINAL_GREEN
                      << "#osc: successfully initialized optix... yay!"
                      << GDT_TERMINAL_DEFAULT << std::endl;

            // for this simple hello-world example, don't do anything else
            // ...
            std::cout << "#osc: done. clean exit." << std::endl;
        }
        catch (std::runtime_error &e)
        {
            std::cout << GDT_TERMINAL_RED << "FATAL ERROR: " << e.what()
                      << GDT_TERMINAL_DEFAULT << std::endl;
            exit(1);
        }
        return 0;
    }
}