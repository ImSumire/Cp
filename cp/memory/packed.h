#pragma once


#ifdef FORCE_UNPACKED
    // Force packed structs to not be packed regardless to the architecture
    #define packed

#elif defined(FORCE_PACKED)
    // Force packed structs to be packed regardless to the architecture
    #define packed __attribute__((__packed__))

#elif defined(__GNUC__)
    #if defined(__x86_64__) || defined(__i386__)
        // x86 and x86_64 are generally safe with packed structs
        #define packed __attribute__((__packed__))
    
    #else
        // ARM, AArch64 and unknown architectures may have alignment issues, so we avoid packing here
        #define packed
    #endif
#else
    // Fallback if compiler is unknown
    #define packed
#endif
