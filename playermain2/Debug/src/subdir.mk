################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/basicenemy.cpp \
../src/player.cpp \
../src/playermain2.cpp 

CPP_DEPS += \
./src/basicenemy.d \
./src/player.d \
./src/playermain2.d 

OBJS += \
./src/basicenemy.o \
./src/player.o \
./src/playermain2.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/basicenemy.d ./src/basicenemy.o ./src/player.d ./src/player.o ./src/playermain2.d ./src/playermain2.o

.PHONY: clean-src

