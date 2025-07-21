Quick Note
1. 3 branches
- `master` - original
- `gcc-13.2.0` - the version im studying on
- `note` - I put note in this branch, including this me-README.md
2. The docker will have the repo ready
- No need remove repo and recommit the docker image
- This is to save build time.
3. The command to build & install gcc, is from the website https://gcc.gnu.org/install/
4. Following the instruction, it is recommneded to make a new folder outside of this repo and build it.
- Hence, in the command below, you will see "mkdir ../objdir" something.
- ALso, it is recommended to use `--prefix`, to separate your built gcc with linux gcc.
- Else, it will have version incompatiblity issue or something.

Pre-requisite
1. `git clone git@github.com:lolzz77/gcc.git`
2. `git clone git@github.com:lolzz77/test.git`
3. In VS Code select `Indent using tabs` -> `8`
- To make the code more readable

All Code:
```bash
apt-get update -y; \
apt-get upgrade -y; \
cd /workspace/gcc; \
./contrib/download_prerequisites; \
apt-get install flex cmake gdb -y; \
cd ../; \
mkdir objdir; \
cd objdir; \
$PWD/../gcc/configure \
  --prefix=$HOME/gcc-light \
  --enable-languages=c \
  --disable-multilib \
  --disable-bootstrap \
  --disable-libquadmath \
  --disable-libsanitizer \
  --disable-libmpx \
  --disable-libvtv \
  --disable-libcilkrts \
  --disable-libssp \
  --disable-libstdcxx-pch \
  --disable-nls
```
Then run `make all -j3` (Takes around 50 minutes)

The output built will be in the same folder, which is `~/objdir`

Then `make install -j3`

Your oinstalled gcc will be what you specified in `--prefix`
Which is `~/gcc-light/bin`

After that, please `cd /workspace; git clone https://github.com/lolzz77/test.git`

This file is for your debugging uses.

To use your built gcc to compile the file, here's the command
`~/gcc-light/bin/gcc /workspace/test/test.c`

# Note
1. By default, gcc built, is using debug flag -O2, i believe it's fine for you. Learn to be fast pls.
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
