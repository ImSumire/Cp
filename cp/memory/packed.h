#pragma once


#ifdef FORCE_UNPACKED
    // Force pstructs to not be packed regardless to the architecture
    #define pstruct struct

#elif defined(FORCE_PACKED)
    // Force pstructs to be packed regardless to the architecture
    #define pstruct struct __attribute__((__packed__))


#elif defined(__GNUC__)
    #if defined(__x86_64__) || defined(__i386__)
        // x86 and x86_64 are generally safe with packed structs
        #define pstruct struct __attribute__((__packed__))
    #else
        // ARM, AArch64 and unknown architectures may have alignment issues, so we avoid packing here
        #define pstruct struct
    #endif
#else

    // Fallback if compiler is unknown
    #define pstruct struct
#endif
