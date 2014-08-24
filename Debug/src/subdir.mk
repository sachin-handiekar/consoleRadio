################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ShoutcastStreamer.c \
../src/curl.c \
../src/files.c \
../src/header.c \
../src/icy-string.c \
../src/log.c \
../src/metadata.c \
../src/mp3data.c \
../src/pls.c \
../src/shoutcast.c \
../src/stream.c 

OBJS += \
./src/ShoutcastStreamer.o \
./src/curl.o \
./src/files.o \
./src/header.o \
./src/icy-string.o \
./src/log.o \
./src/metadata.o \
./src/mp3data.o \
./src/pls.o \
./src/shoutcast.o \
./src/stream.o 

C_DEPS += \
./src/ShoutcastStreamer.d \
./src/curl.d \
./src/files.d \
./src/header.d \
./src/icy-string.d \
./src/log.d \
./src/metadata.d \
./src/mp3data.d \
./src/pls.d \
./src/shoutcast.d \
./src/stream.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Users/SachinHandiekar/Documents/workspace/ShoutcastStreamer/src/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


