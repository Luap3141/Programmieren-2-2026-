################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drawing.cpp \
../PolygonsMain.cpp 

CPP_DEPS += \
./Drawing.d \
./PolygonsMain.d 

OBJS += \
./Drawing.o \
./PolygonsMain.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/luap314/Desktop/Unistuff/Programmieren 2 2026" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Drawing.d ./Drawing.o ./PolygonsMain.d ./PolygonsMain.o

.PHONY: clean--2e-

