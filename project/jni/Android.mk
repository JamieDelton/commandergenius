# If SDL_Mixer should link to libMAD
SDL_MIXER_USE_LIBMAD :=
ifneq ($(strip $(filter mad, $(COMPILED_LIBRARIES))),)
SDL_MIXER_USE_LIBMAD := 1
endif

NDK_VERSION := $(strip $(patsubst android-ndk-%,%,$(filter android-ndk-%, $(subst /, ,$(dir $(TARGET_CC))))))
$(info NDK version $(NDK_VERSION))
ifneq ($(filter r1 r2 r3 r4, $(NDK_VERSION)),)
$(error Your NDK $(NDK_VERSION) is too old, please download NDK r4b from http://developer.android.com )
endif
ifneq ($(filter r5, $(NDK_VERSION)),)
$(error Your NDK $(NDK_VERSION) generates invalid code, please download NDK r4b from http://developer.android.com or wait for NDK r5b release. Details: http://groups.google.com/group/android-ndk/browse_thread/thread/6b35728eec7ef52f/b57f52776842041d )
endif


ifneq ($(findstring -crystax,$(NDK_VERSION)),)
$(info Building with CrystaX toolchain - RTTI and exceptions enabled, STLPort disabled)
CRYSTAX_TOOLCHAIN = 1
endif
ifneq ($(findstring r5,$(NDK_VERSION)),)
$(info Building with NDK r5)
NDK_R5_TOOLCHAIN = 1
endif

include $(call all-subdir-makefiles)
