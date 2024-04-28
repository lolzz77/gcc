All Code:
```bash
apt-get update -y; apt-get upgrade -y; cd /workspace/gcc; ./contrib/download_prerequisites; apt-get install flex cmake gdb -y; cd ../; mkdir objdir; cd objdir; $PWD/../gcc/configure --enable-languages=c,c++ --disable-multilib;
```
Then until here, dont make first, go into the `/objdir/Makefile`

Search for `-O2`, change to `-O0` 
(This is to disable debug optimization for your debugging experience)
https://stackoverflow.com/questions/5497855/what-does-value-optimized-out-mean-in-gdb

Then run `make all -j3` (Takes around 1 hour)

Then `make install -j3`

Note : If you just run `make all-gcc -j3; make install-gcc -j3`

Your installation will success, but when you trigger `gcc`, will fail during linking stage.

I think is because the existing linkers are not compatible with the version you built.

You can just run `make all-gcc -j3; make install-gcc -j3`,

but only after you ran `make all -j3; make install -j3`.

This is to ensure that all other binaries like `ld`, are compatible with your `gcc`.

After that, please `cd /workspace; git clone https://github.com/lolzz77/test.git`

This file is for your debugging uses.

# Note
1. gcc installed in `/usr/local/bin/gcc`
- Try `which gcc` or `whereis gcc`
- You have to restart your terminal for it to take effect
- After restarting terminal, verify the version `gcc -v`
2. Debug ld
- apparently, `ld` is provided under `gnu binutil`, and the repo name is `gdb bin util`
- https://www.gnu.org/software/software.html
- if you scroll to the bottom, you see lots of software names
- click `binutils`
- https://www.gnu.org/software/binutils/
- here says it includes `ld`
- then below says `git clone git://sourceware.org/git/binutils-gdb.git` (you can see is GDB binutils)
- https://sourceware.org/git/binutils-gdb
- see `binutils-gdb.git`, see the description, it says `gdb and binutils

# Appendix
1. Study slide
https://docs.google.com/presentation/d/1XjvRyp_z_nG9I0qUrYwH2GvE3gMFxP61u-djCF0A4Rg/edit#slide=id.p
