### deps
  - CMake
  - build-essential
  - ncurses

```bash
sudo apt install cmake build-essential libncurses-dev
```

### building
make sure dependencies are installed or else it wont work :(

from root dir
```
chmod +x build.sh
./build.sh
```

finished bin is in bin/

### build.sh options
 - ./build.sh         - builds Release
 - ./build.sh debug   - builds Debug (with symbols for gdb or whatever)
 - ./build.sh clean   - rm -rf's the build dir
