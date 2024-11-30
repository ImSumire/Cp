This version isn't safe:
- There's a lot of conditional jumps or moves depends on uninitialised values. If you want to help by fixing all there errors, you can read log/.valgrind and do a pull request :D
- Secondly, all the safety isn't done on all types/collections, like 40% on Vector and that's it. Same, do a pull request if you want to fix it :D
