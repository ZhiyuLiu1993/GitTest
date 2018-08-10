cmake_minimum_required(VERSION 3.5)
project(SongCompare)

#set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_compile_options(-gdwarf-2 -gstrict-dwarf)
#link_libraries(/home/lzy/essentia/build/src/libessentia.a /usr/lib/x86_64-linux-gnu/libsamplerate.a)
link_directories(/usr/lib/x86_64-linux-gnu/)
link_libraries(/home/lzy/essentia/build/src/libessentia.a libyaml.a libfftw3.a libfftw3f.a libavcodec.a
        libavformat.a libavresample.a libsamplerate.a libavcodec-ffmpeg.a
        libavutil-ffmpeg.a libavutil.a libavformat-ffmpeg.a
        libavresample-ffmpeg.a libswresample-ffmpeg.a -lchromaprint -lz -lpthread
        /usr/lib/x86_64-linux-gnu/libva.so.1 -ldl /usr/lib/x86_64-linux-gnu/libzvbi.so.0
        /usr/lib/x86_64-linux-gnu/libxvidcore.so.4 /usr/lib/x86_64-linux-gnu/libx265.so.79
        /usr/lib/x86_64-linux-gnu/libx264.so.148 libwebp.a /usr/lib/x86_64-linux-gnu/libwavpack.so.1
        /usr/lib/x86_64-linux-gnu/libvpx.so.3 libvorbis.a libvorbisenc.a
        /usr/lib/x86_64-linux-gnu/libtwolame.so.0 libtheoraenc.a libtheora.a
        /usr/lib/x86_64-linux-gnu/libspeex.so.1 /usr/lib/x86_64-linux-gnu/libsnappy.so.1
        /usr/lib/x86_64-linux-gnu/libshine.so.3 /usr/lib/x86_64-linux-gnu/libschroedinger-1.0.so.0
        /usr/lib/x86_64-linux-gnu/libopus.so.0 /usr/lib/x86_64-linux-gnu/libopenjpeg.so.5
        /usr/lib/x86_64-linux-gnu/libmp3lame.so.0 /usr/lib/x86_64-linux-gnu/libgsm.so.1
        /usr/lib/x86_64-linux-gnu/libcrystalhd.so.3 liblzma.a libogg.a
        /usr/lib/x86_64-linux-gnu/libsoxr.so.0 /usr/lib/x86_64-linux-gnu/libbluray.so.1
        /usr/lib/x86_64-linux-gnu/libgme.so.0 /usr/lib/x86_64-linux-gnu/libmodplug.so.1
        /usr/lib/x86_64-linux-gnu/librtmp.so.1 /usr/lib/x86_64-linux-gnu/libgnutls.so.30
        /usr/lib/x86_64-linux-gnu/libssh.so.4 libbz2.a
        /home/lzy/songcompare/taglib-1.11/build/taglib/libtag.a)

#link_directories(/home/lzy/essentia/build/src)
add_executable(SongCompare main.cpp Features.cpp Features.h Num.cpp Num.h Comparing.cpp Comparing.h)
#target_link_libraries(SongCompare -lessentia -lsamplerate)
#target_link_libraries(SongCompare libessentia.a libsamplerate.a)
add_library(songcmp STATIC Features.cpp Features.h Num.cpp Num.h Comparing.cpp Comparing.h)
#target_link_libraries(songcmp /home/lzy/essentia/build/src/libessentia.a)
