Yes, it is **normal** that `libtest.a` does not appear in the output of `readelf -a hello_S | grep "Shared library"`. Here's why:

---

### Explanation

1. **Static Libraries (`.a`)**:
   - Static libraries like `libtest.a` are archives of object files.
   - During linking, the linker extracts only the necessary symbols from `libtest.a` and embeds them directly into the final executable (`hello_S`).
   - This means `libtest.a` is not a runtime dependency, unlike shared libraries (`.so`), which are dynamically loaded at runtime.

   As a result, `libtest.a` will not appear in the `Shared library` section of `readelf` because it is not a shared library.

2. **Shared Libraries (`.so`)**:
   - Shared libraries like `libc.so.6` are linked dynamically, and the executable contains references to them.
   - These libraries appear in the `Shared library` section of `readelf`.

---

### How to Confirm `libtest.a` is Linked

Since `libtest.a` won't show up directly in the `readelf` output, you can verify its contents are included in `hello_S` using these methods:

1. **Check for Symbols from `libtest.a` in `hello_S`**:
   Use `nm` to list the symbols in `hello_S` and search for symbols defined in `libtest.a`:

   ```bash
   arm-cortex_a8-linux-gnueabihf-nm hello_S | grep foo2_1
   ```

   If `foo2_1()` or other symbols from `libtest.a` appear, it means the library was successfully linked.

2. **Debug Linker Behavior**:
   Add the `-Wl,--verbose` option to your `gcc` command to debug the linker:

   ```bash
   arm-cortex_a8-linux-gnueabihf-gcc hello.c -L../libs -ltest -o hello_S -Wl,--verbose
   ```

   Look for output like:

   ```
   opened ../libs/libtest.a
   ```

   This confirms that the linker found and used `libtest.a`.

3. **Force Linkage (if needed)**:
   If the linker skips `libtest.a` because `hello.c` does not use any symbols from it, explicitly include the library:

   ```bash
   arm-cortex_a8-linux-gnueabihf-gcc hello.c ../libs/libtest.a -o hello_S
   ```

   This ensures the library is linked, even if its symbols are not referenced.

---

### Final Notes

- It is normal that `libtest.a` does not appear in the `readelf` output because static libraries do not function like shared libraries.
- Use `nm` or verbose linking to confirm that the symbols from `libtest.a` are present in `hello_S`.
- Ensure your program (`hello.c`) uses at least one symbol from `libtest.a` to avoid the linker excluding it as unused.

If you need further assistance or encounter unexpected behavior, share your `nm` output or linker logs!
